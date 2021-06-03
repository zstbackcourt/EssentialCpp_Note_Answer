//
// Created by swj93 on 2021-05-09.
//

#ifndef ESSENTIALCPP_LIFO_STACK_H
#define ESSENTIALCPP_LIFO_STACK_H

#include "Stack.h"

class LIFO_Stack:public Stack{
public:
    LIFO_Stack(int cap = 0):_top(0){
        if(cap){
            _stack.reserve(cap); // 翻转vector
        }
    }

    int size() const { return _stack.size();} // 栈大小
    bool empty() const { return !_top;}
    bool full() const { return size() >= _stack.max_size();}
    int top() const { return _top;}
    void print(ostream &os = cout) const;

    bool pop(elemType &elem);
    bool push(const elemType &elem);
    bool peek(int, elemType&) { return false;}
private:
    int _top;
    vector<elemType> _stack;
};

#endif //ESSENTIALCPP_LIFO_STACK_H
