/*
 * @Author: LeiJiulong
 * @Date: 2024-12-21 14:17:32
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-22 10:39:47
 * @Description:
 */
#include "SingleWritePool.hpp"
#include <iostream>
#include <string>
#include <thread>
#include <functional>
#include <fstream>
#include <memory>

void (*p)(void) = []{
    std::cout << "obj" << std::endl;
};

template<typename T>
class CallObjT
{
public:
    void operator()(const T& ele)
	{
        // fp = std::make_shared<FILE, decltype(&fclose)>(fopen(ele.future_name, "ab+"));
        std::unique_ptr<std::ofstream, void(*)(std::ofstream *)> file_(new std::ofstream(ele.future_name, std::ios::ate|std::ios::app), close_fp);
        *file_ << ele.time_stamp << '\n';
	}
    static void close_fp(std::ofstream *p)
    {
        // std::cout << "close" << std::endl;
        p->close();
    }
private:
    std::shared_ptr<std::ofstream> fp; 
};

void Test(std::string thread_name)
{
    auto c = WritePool<FutureData, CallObjT<FutureData>>::GetInstance();
    FutureData a{};
    memcpy(a.future_name, thread_name.c_str(),thread_name.length());
    a.time_stamp = 0;
    for(int i = 0; i< 4000; ++i)
    {
        a.time_stamp++;
        c->push(a);
    }

}

int main()
{
    auto c = WritePool<FutureData, CallObjT<FutureData>>::GetInstance();
    FutureData a{1, "abb"};
    for(int i =0 ; i< 400; ++i)
    {
        c->push(a);
        a.time_stamp++;
    }
    std::thread t1(Test, "test1");
    std::thread t2(Test, "test2");
    t1.join();
    t2.join();
    WritePool<FutureData, CallObjT<FutureData>>::DeleInstance();
    return 0;
}