//
// Created by swj93 on 2021-04-26.
//

#include <iostream>
using namespace std;

int main() {
    int num, i = 0, sum = 0;
    const int size = 128;
    int arr[size];
    while(cin >> num && num !=0 && i < size){
        arr[i++] = num;
    }
    for(int j = 0; j<i ; ++j){
        sum += arr[j];
    }
    cout << "Sum: " << sum << " Ave: " << (double) sum/i;
}
