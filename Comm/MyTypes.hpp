/*
 * @Author: LeiJiulong
 * @Date: 2024-12-23 12:21:29
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-23 12:22:30
 * @Description: 
 */
#pragma once

class noncopyable
{
public:
    noncopyable(const noncopyable&) = delete;
    noncopyable& operator = (const noncopyable&) = delete;
protected:
    noncopyable() = default;
    ~noncopyable() = default;
};
