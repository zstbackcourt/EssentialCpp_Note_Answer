//
// Created by swj93 on 2021-04-26.
//

#include <iostream>
#include <string>
using namespace std; // 标准库的命名空间,命名空间用于防止发生命名冲突问题

int main() {
    string user_name;
    cout << "Please enter your first name: ";
    cin >> user_name;
    cout << '\n'
         << "Hello, "
         << user_name
         << ".. and goodbye!\n";
    return 0;
}