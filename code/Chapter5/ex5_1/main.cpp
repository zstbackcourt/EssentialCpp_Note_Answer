#include "Peekback_Stack.cpp"
#include "LIFO_Stack.cpp"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& os, const Stack &rhs){
    rhs.print();
    return os;
}

void peek(Stack &stk, int index){
    cout << endl;
    string t;
    if(stk.peek(index, t)){
        cout << "peek:" << t;
    }else{
        cout << "peek failed!";
    }
    cout << endl;
}

int main(){
    LIFO_Stack lifo_stack;
    string str;
    while(cin >> str && str!="-1"){
        lifo_stack.push(str);
    }
    cout << "\n" << "尝试调用LIFO_Stack的peek()" << endl;
    peek(lifo_stack,lifo_stack.top()-1);
    cout << lifo_stack;

    Peekback_Stack pstk;
    while(!lifo_stack.empty()){
        string tmp;
        if(lifo_stack.pop(tmp)){
            pstk.push(tmp);
        }
    }
    cout << "\n" << "尝试调用Peekback_Stack的peek()" << endl;
    peek(pstk,pstk.top()-1);
    cout << pstk;
}