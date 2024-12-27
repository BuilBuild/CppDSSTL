#include "TcpConnection.h"
#include "Logger.h"
#include "Socket.h"
#include "Channel.h"
#include "EventLoop.h"

#include <error.h>
#include <functional>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <netinet/tcp.h>

static EventLoop *CheckLoopNotNull(EventLoop *loop)
{
    if (loop == nullptr)
    {
        LOG_FATAL("mainLoop is null");
    }
    return loop;
}

TcpConnection::TcpConnection(EventLoop *loop, const std::string &name,
                             int sockfd, const InetAddress &localAddr, const InetAddress &peerAddr)
    : loop_(CheckLoopNotNull(loop)), name_(name), state_(kConnecting), reading_(true),
      socket_(new Socket(sockfd)), channel_(new Channel(loop, sockfd)), localAddr_(localAddr),
      peerAddr_(peerAddr), highWaterMark_(64 * 1024 * 1024) // 64m
{
    channel_->setReadCallback(std::bind(&TcpConnection::handleRead, this, std::placeholders::_1));
    channel_->setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    channel_->setCloseCallback(std::bind(&TcpConnection::handleClose, this));
    channel_->setErrorCallback(std::bind(&TcpConnection::handleError, this));

    LOG_INFO("TcpConnection::ctor[%s] at fd=%d", name_.c_str(), sockfd);
    socket_->setKeepAlive(true);
}

TcpConnection::~TcpConnection()
{
    LOG_INFO("TcpConnection[%s] at fd=%d destroy, state=%d", name_.c_str(), socket_->fd(), (int)state_);
}


void TcpConnection::shutdown()
{
    if(state_ == kConnected)
    {
        setState(kDisconnected);
        loop_->runInLoop(std::bind(&TcpConnection::shutdownInLoop, this));
    }
}

void TcpConnection::connectEstablished()
{
    setState(kConnected);
    channel_->tie(shared_from_this());
    channel_->enableReading();
    // 新连接建立执行回调
    connectionCallback_(shared_from_this());
}

void TcpConnection::connectDestroyed()
{
    if(state_ == kConnected)
    {
        setState(kDisconnected);
        channel_->disableAll();
        connectionCallback_(shared_from_this());
    }
    channel_->remove();
}

void TcpConnection::handleRead(TimeStamp receiveTime)
{
    int savedErrno = 0;
    const ssize_t n = inputBuffer_.readFd(channel_->fd(), &savedErrno);
    // 有数据读入
    if (n > 0)
    {
        // 已建立的用户，有可读事件发生了，调用用户传入的onMessage
        messageCallback_(shared_from_this(), &inputBuffer_, receiveTime);
    }
    else if (n == 0)
    {
        handleClose();
    }
    else
    {
        errno = savedErrno;
        LOG_ERROR("handRead error, errno %d", errno);
    }
}

void TcpConnection::handleWrite()
{
    if (channel_->isWriting())
    {
        int saveErrno = 0;
        const ssize_t n = outputBuffer_.writeFd(channel_->fd(), &saveErrno);
        if (n > 0)
        {
            outputBuffer_.retrieve(n);
            if (outputBuffer_.readableBytes() == 0)
            {
                channel_->disableWriting();
                if (writeCompleteCallback_)
                {
                    // 唤醒对应的线程执行回调
                    loop_->queueInLoop(
                        std::bind(writeCompleteCallback_, shared_from_this()));
                }
            }
            if (state_ == kDisconnected)
            {
                shutdownInLoop();
            }
        }
        else
        {
            LOG_ERROR("TCPCOnnection handlewrite");
        }
    }
    else
    {
        LOG_ERROR("channel is not Writing, channel fd is %d", channel_->fd());
    }
}

void TcpConnection::handleClose()
{
    LOG_INFO("fd=%d, state=%d", channel_->fd(), (int)state_);
    setState(kDisconnected);
    channel_->disableAll();

    TcpConnectionPtr connPtr(shared_from_this());
    // 执行关闭连接的回调
    connectionCallback_(connPtr);
    // 关闭连接的回调
    closeCallback_(connPtr);
}

void TcpConnection::handleError()
{
    int optval;
    socklen_t optlen = sizeof optval;
    int err = 0;
    if (::getsockopt(channel_->fd(), SOL_SOCKET, SO_ERROR, &optval, &optlen) < 0)
    {
        err = errno;
    }
    else
    {
        err = optval;
    }
    LOG_ERROR("TcpConnection::handleError name:%s, SO_ERROR:%d", name_.c_str(), err);
}

void TcpConnection::sendInLoop(const void *message, size_t len)
{
    ssize_t nwrote = 0;
    size_t remaining = len;
    bool faultError = false;

    if (state_ == kDisconnected)
    {
        LOG_ERROR("disconnected, give up writing!");
        return;
    }
    // channel 第一次开始写数据，而且缓冲区没有待发送数据
    if (!channel_->isWriting() && outputBuffer_.readableBytes() == 0)
    {
        nwrote = ::write(channel_->fd(), message, len);
        if (nwrote >= 0)
        {
            remaining = len - nwrote;
            if(remaining == 0&& writeCompleteCallback_)
            {
                // 既然在这里数据全全部发送完成，就不用再给channel设置epoll out 事件了
                loop_ -> queueInLoop(std::bind(writeCompleteCallback_, shared_from_this()));
            }
        }
        else
        {
            nwrote = 0;
            if(errno != EWOULDBLOCK)
            {
                LOG_ERROR("TcpConnection::sendInLoop");
                if(errno == EPIPE || errno == ECONNRESET) // 收到连接重置的请求
                {
                    faultError = true;
                }
            }
        }
    }
    // 说明当前的数据没有全部发送出去，剩余的数据需要保存到缓冲区中，然后给channel
    // 注册epoll out事件， pooler发现tcp发送缓冲区有空间，会通知相应的sock channel调用handleWrite回调方法
    // 也就是调用TcpConnection::handleWrite方法，把发送缓冲区的数据全部发送完成
    if(faultError && remaining > 0)
    {
        // 目前缓冲区待发送的数据长度
        size_t oldLen = outputBuffer_.readableBytes();
        if(oldLen + remaining >= highWaterMark_ && oldLen < highWaterMark_ && highWaterMarkCallback_)
        {
            loop_->queueInLoop(std::bind(highWaterMarkCallback_, shared_from_this(), oldLen + remaining));
        }
    }
    outputBuffer_.append((char*)message + nwrote, remaining);
    if(!channel_->isWriting())
    {
        // 注册channel 写事件， 否则poller不会给channel通知epoll out
        channel_->enableWriting();
    }
}

void TcpConnection::shutdownInLoop()
{
    if(!channel_->isWriting())
    {
        socket_->shutdownWrite();
    }
}

void TcpConnection::setState(StatE state)
{
    state_ = state;
}

void TcpConnection::send(const std::string &buf)
{
    if (state_ == kConnected)
    {
        if (loop_->isInLoopThread())
        {
            sendInLoop(buf.c_str(), buf.size());
        }
        else
        {
            loop_->runInLoop(std::bind(&TcpConnection::sendInLoop, this, buf.c_str(), buf.size()));
        }
    }
}
