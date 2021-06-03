# Chapter1：C++编程基础

## 1.1 如何撰写C++程序

第一个完整的C++程序如下所示：

```c++
#include <iostream>
#include <string>
using namespace std; // 标准库的命名空间,命名空间用于防止发生命名冲突问题

int main() {
    string user_name;
    cout << "Please enter your first name: ";
    cin >> user_name;
    cout << '\n'
         << "Hello, "
         << user_name
         << "... and goodbye!\n";
    return 0;
}
```

#### 练习1.4

试着扩充上述程序内容：

（1）要求用户同时输入first name和last name；

（2）修改输出结果，同时打印first name和last name。

```c++
#include <iostream>
#include <string>
using namespace std; 

int main() {
    string first_name, last_name;
    cout << "Please enter your first name: ";
    cin >> first_name;
    cout<<"hi, "<<first_name
        <<" Please enter your last name: ";
    cin >> last_name;
    cout << '\n'
         << "Hello, "
         << first_name << ' ' << last_name
         << "... and goodbye!\n";
    return 0;
}
```

解析：定义两个string对象即可。

## 1.2 对象的定义与初始化

C++提供两种初始化对象的方法，例如对一个用户输入的整型数值，我们可以定一个整数对象，并赋予初值0：

```c++
int user_val = 0;
```

这种用assignment运算符（=）进行初始化的操作沿袭自C语言，如果对象属于内置类型就可以直接使用，如果是用户自定义的class类型，则需要运算符重载。

另外一种对象初始化的方式是利用“构造函数语法”：

```c++
int user_val(0);		
```

这种方式一般用于用户自定义的class对象。

有时候我们需要一些用来表示常量的对象，这种对象的内容（值）在程序执行过程中不会发生变动，因此为了防止我们无意间改变这些对象的值，C++使用关键字const来定义const对象，const对象在获得初值之后，无法再有任何变化，如果你试图为const对象指定新值，编译器会报错，例如：

```c++
const int max_tries = 3; // 定义const对象并赋初值
max_tries= 42; // 企图修改const对象的值,编译报错		
```

## 1.3 撰写表达式

C++的表达式中使用的运算符一般包括算术运算符、关系运算符、逻辑运算符、复合赋值运算符。

##### 条件三目运算符：

```c++
x < 0 ? y = 10 : z = 20;
```

这个语句被称为条件表达式，它由 3 个子表达式组成，使用问号 ? 和冒号 : 分隔。这 3 个表达式分别是：x<0，y = 10 和 z = 20。

上面的条件表达式与以下 if-else 语句执行相同的操作：

```c++
if(x < 0)
	y = 10；
else
	z = 20;
```

##### 复合赋值运算符：

主要为+=、-=、*=、/=和%=，即先运算再将运算的结果赋值

## 1.4 条件语句与循环语句

### 条件语句

1.if ... else ...

2.if ... else if ... else ...

3.如果测试条件属于整数类型，我们还可以使用switch语句来取代一大堆的if...else if...子句。例如：

```c++
switch (expression){
        case condition1:
            statement1;
    				break;
        case condition2:
            statement2;
    				break;
        ...
        case conditionN:
            statementN;
    				break;
        default:
            statement_default;
    				break;
    }
```

switch之后紧接着一个表达式，case用于判断表达式的值是否满足条件，如果满足则执行相应的语句，否则往下判断。default表示如果所有的条件都不满足时执行的默认操作。**注意，case后执行的语句一定要用break结尾，如果没有break则如果满足某一个条件后，该条件后所有的case中的执行语句都会被执行。**

### 循环语句

1.while... 先判断再do

2....while 先do再判断

3.for ( init-statement; condition; expression-statement)

如果在执行循环内的语句时遇上break，循环就会直接结束。如果遇上了continue语句，则结束当前迭代开始下一轮迭代。

## 1.5 运用Array和Vector

C++允许使用内置数组array或者标准库提供的vector类来定义容器。

要定义array，必须制定array的元素类型，并给与array一个名称并指定其尺度大小，array的大小必须是一个常量表达式。例如：

