# Chapter5：面向对象编程风格

## 5.1 面向对象编程概念

OOP的两项主要特质是：继承和多态。继承使得我们可以将一群相关的类组织起来，并让我们分享其间的共通数据和操作行为。后者让我们在这些类上进行编程时，可以如同操控单一个体，而非相互独立的类，并赋予我们更多弹性来加入或移除任何特定类。

#### 继承机制：

定义了父子类，父类定义了所有子类共通的共有接口和私有实现。每个子类都可以增加或覆盖继承而来的东西，以实现其自身独特的行为。在C++中父类被称为基类，子类被称为派生类。

#### 多态机制：

让基类的指针或者引用得以十分透明的指向其任何一个派生类的对象。C++ 多态意味着调用成员函数时，会根据调用函数的对象的类型来执行不同的函数。

下面的实例中，基类 Shape 被派生为两个类，如下所示：

```c++
#include <iostream> 
using namespace std;
 
class Shape {
   protected:
      int width, height;
   public:
      Shape( int a=0, int b=0)
      {
         width = a;
         height = b;
      }
      int area()
      {
         cout << "Parent class area :" <<endl;
         return 0;
      }
};
class Rectangle: public Shape{
   public:
      Rectangle( int a=0, int b=0):Shape(a, b) { }
      int area ()
      { 
         cout << "Rectangle class area :" <<endl;
         return (width * height); 
      }
};
class Triangle: public Shape{
   public:
      Triangle( int a=0, int b=0):Shape(a, b) { }
      int area ()
      { 
         cout << "Triangle class area :" <<endl;
         return (width * height / 2); 
      }
};
// 程序的主函数
int main( )
{
   Shape *shape;
   Rectangle rec(10,7);
   Triangle  tri(10,5);
 
   // 存储矩形的地址
   shape = &rec;
   // 调用矩形的求面积函数 area
   shape->area();
 
   // 存储三角形的地址
   shape = &tri;
   // 调用三角形的求面积函数 area
   shape->area();
   
   return 0;
}
```

当上面的代码被编译和执行时，它会产生下列结果：

```c++
Parent class area
Parent class area
```

导致错误输出的原因是，调用函数 area() 被编译器设置为基类中的版本，这就是所谓的**静态多态**，或**静态链接** - 函数调用在程序执行前就准备好了。有时候这也被称为**早绑定**，因为 area() 函数在程序编译期间就已经设置好了。

但现在，让我们对程序稍作修改，在 Shape 类中，area() 的声明前放置关键字 **virtual**，如下所示：

```c++
class Shape {
   protected:
      int width, height;
   public:
      Shape( int a=0, int b=0)
      {
         width = a;
         height = b;
      }
      virtual int area()
      {
         cout << "Parent class area :" <<endl;
         return 0;
      }
};
```

修改后，当编译和执行前面的实例代码时，它会产生以下结果：

```c++
Rectangle class area
Triangle class area
```

此时，编译器看的是指针的内容，而不是它的类型。因此，由于 tri 和 rec 类的对象的地址存储在 *shape 中，所以会调用各自的 area() 函数。

正如您所看到的，每个子类都有一个函数 area() 的独立实现。这就是**多态**的一般使用方式。有了多态，您可以有多个不同的类，都带有同一个名称但具有不同实现的函数，函数的参数甚至可以是相同的。

#### 动态绑定：

找出实际被调用的究竟是哪一个派生类的函数，是会延迟至运行时才确定。

## 5.2 面向对象编程思维

以图书馆借阅系统LibMat这个抽象基类作为类体系中最根本的类，从LibMat派生出Book。

默认情况系，成员函数的解析都在编译时静态的进行。若要令其在运行时动态进行，就要在它的声明前加上关键字virtual，成为虚函数。

我们定义了如下的基类和继承类。

