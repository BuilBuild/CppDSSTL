/*
 * @Author: LeiJiulong
 * @Date: 2024-12-31 15:54:09
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-31 16:21:52
 * @Description: 
 */
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>

using namespace std;
using namespace muduo;
using namespace muduo::net;



class ChatServer
{
public:
    explicit ChatServer(EventLoop *loop, const InetAddress &listenAddr, const string &nameArg)
        : server_(loop, listenAddr, nameArg), loop_(loop)
        {
            // 给服务器注册用户连接创建和断开的回调
            server_.setConnectionCallback(
                std::bind(&ChatServer::conConnection, this, std::placeholders::_1)
            );

            // 给服务器注册用户读写事件的回调
            server_.setMessageCallback(
                std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
            );

            // 设置服务器端的线程数量
            server_.setThreadNum(3);

        }

    ~ChatServer(){}

    void start(){ server_.start();}

private:
    // 专门处理用户连接的创建和断开
    void conConnection(const TcpConnectionPtr &conn)
    {
        if(conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << " connected!" << endl;
            cout << "local address is " << conn->localAddress().toIpPort()<< endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << " failed!" << endl;
        }
    }
    // 专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn, Buffer *buff, Timestamp ts)
    {
        string buf = buff->retrieveAllAsString();
        cout <<"received ("<< conn->peerAddress().toIpPort() << ") message: " << buf << endl;
        conn->send("hello "+ buf);
    }

private:
    TcpServer server_;
    EventLoop* loop_;
};


int main()
{
    EventLoop loop;
    InetAddress inetAddress(9999);
    ChatServer server(&loop, inetAddress, "server");
    server.start();
    loop.loop();
    return 0;
}
