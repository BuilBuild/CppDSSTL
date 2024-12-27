/*
 * @Author: LeiJiulong
 * @Date: 2024-12-23 12:31:11
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-26 12:26:34
 * @Description: 
 */
#include "Logger.h"

std::once_flag Logger::flag_;
Logger* Logger::logInstance_ = nullptr;

Logger *Logger::getInstance()
{
    std::call_once(flag_, Construct);
    return logInstance_;
}

void Logger::setLogLevel(int level)
{
    log_level_ = level;
}

void Logger::log(std::string msg)
{
    switch (log_level_)
    {
    case INFO:
        std::cout << "[INFO] [" << TimeStamp::now().toFormatString() << "] " << msg << std::endl;
        break;
    case WARRING:
        std::cout << "[WARRING] [" << TimeStamp::now().toFormatString() << "] " << msg << std::endl;
        break;
    case ERROR:
        std::cout << "[ERROR] [" << TimeStamp::now().toFormatString() << "] " << msg << std::endl;
        break;
    case FATAL:
        std::cout << "[FATAL] [" << TimeStamp::now().toFormatString() << "] " << msg << std::endl;
        break;
    case DEBUG:
        std::cout << "[DEBUG] [" << TimeStamp::now().toFormatString() << "] " << msg << std::endl;
        break;
    default:
        break;
    }
}

Logger::Logger()
{
}

void Logger::Construct()
{
    logInstance_ = new Logger();
}
