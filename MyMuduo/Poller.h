/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 12:40:50
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 22:50:28
 * @Description:
 */
#pragma once
#include "MyTypes.hpp"
#include "TimeStamp.h"
#include "Channel.h"

#include <vector>
#include <unordered_map>

class Channel;
class EventLoop;

class Poller : noncopyable
{
public:
    using ChannelList = std::vector<Channel *>;

    Poller(EventLoop *loop);
    virtual ~Poller() = default;
    
    virtual TimeStamp poll(const int timeoutMs, ChannelList *activateChannels) = 0;
    virtual void updateChannel(Channel *channel) = 0;
    virtual void removeChannel(Channel *channel) = 0;

    bool hasChannel(Channel* channel) const;
    
    /**
     * @brief EventLoop 可以通过该接口获取默认的IO复用的具体对象
     * 
     * @param loop 
     * @return Poller* 
     */
    static Poller* NewDefaultPoller(EventLoop *loop);

protected:
    using ChannelMap = std::unordered_map<int, Channel*>;
    ChannelMap channels_;
private:
private:
    EventLoop *ownerLoop_;
};


