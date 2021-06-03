# Chapter3：泛型编程风格

泛型算法提供了可作用域容器类以及数组类型上的操作，这些算法之所以被称为泛型generic，是因为它们和它们想要操作的元素类型无关。

## 3.1 指针的算术运算

当数组被传给函数，或是由函数中返回，仅有第一个元素的地址会被传递。

假设我们有一个任务：（1）给定一个储存整数的vector，以及一个整数值，如果该值在vector中存在，在返回一个指针指向该值，反之则返回0；（2）想办法让这个函数不仅可以处理整数，还要可以处理任何类型；（3）同时该函数不仅可以处理vector还要可以处理array。

如果不使用函数重载的方式，则可以通过指针来处理。

```c++
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


template <typename T>
T* find(const T *start, const T *end, const T &value){
    // 查找value是否存在
    // 因为vector和araay都可以用指针来指示地址,因此直接使用指针就可以不用重载函数了
    // 使用指针时,可以利用指针运算
    if(!start || !end){
        return -1;
    }
    for(;start!=end;start++){
        if(*start == value){
            return start;
        }
    }
    return -1;
}


```

## 3.2 泛型指针Iterator(迭代器)

迭代器的目的是在低层指针的行为之上提供一层抽象，取代程序原本的“指针直接操作”方式。我们把底层指针的处理通通放在此抽象层中，让用户无需直接面对指针操作。

迭代器类可以当成指针使用，与指针的不同在于其提领（*），不等（!=），递增（++）是由迭代器内相关的inline函数提供。

每一个标准容器都提供一个名为begin()的操作函数，可以返回一个iterator指向第一个元素。end()操作函数会范围一个iterator指向最后一个元素。

```c++
vector<string> svec;
// iter指向一个vector，vector的元素类型为string
vector<string>::iterator iter = svec.begin();
// const_iterator则允许我们读取vector的元素,但是不允许任何写入操作
vector<string>::const_iterator iter = svec.begin();
```

## 3.3 所有容器的共通操作

（1）==、!=运算符，返回true/false

（2）赋值运算符

（3）empty()判断容器是否为空

（4）size()返回容器内目前持有的元素个数

（5）clear()删除所有元素

（6）begin()、end()

（7）inset()将单一或某个范围内的元素插入容器内

（8）erase()将容器内单一元素或某个范围内的元素删除

## 3.4 顺序容器

主要是list和vector，具体见文档。

## 3.5 泛型算法

要使用泛型算法首先要引入algorithm头文件，具体见文档。

## 3.6 设计泛型算法

#### Function Object

Function Object是某种class的实例对象，这类class对函数调用运算符做了重载操作，这样可使function object被当成一般函数来使用。function object实现了原本可能以独立函数加以定义的事物，主要是为了效率。我们可以领调用运算符称为inline，从而消除“通过函数指针来调用函数”时需要付出的额外代价。

想要使用标准库中定义的function object需要包含头文件functional，例如：

```c++
// greater<int>()就是一个class template object
sort(vec.begin(),vec.end(),greater<int>()); // 对vector中的元素降序排序

```

#### Function Object Adapter

function object adapter会对function object进行修改操作。所谓binder adapter绑定适配器会将function object的参数绑定至某特定值，使二元function object转化成一元function object。标准库提供了两个binder adapter:bind1st会将指定值绑定至第一操作数，bind2nd则将指定值绑定至第二操作数，例如：

```C++
vector<int> filter(const vector<int> &vec, int val, less<int> &lt){
		vector<int> nvec;
		vector<int>::const_iterator iter = vec.begin();
		// bind2nd(less<int> ,val)会把val绑定于less<int>的第二个参数上。
		// 于是,less<int>会将每个元素拿来和val比较
		while((iter = find_if(iter, vec.end(), bind2nd(lt,val)))!=vec.end()){
				// 每当iter != vec.end(),
				// iter指向某个小于val的元素
				nvec.push_back(*iter);
				iter++;
		}
		return nvec;
}
```

如果用函数模板来将filter()改成function template就可以更加泛型化。

另外一种adapter是negator，它会对function object的真伪值去翻。not1可对一元function object的真伪值去反，not2可对二元function object的真伪值取反。

# 3.7 Map

见文档

# 3.8 Set

见文档

# 3.9 使用Iterator Inserter

针对元素插入和复制，标准库提供了三个所谓的insertion adapter，使我们避免使用容器的assignment运算符。

