//
// Created by swj93 on 2021-04-27.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

inline bool check(int pos){
    // 检查pos是否合理
    return (pos<=0||pos>64) ? false : true;
}


const vector<int>* Pentagonal(int pos){
    static vector<int> vec; // 局部静态对象
    if(check(pos) && (pos>vec.size())){
        for(int i = vec.size()+1 ; i<=pos; i++){
            vec.push_back((i*(3*i-1))/2);
        }
    }
    return &vec; // 返回指针
}


int Cal(int pos){
    if(!check(pos)){
        cerr << "Error pos!\n";
        return -1;
    }
    const vector<int> *ptr = Pentagonal(pos); // 函数指针
    return (*ptr)[pos-1];
}

void print(int pos){
    cout << " Pos: " << pos << " " << Cal(pos);
}

int main(){
    int pos;
    cout << "Please enter a position: ";
    cin >> pos;
    print(pos);
    return 0;
}