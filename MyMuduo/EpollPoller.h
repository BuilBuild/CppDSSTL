/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 13:10:40
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-28 18:09:09
 * @Description: 
 */
#pragma once

#include "Poller.h"
#include "Channel.h"

#include <vector>
#include <sys/epoll.h>

class EpollPoller : public Poller
{
public:
    EpollPoller(EventLoop* loop);
    ~EpollPoller() override;

    // 重写基类的方法
    TimeStamp poll(int timeoutMs, ChannelList *activateChannels) override;
    void updateChannel(Channel *channel) override;
    void removeChannel(Channel *channel) override;

private:
    using EventList = std::vector<epoll_event>;

    /**
     * @brief 填写或也的连接
     * 
     * @param numEvents 
     * @param activeChannels 
     */
    void fillActiveChannels(const int numEvents, ChannelList *activeChannels) const;
    
    /**
     * @brief 更新channel通道
     * 
     * @param operation EPOLL_CTL_ADD/EPOLL_CTL_DEL/EPOLL_CTL_MOD
     * @param channel 
     */
    void update(const int operation, Channel *channel);

private:
    static const int kInitEventListSize = 16;

    const int epollfd_;
    EventList events_;
};
