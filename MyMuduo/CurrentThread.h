/*
 * @Author: LeiJiulong
 * @Date: 2024-12-26 15:35:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 15:43:44
 * @Description: 
 */

#pragma once

#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */

namespace CurrentThread
{
    
    extern  __thread int t_cachedTid;
    void cacheTid();

    inline int tid()
    {
        if(__builtin_expect(t_cachedTid == 0, 0))
        {
            cacheTid();
        }
        return t_cachedTid;
    }






}