```C++
const int seq_siez = 19;
int pell_seq[seq_size];
```

vector是一个class template因此首先需要包含vector头文件，然后在类名之后的尖括号内指定元素的类型，其大小写在小括号中。这里给定的大小并不一定非要是一个常量表达式。例如：

```C++
#include<vector>
int seq_size = 19;
vector<int> pell_seq(seq_size);
```

对于vector的初始化，可以在定义的时候直接初始化为一个相同的值，例如：

```c++
vector<int> vec(size,0); // 定一个大小为size的int型vector vec,并将所有的元素初始化为0
```

也可以利用一个已经初始化的array为vector进行初始化，例如：

```c++
int arr[const_size] = {
	1,2,3,4,5,6,7,
	7,6,5,4,3,2,1
}
// 以arr的值来初始化vec
vector<int> vec(arr, arr + const_size);
```

这里arr和arr+const_size实际上是两个实际内存位置，它们标示出了“用以将vector初始化”的元素范围，并将它们复制到vector中。

**array和vector之间存在一点差异，** vector知道自己的大小是多少，可以通过".size()"的方式获得指定的vector的大小。

## 1.6 指针带来弹性

1.5中array和vector不够弹性，且大小有限，因此C++引入指针pointer，间接的访问每一个元素。

我们通过在类型名称之后加上“*”的方式定义指针，例如：

```c++
int ival = 1024; // 定义int类型变量ival并初始化为1024
int *pi = &ival; // 定义指针pi,通过&ival获得变量ival的地址,并将指针pi指向该地址
```

如果要访问一个由指针所指的对象，我们需要对该指针进行提领dereference操作，即取值操作，也就是取得“位于该指针所指内存地址上”的对象。通过在指针之前使用“*”号来达到该目的：

```c++
if (*pi != 1024){ // 读ival的值
		*pi = 1024; // 写值到ival
}
```

对于空指针null，其地址为0，一般的我们在定义指针时一定要给指针赋值为null或0，这样才不会造成野指针，我们可以通过if (!ptr)的方法来检测指针ptr是不是为空。

我们可以通过指针来指向vector：

```c++
vector<int> vec1,vec2,vec3,vec4,vec5,vec6; // 定义6个vector<int>
const int n = 6;
// vec_addrs是一个大小为6的array，元素类型为vector<int> *,即指向vector<int>的指针,这样我们就可以将			 vec1到vec6的地址全部存到一个array中去了。通过指针间接访问这些vector
vector<int> *vec_addrs[n] = {
		&vec1,&vec2,&vec3,&vec4,&vec5,&vec6
} 
```

## 1.7 文件的读写

#### 写文件

```C++
#include <fstream> // 引入头文件
ofstream outfile("data.txt"); // 声明outfile
```

用outfile声明文件"data.txt"，如果指定的文件并不存在，便会有一个文件被产生出来并开启作为输出使用。如果指定的文件已经存在则文件会被开启，但是文件中原有的数据会被丢弃。

如果不希望丢弃原有的文件内容，而是增加新的数据到文件中，那么必须以追加模式append mode开启这个文件：

```C++
ofstream outfile("data.txt", ios_base::app); // ios_base::app以追加模式开启文件
```

文件可能会开启失败，因此在进行写入之前，要判断文件是否开启成功：

```c++
if (!outfile) // 如果outfile为false则说明文件没有开启成功
```

我们可以通过标准错误输出cerr来将错误信息告知用户:

```c++
if (!outfile){
    // 文件开启失败
		cerr << "Oops! Unable to save session data!\n";
}else{
	 // 文件开启成功,写入数据
		outfile << user_name << ' '
						<< num_tries << ' '
						<< num_right << endl;
}
```

#### 读文件

读文件定义一个ifstream的对象：

```c++
ifstream infile("data.txt"); // 定义读对象
if(!infile){
	 	// 文件无法开启
}else{
		// 文件成功开启
  	string name;
  	int nt;
  	int nc;
  	while(infile >>  name){
  			if(name == user_name){
  					cout << "Welcome back, " << user_name
  							 << "\nYour current score is " << nc
  							 << " out of " << nt << "\nGood Luck!\n";
  			}
  	}
}
```

