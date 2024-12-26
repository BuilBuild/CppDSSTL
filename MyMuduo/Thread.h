/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 20:20:55
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 20:48:30
 * @Description:
 */
#pragma once

#include "MyTypes.hpp"


#include <functional>
#include <thread>
#include <memory>
#include <unistd.h>
#include <string>
#include <atomic>


class Thread : noncopyable
{
public:
    using  ThreadFunc = std::function<void(void)>;

    explicit Thread(ThreadFunc, const std::string &name = std::string());
    ~ Thread();

    void start();
    void join();

    bool started() const {return started_;}
    pid_t tid() const { return tid_;}
    const std::string name() const {return name_;}

    static int numCreated() { return numCreated_;}

private:
    void setDefaultName();
    
private:
    bool started_;
    bool joined_;
    std::shared_ptr<std::thread> thread_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    static std::atomic_int numCreated_;
};
