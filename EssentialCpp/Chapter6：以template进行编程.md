# Chapter6：以template进行编程

## 6.1 被参数化的类型

template机制帮助我们将类定义中“与类型相关”和”独立于类型之外“的两部分分离开来，class template所产生的出来的各个class，其类型都有可能不同。

以一个二叉树BTnode class为例，data member _val的类型就可以被参数化

```c++
template <typename valType> // BTnode class template的前置声明
class BTnode;
```

valType是一个占位符，名称可以任何设定，在用户为它指定某个特定类型之前，它被视为一个可取代的任意类型的东西，可以用来声明_val的所属类型：

```c++
template<typename valType>
class BTnode{
public:
		// ...
private:
		valType   _val;
		int       _cnt;
		BTnode    *_lchild;
		BTnode    *_rchild;
}
```

为了通过class template实例化类，我们必须在class template名称之后，紧接一个尖括号，其内放置一个实际类型，用来取代valType，例如，如果要将valType绑定至int，可以这么写：

```c++
BTnode<int> bti;
```

注意如下的一个例子：

```c++
template <typename elemType>
class BinaryTree{
public:
    // ...
private:
    // BTnode必须以template参数列表加以限定
    BTnode<elemType> *_root
}
```

什么情况下需要以template参数列表进一步限定class template呢？一般的规则是，在class template及其member的定义中，不必如此。除此之外的其他场合就需要以参数列表加以限定。

## 6.2 Class Template的定义

```c++
template <typename elemType>
class BinaryTree{
public:
    BinaryTree();
    BinaryTree(const BinaryTree&);
    ~BinaryTree();
    BinaryTree& operator=(const BinaryTree&);

    bool empty(){ return _root == 0;}
    void clear();
private:
    BTnode<elemType> *_root;
    void copy(BTnode<elemType>*tar,BTnode<elemType>*src);
};
```

以上是BinaryTree class template的部分定义，我们为class template定义了一个inline函数，在类体内class template的成员函数的定义和non-template class的定义一样。但是如果在类体之外，class template成员函数定义的语法则和non-template class大相径庭：

```c++
template <typename elemType>
inline BinaryTree<elemType>:: //在class定义范围之外，所以需要elemType限定
BinaryTree():_root(0){} // 在class定义范围之内，所以不需要elemType限定
```

这个成员函数的定义始于关键字template和一个参数列表，然后是函数定义本身，并带有关键字inline以及class scope运算符，inline一次必须紧跟在管金子template和参数列表之后。

## 6.3 Template类型参数的处理

在实际运用中，不论内置类型或class类型，都可能被指定为class template的实际类型。所以最好将所有的template类型参数视为”class类型“来处理，这意味着我们会把它声明为一个const reference，而不是通过值传递的方式传递。

并且为了效率问题，最好在构造函数定义时在成员初始化列表内为每个类型参数进行初始化操作，而不是在函数体内进行。

## 6.4  实现一个Class Template

略

## 6.5 定义一个Function Template

如果我们希望为BinaryTree class template提供一个output运算符。针对non-template class，我们会这么写：

```c++
ostream& operator<<(ostream&, const int_BinaryTree&);
```

如果对象是class template，我们可以明确指出生成的每个class的名称：

```c++
ostream& operator<<(ostream&, const BinaryTree<int>&);
```

但是这种写法很不好，比较好的方法是将output运算符定义为一个function template。

```c++
template <typename elemType>
inline ostream&
operator<<(ostream &os, const BinaryTree<elemType> &bt){
		os << "Tree: " <<endl;
		bt.print(os);
		return os;
}
```

print()是BinaryTree class template的一个private成员函数。为了让上述的output运算符可以顺利调用print()，output运算符必须成为BinaryTree的一个friend：

```c++
template <typename elemType>
class BinaryTree{
		friend ostream& operator<<(ostream&, const BinaryTree<elemType>& );
}
```

## 6.6 常量表达式与默认参数值

以表达式作为template参数，被称为非类型参数。

Template的参数并不一定非要是某种类型，也可以用常量表达式作为Template的参数

## 6.8 Member Template Function

我们可以将member function定义成template形式，Class Template内也可以定义member template function。

#### 练习 6.1

试改写以下类，使它成为一个class template

```c++
class example{
public:
    example(double min, double max);
    example(const double *array, int size);
    double& operator[](int index);
    bool insert(const double*, int);
    bool insert(double);
    double min() const { return _min;}
    double max() const { return _max;}
    void min(double);
    void max(double);
    int count(double value) const;
private:
    int size;
    double *parray;
    double _min;
    double _max;
};
```

```c++
改写：
template <typename elemType>
class example{
public:
    example(const elemType &min, const elemType &max);
    example(const elemType *array, int size);
    elemType& operator[](int index);
    bool insert(const elemType*, int);
    bool insert(const elemType&);
    elemType min() const { return _min;}
    elemType max() const { return _max;}
    void min(const elemType&);
    void max(const elemType&);
    int count(const elemType &value) const;
private:
    int size;
    double *parray;
    double _min;
    double _max;
};
```

#### 练习6.2 

重新以template形式实习练习4.3的Matrix class，并扩充其功能，使它能够通过heap memory来支持任意行列大小。分配/释放内存的操作，请在构造/解析函数中进行。