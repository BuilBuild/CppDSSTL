/*
 * @Author: LeiJiulong
 * @Date: 2025-03-06 22:52:10
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-06 23:23:35
 * @Description: 
 */
#include "HttpConnection.h"

HttpConnection::HttpConnection(tcp::socket socket)
    :socket_(std::move(socket))
{
}

void HttpConnection::start()
{
    // 生成一个自己的智能指针防止回调之前析构
    auto self = shared_from_this();
    // 读取请求
    http::async_read(socket_, buffer_, request_, [self](beast::error_code ec, std::size_t bytesTransferred){
        // 用try catch 不同条件下有不同的适应情形，看情况使用，最好是不要用
        try
        {
            // ec 为True时是有异常的
            if(ec)
            {
                // TODO: 处理异常
                std::cerr << "http read err: " << ec.message() << std::endl;
                return;
            }
            
            boost::ignore_unused(bytesTransferred);
            // TODO: 处理请求
            self->handleRequest();
            // 启动超时检测
            self->checkTimeout();
            
            
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            std::cerr << ec.message() << std::endl;
        }
        
    });
}

void HttpConnection::checkTimeout()
{
    auto self = shared_from_this();
    // deadline_.expires_after(std::chrono::seconds(5));
    deadline_.async_wait([self](beast::error_code ec){
        if(!ec)
        {
            self->socket_.close();
            std::cerr << "http timeout err: " << ec.message() << std::endl;
            return;
        }
        
    });
}

void HttpConnection::doResponse()
{
    auto self = shared_from_this();
    response_.content_length(response_.body().size());
    http::async_write(socket_, response_, [self](beast::error_code ec, std::size_t bytesTransferred){
       self->socket_.shutdown(tcp::socket::shutdown_send, ec);
       self->deadline_.cancel();
    });
}

void HttpConnection::handleRequest()
{
    // TODO: 处理请求
    // 设置版本
    response_.version(request_.version());
    response_.set(http::field::server, "LeiJiulong");
    response_.keep_alive(false);    
    // 处理get请求
    if(request_.method() == http::verb::get)
    {
        // 处理业务逻辑
        response_.result(http::status::ok);
        response_.set(http::field::content_type, "text/html");
        // beast::os
        // response_.body() = "<html><body><h1>Hello World</h1></body></html>";
        
        // 
        doResponse();
        return ;

        
    }

}
