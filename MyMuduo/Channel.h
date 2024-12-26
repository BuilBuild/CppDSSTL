/*
 * @Author: LeiJiulong
 * @Date: 2024-12-25 16:26:12
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 13:07:49
 * @Description:
 */
#pragma once
#include "MyTypes.hpp"
#include "TimeStamp.h"
#include "EventLoop.h"

#include<functional>
#include <memory>



class EventLoop;

class Channel : noncopyable
{
    using EventCallback = std::function<void()>;
    using ReadEventCallback = std::function<void(TimeStamp)>;
public:
    Channel(EventLoop* loop, int fd);
    ~Channel();

    // fd得到通知以后，处理事件并调用相应的回调方法
    void handleEvent(TimeStamp receiveTime);

    // 设置回调
    void setReadCallback(ReadEventCallback &cb) {readCallback_ = std::move(cb);}
    void setWriteCallback(EventCallback &cb) {writeCallback_ = std::move(cb);}
    void setCloseCallback(EventCallback &cb) {closeCallback_ = std::move(cb);}
    void setErrorCallback(EventCallback &cb) {errorCallback_ = std::move(cb);}

    // 防止channel被手动remove调，channel还在执行回调操作
    void tie(const std::shared_ptr<void>&);
    
    int fd() const {return fd_;}
    int events() const { return events_;}
    void set_revents(int revt) { revents_ = revt;}

    //控制fd的感兴趣的事件,设置相应事件的状态
    void enableReading() {events_ |= kReadEvent; update();}
    void disableReading() {events_ &= ~kReadEvent; update();}
    void enableWriting() {events_ |= kWriteEvent; update();}
    void disableWriting() {events_ &= ~kWriteEvent; update();}
    void disableAll() {events_ = kNoneEvent; update();}

    // 返回事件状态
    bool isNoneEvent() const {return events_ == kNoneEvent;}
    bool isWriting() const {return events_ & kWriteEvent;} 
    bool isReading() const {return events_ & kReadEvent;}

    int index() const { return index_;}
    void set_index(int idx) {index_ = idx;}

    EventLoop* ownerLoop() {return loop_;}
    void remove();

private:
    /**
     * @brief 
     * 改变channel所表示的events事件，update负责在poller里面更改相应事件epoll_ctrl
     */
    void update();

    /**
     * @brief 
     * 根据发生的事件负责调用具体的回调函数
     * 
     * @param receiveTime 
     */
    void handleEventWithGuard(TimeStamp receiveTime);

private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop* loop_;    // 事件循环
    const int fd_;  // 监听的对象
    int events_;    // 注册fd感兴趣的事件
    int revents_;   // poller返回的具体发生的事件
    int index_;

    std::weak_ptr<void> tie_;
    bool tied_;
    
    // channel可以获取fd最总发生的具体事件events,channel负责具体事件的回调
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback closeCallback_;
    EventCallback errorCallback_;

};
