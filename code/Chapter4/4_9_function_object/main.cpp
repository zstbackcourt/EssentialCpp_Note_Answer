#include <iostream>
#include <vector>
#include <iterator>
#include "LessThan.cpp"
using namespace std;


int count_less_than(const vector<int> &vec, int comp){
    LessThan lt(comp); // LessThan object的定义方式和定义一般对象没有两样,定义一个LessThan的class object
    int count = 0;
    for(int i = 0; i < vec.size(); i++){
        if(lt(vec[i])){
            // 将function call运算符应用于对象上,调用function call运算符
            ++count;
        }
    }
    return count;
}


void print_less_than(const vector<int> &vec, int comp, ostream &os = cout){
    // 把function object当做参数传给泛型算法例子
    LessThan lt(comp);
    vector<int>::const_iterator iter = vec.begin();
    vector<int>::const_iterator it_end = vec.end();
    os << "elements less than " << lt.comp_val() << endl;
    while((iter = find_if(iter,it_end,lt)) != it_end){
        // 把function object当做参数传给泛型算法
        os << *iter << " ";
        ++iter;
    }
}

int main(){
    int arr[16] = {17,12,44,9,18,45,6,14,23,67,9,0,27,55,8,16};
    vector<int> vec(arr,arr+16);
    int comp_val = 20;
    cout << "Num of elements less than " << comp_val << " are " << count_less_than(vec, comp_val) <<endl;
    print_less_than(vec,comp_val);
    return 0;
}




