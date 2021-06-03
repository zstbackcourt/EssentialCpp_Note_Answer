//
// Created by swj93 on 2021-04-29.
//
#include "Stack.h"


bool Stack::push(const string &elem) {
    if(full()){
        return false;
    }
    _stack.push_back(elem);
    return true;
}

bool Stack::pop(string &elem) {
    if(empty()){
        return false;
    }
    elem = _stack.back();
    _stack.pop_back();
    return true;
}

bool Stack::peek(string &elem) {
    if(empty()){
        return false;
    }
    elem = _stack.back();
    return true;
}

bool Stack::find(const string &elem) const{
    vector<string>::const_iterator iter = _stack.begin();
    for(;iter!=_stack.end();iter++){
        if(*iter == elem){
            return true;
        }
    }
    return false;
}

int Stack::count(const string &elem) const {
    vector<string>::const_iterator iter = _stack.begin();
    int res = 0;
    for(;iter!=_stack.end();iter++){
        if(*iter == elem){
            res ++ ;
        }
    }
    return res;
}