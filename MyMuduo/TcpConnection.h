/*
 * @Author: LeiJiulong
 * @Date: 2024-12-27 13:15:04
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-27 20:43:43
 * @Description: 
 */
#pragma once

#include "MyTypes.hpp"
#include "InetAddress.h"
#include "Callbacks.h"
#include "Buffer.h"
#include "TimeStamp.h"

#include <memory>
#include <atomic>
#include <string>


class Channel;
class EventLoop;
class Socket;


class TcpConnection: noncopyable, public std::enable_shared_from_this<TcpConnection>
{
public:
    explicit TcpConnection(EventLoop *loop, const std::string &name,
        int sockfd, const InetAddress &localAddr, const InetAddress &peerAddr);
    ~TcpConnection();

    EventLoop* getLoop() const {return loop_;}
    const std::string& name() const {return name_;}
    const InetAddress& localAddress() const {return localAddr_;}
    const InetAddress& peerAddress() const {return peerAddr_;}

    bool connected() const { return state_ == kConnected;}

    /**
     * @brief 发送数据
     * 
     */
    void send(const std::string &buf);

    /**
     * @brief 断开连接
     * 
     */
    void shutdown();

    void setConnectionCallback(const ConnectionCallback &cb) {connectionCallback_ = cb;}
    void setMessageCallback(const MessageCallback &cb) {messageCallback_ = cb;}
    void setWriteCompleteCallback(const WriteCompleteCallback &cb) {writeCompleteCallback_ = cb;}
    void setHighWaterMarkCallback(const HighWaterMarkCallback &cb) {highWaterMarkCallback_ = cb;} 
    
    /**
     * @brief 连接建立 
     * 
     */
    void connectEstablished();
    
    /**
     * @brief 连接销毁 
     * 
     */
    void connectDestroyed();

private:
    enum StatE {kDisconnected, kConnecting, kConnected, kDisconnecting};

    void handleRead(TimeStamp receiveTime);
    void handleWrite();
    void handleClose();
    void handleError();

    /**
     * @brief 发送数据 应用写的块，而内核发送数据慢 需要把待发送的数据写入缓冲区， 而且设置了水位回调
     * 
     * @param message 
     * @param len 
     */
    void sendInLoop(const void *message, size_t len);
    void shutdownInLoop();

    void setState(StatE state);


private:
    EventLoop* loop_;
    std::string name_;
    std::atomic_int state_;
    bool reading_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;
    
    const InetAddress localAddr_;
    const InetAddress peerAddr_;

    // 有新连接时的回调
    ConnectionCallback connectionCallback_;
    // 有读写消息的回调
    MessageCallback messageCallback_;
    // 消息发送完成后的回调
    WriteCompleteCallback writeCompleteCallback_;
    HighWaterMarkCallback highWaterMarkCallback_;
    CloseCallback closeCallback_;

    size_t highWaterMark_;
    Buffer inputBuffer_;
    Buffer outputBuffer_;

};