/*
 * @Author: LeiJiulong
 * @Date: 2025-01-11 19:06:34
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-11 19:12:49
 * @Description: 
 */
#include <zmq.hpp>
#include <string.h>

#include <iostream>

int main()
{
    zmq::context_t ctx(1);
    zmq::socket_t soc(ctx, zmq::socket_type::req);
    soc.connect("tcp://localhost:5656");
    zmq::message_t msg_req(128);
    bzero(msg_req.data(), 128);
    // 发送请求
    memcpy(msg_req.data(), "hello", 5);
    soc.send(msg_req, zmq::send_flags::none);

    // 接收请求
    zmq::message_t msg_rep;
    soc.recv(msg_rep, zmq::recv_flags::none);
    
    std::cout << msg_rep.to_string() << std::endl;

    return 0;
}
