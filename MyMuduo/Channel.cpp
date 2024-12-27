/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 11:29:48
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-27 20:41:37
 * @Description: 
 */
#include "Channel.h"
#include "Logger.h"

#include <sys/epoll.h>


const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = EPOLLIN | EPOLLPRI;
const int Channel::kWriteEvent = EPOLLOUT;

Channel::Channel(EventLoop *loop, int fd)
    : loop_(loop),fd_(fd),events_(0),revents_(0),index_(-1),tied_(false)
{
}

Channel::~Channel()
{
    // 判断当前的channel是否在当前的loop线程析构
    // if(loop_ ->isInLoopThread())
    // {
    //     assert(!loop_->hasChannel(this));
    // }
}

void Channel::handleEvent(TimeStamp receiveTime)
{
    std::shared_ptr<void> guard;
    if(tied_)
    {
        guard = tie_.lock();
        if(guard)
        {
            handleEventWithGuard(receiveTime);
        }
    }
    else
    {
        handleEventWithGuard(receiveTime);
    }

}

void Channel::tie(const std::shared_ptr<void> &obj)
{
    tie_ = obj;
    tied_ = true;
}

void Channel::remove()
{
    // 通过所属的eventloop,调用pooler相应方法，删除对应的channel
    // add code ...
    loop_ -> removeChannel(this); 
}

void Channel::update()
{
    // 通过所属的eventloop,调用pooler相应方法，注册fd的events事件
    // add code ...
    loop_->updateChannel(this);
}

void Channel::handleEventWithGuard(TimeStamp receiveTime)
{
    LOG_INFO("channel handle event revent: %d", revents_);
    if((events_ & EPOLLHUP) && !(revents_ & EPOLLIN))
    {
        if(closeCallback_)
        {
            closeCallback_();
        }
    }

    if(revents_ & EPOLLERR)
    {
        if(errorCallback_)
        {
            errorCallback_();
        }
    }

    if(revents_ & (EPOLLIN | EPOLLPRI))
    {
        if(readCallback_)
        {
            readCallback_(receiveTime);
        }
    }

    if(revents_ & EPOLLOUT)
    {
        if(writeCallback_)
        {
            writeCallback_();
        }
    }
}
