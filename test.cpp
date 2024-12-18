/*
 * @Author: LeiJiulong
 * @Date: 2024-12-18 12:27:42
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-18 14:02:09
 * @Description:
 */
#include "MyList.hpp"
#include<iostream>

class A
{
public:
    explicit A(int i) : i_(i) {}
    ~A()
    {
        std::cout << this << ", A destroy i_: "  << i_ << std::endl;
    }
    int i_;
};

int main()
{
    mylist<A> ml;
    std::cout << "list is empty: " << ml.isempty() << std::endl;
    if (ml.begin() == ml.end())
    {
        std::cout << "list is empty" << std::endl;
    }
    A a(1);
    ml.push_back(a);
    a.i_ = 2;
    ml.push_back(a);
    a.i_ = 3;
    ml.push_back(a);
    return 0;
}