这个while循环的每一次迭代都会读取文件的下一行内容，这样的操作会持续到文件尾端才结束。

如果想同时读写同一个文件，我们需要以追加模式开启文件：

```c++
fstream iofile("data.txt", ios_base::in|ios_base::app);
if (!iofile){
		// 开启文件失败
}else{
		// 开启文件成功
		// 以追加模式开启文件时,文件位置会位于尾端,因此要用seekg()重新定位
		iofile.seekg(0);
}
```

#### 练习1.5

编写程序，询问用户姓名，读取用户输入的内容，确保用户输入的名称长度大于两个字符。用C-style和string对象两种方法编写。

string方法：

```c++
#include <iostream>
#include <string>
using namespace std;

int main() {
    string user_name;
    cout << "Please enter your name: ";
    cin >> user_name;
    switch (user_name.size()){
        case 0:
            cout << "Error! Your name size is 0!\n";
            break;
        case 1:
            cout << "Error! Your name size is 1!\n";
            break;
        default:
            cout << "Hello, " << user_name << endl;
            break;
    }
    return 0;
}
```

C-style方法：

setw(int n)是C++中在输出操作中使用的字段宽度设置，设置输出的域宽，n表示字段宽度。**只对紧接着的输出有效**，紧接着的输出结束后又变回默认的域宽。当后面紧跟着的输出字段长度小于n的时候，在该字段前面用空格补齐；当输出字段长度大于n时，全部整体输出。setw函数使用的头文件为iomanip。

```C++
#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

int main() {
    const int max_n = 127; // 定义名字最大长度
    char user_name[max_n]; // 用户名
    cout << "Please enter your name: ";
    cin >> setw(max_n) >> user_name;
    switch (strlen(user_name)){
        case 0:
            cout << "Error username!\n";
            break;
        case 1:
            cout << "Error username!\n";
            break;
        case 127:
            cout << "Username is too long, and should be shortten!\n";
            // 不用break用于直接执行default
        default:
            cout << "Hello, "
                 << user_name <<endl;
            break;
    }
    return 0;
}

```

#### 练习1.6

编写程序从标准输入中读取一串整数，依次存入array以及vector中，然后遍历这两种容器，求和，将和和平均数输出。

存入vector

```c++
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int num, sum = 0;
    vector<int> vec;
    while(cin >> num && num != 0){
        vec.push_back(num);
    }
    for(int i = 0; i < vec.size(); i++){
        sum += vec[i];
    }
    cout << "Sum: " << sum << " Ave: " << (double) sum/vec.size();
}

```

存入array

```c++
#include <iostream>
using namespace std;

int main() {
    int num, i = 0, sum = 0;
    const int size = 128;
    int arr[size];
    while(cin >> num && num !=0 && i < size){
        arr[i++] = num;
    }
    for(int j = 0; j<i ; ++j){
        sum += arr[j];
    }
    cout << "Sum: " << sum << " Ave: " << (double) sum/i;
}

```

#### 练习1.7

编写程序，从文件中读取两行文字，将每一个单词读取到一个vector<string>对象中，遍历该vector，用cout输出，利用sort对文字排序，然后输入到另一个文件中。

```C++
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ifstream infile("./data.txt");
    if(!infile){
        cerr << "Open file data.txt failed !\n";
        return -1;
    }
    ofstream ofile("./data_sorted.txt");
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

```

#### 练习1.8  

用array储存4种不同的字符串信息，根据用户答错的次数提供不同的安慰语句，并以用户答错的次数作为array的索引值，以此来显示安慰语句。

```C++
#include <iostream>
using namespace std;



const char* msg2user(int num){
    const int n = 4;
    static const char* msgArr[n] = {
        "Error 1",
        "Error 2",
        "Error 3",
        "Error 4"
    };
    if(num<=0){
        return "Yeah, you made it!\n";
    }else if(num>=5){
        return "Error more than 4!\n";
    }else{
        return msgArr[num-1];
    }
}

int main() {
    int num;
    cin >> num;
    cout << msg2user(num);
    return 0;
}

```

