/*
 * @Author: LeiJiulong
 * @Date: 2025-01-11 16:34:59
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-11 17:07:14
 * @Description: 
 */
#include <zmq.hpp>
#include <string>
#include <iostream>

int main() {
    // 创建上下文和套接字
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::sub);

    // 连接到发布者地址
    socket.connect("tcp://localhost:5555");

    // 订阅所有主题
    socket.setsockopt(ZMQ_SUBSCRIBE, "", 0);
    // std::string to = "";
    // socket.setsockopt(zmq::sockopt::subscribe ,to, 0);

    // 接收并处理消息
    while (true) {
        // 接收主题
        zmq::message_t topicMsg;
        socket.recv(topicMsg, zmq::recv_flags::none);
        std::string topic(static_cast<char*>(topicMsg.data()), topicMsg.size());

        // 接收消息
        zmq::message_t messageMsg;
        socket.recv(messageMsg, zmq::recv_flags::none);
        std::string message(static_cast<char*>(messageMsg.data()), messageMsg.size());
        std::cout << "Received: " << topic << " - " << message << std::endl;
        
    }

    return 0;
}