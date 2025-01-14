/*
 * @Author: LeiJiulong
 * @Date: 2025-01-14 21:43:26
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-14 22:09:45
 * @Description: 
 */
#include <zmq.hpp>
#include <iostream>

#include <string>

int main()
{
    zmq::context_t ctx;
    zmq::socket_t sock(ctx,zmq::socket_type::sub);

    sock.setsockopt(ZMQ_SUBSCRIBE, "ZMQ", 3);
    sock.connect("tcp://localhost:9999");
    while (true)
    {
        zmq::message_t topic;
        auto f_topic = sock.recv(topic, zmq::recv_flags::none);
        zmq::message_t msg;
        auto f_msg = sock.recv(msg, zmq::recv_flags::none);
        std::cout << std::string(static_cast<char*>(topic.data()), topic.size()) << " " << std::string(static_cast<char*>(msg.data()), msg.size()) << std::endl;
    }
    
    
    return 0;
}
