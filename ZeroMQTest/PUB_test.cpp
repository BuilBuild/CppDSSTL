/*
 * @Author: LeiJiulong
 * @Date: 2025-01-11 16:16:09
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-14 22:05:56
 * @Description: 
 */
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <unistd.h>

int main() {
    // 创建上下文和套接字
    zmq::context_t context(1);
    zmq::socket_t socket(context, zmq::socket_type::pub);

    // 绑定到指定地址
    socket.bind("tcp://*:5558");

    // 发布消息
    int count = 0;
    while (true) {
        std::string topic = "OMS";
        std::string message = "Message " + std::to_string(count);

        // 发布主题和消息
        zmq::message_t topicMsg(topic.size());
        memcpy(topicMsg.data(), topic.data(), topic.size());
        socket.send(topicMsg, zmq::send_flags::sndmore);

        zmq::message_t messageMsg(message.size());
        memcpy(messageMsg.data(), message.data(), message.size());
        socket.send(messageMsg, zmq::send_flags::none);

        std::cout << "Published: " << std::string(static_cast<char*>(topic.data()), topic.size()) << " - " << static_cast<char*>(message.data()) << std::endl;

        count++;
        sleep(1); // 每秒发布一条消息
    }

    return 0;
}