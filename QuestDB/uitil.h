/*
 * @Author: LeiJiulong
 * @Date: 2025-02-11 22:05:39
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-11 22:10:54
 * @Description: 
 */
#pragma once

#include <iostream>
#include <chrono>
#include <cmath>        // 用于分解浮点数
#include <iomanip>      // 用于格式化时间
#include <sstream>

// 将 float64 时间戳（秒级，含小数）转换为 ISO 8601 字符串
std::string float_to_iso(double timestamp) {
    // 分解整数秒和小数部分
    time_t sec = static_cast<time_t>(timestamp);
    double fractional = timestamp - sec;  // 提取小数部分（0~1秒）
    int milliseconds = static_cast<int>(fractional * 1000);  // 转为毫秒

    // 转换为 time_point
    auto tp = std::chrono::system_clock::from_time_t(sec) 
              + std::chrono::milliseconds(milliseconds);

    // 转换为 time_t（仅用于格式化）
    auto tp_time = std::chrono::system_clock::to_time_t(tp);
    std::tm tm = *std::gmtime(&tp_time);  // 使用 UTC 时间

    // 格式化为 ISO 8601 字符串
    std::stringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S") 
       << "." << std::setw(3) << std::setfill('0') << milliseconds 
       << "Z";
    return ss.str();
}

// 示例：插入数据（使用 PostgreSQL 协议）
// #include <libpq-fe.h>

// int main() {
//     double float_timestamp = 1633046400.123; // 示例：2021-10-01T00:00:00.123Z

//     // 转换为 ISO 字符串
//     std::string iso_ts = float_to_iso(float_timestamp);

//     // 连接到 QuestDB
//     PGconn *conn = PQconnectdb("host=localhost port=8812 user=admin password=quest dbname=qdb");
//     if (PQstatus(conn) != CONNECTION_OK) {
//         std::cerr << "连接失败: " << PQerrorMessage(conn) << std::endl;
//         return 1;
//     }

//     // 插入数据
//     std::string query = 
//         "INSERT INTO sensors(ts, sensor_id, temperature) VALUES ("
//         "'" + iso_ts + "', "
//         "1, "
//         "23.5"
//         ");";

//     PGresult *res = PQexec(conn, query.c_str());
//     if (PQresultStatus(res) != PGRES_COMMAND_OK) {
//         std::cerr << "插入失败: " << PQerrorMessage(conn) << std::endl;
//     } else {
//         std::cout << "数据插入成功！" << std::endl;
//     }

//     PQclear(res);
//     PQfinish(conn);
//     return 0;
// }