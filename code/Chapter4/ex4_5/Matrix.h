//
// Created by swj93 on 2021-05-08.
//

#ifndef ESSENTIALCPP_MATRIX_H
#define ESSENTIALCPP_MATRIX_H

#include <iostream>
using namespace std;

typedef float elemType; // 将floats设置另外的名称elemType

class Matrix{
    friend Matrix operator+(const Matrix &m1, const Matrix &m2);
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);

public:
    Matrix(const elemType*); // 用指针的构造函数
    Matrix(elemType = 0.0, elemType = 0.0, elemType = 0.0, elemType = 0.0,
           elemType = 0.0, elemType = 0.0, elemType = 0.0, elemType = 0.0,
           elemType = 0.0, elemType = 0.0, elemType = 0.0, elemType = 0.0,
           elemType = 0.0, elemType = 0.0, elemType = 0.0, elemType = 0.0);

    void operator+=(const Matrix&);
    elemType operator()(int row,int column) const { return _matirx[row][column];}
    elemType& operator()(int row,int column) { return _matirx[row][column];}
private:
    elemType _matirx[4][4]; // 4*4的矩阵
};



#endif //ESSENTIALCPP_MATRIX_H
