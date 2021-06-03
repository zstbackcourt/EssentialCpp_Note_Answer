# Chapter4：基于对象的编程

## 4.1 实现一个Class

class的前置声明，只是将class名称告诉编译器，并不用提供此class的任何其他信息，前置声明使我们可以进行类指针的定义，或以此class作为数据类型：

```c++
class Stack;  // 前置声明
Stack *pt = 0;
void process(const Stack&);
```

class本身定义：

```c++
class Stack{
public:
		// ...public接口
private:
		// ...private接口
}
```

所有的成员函数必须在class主体内进行声明，至于是否要同时进行定义，可自由决定。如果要在class主体内定义，这个成员函数会自动的被视作inline函数。而如果要在class主体之外定义成员函数，必须使用特殊语法，指定该函数属于哪一个class，例如：

```c++
bool Stack::pop(string &elem){
		// 函数主体
}
```

#### 练习4.1

建立Stack.h和Stack.cpp，实现push、pop、peek并在main函数中调用

Stack.h:

```c++
#ifndef ESSENTIALCPP_STACK_H
#define ESSENTIALCPP_STACK_H

#include <string>
#include <vector>
using namespace std;

class Stack{
public:
    bool push(const string &elem);
    bool pop(string &elem);
    bool peek(string &elem);
    bool empty() const {
        // 这里的const表示不可以修改class的成员
        return _stack.empty();
    }
    bool full() const {
        return _stack.size() == _stack.max_size();
    }
    int size() const {
        return _stack.size();
    }

private:
    vector<string> _stack;
};


#endif //ESSENTIALCPP_STACK_H

```

Stack.cpp

```c++
#include "Stack.h"


bool Stack::push(const string &elem) {
    if(full()){
        return false;
    }
    _stack.push_back(elem);
    return true;
}

bool Stack::pop(string &elem) {
    if(empty()){
        return false;
    }
    elem = _stack.back();
    _stack.pop_back();
    return true;
}

bool Stack::peek(string &elem) {
    if(empty()){
        return false;
    }
    elem = _stack.back();
    return true;
}
```

main.cpp

```c++
#include <iostream>
#include "Stack.cpp"
using namespace std;

int main(){
    Stack stk;
    string str, result;

    while(cin >> str&& str!= "OK"){
        stk.push(str);
    }

    if(stk.empty()){
        cout << "Empty!\n";
        return 0;
    }

    stk.peek(result);
    cout << "Peek result is " << result << " Stack size is " << stk.size() <<endl;

    stk.pop(result);
    cout << "Pop result is " << result << " Stack size is " << stk.size() <<endl;
}

```

#### 练习4.2

给Stack class增加find和count两个成员函数

```c++
#ifndef ESSENTIALCPP_STACK_H
#define ESSENTIALCPP_STACK_H

#include <string>
#include <vector>
#include <iterator>
using namespace std;

class Stack{
public:
    bool push(const string &elem);
    bool pop(string &elem);
    bool peek(string &elem);
    bool find (const string &elem) const ;
    int count(const string &elem) const ;
    bool empty() const {
        // 这里的const表示不可以修改class的成员
        return _stack.empty();
    }
    bool full() const {
        return _stack.size() == _stack.max_size();
    }
    int size() const {
        return _stack.size();
    }


private:
    vector<string> _stack;
};
#endif //ESSENTIALCPP_STACK_H

```

```C++
#include "Stack.h"


bool Stack::push(const string &elem) {
    if(full()){
        return false;
    }
    _stack.push_back(elem);
    return true;
}

bool Stack::pop(string &elem) {
    if(empty()){
        return false;
    }
    elem = _stack.back();
    _stack.pop_back();
    return true;
}

bool Stack::peek(string &elem) {
    if(empty()){
        return false;
    }
    elem = _stack.back();
    return true;
}

bool Stack::find(const string &elem) const{
    vector<string>::const_iterator iter = _stack.begin();
    for(;iter!=_stack.end();iter++){
        if(*iter == elem){
            return true;
        }
    }
    return false;
}

int Stack::count(const string &elem) const {
    vector<string>::const_iterator iter = _stack.begin();
    int res = 0;
    for(;iter!=_stack.end();iter++){
        if(*iter == elem){
            res ++ ;
        }
    }
    return res;
}
```

## 4.2 构造函数与析构函数

构造函数名称必须与class名称相同，且不指定返回类型，不返回任何值。构造函数可以被重载。默认构造函不需要任何参数，这意味着默认构造函数可能不接受任何参数，或者为每个参数提供了默认值。

#### 成员初始化列表

