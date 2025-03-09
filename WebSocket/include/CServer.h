/*
 * @Author: LeiJiulong
 * @Date: 2025-03-06 22:00:50
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-06 22:38:19
 * @Description: 
 */

#pragma once

#include "const.h"

/**
io_context 上下文调度器
事件循环核心：io_context 是异步操作的事件循环引擎，负责轮询 I/O 事件（如 socket 读写、定时器到期等）并触发对应的回调函数。
任务调度器：管理异步任务的调度，确保处理程序（handler）在适当的时机（如数据就绪时）被执行。
资源管理者：关联所有使用该 io_context 的 I/O 对象（如 socket、timer），确保它们的生命周期和事件处理正确。
*/

class CServer : public std::enable_shared_from_this<CServer>
{
public:
    
    CServer(boost::asio::io_context& ioc, unsigned short port);
    void run();
    void stop();

private:
    tcp::acceptor acceptor_;
    boost::asio::io_context& ioc_;
    tcp::socket socket_;
    
};



