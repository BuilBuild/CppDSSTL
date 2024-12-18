/*
 * @Author: LeiJiulong
 * @Date: 2024-12-18 12:06:37
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2024-12-18 14:11:15
 * @Description:
 */
#pragma once
#include <iostream>

template <typename T>
struct mylist_node
{
    explicit mylist_node(const T &x) : pre(nullptr), next(nullptr), data(x) {}

    mylist_node *pre;
    mylist_node *next;
    T data;
};

template <typename T>
struct mylist_iterator
{
    explicit mylist_iterator() : node(nullptr) {}
    explicit mylist_iterator(mylist_node<T> *tmpnode) : node(tmpnode) {}

    mylist_iterator operator++(int)
    {
        mylist_iterator temp(*this);
        node = node->next;
        return temp;
    }

    mylist_iterator &operator++()
    {
        node = node->next;
        return *this;
    }

    T &operator*()
    {
        return node->data;
    }

    bool operator!=(const mylist_iterator &tmpobj)
    {
        return node != tmpobj.node;
    }

    bool operator==(const mylist_iterator &tmpobj)
    {
        return node == tmpobj.node;
    }

    mylist_node<T>* node;
};

template <typename T>
class mylist
{
public:
    using iterator = mylist_iterator<T>;

    explicit mylist()
    {
        void *point = new char[sizeof(mylist_node<T>)];
        head = reinterpret_cast<mylist_node<T> *>(point);
        head->next = head;
        head->pre = head;
    }

    ~mylist()
    {
        std::cout << "destroy" << std::endl;
        clear();
        delete head;
        head = nullptr;
    }

    iterator begin()
    {
        return iterator(head->next);
    }

    iterator end()
    {
        return iterator(head);
    }

    bool isempty()
    {
        return head->next == head;
    }
    
    void push_back(const T& tmpelem)
    {
        mylist_node<T>* newnode = new mylist_node<T>(tmpelem);
        if(isempty())
        {
            newnode->next = head;
            newnode->pre = head;
            head->next = newnode;
            head->pre = newnode;
            std::cout << "first push the ele addr is: " << newnode << std::endl;
        }
        else
        {
            newnode->next = head;
            newnode->pre = head->pre;
            head->pre->next = newnode;
            head->pre = newnode;
            
            std::cout << "not fist push, the ele addr is: "<< newnode << std::endl;
        }
    }

    void clear()
    {
        if(!isempty())
        {
            mylist_node<T> *curr_node = head->next;
            while(curr_node != head)
            {
                mylist_node<T> *next_node = curr_node->next;
                delete curr_node;
                curr_node = next_node;
            }
        }
    }
private:
    mylist_node<T> *head;
};