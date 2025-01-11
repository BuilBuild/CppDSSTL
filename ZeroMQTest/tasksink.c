/*
 * @Author: LeiJiulong
 * @Date: 2025-01-08 19:25:34
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-08 19:35:17
 * @Description: 
 * 任务接受器
 * 将PULL套接字bind 到ctp://localhost:5558
 */

#include "zhelpers.h"



int main()
{
    // 准备上下文
    void *context = zmq_ctx_new();
    void *receiver = zmq_socket(context, ZMQ_PULL);
    zmq_bind(receiver, "tcp://localhost:5558");

    // 等待批次开始
    char *string = s_recv(receiver);
    free(string);

    // 启动时钟
    int64_t start_time = s_clock();

    // 处理100个确认
    int task_nbr = 0;
    for(task_nbr = 0; task_nbr<100; task_nbr++)
    {
        char *string = s_recv(receiver);
        free(string);
        if((task_nbr/10)*10 == task_nbr)
        {
            printf(":");
        }
        else
        {
            printf(".");
        }
        fflush(stdout);
    }

    // 计算并报告批次的用时
    printf("Total elapsed time: %d msec\n",
        (int)(s_clock() - start_time)
    );

    zmq_close(receiver);
    zmq_ctx_destroy(context);

    return 0;
}