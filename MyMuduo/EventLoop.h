/*
 * @Author: LeiJiulong
 * @Date: 2024-12-25 16:24:31
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 20:10:45
 * @Description:
 */
#pragma once
#include "MyTypes.hpp"
#include "TimeStamp.h"
#include "CurrentThread.h"

#include <functional>
#include <vector>
#include <memory>
#include <atomic>
#include <mutex>

class Channel;
class Poller;

class EventLoop : noncopyable
{
public:
    using Functor = std::function<void(void)>;

    explicit EventLoop();
    ~EventLoop();

    /**
     * @brief 开启事件循环 
     * 
     */
    void loop();
    
    /**
     * @brief 退出事件循环 
     * 
     */
    void quit();

    TimeStamp pollReturnTime() const {return pollReturnTime_;}
    
    /**
     * @brief 在当前loop中执行 
     * 
     * @param cb 
     */
    void runInLoop(Functor cb);
    
    /**
     * @brief 把回调对象放入队列中，唤醒loop所在的线程执行cb 
     * 
     * @param cb 
     */
    void queueInLoop(Functor cb);

    /**
     * @brief 唤醒loop中所在的线程 
     * 
     */
    void wakeup();
    

    void updateChannel(Channel *channel);
    void removeChannel(Channel *channel);
    bool hasChannel(Channel *channel);

    /**
     * @brief 判断eventloop 是不是自己的线程里 
     * 
     * @return true 
     * @return false 
     */
    bool isInLoopThread() const {return threadId_ == CurrentThread::tid();}

private:
    using ChannelList = std::vector<Channel *>;

    /**
     * @brief wake up 
     * 
     */
    void handleRead();
    
    /**
     * @brief 执行回调 
     * 
     */
    void doPendingFunctors();

    std::atomic_bool looping_;
    std::atomic_bool quit_; // 标志退出loop循环
    std::atomic_bool callingPendingFunctors_; // 标志当前loop 是否有需要执行回调操作

    const pid_t threadId_; //记录当前loop所在的线程id,可用于判断这个loop的线程是不是在MainLoop中
    TimeStamp pollReturnTime_; //poller返回发生事件的channels的事件的时间点
    std::unique_ptr<Poller> poller_;

    int wakeupFd_;  // 当mainLoop 获取一个新用户的channel，通过轮询算法选择一个subloop,通过该成员通知subloop
    std::unique_ptr<Channel> wakeupChannel_;

    ChannelList activeChannels_;
    Channel* currentActiveChannel_;

    std::vector<Functor> pendingFunctors_; //存储loop中需要执行的回调操作
    std::mutex mutex_;  // 互斥锁用来保护pendingFunctors的线程安全操作

};