//
// Created by swj93 on 2021-04-26.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ifstream infile("/Users/swj93/CLionProjects/EssentialCpp/data.txt");
    if(!infile){
        cerr << "Open file data.txt failed !\n";
        return -1;
    }
    ofstream ofile("/Users/swj93/CLionProjects/EssentialCpp/data_sorted.txt");
    if(!ofile){
        cerr << "Open file data_sorted.txt failed !\n";
        return -2;
    }
    vector<string> vec;
    string curr;
    while(infile >> curr){
        vec.push_back(curr);
    }
    for(string istr:vec){
        cout<< istr << " ";
    }
    cout<<"\n"
        <<"print finished!\n";
    sort(vec.begin(),vec.end());
    for(string ostr:vec){
        ofile << ostr << " ";
    }
    ofile << endl;
    cout << "output finished!\n";
}
