/*
 * @Author: LeiJiulong
 * @Date: 2024-12-23 10:53:45
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-23 11:57:24
 * @Description: 
 */
#pragma once
#include<iostream>
#include <string>

class TimeStamp
{
    static const int kMicroSecondsPerSecond = 1000 * 1000;
public:
    TimeStamp();
    explicit TimeStamp(const int64_t &microSecondsSinceEpoch_);
    std::string toString() const;
    static TimeStamp now();
    std::string toFormatString() const;
private:
    int64_t microSecondsSinceEpoch_;
    
};