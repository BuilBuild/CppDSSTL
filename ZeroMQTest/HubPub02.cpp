/*
 * @Author: LeiJiulong
 * @Date: 2025-01-14 21:41:57
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-14 22:11:20
 * @Description: 
 */
#include <zmq.hpp>
#include <thread>
#include <chrono>
#include <string>

int main()
{
    zmq::context_t ctx;
    zmq::socket_t sock(ctx, zmq::socket_type::pub);
    sock.connect("tcp://localhost:7777");
    int snum = 0;
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        zmq::message_t topic("ZMQ", 3);

        std::string messageString = "hello-02-pub";
        messageString +=  " " + std::to_string(snum++);
        
        zmq::message_t msg(messageString);

        sock.send(topic,zmq::send_flags::sndmore);
        sock.send(msg, zmq::send_flags::none);

    }

    sock.close();
    ctx.close();
    

    return 0;
}