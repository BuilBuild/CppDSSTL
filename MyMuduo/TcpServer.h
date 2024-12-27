/*
 * @Author: LeiJiulong
 * @Date: 2024-12-25 16:23:23
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-27 14:30:49
 * @Description: 
 */
#pragma once

#include "EventLoop.h"
#include "Acceptor.h"
#include "InetAddress.h"
#include "MyTypes.hpp"
#include "EventLoopThreadPool.h"
#include "Callbacks.h"

#include <functional>
#include <string>
#include <memory>
#include <atomic>
#include <unordered_map>

class TcpServer
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    enum Option
    {
        kNoReusePort,
        kReusePort
    };


    explicit TcpServer(EventLoop *loop, const InetAddress &ListenAddr, std::string name = std::string(), Option option = kNoReusePort);
    ~TcpServer();

    void setThreadInitCallback(const ThreadInitCallback &cb) {threadInitCallback_ = cb;}
    void setConnectionCallback(const ConnectionCallback &cb) {connectionCallback_ = cb;}
    void setMessageCallback(const MessageCallback &cb) {messageCallback_ = cb;}
    void setWriteCompleteCallback(const WriteCompleteCallback &cb) {writeCompleteCallback_ = cb;}
    void setThreadNum(int numThreads);

    /**
     * @brief 开启服务器监听
     * 
     */
    void start();

private:
    void newConnection(int sockfd, const InetAddress &peerAddr);
    void removeConnection(const TcpConnectionPtr &conn);
    void removeConnectionInLoop(const TcpConnectionPtr &conn);

private:
    using ConnectionMap = std::unordered_map<std::string, TcpConnectionPtr>;

    EventLoop* loop_;
    const std::string ipPort_;
    const std::string name_;
    
    std::unique_ptr<Acceptor> acceptor_;
    std::shared_ptr<EventLoopThreadPool> threadPool_;
    
    // 有新连接时的回调
    ConnectionCallback connectionCallback_;
    // 有读写消息的回调
    MessageCallback messageCallback_;
    // 消息发送完成后的回调
    WriteCompleteCallback writeCompleteCallback_;
    // 线程初始化后的回调
    ThreadInitCallback threadInitCallback_;

    int nextConnId_;
    // 保存所有连接
    ConnectionMap connections_;
    std::atomic_int started_;

};