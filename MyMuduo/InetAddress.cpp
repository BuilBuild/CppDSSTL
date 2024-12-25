/*
 * @Author: LeiJiulong
 * @Date: 2024-12-25 15:47:36
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-25 16:03:23
 * @Description: 
 */
#include "InetAddress.h"
#include <string.h>

InetAddress::InetAddress(uint16_t port, std::string ip)
{
   bzero(&addr_, sizeof addr_);
   addr_.sin_family = AF_INET;
   // host to net 将本地字节序转网络字节序
   addr_.sin_port = htons(port);
   // 转成点分十进制的网络字节序
   addr_.sin_addr.s_addr = inet_addr(ip.c_str()); 
}

std::string InetAddress::toIp() const
{
    char buf[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    return buf;
}

std::string InetAddress::toIpPort() const
{
    char buf[64] = {0};
    ::inet_ntop(AF_INET, &addr_.sin_addr, buf, sizeof buf);
    size_t end = strlen(buf);
    uint16_t port = ntohs(addr_.sin_port);
    sprintf(buf+end, ":%u", port);
    return buf;
}

uint16_t InetAddress::toPort() const
{
    return ntohs(addr_.sin_port);
}

/*
#include <iostream>
int main()
{

    InetAddress addr(8080);
    std::cout << addr.toIpPort() << std::endl; 
    return 0;
}
*/