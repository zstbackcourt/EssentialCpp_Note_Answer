//
// Created by swj93 on 2021-04-27.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


template <typename numT>
inline numT max(numT &t1, numT &t2){
    return t1 > t2 ? t1 : t2;
}

template <typename vecT>
inline vecT max(const vector<vecT> &vec){
    return *max_element(vec.begin(),vec.end());
}

template <typename arrT>
inline arrT max(const arrT *arr, int size){
    return *max_element(arr, arr+size);
}

int main(){
    int int_t1 = 23, int_t2 = 54;
    float float_t1 = 33.4, float_t2 = 13.4;
    string s1 = "aefc", s2 = "afew";
    vector<string> svec = {
            "dadfasdf",
            "asdfwer",
            "dasdfasdf"
    };
    vector<int> ivec = {1,3,4,23,2};
    int arr[4] = {32,41,12,44};
    cout << "Int: " << max(int_t1,int_t2) << '\n'
         << "Float: " << max(float_t1, float_t2) << '\n'
         << "String: " << max(s1,s2) << '\n'
         << "sVec: " << max(svec) << '\n'
         << "iVec: " << max(ivec) << '\n'
         << "Arr: " << max(arr,4)
         << endl;
}