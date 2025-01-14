/*
 * @Author: LeiJiulong
 * @Date: 2025-01-14 21:21:06
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-14 21:28:49
 * @Description: 
 */
#include<zmq.hpp>
#include <string>

int main()
{
    
    zmq::context_t ctx;
    zmq::socket_t socXSub(ctx, zmq::socket_type::xsub);
    socXSub.bind("tcp://*:7777");

    zmq::socket_t socXPub(ctx, zmq::socket_type::xpub);
    socXPub.bind("tcp://*:9999");
    zmq::proxy_steerable(socXPub, socXSub, nullptr, nullptr);

    socXPub.close();
    socXSub.close();
    ctx.close();


    return 0;
}