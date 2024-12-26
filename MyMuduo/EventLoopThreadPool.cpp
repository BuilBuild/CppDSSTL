/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 22:13:59
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 22:31:04
 * @Description: 
 */
#include "EventLoopThreadPool.h"

#include <string.h>

EventLoopThreadPool::EventLoopThreadPool(EventLoop *loop, const std::string &name)
    : baseLoop_(loop), name_(name)
{
}

EventLoopThreadPool::~EventLoopThreadPool()
{
}

void EventLoopThreadPool::start(const ThreadInitCallback &cb)
{
    started_ = true;
    for(int i=0; i< numThreads_; ++i)
    {
        char buf[name_.size() + 32];
        bzero(buf, sizeof buf);
        sprintf(buf, "%s%d", name_.c_str(), i);
        EventLoopThread *t = new EventLoopThread(cb, buf);
        threads_.emplace_back(t);
        // 让底层的loop启动起来
        loops_.push_back(t->startLoop());
    }

    if(numThreads_ == 0 && cb)
    {
        cb(baseLoop_);
    }
}

EventLoop *EventLoopThreadPool::getNextLoop()
{
    EventLoop* loop = baseLoop_;
    if(!loops_.empty())
    {
        loop = loops_[next_];
        ++next_;
        if(next_> loops_.size())
        {
            next_ = 0;
        }
    }

    return loop;
}

std::vector<EventLoop *> EventLoopThreadPool::getAllLoops()
{
    if(loops_.empty())
    {
        return std::vector<EventLoop*>(1, baseLoop_);
    }
    else
    {
        return loops_;
    }
}
