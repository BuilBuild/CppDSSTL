/*
 * @Author: LeiJiulong
 * @Date: 2025-03-06 22:14:49
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-06 22:32:14
 * @Description: 
 */
#include "CServer.h"

CServer::CServer(boost::asio::io_context &ioc, unsigned short port)
    :ioc_(ioc), acceptor_(ioc, tcp::endpoint(tcp::v4(), port)), socket_(ioc)
{
}

void CServer::run()
{
    // 避免两个智能指针管理同一个对象
    // self的引用计数是同步的，当self被释放时，socket_也会被释放
    auto self = shared_from_this();
    // 接收成功或者失败都会调用这个回调函数
    acceptor_.async_accept(socket_, [self](beast::error_code ec){
        try
        {
            /* code */
            // 接收成功，则调用回调函数
            if(!ec)
            {
                // 创建新连接，用一个Connection 类管理这个连接

                // 继续监听其他连接
                self->run();

            } else {
                // 接收失败，则打印错误信息,并丢弃这个连接
                std::cerr << ec.message() << '\n';
                // 继续监听其他连接
                self->run();
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        
    });

}

void CServer::stop()
{
}