推荐使用这种方式编写构造函数，成员初始化列表紧接在参数列表最后的冒号后面，是个以逗号分隔的列表。其中欲赋值给成员的数值被放在成员名称后面的小括号中：

```c++
class Triangular{
public:
		Triangular(int len, int bp):_len(len),_beg_pos(bp),_next(bo-1);
private:
		int _len, _beg_pos, _next;
};
```

析构函数和构造函数一样，没有返回值，且析构函数没有任何参数，也绝不能被重载。

#### 拷贝构造函数

我们常常会以某个class object作为另外一个object的初值，这时就需要使用拷贝构造函数将成员数据一一复制。拷贝构造函数唯一的参数是一个const reference，指向一个class object：

```c++
class Triangular{
public:
		Triangular(Triangular &tri):_len(tri._len),_beg_pos(tri._beg_pos),_next(tri._next);
private:
		int _len, _beg_pos, _next;
};
```

## 4.3 mutable可变与const不可变

想要保证成员函数不改变class object的值，则需要在成员函数身上标注const，以此告诉编译器，这个成员函数不会更改class object的内容。const修饰符紧接于函数参数列表之后。凡是在class主体以外定义者，如果它是一个const成员函数，就必须同时再声明与定义中指定const。

#### Mutable Data Member

如果class object是const的，但是我们又确实需要对它的成员变量进行修改，则在定义时用mutable关键字进行修饰：

```c++
class Triangular{
public:
		void next_rest() const{_next = _beg_pos - 1};
private:
		mutable int _next; // 这样即使是next_rest()被声明为const的,也可以对_next进行修改
		int _beg_pos;
		int _len;
};
```

## 4.4 this指针

this指针在成员函数内用来指向其调用者，在成员函数内，this指针可以让我们访问其调用者的一切。

## 4.5 静态类成员

静态类成员用来表示唯一的、可共享的member，它可以在同一类的所有对象中被访问。对于class而言，静态类成员只有唯一的一份实体，因此我们必须在程序代码文件中提供其清楚的定义。这种定义看起来很像全局对象，唯一的差别是，其名称必须附上class scope运算符。

#### 静态成员函数

静态成员函数可以在于任何类对象无联系的情形下被调用，但是注意只有在不访问任何非静态成员数据的情况下成员函数才可以被定义为静态成员函数，也就是说静态成员函数只能访问静态成员数据。

注意，当我们在class主体外部进行静态成员函数的定义时，不用重复加上关键字static，只需要在声明时加上该关键字。这个规则同样适用于静态成员数据。

## 4.6 运算符重载

运算符重载的规则：

（1）不可以引入新的运算符；

（2）运算符的操作数幕不可改变；

（3）运算符的优先级不可改变；

（4）运算符函数的参数列中，必须至少有一个参数为class型类别，也就是说，我们无				  法为诸如指针之类的non-class类别重新定义其原已存在的运算符，更不能为它引				  进新运算符。

重载的运算符是带有特殊名称的函数，函数名是由关键字 operator 和其后要重载的运算符符号构成的。与其他函数一样，重载运算符有一个返回类型和一个参数列表。例如：

```c++
Box operator+(const Box&);
```

大多数的重载运算符可被定义为普通的非成员函数或者被定义为类成员函数。如果我们定义上面的函数为类的非成员函数，那么我们需要为每次操作传递两个参数。

```c++
Box operator+(const Box&, const Box&);
```

也就是说，对于一个重载的运算符函数来说，它或者是类的成员，或者至少含有一个类类型的参数。如果重载的运算符函数是成员函数，则它的第一个（左侧）运算对象绑定到隐式的this指针上。

#### 嵌套类型Nested Type

typedef可以为某个类型设定另一个不同的名称。通用形式为：

```c++
typedef existing_tpye new_name;
```

将类型existing_tpye新设定名称为new_name。

## 4.7 友元

任何class都可以将其他的函数或者类指定为自己的友元friend，friend具备了与类成员函数相同的访问权限，可以访问class的private member。只要在某个函数的原型钱加上关键字friend就可以将它声明为某个class的friend。这个声明可以出现在class定义的任意位置上，不受private或者public的影响。如果希望将数个重载函数都声明为某个class的友元，则必须明确的为每个函数加上关键字friend。

例如：

```c++
class Triangular{
		friend int Triangular_iterator::operator*();
  	friend void Triangular_iterator::check_integrity();
  	friend void Triangular_iterator::check_integrity(int &val);
		...
}
```