```c++
// 基类
class LibMat{
public:
    LibMat(){cout << "LibMat::LibMat()默认构造函数被调用!\n";}
    virtual ~LibMat(){cout << "LibMat::~LibMat()默认析构函数被调用!\n";}
    virtual void print() const {
        cout << "LibMat::print()被调用!\n";
    }
};

// 派生类
class Book:public LibMat{
public:
    Book(const string &title, const string &author):_title(title),_author(author){
        cout << "Book::Book()构造函数被调用,书名:" << _title << " 作者:" << _author << endl;
    }
    ~Book(){
        cout << "Book::~Book()析构函数被调用\n";
    }

    virtual void print(){
        cout << "Book::print()被调用!\n";
    }

    const string& title() const { return _title;}
    const string& author() const { return _author;}
private:
    string _title;
    string _author;
};


void print(const LibMat &mat){
    cout << "此时的print():";
    mat.print();
    cout << endl;
}

int main(){
    cout << "创建LibMat对象!" << endl;
    LibMat libmat;
    print(libmat);
    cout << "创建Book对象!" << endl;
    Book book("1984","乔治奥维尔");
    print(book);
}
```

```c++
运行结果：
创建LibMat对象!
LibMat::LibMat()默认构造函数被调用!
此时的print():LibMat::print()被调用!

创建Book对象!
LibMat::LibMat()默认构造函数被调用!
Book::Book()构造函数被调用,书名:1984 作者:乔治奥维尔
此时的print():LibMat::print()被调用!

Book::~Book()析构函数被调用
LibMat::~LibMat()默认析构函数被调用!
LibMat::~LibMat()默认析构函数被调用!
```

可以看到通过mat.print()所进行的虚拟调用操作是有效的，当输入的对象为Book对象时，调用print打印的是Book的内容。同时，可以发现，当程序定义出一个派生对象，基类和派生类的构造函数都会被执行，先执行基类的构造函数再执行派生类的构造函数。当派生对象被销毁时，基类和派生类的析构函数都会被调用，先调用派生类的析构函数再调用基类的析构函数。

**注意：**使用派生类时不必刻意区分”继承而来的成员“和”自身定义的成员“。两者的使用完全透明。

## 5.4 定义一个抽象基类

设计抽象类的第一个步，就是找出所有子类共通的操作行为。

设计抽象类的第二步，就是找出那些操作行为与类型相关，也就是说，有哪些操作行为必须根据不同的派生类定义不同的实现方式。这些操作行为应该成为整个类继承体系中的虚函数。

设计抽象类的第三步，就是找出每个操作行为的访问层级。如果某个操作行为应该让一般程序皆能访问，我们应该将它声明为public，如果某个操作行为在基类之外不需要被用到，就应该将它声明为private，即使是该基类的派生类，也不能访问基类中的private成员。还有第三种访问层级，即protected，这种层级的操作行为可让派生类访问，但是不允许一般程序使用。

每个虚函数，要么得有其定义，要么可以设定为纯虚函数，如果对于该类而言，这个虚函数并无实质意义的话，可以设为纯虚函数。将虚函数赋值为0，便是令它为一个纯虚函数。

任何类如果声明有一个或者多个纯虚函数，那么，由于其接口的不完整性（纯虚函数没有函数定义，是不完整的），程序无法为它产生任何对象。这种类只能用于派生子类，作为派生类的子对象使用。而且前提是这些派生类必须为所有虚函数提供确切的定义。

有纯虚函数的抽象基类可以不定义构造函数，根据一般规则，凡基类定义有一个或者多个虚函数，应该将其析构函数声明为virtual，但不建议声明为纯虚函数。

如果类中没有成员，那么实体化以后只占一个字节。

## 5.5 定义一个派生类

派生类由两个部分组成：（1）基类构成的子对象，由基类的non-static data member——如果有的话——组成；（2）派生类的部分。

派生类的定义如下：

```c++
class SonClass_name:public FatherClass_name{
	 // 这里可以是protected、private或者public三种方式	
};
```

派生类必须为从基类继承而来的每一个纯虚函数提供对应的实现。除此之外它还必须声明自己的专属member。

**注意：**在类外对虚函数进行定义时，不比指明关键字virtual。

一般来说，对于public继承方式继承而来的public和protected成员，不论在继承体系中的深度如何，都可被视为派生类自身拥有的成员。基类的public member在派生类中同样也是public，同样开放给派生类的用户使用。基类的protected member在派生类中同样也是protected，同样只能给后续的派生类使用，无法给目前这个派生类的用户使用。至于基类的private member，则完全无法让派生类使用。

