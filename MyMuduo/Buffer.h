/*
 * @Author: LeiJiulong
 * @Date: 2024-12-27 13:16:36
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-27 19:15:37
 * @Description: 
 */
#pragma once

#include <vector>
#include <stdio.h>
#include <string>
#include <algorithm>

class Buffer
{
public:
    static const size_t kCheapPrepend = 8;
    static const size_t kInitialSize = 1024;

    explicit Buffer(size_t initialSize = kInitialSize)
        : buffer_(kCheapPrepend+ initialSize), readerIndex_(kCheapPrepend), writerIndex_(kCheapPrepend)
        {}
    ~Buffer();

    /**
     * @brief 可以读取的数据字节大小 
     * 
     * @return size_t 
     */
    size_t readableBytes() const {return writerIndex_ - readerIndex_;}
    size_t writableBytes() const {return buffer_.size() - writerIndex_;}
    size_t prependableBytes() const {return readerIndex_;}

    /**
     * @brief 返回数据缓冲区中可读数据的起始地址
     * 
     * @return const char* 
     */
    const char* peek() const {return begin()+readerIndex_;}

    void retrieve(size_t len)
    {
        if(len < readableBytes())
        {
            readerIndex_ += len;
        }
        else
        {
            retirveAll();
        }
    }

    void retirveAll() { readerIndex_ = writerIndex_ = kCheapPrepend;}

    /**
     * @brief 把onMessage函数上报的Buffer数据，转成string类型返回
     * 
     * @return std::string 
     */
    std::string retriveAllAsString(){return retriveAsString(readableBytes());}

    /**
     * @brief 
     * 
     * @return std::string 
     */
    std::string  retriveAsString(size_t len) 
    {
        std::string result(peek(), len);
        // 进行复位操作
        retrieve(len);
        return result;
    }

    void ensureWritableBytes(size_t len)
    {
        if(writableBytes()< len)
        {
            makeSpace(len);
        }
    }

    void append(const char *data, size_t len)
    {
        ensureWritableBytes(len);
        std::copy(data, data+len, beginWrite());
        writerIndex_ += len;
    }

    char* beginWrite()
    {
        return begin() + writerIndex_;
    }

    const char* beginWrite() const 
    {
        return begin() + writerIndex_;
    }
    
    /**
     * @brief 从fd上读取数据 Poller工作在LT模式
     *  buffer缓冲区是有大小的，但是从fd上读取数据的时候却不知道tcp数据最终的大小
     * @param fd 
     * @param saveErrno 
     * @return ssize_t 
     */
    ssize_t readFd(int fd, int* saveErrno);

    //通过fd发送数据
    ssize_t writeFd(int fd, int *saveErrno);

private:
    char* begin() {return &*buffer_.begin();}
    const char* begin() const {return &*buffer_.begin();}
    
    void makeSpace(size_t len)
    {
        if(writableBytes()+ prependableBytes() < len + kCheapPrepend)
        {
            buffer_.resize(writerIndex_ + len);
        }
        else
        {
            size_t readable = readableBytes();
            std::copy(begin() + readerIndex_, begin()+writerIndex_, begin() + kCheapPrepend);
            readerIndex_ = kCheapPrepend;
            writerIndex_ = readerIndex_ + readable;
        }
    }

private:
    std::vector<char> buffer_;
    size_t readerIndex_;
    size_t writerIndex_;
};