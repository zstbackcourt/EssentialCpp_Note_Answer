# Chapter2： 面向过程的编程风格

## 2.1 撰写函数

每一个函数必须定义4个部分：返回类型、函数名、参数列表、函数主体

函数必须先被声明，然后才能被调用。下面是一个Fibonacci数列的函数的例子：

```c++
#include <iostream>
using namespace std;


bool Fibon_elem(int pos, int &elem){
    // 检查位置值是否合理
    if(pos <= 0|| pos > 1024){
        elem = 0;
        return false;
    }
    elem = 1;
    int n = 1, m = 1;
    for(int i = 3;i<=pos;i++){
        elem = n+m;
        n = m;
        m = elem;
    }
    return true;
}

int main(){
    int pos;
    cout << "Please enter a position: ";
    cin >> pos;
    int elem;
    if(Fibon_elem(pos,elem)){
        cout << "elem # " << pos << " is " << elem <<endl;
    } else{
        cout << "Sorry out of range!\n";
    }
    return 0;
}
```

#### 练习2.1

改写上述main()，使得用户输入-1时才停止。

```c++
#include <iostream>
using namespace std;


bool Fibon_elem(int pos, int &elem){
    // 检查位置值是否合理
    if(pos <= 0|| pos > 1024){
        elem = 0;
        return false;
    }
    elem = 1;
    int n = 1, m = 1;
    for(int i = 3;i<=pos;i++){
        elem = n+m;
        n = m;
        m = elem;
    }
    return true;
}

int main(){
    int pos;
    while(cin >> pos&&pos!=-1){
        cout << "Please enter a position: ";
        int elem;
        if(Fibon_elem(pos,elem)){
            cout << "elem # " << pos << " is " << elem <<endl;
        } else{
            cout << "Sorry out of range!\n";
        }
    }
    return 0;
}
```

​	

## 2.2 调用函数

值传递(by value)和地址传递(by reference)。

当我们调用一个函数时，会在内存中建立起一块称为“程序栈”的区域，这块区域提供了每个函数参数的存储空间，它也提供函数所定义的每个对象的内存空间，这些对象被称为局部对象，一旦函数完成，这块内存就会被释放掉，或者说是从程序堆栈中被pop出来。

当我们用传值的方式传入参数是，默认情况下其值会被复制一份，称为参数的局部性定义，因此此时函数中的操作对象和实际的参数没有发生任何关联。如果想要函数操作的对象为实际的参数，则需要通过地址传递的方式来达到这个目的，最简单的方法是将参数声明为一个reference(引用)。

例如：

```c++
void swap(int & val1, int & val2){
		int tmp = val1;
		val1 = val2;
		val2 = tmp;
}
```

#### Pass by Reference语义

```c++
int ival = 1024; // 对象,int类型
int *pi = &ival; // 指针,指向一个int对象
int &rval = ival; // 引用,代表一个int对象
```

当我们以by reference的方式传递对象当做函数参数，对象本身并不会复制出另一份，复制的是对象的地址，函数中对该对象进行的任何操作，都相当于是对传入的对象进行间接操作。

例如，我们可以将要输出的vector以引用的方式传入：

```c++
void display(const vector<int> &vec){
		for(int i = 0;i<vec.size();++i){
				cout << vec[i] << ' ';
		}
		cout << endl;
}
```

也可以用将vector以指针的形式传递，这和以引用的方式传递效果相同，唯一的差别在于reference和pointer的用法不同：

```c++
void display(const vector<int> *vec){
		if(!vec){
        // 一定要先判断pointer是不是空的
				cout << "vector is empty!\n";
		}
		for (int i = 0;i< vec.size();++i){
				cout << (*vec)[i] << ' '; // 注意vec是一个指针,因此要用*vec来获取指向的对象
		}
		cout << endl;
}
```

#### 作用域与范围

函数内定义的对象，只存在于函数执行期间，是局部对象，局部对象的地址是不能返回的，否则就会报错。局部对象只能返回值。

#### 动态内存管理

不论是local scope还是file scope，都是系统自动管理的。第三种储存形式称为动态范围dynamic extent，其内存使用程序的空闲空间分配而来，有时也称为堆内存。这种内存必须由程序员自行管理，其分配通过new表达式来完成，而其释放则通过delete表达式来完成。

new表达式形式如下：

```c++
new Tpye:		
```

此处的Type可以为任意内置类型，也可以是程序已经定义的class类型，new表达式也可以写成：

```c++
new Type(initial_value);
```

例如：

```c++
int *pi;
pi = new int;
```

这样就是先由堆分配出一个类型为int的对象，再将其地址复制给pi。

```c++
pi = new int(1024);
```

这样则是指定了初始值，pi所指的对象的初始值为1024.

如果要从堆中分配数组则：

```C++
int *pia = new int[24]; // array size为24
```

用new分配的地址，一定要用delete释放，否则将永远不会被释放

```c++
delete pi;
delete []pia; //删除数组中的所有对象一定要[] 
```

## 2.3 默认参数

