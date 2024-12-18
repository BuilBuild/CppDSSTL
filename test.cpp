/*
 * @Author: LeiJiulong
 * @Date: 2024-12-18 12:27:42
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-18 14:16:28
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
    for(int i=0; i< 20; i++, a.i_++)
    {    
        ml.push_back(a);
    }
    return 0;
}
