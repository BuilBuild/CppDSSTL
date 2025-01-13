/*
 * @Author: LeiJiulong
 * @Date: 2025-01-11 19:16:29
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-11 19:28:19
 * @Description: 
 */
#include <zmq.hpp>
#include <iostream>
#include <csignal>

using namespace zmq;

bool exitFlag = false;

void signalHandler(int sigNum)
{
    if(sigNum == SIGINT)
    {
        exitFlag = true;
    }
}

int main()
{
    signal(SIGINT, signalHandler);
    context_t ctx;
    socket_t sock(ctx, socket_type::rep);
    sock.bind("tcp://*:5656");

    while(!exitFlag)
    {
        message_t request;
        auto rt = sock.recv(request, recv_flags::none);
        if(rt)
        {
            std::cout << request.to_string() << std::endl;
            message_t msg("world", 5);
            sock.send(msg, send_flags::none);
        }
        else
        {
            break;
        }

    }
    return 0;
}
