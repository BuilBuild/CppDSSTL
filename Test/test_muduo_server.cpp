/*
 * @Author: LeiJiulong
 * @Date: 2024-12-28 13:44:51
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-28 14:09:37
 * @Description: 
 */
#include "TcpServer.h"
#include "Logger.h"


#include <string>
#include <functional>

class EchoServer
{
public:
    EchoServer(EventLoop *loop, const InetAddress &addr, const std::string &name)
        :server_(loop, addr, name),loop_(loop)
    {
        //注册回调
        server_.setConnectionCallback(
            std::bind(&EchoServer::onConnection, this, std::placeholders::_1)
        );
        server_.setMessageCallback(
            std::bind(&EchoServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
        );
        
        server_.setThreadNum(3);
    }
    
    void start()
    {
        server_.start();
    }

private:
    /**
     * @brief 连接建立和断开执行的回调
     * 
     * @param conn 
     */
    void onConnection(const TcpConnectionPtr &conn)
    {
        if(conn->connected())
        {
            LOG_INFO("Connection UP: %s", conn->peerAddress().toIpPort().c_str());
        }
        else
        {
            LOG_INFO("Connection DOWN: %s", conn->peerAddress().toIpPort().c_str());
        }
    }

    /**
     * @brief 可读写事件的回调
     * 
     * @param conn 
     * @param buf 
     * @param time 
     */
    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, TimeStamp time)
    {
        std::string msg = buf->retriveAllAsString();
        conn->send(msg);
        conn->shutdown();
    }


private:
    EventLoop* loop_;
    TcpServer server_;
    std::string name_;


};

int main()
{
    EventLoop loop;
    InetAddress addr(9999);
    EchoServer server(&loop, addr, "EchoServer-01");

    server.start();
    // 启动mainloop 底层Poller
    loop.loop();
    return 0;

}