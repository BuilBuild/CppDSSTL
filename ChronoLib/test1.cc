/*
 * @Author: LeiJiulong
 * @Date: 2025-03-09 13:56:50
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-09 14:34:29
 * @Description: 
 */
#include <chrono>
#include <thread>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <string>

// 时长的表示，比如seconds、milliseconds等，以及如何构造和转换这些单位。
// 这里要注意不同单位之间的隐式转换规则，比如从高精度到低精度需要显式转换，避免数据丢失
std::string timestamp_to_string(int64_t timestamp_ms, const std::string& format);

void timestamp_to_string_test()
{
    /**
     * 常见格式示例
       格式名称	      示例字符串	               格式参数
       ISO 8601	    2023-10-05T14:30:00Z	    "%Y-%m-%dT%H:%M:%SZ"
       含毫秒	     2023-10-05 14:30:00.123	 "%Y-%m-%d %H:%M:%S."
       自定义格式	  05/Oct/2023:14:30:00	      "%d/%b/%Y:%H:%M:%S"
     */
    // 解析含毫秒的时间字符串（如 "2023-10-05 14:30:00.123"）
    std::string time_str = "2023-10-05 14:30:00.123";
    std::string format = "%Y-%m-%d %H:%M:%S";

    std::tm tm = {};
    int milliseconds = 0;
    std::istringstream ss(time_str);
    ss >> std::get_time(&tm, format.c_str()) >> milliseconds;

    // 转换为时间戳（毫秒）
    auto tp =std::chrono::system_clock::from_time_t(std::mktime(&tm)) 
            + std::chrono::milliseconds(milliseconds);
    int64_t timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch()).count();
    std::cout << "时间戳（毫秒）: " << timestamp << std::endl;
}

int main()
{
    // ------------时钟(Clocks)-----------------
    // system_clock 的 epoch 通常是 1970-01-01（UNIX时间）
    // steady_clock 的 epoch 由实现定义（通常为系统启动时间）
    // system_clock 是系统时钟，用于表示当前时间
    auto now = std::chrono::system_clock::now();
    // steady_clock 是稳定时钟，用于表示经过的时间，不受系统时间调整的影响
    auto start = std::chrono::steady_clock::now();
    time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::cout << "当前时间: " << ctime(&now_t);
    std::tm tm = *std::localtime(&now_t);
    std::cout << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << '\n';


    // TO DO
    std::this_thread::sleep_for(std::chrono::seconds(1));
    auto end = std::chrono::steady_clock::now();
    //-------------------时长(Duration)------------
    // duration 表示一段时间，可以表示秒、毫秒、微秒等
    // duration<Rep, Period>
    /**
     * 预定于义：
     *  using nanoseconds  = duration<long long, nano>;
        using microseconds = duration<long long, micro>;
        using milliseconds = duration<long long, milli>;
        using seconds      = duration<long long>;
        using minutes      = duration<int, ratio<60>>;
        using hours        = duration<int, ratio<3600>>;
     * 
     */

    auto duration = end - start;
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "耗时: " << elapsed.count() << "μs\n";

    // ----------------时间点(Time Points)----------------
    int64_t timestamp = 1696518600123; // 2023-10-05 14:30:00.123
    std::string str = timestamp_to_string(timestamp, "%Y-%m-%d %H:%M:%S");
    std::cout << "时间戳: " << str << '\n';

    timestamp_to_string_test();

    return 0;
}

std::string timestamp_to_string(int64_t timestamp_ms, const std::string& format) {
    auto tp = std::chrono::system_clock::time_point(
        std::chrono::milliseconds(timestamp_ms)
    );
    std::time_t t = std::chrono::system_clock::to_time_t(tp);
    std::tm tm = *std::localtime(&t); // 或 gmtime 处理 UTC
    
    std::ostringstream ss;
    ss << std::put_time(&tm, format.c_str());
    return ss.str();
}
