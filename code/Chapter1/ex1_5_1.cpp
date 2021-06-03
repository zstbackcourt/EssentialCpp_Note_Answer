//
// Created by swj93 on 2021-04-26.
//

#include <iostream>
#include <string>
using namespace std;

int main() {
    string user_name;
    cout << "Please enter your name: ";
    cin >> user_name;
    switch (user_name.size()){
        case 0:
            cout << "Error! Your name size is 0!\n";
            break;
        case 1:
            cout << "Error! Your name size is 1!\n";
            break;
        default:
            cout << "Hello, " << user_name << endl;
            break;
    }
    return 0;
}
