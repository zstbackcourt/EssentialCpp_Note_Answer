//
// Created by swj93 on 2021-04-26.
//

#include <iostream>
using namespace std;



const char* msg2user(int num){
    const int n = 4;
    static const char* msgArr[n] = {
            "Error 1",
            "Error 2",
            "Error 3",
            "Error 4"
    };
    if(num<=0){
        return "Yeah, you made it!\n";
    }else if(num>=5){
        return "Error more than 4!\n";
    }else{
        return msgArr[num-1];
    }
}

int main() {
    int num;
    cin >> num;
    cout << msg2user(num);
    return 0;
}
