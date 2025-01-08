/*
 * @Author: LeiJiulong
 * @Date: 2025-01-06 14:11:19
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-08 19:04:40
 * @Description: 
 */
#pragma once

#include <zmq.h>
#include <stdlib.h>
#include <string.h>

#define s_send zmq_send
// 随机生成0-num-1的随机函数
#define randof(num) (int)((float)(num)*random()/(RAND_MAX + 1.0))

static char* s_recv(void *socket)
{
    zmq_msg_t message;
    zmq_msg_init(&message);
    int size = zmq_msg_recv(&message, socket, 0);
    if(size == -1)
        return NULL;
    char *string = (char*)malloc(size +1);
    bzero(string, size+1);
    memcpy(string, zmq_msg_data(&message), size);
    return string;
}