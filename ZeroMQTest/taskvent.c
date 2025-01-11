/*
 * @Author: LeiJiulong
 * @Date: 2025-01-08 18:04:54
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-08 20:32:51
 * @Description: 
 */

#include "zhelpers.h"
#include <time.h>
#include <zmq.h>
#include <unistd.h>




int main()
{
    void *context = zmq_ctx_new();
    
    // 用于发送消息的套接字
    void *sender = zmq_socket(context, ZMQ_PUSH);
    zmq_bind(sender, "tcp://*:5557");
    // 用于发送批次开始消息的套接字
    void *sink = zmq_socket(context, ZMQ_PUSH);
    zmq_connect(sink, "tcp://localhost:5558");

    printf("Press Enter when the new workers are ready:\n");

    // 第一个消息是 0
    s_send(sink, "0");

    // 初始化随机数发生器
    srandom((unsigned) time (NULL));
    
    // 发送100个任务
    int task_nbr;
    int total_msec = 0;
    for(task_nbr = 0; task_nbr < 100; ++task_nbr)
    {
        int workload = 0;
        workload = randof(100)+1;
        total_msec += workload;
        char string[10] = {0};
        sprintf(string, "%hu", workload);
        s_send(sender,string);
    }

    printf("Total expected cost: %d msec\n", total_msec);
    sleep(1);

    zmq_close(sink);
    zmq_close(sender);
    zmq_ctx_destroy(context);
    return 0; 
}