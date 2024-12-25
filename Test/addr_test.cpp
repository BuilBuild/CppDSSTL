/*
 * @Author: LeiJiulong
 * @Date: 2024-12-25 16:04:49
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-25 16:04:50
 * @Description: 
 */
#include <iostream>

#include "InetAddress.h"

int main()
{
    InetAddress addr(8086);
    std::cout << addr.toIpPort() << std::endl;
    return 0;
}