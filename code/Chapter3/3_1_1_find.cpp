//
// Created by swj93 on 2021-04-27.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


template <typename T>
T* find(const T *start, const T *end, const T &value){
    // 查找value是否存在
    // 因为vector和araay都可以用指针来指示地址,因此直接使用指针就可以不用重载函数了
    // 使用指针时,可以利用指针运算
    if(!start || !end){
        return -1;
    }
    for(;start!=end;start++){
        if(*start == value){
            return start;
        }
    }
    return -1;
}

