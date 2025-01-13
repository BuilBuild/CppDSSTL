/*
 * @Author: LeiJiulong
 * @Date: 2025-01-13 08:18:27
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-01-13 08:23:14
 * @Description: 
 */
#include <iostream>
#include <thread>
#include <unistd.h>
#include <vector>

void thread_func()
{
    int i = 0;
    while(true)
    {
        std::cout << i++ << ", this thread id is: "<<std::this_thread::get_id() <<std::endl;
        sleep(1);
    }
}

int main()
{
    std::vector<std::thread> threadVec;

    for(int i =0; i<5; ++i)
    {
        threadVec.emplace_back(thread_func);
    }
    for(auto &t: threadVec)
    {
        if(t.joinable())
        {
            t.join();
        }
    }

    return 0;

}