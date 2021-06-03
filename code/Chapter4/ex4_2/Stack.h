//
// Created by swj93 on 2021-04-29.
//

#ifndef ESSENTIALCPP_STACK_H
#define ESSENTIALCPP_STACK_H

#include <string>
#include <vector>
#include <iterator>
using namespace std;

class Stack{
public:
    bool push(const string &elem);
    bool pop(string &elem);
    bool peek(string &elem);
    bool find (const string &elem) const ;
    int count(const string &elem) const ;
    bool empty() const {
        // 这里的const表示不可以修改class的成员
        return _stack.empty();
    }
    bool full() const {
        return _stack.size() == _stack.max_size();
    }
    int size() const {
        return _stack.size();
    }


private:
    vector<string> _stack;
};


#endif //ESSENTIALCPP_STACK_H
