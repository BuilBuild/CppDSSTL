/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 13:03:46
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 13:40:39
 * @Description:
 */

#include "Poller.h"

#include <stdlib.h>

Poller *Poller::NewDefaultPoller(EventLoop *)
{
    if(::getenv("MUDUO_SUE_POLL"))
    {
        return nullptr;
    }
    else
    {
        return nullptr;
    }
}