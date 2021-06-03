//
// Created by swj93 on 2021-04-28.
//

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(){
    ifstream inf("./data.txt");
    ofstream outf("./output.txt");

    if(!inf||!outf){
        cerr << "Open file failed!\n";
        return -1;
    }
    istream_iterator<string> is(inf); // 将istream_iterator绑定到ifstream object
    istream_iterator<string> eof; // 将istream_iterator绑定到ofstream object
    vector<string> text;
    copy(is,eof,back_inserter(text));
    sort(text.begin(),text.end());
    ostream_iterator<string> os(outf, " ");
    copy(text.begin(),text.end(),os);
    cout<< "Finished!\n";
}




