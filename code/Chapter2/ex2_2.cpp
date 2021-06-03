//
// Created by swj93 on 2021-04-27.
//

#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool Pentagonal(vector<int> &vec, int pos){
    if(pos<0||pos>64){
        cerr << "Error pos!\n";
        return false;
    }
    for(int i = 0;i<pos;i++){
        vec.push_back((i*(3*i-1))/2);
    }
    return true;
}

void print(vector<int> &vec, const string &s){
    cout << "iter: " << s << ":\n";
    for(int num:vec){
        cout << num << ',';
    }
    cout << endl;
}

int main(){
    int pos, i = 0;
    cout << "Please enter a position: ";
    cin >> pos;
    vector<int> vec;
    Pentagonal(vec,pos);
    print(vec,to_string(i));
    return 0;
}