为了让上述定义成功编译，我们必须在上述三行之前，先提供Triangular_iterator的定义让Triangular知道，否则编译器就没有足够的信息可以确定上述两个函数原型是否正确，也无法确定它们是否的确是Triangular_iterator的成员函数。

类的友元函数是定义在类外部，但是访问类的所有private成员和protected成员。尽管友元函数的原型在类的定义中出现过，但友元函数不是成员函数。如果一个class被定义成友元则它的所有成员都是友元。

我们也可以令class A与class B建立有缘关系，借此让class A的所有成员函数都成为class B的友元，例如：

```c++
class Triangular{
		// 以下造成Triangular_iterator的所有成员函数都成为Triangular的友元
		friend class Triangular_iterator;
}
```

如果以这种形式来声明class之间的友谊，就不需要在友谊声明之前先显现class的定义。

**注意：**

友元函数的使用：

因为友元函数没有this指针，则参数要有三种情况：

（1）要访问非static成员时，要类对象做参数；

（2）访问static成员或全局变量，不需要类对象做参数；

（3）可直接调用友元函数，不需要对象或指针。

## 4.9 function object

所谓function object是一种“提供function call运算符”的class。

function call运算符可接受任意个数的参数，下面一个function call运算符的实现，测试传入值是否小于某指定值。将此class命名为LessThan，其每个对象都必须被初始化为某基值。此外，也提供该基值的读取以及写入操作。

```c++
#ifndef ESSENTIALCPP_LESSTHAN_H
#define ESSENTIALCPP_LESSTHAN_H

class LessThan{
public:
    LessThan(int val):_val(val){}
    int comp_val() const { return _val;} // 基值的读取
    void comp_val(int nval){_val = nval;} // 基值的写入

    bool operator()(int value) const ;
private:
    int _val;
};

#endif //ESSENTIALCPP_LESSTHAN_H
```

 

```c++
#include "LessThan.h"

inline bool LessThan::operator()(int value) const {
    return value < _val;
}
```

```c++
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

```

## 4.10 重载iostream运算符

我们如果希望对某个class object进行读取和写入操作，需要对output运算符进行重载，例如：

```c++
ostream& operator<<(ostream &os, const Triangular &rhs){
		os << "(" << rhs.beg_pos() << ", "
			 << rhs.length() << " )";
		
		rhs.display(rhs.length(), rhs.beg_pos(), os);
		return os;
}
```

参数列表中的两个对象皆是地址传递方式传入，其中的ostream对象并没有声明为const，因为每个output操作都会更改ostream对象的内部状态。至于rhs这种将要被输出的对象，就会被声明为const——因为这里使用的是地址传递的目的是为了提高效率而不是为了修改其对象内容。**这里为什么不把output运算符设计为一个成员函数呢，因为作为一个成员函数，其做操作数必须隶属于同一个class的对象，如果output运算符被设计为类的成员函数就会对用户造成困扰。**

input运算符的重定义同output运算符一致，但是考虑读入数据可能存在的问题，因此需要设计错误检验。

## 4.11 指向类成员函数的指针

指向成员函数的指针除了需要指定返回类型和参数列表还要指定它所指的究竟是哪一个class，例如：

```c++
void(num_sequence::*pm)(int) = 0;
```

将pm声明为一个指针，指向num_sequence的成员函数，后者的返回类型是void，并且只接受单一参数，参数类型为int，pm的初始值为0，表示它目前不指向任何成员函数。我们可以通过typedef对代码进行简化，例如：

```c++
typedef void(num_sequence::*PtrType)(int);
PtrType pm = 0;
```

这就是将PtrType声明为一个指针，指向num_sequence的成员函数，后者的返回类型是void，只接受一个int参数。这种声明方式和先前的声明方式完全相同。

如果num_sequence提供以下六个成员函数，每一个都可由PtrType指针加以定位：

```c++
class num_sequence{
public:
    typedef void (num_sequence::*PtrType)(int);
    // _pmf可以指向下列任何一个函数
    void fibonacci(int);
    void pell(int);
    void lucas(int);
    void triangular(int);
    void sequare(int);
    void pentagonal(int);
private:
    PtrType _pmf;
};
```

为了取得某个成员函数的地址，我们队函数名称应用取址运算符，注意函数名称钱必须先以class scope运算符加以限定，至于返回类型和参数列表皆不必指明。例如，如果要定义一个指针，并令它指向成员函数fibonacci()，我们可以这么写：

```c++
PtrType pm = &num_sequence::fibonacci;
```

同理，如果要指定pm的值，可以这么写：

```c++
pm = &num_sequence::triangular;
```

指向成员函数的指针和指向函数的指针有一个不同点是，前者必须通过同一类的对象加以调用，而该对象便是次成员函数内的this指针所指之物。

