/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 15:36:58
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 15:43:00
 * @Description: 
 */
#include "CurrentThread.h"

namespace CUrrentThread
{
    __thread int t_cachedTid = 0;

    void cacheTid()
    {
        if(t_cachedTid == 0)
        {
            // 通过系统调用获取当前线程id
            t_cachedTid = static_cast<pid_t>(::syscall(SYS_gettid));
        }
    }
}