默认参数的提供有两个原则：

（1）如果某个参数有默认值，那么该参数右边的所有参数都应该有默认值；

（2）默认值只能指定一次，可以在函数声明时指定，也可以在函数定义出指定，但是不能两个地方同时指定；

通常函数声明会放在头文件中。

## 2.4 局部静态对象

local static object，例如：

```c++
const vector<int>* fibon_seq(int size){
		static vector<int> elems; // 局部静态对象
		return &elems;
}
```

elems被定义为局部静态对象，局部静态对象所处的内存空间，即使在不同的函数调用过程中，依然持续存在，因此可以安全的将elems的地址返回。

## 2.5 inline内联函数

内联函数和普通函数的区别在于，当编译器处理内联函数的语句时，不会将该语句编译，而是直接将函数体代码插入调用语句处。因此内联函数一般而言是体积很小的函数，而且事实上你可以将所有的函数都声明为内联函数，因为某一个函数最终是否被作为内联函数进行执行取决于编译器而不是用户本身。但是需要注意的是，内联函数的定义常常放在头文件中，因为编译器必须在它被调用的时候加以展开，因此这个时候该函数的定义必须是有效的。

## 2.6 重载函数

某一个函数是否被重载取决于参数列表而不是返回值类型。

## 2.7 函数模板

函数模板，function template将参数列表中指定的全部（或者部分）参数的类型信息抽离出来。函数模板以关键字template开场，其后紧接着以成对尖括号（<>）包围起来的一个或者多个标识符。这些标识符用以表示我们希望推迟决定的数据类型。用户每次利用这一模板产生函数，都必须提供确实的类型信息。实际上，这些标识符扮演着占位符的角色，用来放置函数参数列表以及函数体中某些实际数据类型，例如：

```c++
template <typename elemType>
void display_message(const string &msg, const vector<elemType> &vec){
		cout << msg;
		for(int i = 0;i < vec.size();++i){
				elemType t = vec[i];
				cout << t << ' ';
		}
}
```

关键字typename表示，elemType在函数display_message()中是一个咱叔放置类型的占位符，elemType是一个任意名称。通常函数模板的参数列表由两种类型构成，一类是明确的类型如msg，一类是暂缓决定的类型。

当然，函数模板可以进一步进行函数重载。

## 2.8 函数指针

函数指针必须指明其函数的返回类型以及参数列表。例如：

```c++
const vector<int>* (*seq_ptr)(int);
```

这里seq_ptr是一个函数，参数列表中只有一个int类型的参数，const vector<int>* 表示函数的返回值是一个指向const vector的指针，(*seq_ptr)表示这是一个指向函数的指针。

例如：

```c++
bool seq_elem(int pos, int &elem, const vector<int>* (*seq_ptr)(int)){
		// 调用seq_ptr所指的函数
		const vector<int> *pseq = seq_ptr(pos);
		if(!pseq){
				elem = 0;
				return false;
		}
		elem = (*pseq)[-1];
		return true;
}
```

如果我们个函数指针赋予初值0，则表示该指针初始时并没有指向任何函数。

```c++
// 将pell_seq()的地址复制给seq_ptr
seq_ptr= pell_seq;
```

## 2.9 设定头文件

我们把函数声明放在头文件中，并在相应的程序代码文件内include这些函数声明。函数的定义只能有一份，但是可以有许多份声明，我们不把函数的定义放入头文件，因为同一个程序的多个代码文件可能都会包含这个头文件。**注意：inline函数的定义一定要放在头文件中。**

在file scope内定义的对象，如果可能被多个文件访问，也需要被声明在头文件中。注意同函数一样，一个对象只能在程序中北定义一次，因此对象的定义一定要放在程序代码文件中。故，需要在对象的定义前加上关键字extern，将其标称一个声明。但是const对象例外。

如果头文件被认定为标准的或者项目专属的头文件，就用尖括号进行include，编译器搜索此文件时，会先在某些默认的磁盘目录中寻找。如果文件名有成对的双引号括住，此文件便被认为是一个用户提供的头文件；搜索此文件时，会由要包含此文件的文件所在的磁盘目录开始找起。

#### 练习2.2

数列的求值公式为$P(n)=n(3n-1)/2$，借此产生1，5，12，22，35等元素值。定义一个函数，利用上述公式，将产生的元素放到用户传入的vector之中，元素个数由用户指定。请检查元数个数的有效性。然后编写第二个函数，将给定的vector的所有元素一一打印，此函数第二参数接受一个字符串，表示存放在vector内的数列的类型。最后编写main函数，测试这两个函数。

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;

bool Pentagonal(vector<int> &vec, int pos){
    if(pos<0||pos>64){
        cerr << "Error pos!\n";
        return false;
    }
    for(int i = 0;i<pos;i++){
        vec.push_back((i*(3*i-1))/2);
    }
    return true;
}

void print(vector<int> &vec, const string &s){
    cout << "iter: " << s << ":\n";
    for(int num:vec){
        cout << num << ',';
    }
    cout << endl;
}

