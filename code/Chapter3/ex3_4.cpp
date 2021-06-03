#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

class even_elem{
public:
    bool operator()(int elem){
        return elem%2 ? false : true;
    }
};


int main(){
    vector<int> input = {2, 4, 5, 3, 9, 5, 2, 6, 8, 1, 8, 4, 5, 7, 3};
    vector<int>::iterator division = partition(input.begin(),input.end(),even_elem());
    ofstream even_file("/Users/swj93/CLionProjects/EssentialCpp/even.txt");
    ofstream odd_file("/Users/swj93/CLionProjects/EssentialCpp/odd.txt");
    if(!even_file||!odd_file){
        cerr << "打开文件失败\n";
        return -1;
    }
    ostream_iterator<int> even_iter(even_file,"\n");
    ostream_iterator<int> odd_iter(odd_file," ");
    copy(input.begin(),division,even_iter);
    copy(division,input.end(),odd_iter);
    return 0;
}