#include "EventLoopThread.h"
#include "EventLoop.h"

EventLoopThread::EventLoopThread(const ThreadInitCallback &cb, const std::string &name)
    : loop_(nullptr), exiting_(false),
    thread_(std::bind(&EventLoopThread::threadFunc, this), name),
    cond_(), mutex_(), callback_(cb)
{
}

EventLoopThread::~EventLoopThread()
{
    exiting_ = true;
    if(loop_ != nullptr)
    {
        loop_->quit();
        thread_.join();
    }
}

EventLoop *EventLoopThread::startLoop()
{
    thread_.start(); // 底层启动新线程
    std::unique_lock<std::mutex> lock(mutex_);
    cond_.wait(lock, [&]{return loop_ != nullptr;});
    return loop_;
}

// 下面这个方法，是在单独的新线程里面运行的
void EventLoopThread::threadFunc()
{
    // 创建一个独立的eventloop, 和上面的线程一一对应，one loop per thread
    EventLoop loop;
    if(callback_)
    {
        callback_(&loop);
    }
    {
        std::unique_lock<std::mutex> lock(mutex_);
        // 线程绑定一个loop对象
        loop_ = &loop;
        cond_.notify_one();
    }
    loop.loop(); // 开启地称poller 监听状态
    std::unique_lock<std::mutex> lock(mutex_);
    loop_ = nullptr;
}
