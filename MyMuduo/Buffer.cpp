/*
 * @Author: LeiJiulong
 * @Date: 2024-12-27 16:40:02
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-27 17:06:54
 * @Description: 
 */
#include "Buffer.h"

#include <errno.h>
#include <sys/uio.h>

ssize_t Buffer::readFd(int fd, int *saveErrno)
{
    // 栈上的空间
    char extrabuf[65536] = {0};
    struct iovec vec[2];

    const size_t writable = writableBytes();
    vec[0].iov_base = begin() + writerIndex_;
    vec[0].iov_len = writable;

    vec[1].iov_base = extrabuf;
    vec[2].iov_len  = sizeof extrabuf;
    
    const int iovcnt = (writable < sizeof extrabuf)? 2 : 1;
    const ssize_t n = ::readv(fd, vec, iovcnt);

    if(n<0)
    {
        *saveErrno = errno;
    }
    else if (n <= writable)
    {
        writerIndex_ += n;
    }
    else // extrabuf 里面也写入了数据，要对buff扩容
    {
        writerIndex_ = buffer_.size();
        append(extrabuf, n-writable);
    }

    return n;
}