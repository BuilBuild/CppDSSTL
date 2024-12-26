/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 21:40:25
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 22:27:21
 * @Description: 
 */
#pragma once

#include "EventLoopThread.h"
#include "MyTypes.hpp"

#include <functional>
#include <thread>
#include <vector>
#include <memory>
#include <string>



class EventLoopThreadPool : noncopyable
{
public:
    using ThreadInitCallback = std::function<void(EventLoop*)>;

    explicit EventLoopThreadPool(EventLoop* loop, const std::string &name = std::string());
    ~EventLoopThreadPool();

    void setThreadNum(int numThreads) {numThreads_ = numThreads;}

    void start(const ThreadInitCallback &cb = ThreadInitCallback());

    EventLoop* getNextLoop();

    std::vector<EventLoop*> getAllLoops();
    bool started() const { return started_;}
    const std::string& name() const {return name_;};

private:

private:
    EventLoop *baseLoop_;
    std::string name_;
    bool started_;
    int numThreads_;
    int next_;
    std::vector<std::unique_ptr<EventLoopThread>> threads_;
    std::vector<EventLoop*> loops_;

};

