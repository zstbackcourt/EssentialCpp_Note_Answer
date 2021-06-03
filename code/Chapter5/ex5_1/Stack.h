//
// Created by swj93 on 2021-04-29.
//

#ifndef ESSENTIALCPP_STACK_H
#define ESSENTIALCPP_STACK_H

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

typedef string elemType;

class Stack{
public:
    virtual ~Stack(){} // 抽象类需要析构函数
    virtual bool pop(elemType&) = 0; // 纯虚函数
    virtual bool push(const elemType&) = 0;
    virtual bool peek(int index, elemType&) = 0;

    virtual int top() const = 0;
    virtual int size() const = 0;

    virtual bool empty() const = 0;
    virtual bool full() const = 0;
    virtual void print(ostream& = cout) const = 0;
};


#endif //ESSENTIALCPP_STACK_H
