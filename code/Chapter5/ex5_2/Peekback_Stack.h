//
// Created by swj93 on 2021-05-09.
//

#ifndef ESSENTIALCPP_PEEKBACK_STACK_H
#define ESSENTIALCPP_PEEKBACK_STACK_H

#include "Stack.h"

class Peekback_Stack:public Stack{
public:
    Peekback_Stack(int cap = 0):_top(0){
        if(cap){
            _stack.reserve(cap); // 翻转vector
        }
    }

    virtual bool  peek(int index, elemType &elem);
private:
    int _top;
    vector<elemType> _stack;
};


#endif //ESSENTIALCPP_PEEKBACK_STACK_H
