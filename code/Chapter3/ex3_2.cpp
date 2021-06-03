#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
using namespace std;



class LessThan{
public:
    bool operator()(const string &s1, const string &s2){
        return s1.size() < s2.size();
    }
};

template <typename elemType>
void display_word_count(const vector<elemType> &vec,ofstream &os){
    typename vector<elemType>::const_iterator iter = vec.begin(); // 注意这里的typename一定要加
    typename vector<elemType>::const_iterator end_it = vec.end();
    while(iter!=end_it){
        os << *iter++ << ' ';
    }
    os << endl;
}

int main(){
    ifstream ifile("/Users/swj93/CLionProjects/EssentialCpp/column.txt");
    ofstream ofile("/Users/swj93/CLionProjects/EssentialCpp/column_output.txt");
    if(!ifile){
        cerr << "打开文件失败！\n";
        return -1;
    }
    vector<string> text;
    string word;
    while (ifile >> word){
        text.push_back(word);
    }
    sort(text.begin(),text.end(),LessThan());
    display_word_count(text,ofile);
}