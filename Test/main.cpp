/*
 * @Author: LeiJiulong
 * @Date: 2024-12-20 04:17:15
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-20 04:49:00
 * @Description: 
 */
/*
https://www.cnblogs.com/jwk000/p/3560086.html
https://blog.csdn.net/QLeelq/article/details/111059187
https://blog.csdn.net/HW140701/article/details/125003612
https://zhuanlan.zhihu.com/p/373392670

Durations
std::chrono::duration 表示一段时间，比如两个小时，12.88秒，半个时辰，一炷香的时间等等，只要能换算成秒即可。
template <class Rep, class Period = ratio<1> > class duration;

由于各种duration表示不同，chrono库提供了duration_cast类型转换函数。
template <class ToDuration, class Rep, class Period>
constexpr ToDuration duration_cast (const duration<Rep,Period>& dtn);

*/
// duration constructor
#include <iostream>
#include <ratio>
#include <chrono>

int main ()
{
  typedef std::chrono::duration<int> seconds_type;
  typedef std::chrono::duration<int,std::milli> milliseconds_type;
  typedef std::chrono::duration<int,std::ratio<60*60>> hours_type;

  hours_type h_oneday (24);                  // 24h
  seconds_type s_oneday (60*60*24);          // 86400s
  milliseconds_type ms_oneday (s_oneday);    // 86400000ms

  seconds_type s_onehour (60*60);            // 3600s
//hours_type h_onehour (s_onehour);          // NOT VALID (type truncates), use:
  hours_type h_onehour (std::chrono::duration_cast<hours_type>(s_onehour));
  milliseconds_type ms_onehour (s_onehour);  // 3600000ms (ok, no type truncation)

  std::cout << ms_onehour.count() << "ms in 1h" << std::endl;

  return 0;
}

/*

// duration还有一个成员函数count()返回Rep类型的Period数量，看代码：

// duration::count
#include <iostream>     // std::cout
#include <chrono>       // std::chrono::seconds, std::chrono::milliseconds
                        // std::chrono::duration_cast

int main ()
{
  using namespace std::chrono;
  // std::chrono::milliseconds is an instatiation of std::chrono::duration:
  milliseconds foo (1000); // 1 second
  foo*=60;

  std::cout << "duration (in periods): ";
  std::cout << foo.count() << " milliseconds.\n";

  std::cout << "duration (in seconds): ";
  std::cout << foo.count() * milliseconds::period::num / milliseconds::period::den;
  std::cout << " seconds.\n";

  return 0;
}

*/