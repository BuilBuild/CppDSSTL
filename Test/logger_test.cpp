/*
 * @Author: LeiJiulong
 * @Date: 2024-12-23 17:45:58
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-23 18:15:21
 * @Description: 
 */
#include"Logger.h"


int main()
{
    auto c = Logger::getInstance();
    c->log("test");
    LOG_INFO("info test");
    LOG_FATAL("log FATAL test");
    LOG_DEBUG("log DEBUG test");
    
    return 0;
}

