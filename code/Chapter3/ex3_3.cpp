#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <fstream>
using namespace std;



void read_file(ifstream &filename, map<string,vector<string>> &families){
    string textline;
    while(getline(filename,textline)){
        string fam_name;
        vector<string> child;
        string::size_type pos = 0;
        string::size_type prev_pos = 0;
        string::size_type text_size = textline.size();

        while((pos = textline.find_first_of(' ',pos))!=string::npos){
            // 找出空格符分隔所有单词
            string::size_type end_pos = pos - prev_pos; // 计算子字符串的终点
            if(!prev_pos){
                fam_name = textline.substr(prev_pos,end_pos);
            } else{
                child.push_back(textline.substr(prev_pos,end_pos));
            }
            prev_pos = ++pos;
        }
        if(prev_pos<text_size){
            child.push_back(textline.substr(prev_pos,pos-prev_pos));
        }
        if(!families.count(fam_name)){
            families[fam_name] = child;
        }else{
            cerr << "错误,map中已经有 " << fam_name << endl;
        }
    }
}

void display_map(const map<string,vector<string>> &families, ostream &os){
    map<string,vector<string>>::const_iterator it = families.begin();
    map<string,vector<string>>::const_iterator end_it = families.end();

    while(it!=end_it){
        os << it->first << " 家庭";
        if(it->second.empty()){
            os << "没有孩子\n";
        }else{
            os << "有" << it->second.size() << "个孩子,分别是:" << endl;
            for(auto ch:it->second){
                os << ch << " ";
            }
            os << endl;
        }
        ++ it;
    }
}

void query_map(const string &family, const map<string,vector<string>> &families){
    map<string,vector<string>>::const_iterator it =families.find(family);
    if(it == families.end()){
        cout << family << "不在map中\n";
        return;
    }
    cout << family << "在map中\n";
}

int main(){
    map<string,vector<string>> families;
    ifstream namefile("/Users/swj93/CLionProjects/EssentialCpp/families.txt");
    if(!namefile){
        cerr << "文件打开失败\n";
        return -1;
    }
    read_file(namefile,families);
    string fam;
    while(1){
        cout << "输入你要查找的家庭(q退出):";
        cin >> fam;
        if(fam == "q"){
            break;
        }
        query_map(fam,families);
    }
    display_map(families,cout);
};