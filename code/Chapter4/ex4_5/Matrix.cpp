//
// Created by swj93 on 2021-05-08.
//
#include "Matrix.h"


inline Matrix::Matrix(const elemType *arr) {
    int arr_id = 0;
    for(int i= 0; i< 4;i++){
        for(int j = 0;j<4;j++){
            _matirx[i][j] = arr[arr_id++];
        }
    }
}

inline Matrix::Matrix(elemType a11, elemType a12, elemType a13, elemType a14, elemType a21, elemType a22, elemType a23,
                      elemType a24, elemType a31, elemType a32, elemType a33, elemType a34, elemType a41, elemType a42,
                      elemType a43, elemType a44) {
    _matirx[0][0] = a11; _matirx[0][1] = a12; _matirx[0][2] = a13; _matirx[0][3] = a14;
    _matirx[1][0] = a21; _matirx[1][1] = a22; _matirx[1][2] = a23; _matirx[1][3] = a24;
    _matirx[2][0] = a31; _matirx[2][1] = a32; _matirx[2][2] = a33; _matirx[2][3] = a34;
    _matirx[3][0] = a41; _matirx[3][1] = a42; _matirx[3][2] = a43; _matirx[3][3] = a44;
}


inline ostream& operator<<(ostream &os, const Matrix &ref){
    for(int i = 0;i < 4;++i){
        for(int j = 0;j < 4;++j){
            cout << ref(i,j) << " ";
        }
        cout << endl;
    }
    return os;
}

void Matrix::operator+=(const Matrix &m) {
    for(int i = 0;i<4;++i){
        for(int j = 0;j<4;j++){
            _matirx[i][j] += m._matirx[i][j];
        }
    }
}

Matrix operator+(const Matrix &m1, const Matrix &m2){
    Matrix res(m1);
    res += m2;
    return res;
}

Matrix operator*(const Matrix &m1, const Matrix &m2){
    Matrix res;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            res(i,j) = 0;
            for(int k = 0;k<4;k++){
                res(i,j) += m1(i,k)*m2(k,j);
            }
        }
    }
    return res;
}