//
// Created by swj93 on 2021-04-27.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

inline int max(int a, int b){
    return a > b ? a : b;
}

inline float max(float a, float b){
    return a > b ? a : b;
}

inline string max(const string &s1, const string &s2){
    return s1 > s2 ? s1 : s2;
}

inline int max(const vector<int> &vec){
    return *max_element(vec.begin(),vec.end()); // *max_element返回vector中最大值,如果没有*表示地址
}

inline float max(const vector<float> &vec){
    return *max_element(vec.begin(),vec.end());
}

inline string max(const vector<string> &vec){
    return *max_element(vec.begin(),vec.end());
}

inline int max(const int *arr, int size){
    return *max_element(arr,arr+size);
}

inline float max(const float *arr, int size){
    return *max_element(arr,arr+size);
}

inline string max(const string *arr, int size){
    return *max_element(arr,arr+size);
}