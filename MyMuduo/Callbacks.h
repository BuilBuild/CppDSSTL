/*
 * @Author: LeiJiulong
 * @Date: 2024-12-27 13:16:06
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-27 18:17:20
 * @Description: 
 */
#pragma once

#include <memory>
#include <functional>
#include <stdio.h>

class Buffer;
class TcpConnection;
class TimeStamp;

using TcpConnectionPtr = std::shared_ptr<TcpConnection>;
using ConnectionCallback = std::function<void(const TcpConnectionPtr&)>;
using CloseCallback = std::function<void(const TcpConnectionPtr&)>;
using WriteCompleteCallback = std::function<void(const TcpConnectionPtr&)>;
using MessageCallback = std::function<void(const TcpConnectionPtr&, Buffer*, TimeStamp)>;

using HighWaterMarkCallback = std::function<void(const TcpConnectionPtr&, size_t)>;
