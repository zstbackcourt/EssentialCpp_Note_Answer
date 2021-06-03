#include <iostream>
#include <map>
#include <set>
#include <string>
#include <fstream>
using namespace std;


void initialize_exclusion_set(set<string>&); // 初始化排除字集
void process_file(map<string,int>&, const set<string>&, ifstream&); // 处理文件
void user_query(const map<string,int>&);
void display_word_count(const map<string,int>&, ofstream&);


void initialize_exclusion_set(set<string> &exs){
    static string excluded_words[25] = {
            "the","and","but","that","then","are","been",
            "can","a","could","did","for","of",
            "had","have","him","his","her","its","is",
            "were","which","when","with","would"
    };
    exs.insert(excluded_words,excluded_words+25);
}

void process_file(map<string,int> &word_count, const set<string> &exclude_set, ifstream &ifile){
    string word;
    while(ifile>>word){
        if(exclude_set.count(word)){
            continue;
        }
        word_count[word] ++ ;
    }
}

void user_query(const map<string,int> &word_map){
    string search_word;
    cout << "输入一个你要查的单词,输入q退出";
    cin >> search_word;
    while(search_word.size()&&search_word!="q"){
        map<string,int>::const_iterator it;
        if((it = word_map.find(search_word)) != word_map.end()){
            cout << "找到了！ " << it->first
                 << "出现了 "   << it->second
                 << "次.\n";
        }
        else{
            cout << search_word << "不在文件中.\n";
        }
        cout << "继续么?(输入q退出)";
        cin >> search_word;
    }
}

void display_word_count(const map<string,int> &word_map,ofstream &os){
    map<string,int>::const_iterator iter = word_map.begin();
    map<string,int>::const_iterator end_it = word_map.end();
    while(iter!=end_it){
        os << iter->first << "("
           << iter->second << ")" <<endl;
        iter ++;
    }
    os << endl;
}

int main(){
    ifstream ifile("/Users/swj93/CLionProjects/EssentialCpp/column.txt");
    ofstream ofile("/Users/swj93/CLionProjects/EssentialCpp/column_output.txt");
    if(!ifile||!ofile){
        cerr << "无法打开文件!\n";
        return -1;
    }

    set<string> exclude_set;
    initialize_exclusion_set(exclude_set);

    map<string,int> word_count;
    process_file(word_count,exclude_set,ifile);
    user_query(word_count);
    display_word_count(word_count,ofile);
}