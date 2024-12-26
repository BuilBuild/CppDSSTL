/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 22:41:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 23:06:58
 * @Description: 
 */
#pragma once

#include "MyTypes.hpp"
#include "InetAddress.h"

#include <unistd.h>



class Socket : noncopyable
{
public:
    explicit Socket(int sockfd): sockfd_(sockfd){}
    ~Socket() {::close(sockfd_);}

    const int fd() const {return sockfd_;}

    void bindAddress(const InetAddress &localaddr);
    void listen();
    int accept(InetAddress *peeraddr);
    
    void shutdownWrite();

    void setTcpNoDelay(bool on);
    void setReuseAddr(bool on);
    void setReusePort(bool on);
    void setKeepAlive(bool on);


private:

private:
    const int sockfd_;
};


