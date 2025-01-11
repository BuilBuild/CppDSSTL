/*
 * @Author: LeiJiulong
 * @Date: 2025-01-08 19:03:44
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-08 19:23:08
 * @Description: 
 */
#include "zhelpers.h"

int main()
{
    void *context = zmq_ctx_new();

    // 用于接收套接字
    void *receiver = zmq_socket(context, ZMQ_PULL);
    zmq_connect(receiver, "tcp://localhost:5557");

    // 用于发送消息的套接字
    void *sender = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sender, "tcp://localhost:5558");

    // 永远处理任务
    while(1)
    {
        char *string  = s_recv(receiver);
        fflush(stdout);
        printf("%s.", string);

        // 不做工作
        s_sleep(atoi(string));
        free(string);

        // 将结果发送给接收器具
        s_send(sender, "");
    }

    zmq_close(receiver);
    zmq_close(sender);
    zmq_ctx_destroy(context);
    return 0;

}