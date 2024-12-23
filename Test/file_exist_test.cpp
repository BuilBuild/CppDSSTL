/*
 * @Author: LeiJiulong
 * @Date: 2024-12-22 15:18:19
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-22 15:36:08
 * @Description: 
 */

#include <iostream>
#include <fstream>

int main() {
    std::ifstream file("example.txt", std::ios::in);
    if (file.good()) {
        std::cout << "File exists!" << std::endl;
        
    } else {
        file.close();
        std::cout << "File does not exist." << std::endl;
        
    }
    std::cout << file.is_open() << "mm" << std::endl;
    return 0;
}
