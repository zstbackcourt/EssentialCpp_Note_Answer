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
    Stack(int capacity = 0):_top(0){
        if (capacity){
            _stack.reserve(capacity);
        }
    }
    virtual ~Stack(){}
    bool pop(elemType&);
    bool push(const elemType&);
    virtual bool peek(int ,elemType&){
        return false;
    }
    int size() const { return !_top;}
    bool full() const { return size()>=_stack.max_size();}
    void print(ostream &os=cout) const ;
protected:
    vector<elemType> _stack;
    int _top;
};


#endif //ESSENTIALCPP_STACK_H
