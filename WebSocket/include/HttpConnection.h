/*
 * @Author: LeiJiulong
 * @Date: 2025-03-06 22:39:33
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-06 22:50:14
 * @Description: 
 */
#pragma once

#include "const.h"


class HttpConnection : public std::enable_shared_from_this<HttpConnection>
{
public:
    HttpConnection(tcp::socket socket);

    // 监听读写事件
    void start();

private:
    // 检测超时函数
    void checkTimeout();
    // 应答
    void doResponse();
    // 处理请求
    void handleRequest();

private:

    tcp::socket socket_;                                        // 套接字
    beast::flat_static_buffer<8*1024> buffer_{};                // 缓冲区

    http::request<http::dynamic_body> request_;                 // 请求
    http::response<http::dynamic_body> response_;               // 响应

    net::steady_timer deadline_ {                               // 定时器 需要绑定一个调度器
        socket_.get_executor(), std::chrono::seconds(60)
    };                                                          

    
};