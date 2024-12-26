/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 13:03:46
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 19:35:00
 * @Description:
 */

#include "Poller.h"
#include "EpollPoller.h"



#include <stdlib.h>

Poller* Poller::NewDefaultPoller(EventLoop *loop)
{
    if(::getenv("MUDUO_SUE_POLL"))
    {
        return nullptr;
    }
    else
    {
        return new EpollPoller(loop);
    }
}