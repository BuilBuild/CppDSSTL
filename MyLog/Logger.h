/*
 * @Author: LeiJiulong
 * @Date: 2024-12-23 12:24:10
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-23 12:59:27
 * @Description: 
 */
#pragma once
#include <mutex>

#include "MyTypes.hpp"
#include "TimeStamp.h"

/*
日志级别
    INFO
    ERROR
    FATAL
    DEBUG
*/

// LOG_INFO(%s %d, arg1, arg2...)
#define LOG_INFO(LogmsgFormat, ...) \
    do \
    { \
        Logger& logger = *(Logger::getInstance()); \
        logger.setLogLevel(INFO); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, LogmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)

#define LOG_ERROR(LogmsgFormat, ...) \
    do \
    { \
        Logger& logger = *(Logger::getInstance()); \
        logger.setLogLevel(ERROR); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, LogmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)

#ifdef LOGDEBUG
#define LOG_DEBUG(LogmsgFormat, ...) \
    do \
    { \
        Logger& logger = *(Logger::getInstance()); \
        logger.setLogLevel(DEBUG); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, LogmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)
#else
   #define LOG_DEBUG(LogmsgFormat, ...) 
#endif

#define LOG_FATAL(LogmsgFormat, ...) \
    do \
    { \
        Logger& logger = *(Logger::getInstance()); \
        logger.setLogLevel(FATAL); \
        char buf[1024] = {0}; \
        snprintf(buf, 1024, LogmsgFormat, ##__VA_ARGS__); \
        logger.log(buf); \
    } while(0)


enum LogLevel
{
    INFO,   // 普通信息
    ERROR,  // 错误信息
    FATAL,  // core dump
    DEBUG   // 调试信息
};

class Logger : noncopyable
{
public:
    static Logger* getInstance();
    void setLogLevel(int level);
    void log(std::string &msg);
private:
    Logger();
    static void Construct();
private:
    // 日志级别
    int log_level_;
    static std::once_flag flag_;
    static Logger* logInstance_;
};