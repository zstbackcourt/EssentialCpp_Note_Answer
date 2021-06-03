#include <iostream>
#include "Stack.cpp"
using namespace std;

int main(){
    Stack stk;
    string str, result;

    while(cin >> str&& str!= "OK"){
        stk.push(str);
    }

    if(stk.empty()){
        cout << "Empty!\n";
        return 0;
    }

    stk.peek(result);
    cout << "Peek result is " << result << " Stack size is " << stk.size() <<endl;

    stk.pop(result);
    cout << "Pop result is " << result << " Stack size is " << stk.size() <<endl;
}




