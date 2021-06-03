//
// Created by swj93 on 2021-04-26.
//

#include <iostream>
using namespace std;


bool Fibon_elem(int pos, int &elem){
    // 检查位置值是否合理
    if(pos <= 0|| pos > 1024){
        elem = 0;
        return false;
    }
    elem = 1;
    int n = 1, m = 1;
    for(int i = 3;i<=pos;i++){
        elem = n+m;
        n = m;
        m = elem;
    }
    return true;
}

int main(){
    int pos;
    while(cin >> pos&&pos!=-1){
        cout << "Please enter a position: ";
        int elem;
        if(Fibon_elem(pos,elem)){
            cout << "elem # " << pos << " is " << elem <<endl;
        } else{
            cout << "Sorry out of range!\n";
        }
    }
    return 0;
}