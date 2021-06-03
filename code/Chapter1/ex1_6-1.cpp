//
// Created by swj93 on 2021-04-26.
//

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int num, sum = 0;
    vector<int> vec;
    while(cin >> num && num != 0){
        vec.push_back(num);
    }
    for(int i = 0; i < vec.size(); i++){
        sum += vec[i];
    }
    cout << "Sum: " << sum << " Ave: " << (double) sum/vec.size();
}
