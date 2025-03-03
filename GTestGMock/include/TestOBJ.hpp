/*
 * @Author: LeiJiulong
 * @Date: 2025-03-03 09:29:10
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-03 10:09:16
 * @Description:
 */
#pragma once
#include <string>

namespace TestOBJ
{

    class OBJ01
    {
    public:
        OBJ01() = default;
        OBJ01(const std::string &name, bool flag) : name_(name), flag_(flag) {}
        ~OBJ01() = default;
        const std::string &name() const { return name_; }
        bool flag() const { return flag_; }

    private:
        std::string name_;
        bool flag_;
    };
}

namespace MockOBJ{
    
class UserService
{
public:
    virtual ~UserService() = default;
    virtual bool Login(const std::string &username, const std::string &password) = 0;
    virtual int GetUserAge(const std::string &username) = 0;
};

}
