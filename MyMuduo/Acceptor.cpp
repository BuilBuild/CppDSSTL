/*
 * @Author: LeiJiulong
 * @Date: 2024-12-27 12:38:20
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-27 13:00:15
 * @Description: 
 */
#include "Acceptor.h"
#include "Logger.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>

static int creatNonblocking()
{
    int sockfd = ::socket(AF_INET, SOCK_NONBLOCK | SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
    if( sockfd <0 )
    {
        LOG_FATAL("socket create failed, errno %d", errno);
    }
    return sockfd;
}

Acceptor::Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport)
    :loop_(loop),acceptSocket_(creatNonblocking()),acceptChannel_(loop, acceptSocket_.fd()),listening_(false)
{
    acceptSocket_.setReuseAddr(true);
    acceptSocket_.setReusePort(true);
    acceptSocket_.bindAddress(listenAddr);
    // 给accept注册读回调
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor()
{
    acceptChannel_.disableAll();
    acceptChannel_.remove();
    
}

void Acceptor::listen()
{
    listening_ = true;
    acceptSocket_.listen();
    acceptChannel_.enableReading();
}

void Acceptor::handleRead()
{
    InetAddress peerAddr;
    int connfd = acceptSocket_.accept(&peerAddr);
    if(connfd > 0)
    {
        if(newConnectCallback_)
        {
            newConnectCallback_(connfd, peerAddr);
        }
        else
        {
            ::close(connfd);
        }
    }
    else
    {
        LOG_ERROR("accept error, errno %d", errno);
        if(errno == EMFILE)
        {
             LOG_ERROR("accept error, errno %d", errno);
        }
    }
}
