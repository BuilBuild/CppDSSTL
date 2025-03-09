/*
 * @Author: LeiJiulong
 * @Date: 2025-03-09 13:15:58
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-03-09 13:36:16
 * @Description: 
 */

#pragma once

#include <list>
#include <unordered_map>
#include <mutex>

namespace MYLRU {

template<typename Key, typename Value>
class MyLRU
{
public:
    explicit MyLRU(size_t capacity): capacity(capacity) {}

    Value get(const Key& key)
    {
        std::unique_lock<std::mutex> lock(mtx);
        auto it = cacheMap.find(key);
        if(it == cacheMap.end())
        {
            return Value();
        }
        cache.splice(cacheMap.begin(), cache, it->second);
        return it->second->second;
    }

    void put(const Key& key, const Value& value)
    {
        std::unique_lock<std::mutex> lock(mtx);
        auto it = cacheMap.find(key);
        // 更新节点
        if(it != cacheMap.end())
        {
            cache.splice(cacheMap.begin(), cache, it->second);
            it->second->second = value;
            return;
        }
        // 插入新节点
        if(cache.size() == capacity)
        {
            auto last = cache.back();
            cacheMap.erase(last.first);
            cache.pop_back();
        }
        cache.emplace_front(key, value);
        cacheMap[key] = cache.begin();
    }

private:
    size_t capacity;
    std::list<std::pair<Key, Value>> cache;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cacheMap;
    std::mutex mtx;
};
} // namespace MYLRU