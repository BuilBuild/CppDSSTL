#include "EpollPoller.h"
#include "Logger.h"

#include <errno.h>
#include <unistd.h>
#include <string.h>


const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;

EpollPoller::EpollPoller(EventLoop *loop)
    : Poller(loop), epollfd_(epoll_create1(EPOLL_CLOEXEC)), events_(kInitEventListSize)
{
    if (epollfd_ < 0)
    {
        LOG_FATAL("epoll fd cread failed %d", errno);
    }
}

EpollPoller::~EpollPoller()
{
    ::close(epollfd_);
}

TimeStamp EpollPoller::poll(const int timeoutMs, ChannelList *activateChannels)
{
    LOG_INFO("fd total count:%lu", channels_.size());
    const int numEvents = ::epoll_wait(epollfd_, &*events_.begin(),static_cast<int>(events_.size()), timeoutMs);
    const int saveErrno = errno;

    TimeStamp now(TimeStamp::now());

    if(numEvents>0)
    {
        LOG_INFO("%d events happened ", numEvents);
        fillActiveChannels(numEvents,activateChannels);
        if(numEvents == events_.size())
        {
            events_.resize(2*numEvents);
        }
    }
    else if (numEvents == 0)
    {
        LOG_DEBUG("timeout");
    }
    else
    {
        if(saveErrno != EINTR)
        {
            errno = saveErrno;
            LOG_ERROR("EpollPoller::poll() err");
        }
    }

    return now;
}

void EpollPoller::updateChannel(Channel *channel)
{
    const int index = channel->index();
    LOG_INFO("fd=%d, events=%d, index=%d", channel->fd(), channel->events(), index);
    if(index== kNew || index==kDeleted)
    {
        if(index == kNew)
        {
            const int fd = channel->fd();
            channels_[fd] = channel;
        }
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
    }
    else // channel已经在poller上注册过了
    {
        const int fd = channel->fd();
        if(channel->isNoneEvent())
        {
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
        }
        else
        {
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void EpollPoller::removeChannel(Channel *channel)
{
    LOG_INFO("fd=%d, events=%d, index=%d", channel->fd(), channel->events(), channel->index());
    const int fd = channel->fd();
    channels_.erase(fd);

    const int index = channel->index();
    if(index == kAdded)
    {
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kDeleted);
}

void EpollPoller::fillActiveChannels(const int numEvents, ChannelList *activeChannels) const
{
    for(int i=0; i< numEvents; ++i)
    {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->set_revents(events_[i].events);
        activeChannels->push_back(channel); // 至此EventLoop可以拿到对于的事件
    }
}

void EpollPoller::update(const int operation, Channel *channel)
{
    struct epoll_event event;
    bzero(&event, sizeof event);
    const int fd = channel->fd();

    event.events = channel->events();
    event.data.ptr = channel;
    event.data.fd = fd;


    if(::epoll_ctl(epollfd_, operation, fd, &event)<0)
    {
        if(operation == EPOLL_CTL_DEL)
        {
            LOG_ERROR("epoll_ctl delete failed, error=%d", errno);
        }
        else
        {
            LOG_FATAL("epoll_ctl add/modify failed, error=%d", errno);
        }
    }

}