#### 练习 4.3

考虑以下所定义的全局数据：

String program_name;

string version_stamp;

int version_number;

int tests_run;

int tests_passed;

编写一个用以包装这些数据的类。

```C++
#ifndef ESSENTIALCPP_GLOBALWRAPPER_H
#define ESSENTIALCPP_GLOBALWRAPPER_H

#include <string>
class globalWrapper{
public:
    static int tests_passed() { return _tests_passed;}
    static int tests_run() { return  _tests_run;}
    static int version_number() { return _version_number;}
    static string version_stamp() { return _version_stamp;}
    static string program_name() { return _program_name;}

    static void tests_passed(int val) { _tests_passed = val;}
    static void tests_run(int val) { _tests_run = val;}
    static void version_number(int val) { _version_number = val;}
    static void version_stamp(string str) { _version_stamp = str;}
    static void program_name(string str) { _program_name = str;}
private:
    static string _program_name;
    static string _version_stamp;
    static int _version_number;
    static int _tests_run;
    static int _tests_passed;
};

#endif //ESSENTIALCPP_GLOBALWRAPPER_H
```

#### 练习 4.4

一份用户记录内含以下数据：登录记录、实际姓名、登入次数、猜过次数、猜对次数、等级——包括初级、终极、高级、专家，以及猜对百分比（可实时计算或者将其只储存起来备用）。请写出一个名为UserPfrofile的class，提供以下操作：输入、输出、相等测试、不等测试。其构造函数必须能够处理默认的用户等级、默认的登录名称（"guest"）。对于同样名为guest的多个用户，该如何保证每个guest有自己独有的登录会话（login session）不和其他人混淆呢？

UserProfile.h:

```c++
#ifndef ESSENTIALCPP_USERPROFILE_H
#define ESSENTIALCPP_USERPROFILE_H

#include <string>
#include <map>
#include <set>
#include <iostream>
using namespace std;

class UserProfile{
public:

    UserProfile();
    UserProfile(const string& user_name, const string& level);
    // 用于写入数据
    void reset_login_session(const long &id) {_login_session = id;}
    void reset_user_name(const string &name) {_user_name = name;}
    void reset_times_logged(int val) {_times_logged = val;}
    void reset_guesses(int val) {_guesses = val;}
    void reset_correct_guesses(int val) {_correct_guesses = val;}
    void reset_uLevel(const string &level) {_uLevel = level;}

    // 自动增加
    void add_times_logged() {_times_logged += 1;}
    void add_guesses() {_guesses += 1;}
    void add_correct_guesses() {_correct_guesses += 1;}

    // 用于直接访问成员对象
    long login_session()const { return _login_session;}
    string user_name()const { return _user_name;}
    int times_logged()const { return _times_logged;}
    int guesses()const { return _guesses;}
    int correct_guesses()const { return _correct_guesses;}
    string uLevel()const { return _uLevel;}

    static void print_session_set(); // 打印用户的会话id
    double average() const;

    bool operator==(const UserProfile &ref);
    bool operator!=(const UserProfile &ref);

private:
    long _login_session; // session id
    static set<long> _login_session_set; // 静态成员变量用于存放所有用户的session id保证session id是独一无二的
    string _user_name; // 用户名
    int _times_logged; // 用户登录次数
    int _guesses; // 用户猜测次数
    int _correct_guesses; // 用户猜对次数
    string _uLevel; // Junior Intermediate Senior Expert
};


#endif //ESSENTIALCPP_USERPROFILE_H

```

UserProfile.cpp:

```c++
#include "UserProfile.h"


set<long> UserProfile::_login_session_set = {};

inline UserProfile::UserProfile():_user_name("guest"),_times_logged(0),_guesses(0),_correct_guesses(0),_uLevel("Junior"){
    long tmp_session = rand();
    while (_login_session_set.find(tmp_session)!=_login_session_set.end()){
        tmp_session = rand();
    }
    _login_session_set.insert(tmp_session);
    _login_session = tmp_session;
}

inline UserProfile::UserProfile(const string& user_name, const string& level):
_user_name(user_name),_times_logged(0),_guesses(0),_correct_guesses(0),_uLevel(level){
    long tmp_session = rand();
    while (_login_session_set.find(tmp_session)!=_login_session_set.end()){
        tmp_session = rand();
    }
    _login_session_set.insert(tmp_session);
    _login_session = tmp_session;
}

inline double UserProfile::average() const {
    return _guesses ? double(_correct_guesses)/double(_guesses) *100 : 0.0;
}

inline bool UserProfile::operator==(const UserProfile &ref) {
    if(_login_session == ref._login_session && _user_name == ref._user_name){
        return true;
    }
    return false;
}

inline bool UserProfile::operator!=(const UserProfile &ref) {
    if(_login_session == ref._login_session && _user_name == ref._user_name){
        return false;
    }
    return true;
}

ostream& operator<<(ostream& os, const UserProfile &user){
    cout << " User_name: " << user.user_name()
         << " login_session: " << user.login_session()
         << " times_logged: " << user.times_logged()
         << " guesses: " << user.guesses()
         << " correct_guesses: " << user.correct_guesses()
         << " uLevel: " << user.uLevel() << endl;
    return os;
}

void UserProfile::print_session_set(){
    cout << "Exist session: " << endl;
    for(long sess:_login_session_set){
        cout << sess << " ";
    }
    cout << endl;
}


```