（1）back_inserter()会以容器的push_back()函数取代赋值运算符，对于vector来说这是比较适合的inserter，传入的参数就是容器本身：

```C++
vector<int> result_vec;
unique_copy(ivec.begin(), ivec.end(), back_inserter(result_vec));
```

（2）inserter()会以容器的insert()函数取代赋值运算符。inserter()接收两个参数，一个是容器，另一个是iterator，指向容器内的插入操作起点：

```c++
vector<string> result_vec;
unique_copy(svec.begin(), svec.end(), inserter(result_vec, result_vec.end()));
```

（3）front_inserter()会以容器的push_front()函数取代赋值运算符，这个inserter只适用于list和deque：

```c++
list<int> ilist_res;
copy(ilist.begin(), ilist.end(), front_inserter(ilist_res));
```

要使用上述三种adapter需要包含头文件iterator，**注意：这些adapter不能用在array上，因为array不支持元素插入操作。**

# 3.10 iostream Iterator

从标准输入设备读取一串string元素，将它们存到vector内，并进行排序，最后再将这些字符串写回标准输出设备。

标准库定义了提供输入输出的iostream iterator类，称为istream_iterator和ostream_iterator，分别支持单一类型的元素读取和写入。使用这两个iterator class之前，要先包含iterator头文件。

#### 如何利用istream_iterator从标准输入设备读取字符串

我们需要一堆iterator:first和last，用来标示元素范围。定义：

```c++
istream_iterator<string> is(cin);
```

为我们提供了一个first iterator，它将is定义为一个“绑至标准输入设备”的istream_iterator，对于标准输入设备而言，end-of-file就代表，标示尧都区的最后一个元素的下一位置。只要在定义istream_iterator时不为它指定istream对象，便代表了end-of-file。例如：

```c++
istream_iterator<string> eof;
```

ostream_iterator，用来标示字符串元素的输出位置，一旦不再有任何元素需要输出，就停止输出操作。

```c++
ostream_iterator<string> os(cout, " ");
```

第二个参数标示各个元素被输出时的分隔。

以下是一个完整的程序，将text中的每个元素一一写到由os所表示的ostream，每个元素用空格分割开来。

```C++
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

int main(){
    istream_iterator<string> is(cin); // first
    istream_iterator<string> eof; // last
    vector<string> text;
    copy(is,eof,back_inserter(text));
    sort(text.begin(),text.end());
    ostream_iterator<string> os(cout, " ");
    copy(text.begin(),text.end(),os);
}
```

通常我们不是要从标准输入设备中读取再写入标准输出设备中去，而是要从文件中读取，再写到文件中去。此时只要将istream_iterator绑定至ifstream object，将ostream_iterator绑定至ofstream object即可。

```C++
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
```

#### 练习 3.1

写一个读取文本文件的程序，将文件中的每个单词存入map，map的key是单词，value是该单词在文本中的出现次数。再定义一份由”排除字眼“组成的set，其中包含诸如a\an\or\the\and和but之类的单词。将某单词放入map之前，先确定该单词并不在”排除字集“中。一旦文本文件读取完毕，请显示一份单词清单，并显示各单词的出现次数。你也可以再加以扩展，在显示单词之前，允许用户查询某个单词是否出现于文本文件中。

```c++
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
    ifstream ifile("/EssentialCpp/column.txt");
    ofstream ofile("/EssentialCpp/column_output.txt");
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
```

#### 练习 3.2

读取文本文件内容，并将内容存储与vector，以字符串长度为依据，对vector排序。定义一个function object并传给sort()；这一function object接受两个字符串，当第一字符串的长度小于第二个字符串的长度时，就返回true。最后打印排序后的vector内容。

```c++
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
```

#### 练习 3.3

定义一个map，以家庭姓氏为key，value是所有小孩的名字，令此map至少容纳六笔数据。允许用户根据姓氏来查询，并得以打印map内的每一笔数据。

```c++
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
    ifstream namefile("/families.txt");
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
```

#### 练习 3.4

编写一个程序，利用istream_iterator从标准输入设备读取一串整数。利用ostream_iterator将其中的技术写入文件，以控制分隔。将偶数写入另一个文件，每个数值单独放入一行。

```c++
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
    ofstream even_file("/EssentialCpp/even.txt");
    ofstream odd_file("/EssentialCpp/odd.txt");
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
```

