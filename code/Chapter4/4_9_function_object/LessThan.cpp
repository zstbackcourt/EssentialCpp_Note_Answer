//
// Created by swj93 on 2021-05-01.
//
#include "LessThan.h"

inline bool LessThan::operator()(int value) const {
    return value < _val;
}
