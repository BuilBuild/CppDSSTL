/*
 * @Author: LeiJiulong
 * @Date: 2024-12-30 16:59:14
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-30 17:04:07
 * @Description: 
 */
#include<json.hpp>

#include <iostream>
#include <string>

using json = nlohmann::json;

void func1()
{
    json js;
    js["msg_type"] = 2;
    js["msg"] = "hello nlohmann json";

    std::string s = js.dump();
    std::cout << s << std::endl;
}

int main()
{
    func1();
    return 0;
}