//
// Created by swj93 on 2021-05-09.
//

#include "LIFO_Stack.h"


bool LIFO_Stack::pop(elemType &elem) {
    if(empty()) return false;
    elem = _stack[--_top];
    _stack.pop_back();
    return true;
}

bool LIFO_Stack::push(const elemType &elem) {
    if(full()) return false;
    _stack.push_back(elem);
    ++ _top;
    return true;
}

void LIFO_Stack::print(ostream &os) const {
    // 注意在声明的时候已经设定了默认参数所以这里不能再重复设定
    vector<elemType>::const_reverse_iterator riter = _stack.rbegin(); // 反向迭代器
    vector<elemType>::const_reverse_iterator rend = _stack.rend();
    for(; riter!= rend; ++riter)
    {
        os << *riter << " ";
    }
    os << endl;
}