**注意：** cpp文件中 set<long> UserProfile::_login_session_set = {}; 这句话是对静态成员的初始化，静态成员的初始化一定不能放在class体内，应该在class结构体之外，相当于一个全局变量一样初始化。

#### 练习 4.5 

实现一个4*4的Matrix类，至少提供以下接口：矩阵加法、矩阵乘法、打印函数print()、复合运算符+=，以及一组支持下标操作的function call运算符，像下面这样：

```c++
float& operator() (int row, int column);
flaot operator() (int row, int column) const;
```

```c++
#ifndef ESSENTIALCPP_MATRIX_H
#define ESSENTIALCPP_MATRIX_H

#include <iostream>
using namespace std;

typedef float elemType; // 将floats设置另外的名称elemType

class Matrix{
    friend Matrix operator+(const Matrix &m1, const Matrix &m2);
    friend Matrix operator*(const Matrix &m1, const Matrix &m2);

public:
    Matrix(const elemType*); // 用指针的构造函数
    Matrix(elemType = 0.0, elemType = 0.0, elemType = 0.0, elemType = 0.0,
           elemType = 0.0, elemType = 0.0, elemType = 0.0, elemType = 0.0,
           elemType = 0.0, elemType = 0.0, elemType = 0.0, elemType = 0.0,
           elemType = 0.0, elemType = 0.0, elemType = 0.0, elemType = 0.0);

    void operator+=(const Matrix&);
    elemType operator()(int row,int column) const { return _matirx[row][column];}
    elemType& operator()(int row,int column) { return _matirx[row][column];}
private:
    elemType _matirx[4][4]; // 4*4的矩阵
};



#endif //ESSENTIALCPP_MATRIX_H

```

```c++
#include "Matrix.h"


inline Matrix::Matrix(const elemType *arr) {
    int arr_id = 0;
    for(int i= 0; i< 4;i++){
        for(int j = 0;j<4;j++){
            _matirx[i][j] = arr[arr_id++];
        }
    }
}

inline Matrix::Matrix(elemType a11, elemType a12, elemType a13, elemType a14, elemType a21, elemType a22, elemType a23,
                      elemType a24, elemType a31, elemType a32, elemType a33, elemType a34, elemType a41, elemType a42,
                      elemType a43, elemType a44) {
    _matirx[0][0] = a11; _matirx[0][1] = a12; _matirx[0][2] = a13; _matirx[0][3] = a14;
    _matirx[1][0] = a21; _matirx[1][1] = a22; _matirx[1][2] = a23; _matirx[1][3] = a24;
    _matirx[2][0] = a31; _matirx[2][1] = a32; _matirx[2][2] = a33; _matirx[2][3] = a34;
    _matirx[3][0] = a41; _matirx[3][1] = a42; _matirx[3][2] = a43; _matirx[3][3] = a44;
}


inline ostream& operator<<(ostream &os, const Matrix &ref){
    for(int i = 0;i < 4;++i){
        for(int j = 0;j < 4;++j){
            cout << ref(i,j) << " ";
        }
        cout << endl;
    }
    return os;
}

void Matrix::operator+=(const Matrix &m) {
    for(int i = 0;i<4;++i){
        for(int j = 0;j<4;j++){
            _matirx[i][j] += m._matirx[i][j];
        }
    }
}

Matrix operator+(const Matrix &m1, const Matrix &m2){
    Matrix res(m1);
    res += m2;
    return res;
}

Matrix operator*(const Matrix &m1, const Matrix &m2){
    Matrix res;
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            res(i,j) = 0;
            for(int k = 0;k<4;k++){
                res(i,j) += m1(i,k)*m2(k,j);
            }
        }
    }
    return res;
}
```

