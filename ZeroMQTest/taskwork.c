/*
 * @Author: LeiJiulong
 * @Date: 2025-01-08 19:03:44
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-08 19:10:31
 * @Description: 
 */
#include "zhelpers.h"

int main()
{
    void *context = zmq_ctx_new();

    // 用于接收套接字
    void *receive = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receive, "tcp://localhost:5557");

    // 用于发送消息的套接字
    void *send = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(send, "tcp://localhost:5558");

    // 永远处理任务
    while(1)
    {
        // char *string  = s_recv(receive)
    }

}