int main(){
    int pos, i = 0;
  	cout << "Please enter a position: ";
  	cin >> i;
  	vector<int> vec;
  	Pentagonal(vec,pos);
  	print(vec,to_string(i));
    return 0;
}
```

#### 练习2.3

将练习2.2的Pentagonal数列求值函数拆分为两个函数，其中之一是inline，用来检验元素个数是否合理，如果合理且尚未被计算，便执行第二个函数，执行实际的求值工作。

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;



void Pentagonal(vector<int> &vec, int pos){
    for(int i = 0;i<pos;i++){
        vec.push_back((i*(3*i-1))/2);
    }
}


inline bool Cal(vector<int> &vec, int pos){
    if(pos<0||pos>64){
        cerr << "Error pos!\n";
        return false;
    }

    if(vec.size()<pos){
        Pentagonal(vec,pos);
    }
    return true;
}

void print(vector<int> &vec, const string &s){
    cout << "iter: " << s << ":\n";
    for(int num:vec){
        cout << num << ',';
    }
    cout << endl;
}

int main(){
    int pos, i = 0;
  	cout << "Please enter a position: ";
    cin >> i;
  	vector<int> vec;
  	Pentagonal(vec,pos);
  	print(vec,to_string(i));
    return 0;
}
```

#### 练习2.4 

写一个函数，以局部静态的vector存储Pentagonal数列元素，此函数返回一个const指针，指向该vector。如果vector的大小小于指定的元素个数，就扩充vector的大小。接下来再实现第二个函数，接受一个位置值，返回该位置上的元素。

```c++
#include <iostream>
#include <string>
#include <vector>
using namespace std;

inline bool check(int pos){
    // 检查pos是否合理
    return (pos<=0||pos>64) ? false : true;
}


const vector<int>* Pentagonal(int pos){
    static vector<int> vec; // 局部静态对象
    if(check(pos) && (pos>vec.size())){
        for(int i = vec.size()+1 ; i<=pos; i++){
            vec.push_back((i*(3*i-1))/2);
        }
    }
    return &vec; // 返回指针
}


int Cal(int pos){
    if(!check(pos)){
        cerr << "Error pos!\n";
        return -1;
    }
    const vector<int> *ptr = Pentagonal(pos); // 函数指针
    return (*ptr)[pos-1];
}

void print(int pos){
    cout << " Pos: " << pos << " " << Cal(pos);
}

int main(){
    int pos;
    cout << "Please enter a position: ";
    cin >> pos;
    print(pos);
    return 0;
}
```

#### 练习2.5 

实现一个重载的max函数，让它接受以下参数:（1）两个整数，（2）两个浮点数，（3）两个字符串，（4）一个整数vector，（5）一个浮点数vector，（6）一个字符串vector，（7）一个整数数组，以及一个表示数组大小的整数值，（8）一个浮点数数组，以及一个表示数组大小的整数值，（9）一个字符串数组，以及一个表示数组大小的整数值。

```c++
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

inline int max(int a, int b){
    return a > b ? a : b;
}

inline float max(float a, float b){
    return a > b ? a : b;
}

inline string max(const string &s1, const string &s2){
    return s1 > s2 ? s1 : s2;
}

inline int max(const vector<int> &vec){
    return *max_element(vec.begin(),vec.end()); // *max_element返回vector中最大值,如果没有*表示地址
}

inline float max(const vector<float> &vec){
    return *max_element(vec.begin(),vec.end());
}

inline string max(const vector<string> &vec){
    return *max_element(vec.begin(),vec.end());
}

inline int max(const int *arr, int size){
    return *max_element(arr,arr+size);
}

inline float max(const float *arr, int size){
    return *max_element(arr,arr+size);
}

inline string max(const string *arr, int size){
    return *max_element(arr,arr+size);
}
```

#### 练习2.6 

用template改写练习2.5

```c++
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


template <typename numT>
inline numT max(numT &t1, numT &t2){
    return t1 > t2 ? t1 : t2;
}

template <typename vecT>
inline vecT max(const vector<vecT> &vec){
    return *max_element(vec.begin(),vec.end());
}

template <typename arrT>
inline arrT max(const arrT *arr, int size){
    return *max_element(arr, arr+size);
}

int main(){
    int int_t1 = 23, int_t2 = 54;
    float float_t1 = 33.4, float_t2 = 13.4;
    string s1 = "aefc", s2 = "afew";
    vector<string> svec = {
            "dadfasdf",
            "asdfwer",
            "dasdfasdf"
    };
    vector<int> ivec = {1,3,4,23,2};
    int arr[4] = {32,41,12,44};
    cout << "Int: " << max(int_t1,int_t2) << '\n'
         << "Float: " << max(float_t1, float_t2) << '\n'
         << "String: " << max(s1,s2) << '\n'
         << "sVec: " << max(svec) << '\n'
         << "iVec: " << max(ivec) << '\n'
         << "Arr: " << max(arr,4)
         << endl;
}
```

