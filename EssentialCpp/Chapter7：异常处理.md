# Chapter7：异常处理

## 7.1 抛出异常

异常处理机制有两个主要成分：异常的鉴定与发出，以及异常的处理方式。异常出现之后，正常程序的执行便被暂停，于此同时，异常处理机制开始搜索程序中有能力处理这一异常的地点。异常被处理完毕后，程序的执行过便会继续，从异常处理点接着执行下去。

C++通过throw表达式产生异常：

```c++
inline void Tri_iter::
check_integrity(){
		if(_index>=Tri_iter::_max_elems){
				throw iterator_overflow(_index, Triangular::_max_elems)
		}
		if(_index>=Triangular::_elems.size()){
				Triangular::gen_elements(_index + 1);
		}
}
```

所谓异常（exception）是某种对象，最简单的异常对象可以设计为整数或字符串：

```c++
throw 42;
throw "panic: no buffer!";
```

大部分时候，被抛出的异常都属于特定的异常类（也许形成一个继承体系）例如：

```c++
class iterator_overflow{
public:
		iterator_overflow(int index, int max):_index(index),_max(max){}
		
		int index(){return _index;}
		int max(){return _max;}
		
		void what_happened(ostream &os = cerr){
				os << "Internal error: current index "
				   << _index << " exxceeds maximum bound: "
				   << _max;
		}
private:
		int _index;
		int _max;
}
```

我们令它得以储存某些必要数据，用以表示异常的性质，以便我们得以在不同程序的不同调用点上相互传递这些性质。

前例的throw表达式，会直接调用拥有两个参数的构造函数，我们也可以换一种方式，明确指出被抛出的对象名称：

```c++
if(_index>Triangular::_max_elems){
		iterator_overflow ex(_index,Triangular::_max_elems);
		throw ex;
}
```

## 7.2 捕获异常

我们可以利用单条或一连串的从catch子句来捕获被抛出的异常对象。catch子句由三部分组成：关键字catch、小括号内的一个类型或对象、大括号内的一组语句（用以处理异常），下面是一个例子：

```c++
bool some_function(){
		bool status = true;
		// ... 假设我们达到这里
		catch(int errno){
				log_message(err_messages[errno]);
				status = false;
		}
		catch(const char *str){
				log_message(str);
				status = false;
		}
		catch(iterator_overflow &iof){
				iof.whaat_happened(log_file);
				status = false;
		}
		return status;
}
```

异常对象的类型会被拿来逐一和每个catch子句对比，如果类型符合，那么该catch子句的内容便会执行。在通过所有catch子句之后，由正常程序重新接手。

有时候我们可能无法完成异常的完整处理，在记录信息之外，我们或许需要重新抛出（rethrow）异常，以想寻求其他catch子句的协助，做进一步的处理：

```c=+
catch(iterator_overflow &iof){
		log_message(iof.what_happened());
		// 重新抛出异常，由另一个catch子句接手处理
		throw;
}
```

重新抛出时，只需写下关键字throw即可。它只能出现在catch子句中，它会将捕获的异常对象再一次抛出，并由另一个类型吻合的catch子句接手处理。

如果我们想要捕获任何类型的异常，可以在异常声明部分指定省略号(...)即可：

```c++
catch(...){
		log_message("抛出未知异常！");
		// 清理然后退出。
}
```

## 7.3 提炼异常

catch子句应该和try子块相应而生。如果try子块内有任何异常发生，便由接下来的catch子句加以处理。

```c++
try{
		...
		// 出现异常
}
catch(异常类型){
		// 处理异常
}
```

如果一直回到main()还是找不到合适的catch子句，C++则会调用标准库提供的terminate()，该函数的默认行为是中断整个程序的执行。

## 7.4 局部资源管理

对对象而言，初始化操作发生于构造函数内，资源的请求亦应在构造函数内完成。资源的释放则应该在析构函数内完成。

```c++
#include<memory>
void f(){
		auto_ptr<int> p(new int);
		MutexLock ml(m);
		process(p);
		// p和ml的析构函数会在这里被悄悄调用
}
```

p和ml都是局部对象，如果process函数执行无误，那么相应的析构函数便会在函数结束前自动作用于p和ml上。如果process函数执行过程中有任何异常被抛出，p和ml的析构函数保证被调用。

## 7.5 标准异常

标准库定义了一套异常类体系，其根部是名为exception的抽象基类，表明有一个what()虚函数，会范围const char*，用以表示被抛出异常的文字描述和代码段。

#### 练习7.1

以下函数完全没有检查可能的数据错误以及可能的执行失败。请找出此函数所有可能发生错误的地方。本题不考虑出现异常。

```c++
int *alloc_and_init(string file_name){
    ifstream infile(file_name); 
    int elem_cnt;
    infile >> elem_cnt;
    int *pi = allocate_array(elem_cnt);

    int elem;
    int index = 0;
    while(infile >> elem){
        pi[index++] = elem;
    }
    sort_array(pi,elem_cnt);
    register_data(pi);
    return pi;
}
```

1.ifstream的构造函数接受的参数类型是const char* 而不是string

2.infile被定义后，我们应该检查它是否被成功打开

3.处理指针必须检查指针是否确指向实际存在的对象，如果allocate_array()无法分配足够内存，pi便会被设置为0，因此我们必须检查pi是否分配到了内存。

#### 练习7.2 

下列函数被上题的alloc_and_ini()调用，执行失败时会发出异常：

allocate_array()  发出异常noMem

sort_array() 发出异常int

register_data()  发出异常string

请安置一个或多个try块，以及相应的catch子句，以便能适当地处理这些异常。相应的catch子句中只需将错误打印出来即可。

```c++
int *alloc_and_init(string file_name){
    ifstream infile(file_name.c_str());
    if(!infile) return 0;

    int elem_cnt;
    infile >> elem_cnt;
    if(!infile) return 0;

    try {
        int  *pi =  alloc_array(elem_cnt);
        int  elem;
        int  index = 0;
        while(infile >> elem&&index<elem_cnt){
            pi[index++] = elem;
        }
        sort_array(pi,elem_cnt);
        register_data(pi);
    }
    catch(const noMem &err){
        cerr << "Error noMem" <<endl;
        return 0;
    }
    catch(int &err){
        cerr << "Error int" << endl;
        return 0;
    }
    catch(string &err){
        cerr << "Error String" <<endl;
        return 0;
    }
    return pi;
}
```