每当派生类有某个member与其基类的member同名，变回遮掩住基类的那份member。也就是说，派生类内对该名称的任何使用，都会被解析为该派生类自身的那份member，而非继承来的那份member。这种情况下，如果要在派生类内使用继承来的那份member，必须利用class scope运算符加以限定。

## 5.8 初始化、析构、复制

将初始化操作留给每个派生类会存在潜在的危机。比较好的设计方式是，为基类提供构造函数，并利用这个构造函数处理基类所声明的所有data member的初始化操作。

如果基类是一个抽象基类，我们就无法为它定义任何对象。该基类扮演的角色是每个派生类对象的子对象。基于这个原因，我们可以将该基类的构造函数声明为protected而不是public的。 

派生类对象的初始化行为，包含调用其基类的构造函数，然后再调用派生类自己的构造函数，派生类对象之中其实含有多个子对象：由基类构造函数初始化的基类子对象、以及由派生类构造函数所初始化的派生类子对象。

派生类的构造函数，不仅必须为派生类的data member进行初始化操作，还需要为其基类的data member提供适当的值。

如果派生类的构造函数没能明确指出调用基类的哪一个构造函数，编译器会自动调用基类的默认构造函数。

如果基类没有定义复制构造函数，则调用默认的复制构造函数。

## 5.9 在派生类中定义一个虚函数

当我们定义派生类时，我们必须决定，究竟要将基类中的虚函数覆盖掉，还是原封不动的加以集成。如果我们继承了纯虚函数，那么这个派生类也会被视为抽象类，无法为它定义任何对象。

如果我们决定覆盖基类所提供的虚函数，那么派生类提供的新定义，其函数原型必须完全符合基类所声明的函数原型，包括：参数列表、返回类型、是否为const等。

**“返回类型必须完全吻合”有一个例外——当基类的虚函数返回某个基类形式（通常是指针或者引用）时：**

```c++
class num_sequence{
public:
		// 派生类的clone()函数可返回一个指针,
		// 指向num_sequence的任何一个派生类
		virtual num_sequence *clone() = 0;
};
```

派生类中同名函数便可以返回该基类所派生出类的类型：

```c++
class Fibonacci:public num_sequence{
public:
		// Fibonacci是派生自num_sequence
		// 注意，在派生类中，关键字virtual并非必要
		Fibonacci *clone(){ return new Fibonacci(*this);}
};
```

#### 虚函数的静态解析

有两种情况，虚函数机制不会出现预期行为：

（1）基类的构造函数和析构函数内；

（2）当我们使用的是基类的对象，而非基类对象的指针或者引用时。

在基类的构造函数中，派生类的虚函数绝对不会被调用。

#### 练习 5.1

实现一个两层的stack类体系，其基类是一个纯抽象类Stack，只提供最简单的接口：pop()、push()、size()、empty()、full()、peekl()和print()。两个派生类则为LIFO_Stack和Peekback_Stack。Peekback_Stack可以让用户在不更改stack元素的前提下，访问任何一个元素。

Stack.h

```C++
#ifndef ESSENTIALCPP_STACK_H
#define ESSENTIALCPP_STACK_H

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

typedef string elemType;

class Stack{
public:
    virtual ~Stack(){} // 抽象类需要析构函数
    virtual bool pop(elemType&) = 0; // 纯虚函数
    virtual bool push(const elemType&) = 0;
    virtual bool peek(int index, elemType&) = 0;

    virtual int top() const = 0;
    virtual int size() const = 0;

    virtual bool empty() const = 0;
    virtual bool full() const = 0;
    virtual void print(ostream& = cout) const = 0;
};


#endif //ESSENTIALCPP_STACK_H
```

LIFO_Stack.h

```c++
#ifndef ESSENTIALCPP_LIFO_STACK_H
#define ESSENTIALCPP_LIFO_STACK_H

#include "Stack.h"

class LIFO_Stack:public Stack{
public:
    LIFO_Stack(int cap = 0):_top(0){
        if(cap){
            _stack.reserve(cap); // 翻转vector
        }
    }

    int size() const { return _stack.size();} // 栈大小
    bool empty() const { return !_top;}
    bool full() const { return size() >= _stack.max_size();}
    int top() const { return _top;}
    void print(ostream &os = cout) const;

    bool pop(elemType &elem);
    bool push(const elemType &elem);
    bool peek(int, elemType&) { return false;}
private:
    int _top;
    vector<elemType> _stack;
};

#endif //ESSENTIALCPP_LIFO_STACK_H
```

