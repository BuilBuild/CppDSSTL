/*
 * @Author: LeiJiulong
 * @Date: 2025-03-06 22:37:45
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-06 22:37:47
 * @Description: 
 */
#pragma once

#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/asio.hpp>
#include <memory>
#include <chrono>
#include  <iostream>

namespace beast = boost::beast;         // from <boost/beast.hpp>   
namespace http = beast::http;         // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>