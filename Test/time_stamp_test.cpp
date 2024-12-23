/*
 * @Author: LeiJiulong
 * @Date: 2024-12-23 11:13:32
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-23 12:00:26
 * @Description: 
 */
#include<iostream>
#include "TimeStamp.h"

int main()
{
    std::cout << TimeStamp::now().toString() << std::endl;
    std::cout << TimeStamp::now().toFormatString() << std::endl;
    
    return 0;
}