LIFO_Stack.cpp

```c++
#include "LIFO_Stack.h"


bool LIFO_Stack::pop(elemType &elem) {
    if(empty()) return false;
    elem = _stack[--_top];
    _stack.pop_back();
    return true;
}

bool LIFO_Stack::push(const elemType &elem) {
    if(full()) return false;
    _stack.push_back(elem);
    ++ _top;
    return true;
}

void LIFO_Stack::print(ostream &os) const {
    // 注意在声明的时候已经设定了默认参数所以这里不能再重复设定
    vector<elemType>::const_reverse_iterator riter = _stack.rbegin(); // 反向迭代器
    vector<elemType>::const_reverse_iterator rend = _stack.rend();
    for(; riter!= rend; ++riter)
    {
        os << *riter << " ";
    }
    os << endl;
}

```

Peekback_Stack.h

```c++
#ifndef ESSENTIALCPP_PEEKBACK_STACK_H
#define ESSENTIALCPP_PEEKBACK_STACK_H

#include "Stack.h"

class Peekback_Stack:public Stack{
public:
    Peekback_Stack(int cap = 0):_top(0){
        if(cap){
            _stack.reserve(cap); // 翻转vector
        }
    }

    int size() const { return _stack.size();} // 栈大小
    bool empty() const { return !_top;}
    bool full() const { return size() >= _stack.max_size();}
    int top() const { return _top;}
    void print(ostream &os = cout) const;

    bool pop(elemType &elem);
    bool push(const elemType &elem);
    bool peek(int, elemType&);
private:
    int _top;
    vector<elemType> _stack;
};


#endif //ESSENTIALCPP_PEEKBACK_STACK_H
```

Peekback_Stack.cpp

```c++
#include "Peekback_Stack.h"


bool Peekback_Stack::pop(elemType &elem) {
    if(empty()) return false;
    elem = _stack[--_top];
    _stack.pop_back();
    return true;
}

bool Peekback_Stack::push(const elemType &elem) {
    if(full()) return false;
    _stack.push_back(elem);
    ++ _top;
    return true;
}

void Peekback_Stack::print(ostream &os) const {
    // 注意在声明的时候已经设定了默认参数所以这里不能再重复设定
    vector<elemType>::const_reverse_iterator riter = _stack.rbegin(); // 反向迭代器
    vector<elemType>::const_reverse_iterator rend = _stack.rend();
    for(; riter!= rend; ++riter)
    {
        os << *riter << " ";
    }
    os << endl;
}

bool Peekback_Stack::peek(int index, elemType &elem) {
    if(empty()) return false;
    if(index<0||index>=size()) return false;
    elem = _stack[index];
    return true;
}
```

#### 练习 5.2

重新实现练习5.1的类体系，令基类Stack实现出各派生类共享的、与类型无关的所有成员

（具象基类）

```c++
#ifndef ESSENTIALCPP_STACK_H
#define ESSENTIALCPP_STACK_H

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
using namespace std;

typedef string elemType;

class Stack{
public:
    Stack(int capacity = 0):_top(0){
        if (capacity){
            _stack.reserve(capacity);
        }
    }
    virtual ~Stack(){}
    bool pop(elemType&);
    bool push(const elemType&);
    virtual bool peek(int ,elemType&){
        return false;
    }
    int size() const { return !_top;}
    bool full() const { return size()>=_stack.max_size();}
    void print(ostream &os=cout) const ;
protected:
    vector<elemType> _stack;
    int _top;
};


#endif //ESSENTIALCPP_STACK_H


#ifndef ESSENTIALCPP_PEEKBACK_STACK_H
#define ESSENTIALCPP_PEEKBACK_STACK_H

#include "Stack.h"

class Peekback_Stack:public Stack{
public:
    Peekback_Stack(int cap = 0):_top(0){
        if(cap){
            _stack.reserve(cap); // 翻转vector
        }
    }

    virtual bool  peek(int index, elemType &elem);
private:
    int _top;
    vector<elemType> _stack;
};


#endif //ESSENTIALCPP_PEEKBACK_STACK_H

```