/*
 * @Author: LeiJiulong
 * @Date: 2024-12-21 09:33:18
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-21 10:33:33
 * @Description: 
 */
#pragma once
#include <mutex>

template<typename T>
class Singleton
{
public:
    static T* getInstance()
    {
        std::call_once(cflag_, ConstructInstance);   
        return cinstance_;
    }

    // ~Singleton() = delete;
    Singleton(const Singleton&) = delete;
    Singleton& operator = (const Singleton &) = delete;

private:
    Singleton() = default;
    static T* cinstance_;
    static std::once_flag cflag_;
    static void ConstructInstance()
    {
        cinstance_ = new T();
    }
};

template<typename T>
std::once_flag Singleton<T>::cflag_;

template<typename T>
T* Singleton<T>::cinstance_=nullptr;

