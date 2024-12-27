/*
 * @Author: LeiJiulong
 * @Date: 2024-12-27 12:29:56
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-27 12:52:23
 * @Description: 
 */
#pragma once

#include "MyTypes.hpp"
#include "Socket.h"
#include "Channel.h"


#include <functional>

class EventLoop;
class InetAddress;


class Acceptor : noncopyable
{
public:
    using NewConnectCallback = std::function<void(int sockfd, const InetAddress&)>;

    explicit Acceptor(EventLoop *loop, const InetAddress &listenAddr, bool reuseport);
    ~Acceptor();

    void setNewConnectionCallback(const NewConnectCallback &cb) {newConnectCallback_ = cb;}

    bool listening() const {return listening_;}
    void listen();

private:
    /**
     * @brief 有新用户连接了就会触发accept读回调，封装包含connfd的channel给相应的loop 
     * 
     */
    void handleRead();

private:
    EventLoop *loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectCallback newConnectCallback_;
    bool listening_;

};