/*
 * @Author: LeiJiulong
 * @Date: 2024-12-21 09:32:45
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-21 09:32:45
 * @Description: 
 */
#include <iostream>
 
// 单例模板类
template <typename T>
class Singleton {
private:
    static T* instance;
 
protected:
    // 由子类覆盖以初始化实例
    static T* createInstance() {
        return new T();
    }
 
    Singleton(const Singleton& other) = delete;
    Singleton& operator=(const Singleton& other) = delete;
 
public:
    // 获取单例实例
    static T* getInstance() {
        if (instance == nullptr) {
            instance = createInstance();
        }
        return instance;
    }
 
    // 析构单例实例
    static void deleteInstance() {
        if (instance != nullptr) {
            delete instance;
            instance = nullptr;
        }
    }
};
 
// 定义静态成员变量
template <typename T>
T* Singleton<T>::instance = nullptr;
 
// 示例类
class MySingleton : public Singleton<MySingleton> {
private:
    friend class Singleton<MySingleton>;
 
    // 私有构造函数
    MySingleton() {}
 
    // 自定义初始化方法
    static MySingleton* createInstance() {
        return new MySingleton();
    }
};
 
