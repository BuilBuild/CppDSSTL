/*
 * @Author: LeiJiulong
 * @Date: 2024-12-25 14:43:10
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-25 14:44:17
 * @Description: 
 */
#include<memory>
#include<iostream>


int main()
{   
    std::unique_ptr<char> a = std::make_unique<char>('a');
    return 0;
}
