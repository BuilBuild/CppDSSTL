/*
 * @Author: LeiJiulong
 * @Date: 2024-12-23 12:31:11
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-23 12:44:49
 * @Description: 
 */
#include "Logger.h"

Logger *Logger::getInstance()
{
    std::call_once(flag_, Construct);
    return logInstance_;
}

void Logger::setLogLevel(int level)
{
    log_level_ = level;
}

void Logger::log(std::string &msg)
{
    switch (log_level_)
    {
    case INFO:
        std::cout << "[INFO] [" << TimeStamp::now().toFormatString() << "] " << msg << std::endl;
        break;
    case ERROR:
        std::cout << "[ERROR] " << TimeStamp::now().toFormatString() << "] " << msg << std::endl;
        break;
    case FATAL:
        std::cout << "[FATAL] " << TimeStamp::now().toFormatString() << "] " << msg << std::endl;
        break;
    case DEBUG:
        std::cout << "[DEBUG] " << TimeStamp::now().toFormatString() << "] " << msg << std::endl;
        break;
    default:
        break;
    }
}
