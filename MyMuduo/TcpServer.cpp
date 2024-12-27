/*
 * @Author: LeiJiulong
 * @Date: 2024-12-27 13:53:59
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-27 14:32:26
 * @Description: 
 */
#include "TcpServer.h"
#include "Logger.h"

#include<functional>


EventLoop* checkLoopNotNull(EventLoop *loop)
{
    if(loop==nullptr)
    {
        LOG_FATAL("loop is nullptr");
    }
    return loop;
}


TcpServer::TcpServer(EventLoop *loop, const InetAddress &ListenAddr, std::string name, Option option)
    :loop_(checkLoopNotNull(loop)), ipPort_(ListenAddr.toIpPort()), name_(name),
    acceptor_(new Acceptor(loop, ListenAddr, option == kReusePort)),
    threadPool_(new EventLoopThreadPool(loop, name_)), connectionCallback_(), messageCallback_(),nextConnId_(1),
    started_(0)
{
    // 当有新用户连接时会执行该回调
    acceptor_->setNewConnectionCallback(std::bind(&TcpServer::newConnection, this,
        std::placeholders::_1, std::placeholders::_2));
}

TcpServer::~TcpServer()
{
}

void TcpServer::setThreadNum(int numThreads)
{
    threadPool_->setThreadNum(numThreads);
}

void TcpServer::start()
{
    if(started_++ == 0)
    {
        threadPool_->start();
        loop_->runInLoop(std::bind(&Acceptor::listen, acceptor_.get()));
    }
}

void TcpServer::newConnection(int sockfd, const InetAddress &peerAddr)
{
}

void TcpServer::removeConnection(const TcpConnectionPtr &conn)
{
}

void TcpServer::removeConnectionInLoop(const TcpConnectionPtr &conn)
{
}
