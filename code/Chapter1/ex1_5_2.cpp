//
// Created by swj93 on 2021-04-26.
//

#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

int main() {
    const int max_n = 127; // 定义名字最大长度
    char user_name[max_n]; // 用户名
    cout << "Please enter your name: ";
    cin >> setw(max_n) >> user_name;
    switch (strlen(user_name)){
        case 0:
            cout << "Error username!\n";
            break;
        case 1:
            cout << "Error username!\n";
            break;
        case 127:
            cout << "Username is too long, and should be shortten!\n";
            // 不用break用于直接执行default
        default:
            cout << "Hello, "
                 << user_name <<endl;
            break;
    }
    return 0;
}
