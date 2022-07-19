

# 第六章

- ### **一个小问题**：

```c++
class A{
public:
	const A &operator=(const A &a)const{//const{}也就意味着我不会去修改类中的内容	//赋值运算符重载函数的参数是函数所在类的const类型的引用
		return *this;
	}
};

const A a;
A b;
a=b;//为什么对const对象赋值不会报错呢？得从概念上理解，我实际并没有去赋值操作，返回的也是const A的引用——相当于啥也没干。(a=b)这一整个就是b的地址。
```

> - const{}也就意味着我不会去修改类中的内容
> - 赋值运算符重载函数的参数是函数所在类的const类型的引用。为什么要加上const呢？
>   - 我们不希望在这个函数中对用来进行赋值的"原版"做任何修改，这里即便b不是const，但我们只是想把b中的内容读出来，加上const是为了表示这个衷心。
>   - 加上const，对于const和非const的实参，函数就都能接受；如果不加，就只能接受非const的实参。
>
> ### 返回值：
>
> 一般返回值是被赋值者的引用，即*this，原因是：
>
> 1. 在函数返回时避免了一次拷贝，提高了效率
> 2. 更重要的，这样可以实现连续赋值，引用作为左值。
>
> ### 调用时机：
>
> Mystr str2;
>
> str2 = str1;
>
> 和
>
> Mystr str3 = str2
>
> 在调用函数上是有区别的，前者的前一句，声明加定义，调用无参构造函数；后一句调用拷贝构造加赋值运算符重载函数。而后者是用str2来初始化str3，调用的是拷贝构造函数。
>
> #### 赋值运算符重载函数只能是类的非静态成员函数：
>
> 是因为静态成员函数只能操作类的静态成员，不能操作非静态成员
>
> ### 赋值运算符重载要避免自赋值：
>
> 我们通过比较两者的地址是否相同（if(this != &str)）来判断两者是否为同一对象。
>
> 1. 为了效率。避免对其他函数的调用。直接return *this
> 2. 如果类的数据成员中含有指针，自赋值会导致灾难性的后果。假设p=p,先要将p所指向的空间delete掉，因为p所指的空间通常都是new出来的，如果在为p分配新的空间前没有将p原来的空间delete掉，会造成内存泄露。然后再为p分配空间，但是p所指的数据在delete的时候已被销毁，你拿什么来赋？

### 自己实现一个sort函数：

```c++
void sort(int *arr,int l,int r,function<bool(int,int)>cmp){//万能指针
    if(l>r){
        return ;
    }
    int x=l,y=r,z=arr[(l+r)>>1];
    do{
        while(arr[x]<z) ++x;
        while(z<arr[y]) --y;
        if(x<=y){
			swap(arr[x],arr[y]);
            ++x,--y;
        }
    }while(x<=y);
    sort(arr,l,y,cmp);
    sort(arr,x,r,cmp)
}

```





# 第9章

### 性能测试工具：**bench.cpp**

```c++
#include <iostream>
#include <chrono>
using namespace std;
using hrc=std::chrono::high_resolution_clock;//名字太长
using mcs=std::chrono::microseconds;


class Timer{
    std::chrono::time_point<hrc> startTimePoint;
public:
    Timer(){
        startTimePoint = hrc::now();
    }
    void stop(){
        auto endTimePoint=hrc::now();
        auto start=std::chrono::time_point_cast<mcs> (startTimePoint).time_since_epoch().count();
        auto end=std::chrono::time_point_cast<mcs> (endTimePoint).time_since_epoch().count();
        auto duration = end-start;
        cout<<"耗时："<<duration*0.001<<"毫秒("<<duration<<"微秒)"<<endl;
    }
    ~Timer(){
        stop();
    }
};
int main(){
    {//变量作用域
        Timer t;
        int sum=0;
        for(int i=0;i<1000000;i++){
            sum+=2;
        }
    }
    return 0;
}
```

> 使用测试时间只需要将代码范围用{}括起来，作为变量作用域，一开始定义，自动构造开始计时，结束时候，自动调用析构函数，输出时间。

我们无法在类中成员属性里定义auto。

计算duration

计算机到微秒级别就能区分出明显的时间变化

需要把时间转换成微秒级别。

### 代码的优化级别：

- O1   （）
- O2  （进一步优化，使用次数最多）
- O3  （最终发行版）

`g++ bench.cpp -O2`

<img src="C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220317163429183.png" alt="image-20220317163429183" style="zoom: 50%;" />

<img src="C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220317163748316.png" alt="image-20220317163748316" style="zoom: 33%;" />

如果不输出的话，汇编代码都不会生成。

<img src="C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220317163846077.png" alt="image-20220317163846077" style="zoom:33%;" />

**独有指针**：同一时间最多只能有一个指针指向这个对象。（“霸占”）

```c++
unique_ptr<int> p=new int;//不支持隐式转换构造。必须显式 explicit是只能显式转换构造，不能隐式。
unique_ptr<int> p(new int);//这样就是显式构造了
```

> 效率比shared_ptr高

### 把测试时间的工具做进一步拆分

`cp bench.cpp bech.cpp`源文件,删去里面的main函数部分。

`cp bech.cpp bench.h` 还得需要一个头文件。

### **头文件里放什么**：

1. 预处理命令
2. 新类型的定义
3. 函数或者全局变量的声明

> - 带双引号的是当前路径下的#include "bench.h"

> 可以把bech.cpp（源文件，函数实现） 和bench.h（头文件）放到一个文件夹里（bench）主文件里修改头文件路径就可以了，当然链接器链接的时候也要把路径加上。

#### bech.cpp

```c++
#include "bench.h"
Timer::Timer(){
        startTimePoint = hrc::now();
    }
void Timer::stop(){
    auto endTimePoint=hrc::now();
    auto start=std::chrono::time_point_cast<mcs> (startTimePoint).time_since_epoch().count();
    auto end=std::chrono::time_point_cast<mcs> (endTimePoint).time_since_epoch().count();
    auto duration = end-start;
    cout<<"耗时："<<duration*0.001<<"毫秒("<<duration<<"微秒)"<<endl;
}
Timer::~Timer(){
    stop();
}
```

#### bench.h

```c++
#ifndef _BENCH_H_
#define _BENCH_H
#include <iostream>
#include <chrono>
#define BEGINT {\
    Timer t;
#define ENDT }
using namespace std;
using hrc=std::chrono::high_resolution_clock;
using mcs=std::chrono::microseconds;


class Timer{
    std::chrono::time_point<hrc> startTimePoint;
public:
    Timer();
    void stop();
    ~Timer();
};
#endif
```

#### bench.cpp

```c++
#include <iostream>
#include <chrono>
#include <memory>
#include <vector>
#include "bench/bench.h"
using namespace std;

int main(){

BEGINT
    int sum=0;
    for(int i=0;i<1000000;i++){
        sum+=2;
    }
ENDT

    cout<<"make shared"<<endl;
BEGINT
    vector<shared_ptr<int>> shared_vector;
    for(int i=0;i<1000;i++){
        shared_vector.push_back(make_shared<int>());
    }
ENDT

    cout<<"new shared"<<endl;
BEGINT
    vector<shared_ptr<int>> shared_vector2;
    for(int i=0;i<1000;i++){
        shared_vector2.push_back(shared_ptr<int>(new int));
    }
ENDT
    
    cout<<"new unique"<<endl;
BEGINT
    vector<unique_ptr<int>> unique_vector;
    for(int i=0;i<1000;i++){
        unique_vector.push_back(unique_ptr<int>(new int));
    }
ENDT
    /*
    vector<unique_ptr<int>> unique_vector2;
    for(int i=0;i<1000;i++){
        unique_vector2.push_back(make_unique<int>());
    }*/
    return 0;
}
```





### 实现自己的优先队列：PQueue

```c++
#include <iostream>
using namespace std;
class PQueue{
public:
    virtual void push(int)=0;
    virtual void pop()=0;
    virtual bool empty()=0;
    virtual int top()=0;
    virtual int size()=0;
};
class vector_queue:public:PQueue, public:vector<int>{

};

int main(){

    return 0;
}

```



```c++
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<vector>
#include "bench/bench.h"
using namespace std;

class PQueue{
    virtual void push(int x);
    virtual void pop();
    virtual int top();
    virtual int empty();
    virtual int size();
};

class vector_queue:public PQueue,public vector<int>{
    virtual void push(int x){
        this->vector<int>::push_back(x);
    }
    virtual void pop(){
        if(empty())
            return ;
        vector<int>::iterator p=begin();
        for(auto iter=begin();iter!=end();iter++){
			if(*iter>*p)
                p=iter;
        }
        erase(p);
        return ;
    }
    virtual int top(){
        if(empty())
            return 0;
        int m=at(0);
        for(int i=1;i<size();i++){
            m=max(m,at(i));
        }
        return m;
    }
    virtual int empty(){
        return size()==0;
    }
    virtual int size(){
        return vector<int>::size();
    }
};


int main(){
	srand(time(0));
    vector_queue q1;
    for(int i=0;i<10;i++){
        int rnd=rand()%100;
        q1.push(rnd);
        cout<<rnd<<" ";
    }
    cout<<endl;
BEGINT
    while(!q1.empty()){
        cout<<q1.top()<<" ";
        q1.pop();
    }
    cout<<endl;
ENDT
	return 0;
}
```



### map<key,value> m

```c++
//申明
map<int,int>m;
//插入值
for(int i=0;i<10;i++){
    m[rand()%10]=rand();
}
//输出值
for(auto it=m.begin();it!=m.end();it++){
	cout<<it->first<<it->second<<endl;
}
```

### 左右值引用

```c++
//左值引用
void func(int &x){
    cout<<"left value"<<endl;
    return ;
}
//右值引用
void func(int &&x){
    cout<<"right value"<<endl;
    return ;
}

int x=123;
func(123);// right value;
func(x);// left value;
```

![image-20220317224359017](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220317224359017.png)

### 宏定义

```c++
#define func(x) __func(x,"func(" #x ")")
void __func(int &x,string str){
    cout<<x<<" is left value"<<endl;
}
func(123);//func(123) is right value;
```

### vector.cpp

```c++
#include<iostream>
using namespace std;
#define KKBB namespace kkb{
#define KKBE }

KKBB
class vector{
    int __size;
    int *data;
public: 
    vector(int n=10):__size(n),data(new int[n]){}
    ~vector(){
        delete[] data;
        data=nullptr;
        __size=0;
    }
    vector(const vector &v):__size(v.__size),data(new int[v.__size]){
        for(int i=0;i<__size;i++){
            data[i]=v[i];
        }
    }
    vector(vector &&v):__size(v.__size),data(v.data){
        cout<<"move constructor"<<endl;//移动构造
        v.__size=0;
        v.data=nullptr;
    }
    vector operator+(const vector &v){
        vector ret(this->__size+v.size);
        for(int i=0;i<this->__size;i++){
            ret[i]=(*this)[i];
        }
        for(int i=this->__size;i<ret.__size;i++){
            ret[i]=v[i-__size];
        }
        return ret;
    }
    int &operator[](int idx)const{//const对象要用const方法
        return this->data[idx];
    }
    int size(){
        return __size;
    }
};
KKBE
    
ostream &operator<<(ostream &out,const kkb::vector &v){
	for(int i=0;i<v.size();i++){
        i && cout<<",";
        cout<<v[i]<<endl;
    }
    return out;
}
int main(){
	kkb::vector v1,v2;
    for(int i=0;i<v1.size();i++){
        v1[i]=rand()%100;
    }
    for(int i=0;i<v1.size();i++){
        v2[i]=rand()%100;
    }
    kkb::vector v3=v1+v2;
    cout<<v1<<endl;
    cout<<v2<<endl;
    cout<<v3<<endl;
    return 0;
}
```

使用两次移动构造：

![image-20220318085026418](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220318085026418.png)

![image-20220318084938951](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220318084938951.png)

```c++
kkb::vector v4(v3);
kkb::vector v4(forward<const kkb::vector &>(v3));//还是深拷贝

kkb::vector v4(move(v3));//这下变成右值以后调用的就是移动拷贝
kkb::vector v4(forward<kkb::vector &&>(v3));
cout<<v4<<endl;
```

### const引用能兼容左值和右值

![image-20220318090130876](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220318090130876.png)

![image-20220318090715709](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220318090715709.png)





### 模板函数(例一)add.cpp

> - 抽象程度更高。

以一个简单的例子作为切入：

```c++
#include <iostream>
using namespace std;
int add(int a,int b){
    return a+b;
}
double add(double a,double b){
    return a+b;
}

int main(){
    cout<<add(1,2)<<endl;
    cout<<add(1.2,4.3)<<endl;
    return 0;
}
```

仅是换个类型就需要重新定义是不是觉得很麻烦，**模板**可以解决这一切。

- **模板的声明**：

```c++
template <typename T> //<>里面写下你接下来在这个模板中要出现的类型有哪些？
```

之前代码只需做如下更改：

```c++
#include <iostream>
using namespace std;
template <typename T>
T add(T a,T b){
    cout<<"moban"<<endl;
    return a+b;
}
double add(double a,double b){
    cout<<"putong"<<endl;
    return a+b;
}

int main(){
    cout<<add(1,2)<<endl;//调用了模板函数
    cout<<add(1.2,4.3)<<endl;//调用的任然是普通函数
    return 0;
}
```

> 注意模板可以看作是备选项，优先会调用本身就契合的函数调用。

- **模板在不调用它的时候**，**是不占内存的**：

![image-20220320214212409](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220320214212409.png)

> 如图，相比于普通函数，模板函数汇编代码都没有生成。

- **显示地指定所传入的类型：**

```c++
//方法一：

#include <iostream>
using namespace std;
template <typename T>
T add(T a,T b){
    return a+b;
}
int main(){
    cout<<add<float>(1.2,3,3)<<endl;//显示地指定所传入的类型
    return 0;
}
————————————————————————————————————————————————————————————
//方法二：
    
#include <iostream>
using namespace std;
template <typename T,typename U>//能兼容T和U为同一类型的情况

//直接a+b是会报错的，这个时候还不知道a和b是什么呢。
/*decltype(a+b) add(T a,U b){
    return a+b;
}*/

//构造俩临时对象，加完啥就是啥，作为我返回的类型：
decltype(T()+U()) add(T a,U b){
    return a+b;
}
int main(){
    cout<<add(1.2,3)<<endl;
    return 0;
}
```

> 但是第二种方法还有漏洞：它依赖于类的默认构造函数。

- **decltype(表达式)** 返回表达式类型 

- **typeid(a).name()** 查看变量类型

  ```c++
  #include<typeinfo>
  
  decltype(1+2) a; //定义一个int类型的a
  cout<<typeid(a).name()<<endl; //i
  ```

> 举个漏洞的简单例子：

```c++
//定义这样一个类：
class A{
    int x;
public:
    A()=delete;//默认构造函数被删了，只留下了转换构造函数。
    A(int x):x(x){}
    
    //加法重定义
    A operator+(const A &b){//传进要被加的参数。用const修饰，表示对象是只读的。
        return A(x+b.x);//私有成员属性可以在类内被访问。参数类也算在类内。
    }
    friend ostream &operator<<(ostream &out,const A &a);//友元函数
};

ostream &operator<<(ostream &out,const A &a){
    cout<<a.x; //类外不能直接访问私有的成员属性。可以通过设置成友元函数解决
    return out;
}

template <typename T,typename U>
decltype(T()+U()) add(T a,U b){//这下T 和U 所依赖的默认构造函数被删了，程序会报错
    return a+b;
}
```

> - 注意在加法重载的时候不能返回类的引用，因为匿名对象会被销毁，那块内存也随之被销毁。
> - 我们可以把外面的引用往里传，不可以把里面的引用往外传。

- 解决方法是**返回值后置：**

```c++
template <typename T,typename U>
auto add(T a,U b)->decltype(a+b){//这样完美解决了问题，且就不需要对A进行默认构造了
	return a+b;
}
```

#### 例一完整代码：(模板函数)add.cpp

```c++
#include <iostream>
#include <typeinfo>
using namespace std;
class A{
    int x;
public:
    A()=delete;
    A(int x):x(x){};
    
    
    A operator+(const A &a){
        return A(x+a.x);
    }
    friend ostream &operator<<(ostream &out,const A &a);
};
ostream &operator<<(ostream &out,const A &a){
    cout<<a.x;
    return out;
}

/*template <typename T,typename U>
decltype(T()+U()) add(T a, U b){
    cout<<"moban2"<<endl;
    return a+b;

}*/
template <typename T,typename U>
auto add(T a,U b)->decltype(a+b){
    cout<<"moban"<<endl;
    return a+b;
}

int main(){
    decltype(1+2) a;
    cout<<typeid(a).name()<<endl;
    cout<<add(1,2)<<endl;
    cout<<add(1.2,4)<<endl;
    
    A aa(3),bb(4);
    cout<<add(aa,bb)<<endl;
    
    return 0;
}
```

------

### 模板的类：

```c++
#include <iostream>
using namespace std;

template <typename T>
class PRINT{
public:
    //template <typename T>//
    
    //重载小括号,实现仿函数功能
    PRINT &operator()(T t){
        //传进来一个T的对象，任务就是输出t.
        cout<<t<<endl;
        //我希望能够连续输出，返回的还是一个函数对象
        return *this;
    }
};

int main(){
    PRINT<int> pint;//必须指明T是什么类型,用 <type>来表示；
    pint(123)(423)(654);
    PRINT<string> pstr;
    pstr("kkb")("hh")("good");
    
    return 0;
}
```

> 注意如果template <typename T>放到类中的话就变成，类中的模板函数。
>
> 于是实例化类的时候不需要指定类型，就可以根据实际传入类型连续输出：
>
> ```c++
> PRINT pt;
> pt(123)(423)(654)("kkb")("hh")("good");
> ```



### myvec.cpp(例二)

- 定义好自己的命名空间：

```c++
#define KKBB namespace kkb{
#define KKBE }
```

- 用模板类实现自己的vector：

  ```c++
  KKBB
  template <typename T>
  class vector{
      int __Size;
      T *data;//改成任意类型
  public:
      vector(int n=10):__size(n),data(new T[__size]){}
      virtual ~vector(){//一般析构都要定义成虚析构
          if(data)
              delete[] data;
          __size=0;
      }
  };
  KKBE
  ```

  > 注意，一般析构函数都要定义成虚析构，毕竟继承的子类析构方法当然可能和父类不一样
  >
  > 同时也还是会有默认构造函数没有，new时导致报错的情况，解决办法如下：
  >
  > ```c++
  > vector(int n=10):__size(n),data(nullptr){
  >     data=(T *)malloc(sizeof(T)*n);
  > }
  > virtual ~vector(){//一般析构都要定义成虚析构
  >         if(data)
  >             free(data);//上面用malloc,下面用free.
  >         __size=0;
  >     }
  > ```
  >
  > malloc并不会调用构造函数，用它替代就能避开构造问题；

- 实现拷贝构造函数：

  ```c++
  vector(const vector<T> &v):__size(v.__size){
      data=(T *)malloc(sizeof(T)*__size);
      for(int i=0;i<__size;i++){
          //data[i]=v.data[i];//data没有初始化，赋值之前得想办法让它初始化，否则不妥
          new (data+i) T(v.data[i])//原地构造
      }
  }
  ```

- 实现移动构造：

  ```c++
  vector(vector<T> &&v):__size(v.__size),data(v.data){
      v.__size=0;
      v.data=nullptr;
  }
  ```

- 中括号访问：

  ```c++
  T &operator[](int idx)const{//为了使用更加多样化
     return data[idx] 
  }
  ```

- 能返回size：

  ```c++
  int size()const{ //加const防止对象是常对象的情况，提高健壮性。
      return __size;
  }
  ```

- __size默认就是10，其意义应当是容量，而系统的vector是个数的意思。所以把所有的size换成capacity，vim指令为：`:%s/__size/__capacity/g`。完整代码如下：

  ```c++
  #include <iostream>
  #include <vector>
  using namespace std;
  #define KKBB namespace kkb{
  #define KKBE }
  class A{
      int x;
  public:
      A()=delete;
      A(int x):x(x){}
  };
  KKBB
  template <typename T>
  class vector{
      int __capacity;
      T *data;
      int __size;
  public:
      vector(int n=10):__capacity(n),data(nullptr),__size(0){
          data=(T *)malloc(sizeof(T)*__capacity);
      }
      virtual ~vector(){
          if(data)
              free(data);
          __capacity=0;
          __size=0;
      }
      vector(const vector<T> &v):__capacity(v.__capacity),data(v.data),__size(v.__size){
          data=(T *)malloc(sizeof(T)*__size);
          for(int i=0;i<__size;i++){
              new (data+i) T(v.data[i]);
          }
      }
      vector(const vector<T> &&v):__capacity(v.__capacity),data(v.data),__size(v.__size){
          v.__capacity=0;
          v.__size=0;
          v.data=nullptr;
      }
      T &operator[](int idx)const{
          return data[idx];
      }
      int size()const{
          return __size;
      }
  };
  
  KKBE
  int main(){
      const vector<A> a;
      const kkb::vector<A> b;
      cout<<a.size()<<endl;
      cout<<b.size()<<endl;
  
      return 0;
  }
  
  ```

**优化**：开发的时候往往要求类的声明和里面的东西分开写：

```c++
KKBB
template <typename T>
class vector{
    int __capacity;
    T *data;
    int __size;
public:
    vector(int n=10);//成员函数在类外定义时，默认参数写在声明处。
    virtual ~vector();
    vector(const vector<T> &v);
    vector(const vector<T> &&v);
    T &operator[](int idx)const;
    int size()const;
};

/*template <typename T>
vector<T>::vector(int n=10):__capacity(n),data(nullptr),__size(0){
    data=(T *)malloc(sizeof(T)*__capacity);
}*/
template <typename T>
vector<T>::vector(int n):__capacity(n),data(nullptr),__size(0){//成员函数在类外定义时，默认参数写在声明处。
    data=(T *)malloc(sizeof(T)*__capacity);
}
template <typename T>
vector<T>::~vector(){//析构函数在外面定义的时候就不用写virtual了
    if(data)
        free(data);
    __capacity=0;
    __size=0;
}

template <typename T>
vector<T>::vector(const vector<T> &v):__capacity(v.__capacity),data(v.data),__size(v.__size){
    data=(T *)malloc(sizeof(T)*__size);
    for(int i=0;i<__size;i++){
        new (data+i) T(v.data[i]);
    }
}

template <typename T>
vector<T>::vector(const vector<T> &&v):__capacity(v.__capacity),data(v.data),__size(v.__size){
    v.__capacity=0;
    v.__size=0;
    v.data=nullptr;
}

template <typename T>
T &vector<T>::operator[](int idx)const{
    return data[idx];
}

template <typename T>
int vector<T>::size()const{
    return __size;
}
KKBE
-----------------------------------------------------------------------------------------

```

> - 注意析构函数在外面定义的时候就不用写virtual了，声明的时候写就够了。
>
> - 成员函数在类外定义时，默认参数写在声明处
> - 接口函数说明就可以写在声明处了。

输出v的内容：

```c++
//
class A{
    int x;
public:
    A()=delete;
    A(int x):x(x){}
    friend ostream &operator<<(const A &a);
};
ostream &operator<<(const A &a){
    cout<<a.x<<endl;
    return out;
}
int main{
    vector<int> v;
    kkb::vector<int> v2;
    
    cout<<v[0]<<endl;//segmentationfault，原因是数组访问越界了
    cout<<v2[0]<<endl;//能输出0;
    return 0;
}
```

- **实现push_back():**

```c++
void push_back(const T t){
    new (data+__size) T(t);//但是这样做拷贝次数会比较多
    __size++;
    return ;
}
void push_back(T &&t){//传右值引用的情况：
    new (data+__size) T(move(t));
    __size++;
    return ;
}
int main(){
    vector<A> a;
    kkb::vector<A> b;
    for(int i=0;i<10;i++){
        a.push_back(rand()%100);
    }
    for(int i=0;i<10;i++){
        b.push_back(rand()%100);
    }
    cout<<a<<endl;
    cout<<b<<endl;

    return 0;
}
```

> **move()：将左值变成右值。**

- A类vector对象的输出重载：

  ```c++
  ostream &operator<<(ostream &out,const kkb::vector<A> &v){//kkb下的
      for(int i=0;i<v.size();i++){
          i && out<<",";
          out<<v[i];
      }
      return out;
  }
  ostream &operator<<(ostream &out,const vector<A> &v){//系统的
      for(int i=0;i<v.size();i++){
          i && out<<",";
          out<<v[i];
      }
      return out;
  }
  ```

#### 例二完整代码：(myvec)

```c++
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
#define KKBB namespace kkb{
#define KKBE }

class A{
    int x;
public:
    A()=delete;
    A(int x):x(x){}
    friend ostream &operator<<(ostream &out, const A &a);
};

ostream &operator<<(ostream &out, const A &a){
    out<<a.x;
    return out;
}
KKBB

template <typename T>
class vector{
    int __capacity;
    T *data;
    int __size;
public:
    vector(int n=10);
    virtual ~vector();

    vector(const vector<T> &v);
    vector(const vector<T> &&v);
    T &operator[](int idx)const;
    int size()const;
    void push_back(const T &t);
    void push_back(T &&t);

};

template <typename T>
vector<T>::vector(int n):__capacity(n),data(nullptr),__size(0){
    data=(T *)malloc(sizeof(T)*__capacity);
}
template<typename T>
vector<T>::~vector(){
    if(data)
        free(data);
        __capacity=0;
        __size=0;
}
template<typename T>
vector<T>::vector(const vector<T> &v):__capacity(v.__capacity),data(v.data),__size(v.__size){
    data=(T *)malloc(sizeof(T)*__size);
    for(int i=0;i<__size;i++){
        new (data+i) T(v.data[i]);
    }
}
template<typename T>
vector<T>::vector(const vector<T> &&v):__capacity(v.__capacity),data(v.data),__size(v.__size){
    v.__capacity=0;
    v.__size=0;
    v.data=nullptr;
}
template<typename T>
T &vector<T>::operator[](int idx)const{
    return data[idx];
}
template<typename T>
int vector<T>::size()const{
    return __size;
}
template<typename T>
void vector<T>::push_back(const T &t){
    new (data+__size) T(t);
    __size++;
    return ;
}
template<typename T>
void vector<T>::push_back(T &&t){
    new (data+__size) T(move(t));
    __size++;
    return ;
}
KKBE

ostream &operator<<(ostream &out,const kkb::vector<A> &v){
    for(int i=0;i<v.size();i++){
        i && out<<",";
        out<<v[i];
    }
    return out;
}
ostream &operator<<(ostream &out,const vector<A> &v){
    for(int i=0;i<v.size();i++){
        i && out<<",";
        out<<v[i];
    }
    return out;
}
int main(){
    vector<A> a;
    kkb::vector<A> b;
    cout<<a.size()<<endl;
    cout<<b.size()<<endl;
    //cout<<a[0]<<endl;
    cout<<b[0]<<endl;

    for(int i=0;i<10;i++){
        a.push_back(rand()%100);
    }
    for(int i=0;i<10;i++){
        b.push_back(rand()%100);
    }
    cout<<a<<endl;
    cout<<b<<endl;

    return 0;
}
```

### 引用折叠：

- 例子：用模板实现swap()

```c++
#include <iostream>
using namespace std;
#define KKBB namespace kkb{
#define KKBE }
KKBB
template<typename T>
//void swap(T &a,T &b){//这样子当我们传入一个右值的时候会报错
void swap(T &&a,T &&b){//引用折叠，&&并不代表这是个右值引用，而是代表这是个引用，但至于是哪个引用，再让模板判断。
    T c;//会报错，如果传进来的是m和n是个左值引用，那么c必须初始化。
    c=a;
    //T c=a;//这样写的话，c是a的别名，a又是b的别名，a,b,三人就都是4
    //正确方法是 auto c=a;
    a=b;
    b=c;
    return ;
}
KKBE
int main(){   
    int m=4,n=3;
    swap(m,n);//T被推理成int&  即：int&&& a等价于 int &a
    kkb::swap(111,222);//传进去两个右值T被推理成int   即int &&a
    return 0;
}

```

> swap()传进去两个右值，我们当然希望模板能把T &a解释成 T &&a   也就是T对应T& ,但是模板并没有这样做，还报了个错。
>
> 模板中&&并不代表这是个右值引用，而是代表这是个引用，但至于是哪个引用，再让模板判断。
>
> ### 引用特性：
>
> - 奇数个引用是左值引用，
>
> - 偶数个引用是右值引用。

> - 引用需要被初始化

## typename remove_reference<T>::type

- **去掉模板推断的引用效果:** 

> 如果T是int & 那么处理之后就变成int 如果原来是int，那么处理之后也是int

```c++
#include <iostream>
using namespace std;
#define KKBB namespace kkb{
#define KKBE }
KKBB
template<typename T>
void swap(T &&a,T &&b){
    //定义typename remove_reference<T>::type 这样的类型：
   	typename remove_reference<T>::type c=a;//去掉模板推断的引用效果:如果T是int & 那么处理之后就变成int 如果原来是int，那么处理之后也是int;
    a=b;
    b=c;
    return ;
}
KKBE
int main(){   
    int m=4,n=3;
    swap(m,n);
    kkb::swap(111,222);
    return 0;
}
```



## 第13章

## 类的特化：

- ### 全特化：（自己的房间自己扫）

> ### 类型全部确定

> 出现特殊情况，就得按我说的去做：

```c++
#include <iostream>
#include <typeinfo>
using namespace std;
class A{
    int x;
public:
    A()=delete;
    A(int x):x(x){};
    
    
    A operator+(const A &a){
        return A(x+a.x);
    }
    friend ostream &operator<<(ostream &out,const A &a);
};
ostream &operator<<(ostream &out,const A &a){
    cout<<a.x;
    return out;
}
template <typename T,typename U>
auto add(T a,U b)->decltype(a+b){//就算推成指针类型，指针地址加来加去的也是不对的。
    cout<<"moban"<<endl;
    return a+b;
}
//函数模板的全特化：出现特殊情况，就得按我说的去做：
template <typename T,typename U>
auto add(T *a,U *b)->decltype(*a+*b){//对于指针的情况，这样来做
    cout<<"moban"<<endl;
    return *a+*b;
}
template <>//有<>说明也是模板函数的特化版本，因为类型是什么都已经确定下来了，所以<>里面也就不再写什么东西了
auto add(int a,int b){//里面的T和U都已经非常确定了，都是int类型
    return a*b;
}

int main(){
    decltype(1+2) a;
    cout<<typeid(a).name()<<endl;
    cout<<add(1,2)<<endl;//输出的变成了2
    cout<<add(1.2,4)<<endl;
    
    A aa(3),bb(4);
    cout<<add(aa,bb)<<endl;

    int m=123,n=456;
    int *p=&m,*q=&n;
    cout<<add(p,q)<<endl;//输出指针类型就不行？
    
    return 0;
}
```

> - **指针类型不在模板的控制范围之内，我们需要对指针类型做特殊化处理**

> - **如果有模板全特化的，优先走模板特化类型。**



- ### 偏特化：

> #### 已经有部分的类是确定的

### classspecial.cpp

```c++
#include <iostream>
using namespace std;

template <typename T,typename U>//普通版本
class Test{
public:
    Test(){
        cout<<"normal template"<<endl; 
    }
};
template <>//全特化版本
class Test<int ,double>{//上面<>里面不用写，但是这里得写上类型是什么
public:
    Test(){
        cout<<"specialization template"<<endl; 
    }
};
template <typename T>//偏特化版本
class Test<int,T>{
public:
    Test(){
        cout<<"partial specialization template<int ,T>"<<endl; 
    }
};

int main(){
    //问题来了，这三个对应版本，到底哪个优先执行？
	Test<int,double> t1;//全特化
    Test<double,int> t2;//普通版本
    Test<int,int> t3;//偏特化

    return 0;
}
```

> **调用模板类的顺序也就是 全特化->偏特化->普通版本**
>
> 

```c++
#include <iostream>
using namespace std;

template <class T>
class Type_trail{
public:
    static string has_constructor;//static声明这是静态的一个属性
};
template<class T>//类外定义
string Type_trail<T>::has_constructor="yes";

class A{};
class C{};

template <>
class Type_trail<double>{
public:
    static string has_constructor;
};
//template<>//对于显示的全特化，类外定义要去掉模板头。without a template header
string Type_trail<double>::has_constructor="no";

template <>
class Type_trail<int>{
public:
    static string has_constructor;
};
string Type_trail<int>::has_constructor="no";

template <>
class Type_trail<string>{
public:
    static string has_constructor;
};
string Type_trail<string>::has_constructor="no";

template <>
class Type_trail<bool>{
public:
    static string has_constructor;
};
string Type_trail<bool>::has_constructor="no";

template <class T>
class Type_trail<T *>{//指针类型
public:
    static string has_constructor;
};
template <class T>
string Type_trail<T *>::has_constructor="no";


int main(){
    //实现对下列类型输出no
    cout<<Type_trail<double>::has_constructor<<endl;
    cout<<Type_trail<int>::has_constructor<<endl;
    cout<<Type_trail<string>::has_constructor<<endl;
    cout<<Type_trail<bool>::has_constructor<<endl;
	cout<<Type_trail<char *>::has_constructor<<endl;
    
    //对自己写的类呢输出yes
    cout<<Type_trail<A>::has_constructor<<endl;
	cout<<Type_trail<C>::has_constructor<<endl;
    return 0;
}

```

> - 利用**类名::**就能访问的属性是**static**，它的定义要放在类外面

`报错信息：members of an explicitly specialized class are defined without a template header`

> 对于显示的全特化，类外定义要去掉模板头。

- 显然以上方法，结构性不强，做了很多重复工作。既然学了类的继承，我们想办法做一个统一的内容，让大家去调用。有一个专门放yes属性的类，和专门放no属性的一个类。然后谁是哪个类的就继承过去。完事了

## 实操：不同类型输出不同内容的模板类属性

### 一：constructor.cpp(通过继承实现)

```c++
#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <cstdio>
#include <map>
#include <string>
#include <algorithm>
using namespace std;
#define KKBB namespace kkb{
#define KKBE }
KKBB
KKBE
class yes_constructor{
public:
    static string has_constructor;
};
string yes_constructor::has_constructor="yes";

class no_constructor{
public:
    static string has_constructor;
};
string no_constructor::has_constructor="no";

template <class T>
class Type_trail:public yes_constructor{
};


template <>
class Type_trail<double>:public no_constructor{
public:
};

template <>
class Type_trail<int>:public no_constructor{
public:
};

template <>
class Type_trail<string>:public no_constructor{
public:
};

template <>
class Type_trail<bool>:public no_constructor{
public:
};

template <class T>
class Type_trail<T *>:public no_constructor{

};

class A{};
class C{};
int main(){

    cout<<Type_trail<double>::has_constructor<<endl;
    cout<<Type_trail<int>::has_constructor<<endl;
    cout<<Type_trail<string>::has_constructor<<endl;
    cout<<Type_trail<bool>::has_constructor<<endl;
    cout<<Type_trail<char *>::has_constructor<<endl;

    cout<<Type_trail<A>::has_constructor<<endl;
    cout<<Type_trail<C>::has_constructor<<endl;

    return 0;
}

```

**输出测试宏的封装：**

```c++
#define TEST(type){\
    cout<<#type<<":"<<Type_trail<type>::has_constructor<<endl;\
}
int main(){
    TEST(double);
    TEST(int);
    TEST(string);
    TEST(bool);
    TEST(char *);
    TEST(A);
    TEST(C);
    return 0;
}

```



### **二：作为类中的一个类型：**

```c++
#include <iostream>

class yes_constructor{};
class no_constructor{};

template <class T>
class Type_trail{
public:
    typedef yes_constructor has_constructor;
};

template <>
class Type_trail<double>{
public:
    typedef no_constructor has_constructor;
};

template <>
class Type_trail<int>{
public:
    typedef no_constructor has_constructor;
};

template <>
class Type_trail<string>{
public:
    typedef no_constructor has_constructor;
};

template <>
class Type_trail<bool>{
public:
    typedef no_constructor has_constructor;
};

template <class T>
class Type_trail<T *>{
public:
    typedef no_constructor has_constructor;//为类起个别名，作为类中的一个类型
};

class A{};
class C{};
#define TEST(type){\
    cout<<#type<<":"<<Type_trail<type>::has_constructor()<<endl;\//类名+()  构造，构造完形成构造好的一个对象，所以输出的就是yes_constructor或者no_constructor的一个对象
}
ostream &operator<<(ostream &out,const yes_constructor &){//重载输出不同类的内容
    out<<"yes";
    return out;
}
ostream &operator<<(ostream &out,const no_constructor &){
    out<<"no";
    return out;
}
int main(){
    TEST(double);
    TEST(int);
    TEST(string);
    TEST(bool);
    TEST(char *);
    TEST(A);
    TEST(C);

    return 0;
}

```

类名+()  构造，构造完形成构造好的一个对象，所以输出的就是yes_constructor或者no_constructor的一个对象



### 三：重载小括号版本：

```c++
#include <iostream>

class yes_constructor{
public:
    string operator()(){//重载小括号
        return "yes";
    }
};
class no_constructor{
public:
    string operator()(){//重载小括号
        return "no";
    }
};


template <class T>
class Type_trail{
public:
    typedef yes_constructor has_constructor;
};


template <>
class Type_trail<double>{
public:
    typedef no_constructor has_constructor;
};

template <>
class Type_trail<int>{
public:
    typedef no_constructor has_constructor;
};

template <>
class Type_trail<string>{
public:
    typedef no_constructor has_constructor;
};

template <>
class Type_trail<bool>{
public:
    typedef no_constructor has_constructor;
};

template <class T>
class Type_trail<T *>{
public:
    typedef no_constructor has_constructor;
};

class A{};
class C{};
#define TEST(type){\
    cout<<#type<<":"<<Type_trail<type>::has_constructor()()<<endl;\//这里第一个小括号是构造函数返回一个类，第二个是使用仿函数调用小括号重载函数
}

int main(){
    TEST(double);
    TEST(int);
    TEST(string);
    TEST(bool);
    TEST(char *);
    TEST(A);
    TEST(C);
   
    return 0;
}

```

## 不定参

#### 一：连续输出内容（不定参函数）

```c++
#include <iostream>

template <class T>
void print(T a){//递归边界首先定义
    cout<<a<<endl;
}
template <class T,class ...ARGS>//...ARGS表示有多个参数
void print(T a,ARGS... args){//定义有多个的参数
    cout<<a<<endl;
    print(args...);//递归调用时...
}
//模板类——能够取出不定参的类型。
int main(){
    print(123);
    print("asd");
    print(12.3,'a',"sad");
    return 0;
}
```

#### 二：输出类型（不定参类）

```c++
#include <iostream>
#include <typeinfo>
using namespace std;

template <class T,class ...ARGS>
class N_ARGS{
public:
    typedef T type;
    typedef N_ARGS<ARGS...> rest;//当ARGS的个数只有一个的时候，模板就会出现不匹配的情况，这时就需要定义下方的偏特化的模板（递归边界）
};
template <class T>//特化版本要写在普通版本之后
class N_ARGS<T>{//在此加上<>是为了说明这个是上面那种情况的特例，而不是我新定义的一个模板。
public:
	typedef T type;
};

int main(){
    
    N_ARGS<int,double,string >::type a;
    N_ARGS<int,double,string>::rest::type b;
    N_ARGS<int,double,string>::rest::rest::type c;

	cout<<typeid(a).name()<<endl;
	cout<<typeid(b).name()<<endl;
	cout<<typeid(c).name()<<endl;

    return 0;
}

```

> - 当ARGS的个数只有一个的时候，模板就会出现不匹配的情况，这时就需要定义下方的偏特化的模板（递归边界）
> - 特化版本要写在普通版本之后
> - 在特化版本class 类的时候加上<>是为了说明这个是上面那种情况的特例，而不是我新定义的一个模板。

#### 三：实现两数相加在返回（不定参函数对象）

```c++
#include <iostream>
#include <typeinfo>
using namespace std;

template <class T,class ...ARGS>
class N_ARGS{
public:
    typedef T type;
    typedef N_ARGS<ARGS...> rest;
};
template <class T>
class N_ARGS<T>{
public:
	typedef T type;
    typedef T last;//last跟type含义不一样，type在普通模板和最终版本里都有定义，而last只在最终版本有定义。//last的功能就是限制传参个数；如果传了last就说明，这个是最终版本，你不能再传参了
};

template <class T,class ...ARGS>
class Test{
public:
    T operator()(typename N_ARGS<ARGS...>::type a,typename N_ARGS<ARGS...>::rest::last b){//传了个last
        return a+b;
    }
};

int main(){
    
    N_ARGS<int,double,string >::type a;
    N_ARGS<int,double,string>::rest::type b;
    N_ARGS<int,double,string>::rest::rest::type c;
    N_ARGS<int,double,string,int>::rest::rest::last c;//会报错，这里想返回的是第三个参数，但是last限定第三个参数为末尾参数，现在有四个参数，所以报错。

	cout<<typeid(a).name()<<endl;
	cout<<typeid(b).name()<<endl;
	cout<<typeid(c).name()<<endl;

    cout<<"==============================="<<endl;
    Test<int,int,int> t1;
    Test<double,double,int> t2;
    
    cout<<t1(1.1,2.2)<<endl;
    cout<<t2(1.1,2.2)<<endl;
    cout<<t2(1.1,2.2,3.3)<<endl;//会报错，小括号重载里面写的是last，限制了传参个数为2个.
    return 0;
}

```

> 利用了第二个例子取类型。

**模板编程需要注意的事项**：	

> - <>需不需要加
> - template 需不需要加
> - 统一用typename，不用class 





## 第14章

#### 一、承接上一章第三个

> - 能不能实现像下面这样更像个函数一点的：

```r
Test<int(int,int)> t1
Test<double(double,int)> t2
```

```c++
#include <iostream>
using namespace std;

template <class T,class ...ARGS>
class N_ARGS{
public:
    typedef T type;
    typedef N_ARGS<ARGS...> rest;
};
template <class T>
class N_ARGS<T>{
public:
    typedef T last;//可以只剩下last,更为严格
};

template <class T,class ...ARGS>
class Test{};//普通版本。。。啥也没干，目的就是让我们定义偏特化版本。

template <class T,class ...ARGS>
class Test<T(ARGS...)>{//实现偏特化版本的模板特例，返回值是T,参数是ARGS...
public:
    T operator()(typename N_ARGS<ARGS...>::type a,typename N_ARGS<ARGS...>::rest::last b){//传了个last
        return a+b;
    }
};

int main(){
    
    Test<int(int,int)> t1;
    Test<double(double,int)> t2;
    
    cout<<t1(1.1,2.2)<<endl;
    cout<<t2(1.1,2.2)<<endl;
    cout<<t2(1.1,2.2,3.3)<<endl;//会报错，小括号重载里面写的是last，限制了传参个数为2个.
    return 0;
}

```

- 普通版本（主模板）更为简洁的写法：

```c++
template <class T,class ...ARGS> class Test;
```

#### 二：传入数字

```c++
#include <iostream>
using namespace std;
template <int M>
void print(){
    cout<<M<<",";
    print<M-1>();
    return ;
}
template <>
void print<1>(){
    cout<<1<<endl;
}
int main(){
    print<5>();
    print<3>();
    return 0;
}
```

#### 三、承接上一章第二个：`C_ARGS<1, ARGS...>`

**能不能实现指定取第几个参数**：

```c++
#include <iostream>
#include <typeinfo>
using namespace std;

template <int N, class T,class ...ARGS>
class C_ARGS{
public:
    typedef typename C_ARGS<int N-1,class ARGS...>:: type;//递归调用
};
template <typename T,typename ...ARGS>
class C_ARGS<1,T,ARGS...>{//递归边界
public:
	typedef T type;
};
template <typename T>
class C_ARGS<1,T>{//递归边界
public:
	typedef T type;
};

template <class T,class ...ARGS>
class Test{
public:
    //判断剩下的参数就是2个
    T operator()(typename C_ARGS<1, ARGS...>::type a,\
                 typename C_ARGS<2,ARGS...>::type b){
        return a+b;
    }
};

int main(){
    
    Test<int,int,int> t1;
    Test<double,double,int> t2;
    
    cout<<t1(1.1,2.2)<<endl;
    cout<<t2(1.1,2.2)<<endl;
    return 0;
}
```



#### 四：获得参数个数

```c++
#include <iostream>
#include <typeinfo>
using namespace std;

template <typename T,typename ...ARGS>
struct NUM_ARGS{
    static constexpr int n=NUM_ARGS<ARGS...>::n+1;//递归
};
template <typename T>
struct NUM_ARGS<T>{
    static constexpr int n=1;//递归边界
};

int main(){

    cout<<NUM_ARGS<int,double,bool>::n<<endl;
    return 0;
}
```

> constexpr 是在编译器就应该确定下来。特别适合模板类
>

#### 五：判断是否为0

```c++
template <int N>
struct Zero{
    typedef int no;
};
template <>
struct Zero<0>{
    typedef int yes;
};

template <class T,class ...ARGS>
class Test{
public:
    typedef typename Zero<NUM_ARGS<ARGS...>::n-2>::yes N2ARGS;//如果参数是2就是yes
    T operator()(typename C_ARGS<1,ARGS...>::type a,\
                 typename C_ARGS<2, ARGS...>::type b){
        return a+b;
    }
};

```

## 用模板：

### 1. 实现累加和

```c++
template <int N>
class Sum{
	static constexpr int n=Sum<N-1>::n+N;
};
template <>
class Sum<1>{
	static constexpr int n=1;
};
int main(){
    cout<<Sum<4>::n<<endl;
    return 0;
}
```

> 模板递归深度不能太深最多904层

### 2. 判断奇偶

```c++
#include <iostream>
using namespace std;

template <int N>
class is_even{
public:
    static constexpr const char * r=is_even<N%2>::r;
};
template <>
class is_even<1>{
public:
    static constexpr const char *r="no";
};
template <>
class is_even<0>{
public:
    static constexpr const char *r="yes";//不能用string类，而是char * 但是char又会和consexpr结合，所以前面得再加上一个const
};

int main(){
    cout<<is_even<6>::r<<endl;
    return 0;
}

、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、
template <int N>
struct is_even{
    static constexpr const char * r=N%2==0?"yes":"no";//直接这样也能行得通。
};
```

> 不能用string类，而是char * 但是char又会和consexpr结合，所以前面得再加上一个const

### 3. 判断$\geq$​60

```c++
#include <iostream>
using namespace std;
template <int N>
struct good_bad{};//作为工具类
template <>
struct good_bad<0>{
    static constexpr const char *r="no";
};
template <>
struct good_bad<1>{
    static constexpr const char *r="yes";
};

template <int N>
struct score_judge{
    static constexpr const char *r=good_bad<(N>=60)>::r;
};

int main(){
    cout<<score_judge<61>::r<<endl;
    cout<<score_judge<41>::r<<endl;

    return 0;
}
```



### 4. 判断素数

```c++
#include <iostream>
using namespace std;

template <int i,int N>
struct getnext{
    static constexpr int r=(N%i)?i+1:0;
};

template <int i,int N>
struct test_prime{
    static constexpr const char *r=(i*i>N)?"yes":test_prime<getnext<i,N>::r,N>::r;
};
template <int N>
struct test_prime<0,N>{
    static constexpr const char *r="no";
};//逻辑的封装


template <int N>
struct is_prime{
    static constexpr const char *r=test_prime<2,N>::r;
};

int main(){
    cout<<is_prime<31>::r<<endl;
    cout<<is_prime<21>::r<<endl;

    return 0;
}

```

> 指针需要放两个const目的是：const char *是一个整体
>
> 而其他类型不需要，

### 5. rmvr.cpp(实现自己的remove_reference)

```c++
#include <iostream>
#include <typeinfo>
using namespace std;
#define BEGIN(x) namespace x{
#define END(x) }
BEGIN(rmvr)
template <typename T>
struct remove_reference{
    typedef T type;
};
template <typename T>
struct remove_reference<T &>{
    typedef T type;
};
template <typename T>
struct remove_reference<T &&>{
    typedef T type;
};

template <typename T>
void func(T &&a){
    typename remove_reference<T>::type b;
    b=a;
    cout<<b<<endl;
}
int main(){
    int n=3;
    func(n);
    func(234);
    cout<<"==================="<<endl;
    typename remove_reference<int>::type a;
    typename remove_reference<int &>::type b;
    typename remove_reference<int &&>::type c;

    cout<<typeid(a).name()<<endl;
    cout<<typeid(b).name()<<endl;
    cout<<typeid(c).name()<<endl;

    return 0;
}
END(rmvr)
    
int main(){
    rmvr::main();//实现自己的命名空间
    return 0;
}

```

### 6. add_lvale_reference 转成左值引用

```c++
#include <iostream>
#include <typeinfo>
using namespace std;
template <typename T>
struct add_lvale_reference{
    typedef T& type;
};
template <typename T>
struct add_lvale_reference<T &&>{
    typedef T& type;
};

int main(){
    int b=3;
    typename add_lvale_reference<int &&>::type a=b;
    cout<<typeid(a).name()<<endl;
    return 0;
}
///////////////////////////////////////////////
BEGIN(adlvr)
template <typename T>
struct add_reference{
    typedef T& type;
};
template <typename T>
struct add_reference<T &>{
    typedef T& type;
};
template <typename T>
struct add_reference<T &&>{
    typedef T& type;
};
int main(){
    int n=3;
    typename add_reference<int>::type a=n;
    typename add_reference<int &>::type b=n;
    typename add_reference<int &&>::type c=n;

    cout<<typeid(a).name()<<endl;
    cout<<typeid(b).name()<<endl;
    cout<<typeid(c).name()<<endl;

    return 0;
}
END(adlvr)
int main(){
    adlvr::main();
    return 0;
}
```

### 7. remove_pointer 去掉指针

```c++
#include <iostream>
#include <typeinfo>
using namespace std;
#define BEGIN(x) namespace x{
#define END(x) }

BEGIN(rmvp)
template <typename T>
struct remove_pointer{
    typedef T type;
};
template <typename T>
struct remove_pointer<T *>{
    typedef typename remove_pointer<T>::type type;
};

int main(){
    int n=3;
    typename remove_pointer<int*>::type a;
    typename remove_pointer<int **>::type b;
    typename remove_pointer<int ***>::type c;

    cout<<typeid(a).name()<<endl;
    cout<<typeid(b).name()<<endl;
    cout<<typeid(c).name()<<endl;

    return 0;
}
END(rmvp)

int main(){
    rmvp::main();
    return 0;
}
```

### 8. add_const 增加const限定

```c++
BEGIN(addconst)
template <typename T>
struct add_const{
    typedef const T type;
};
template <typename T>
struct add_const<const T>{
    typedef const T type;
};

int main(){
    int n=3;
    typename add_const<int>::type a=n;
    typename add_const<const int>::type b=n;

    cout<<typeid(a).name()<<endl;
    cout<<typeid(b).name()<<endl;
    return 0;
}
END(addconst)
int main(){
    addconst::main();
    return 0;
}
```



## 第15章



### bindtest

```c++
#include<functional>
#define BEGIN(x) namepsace x{
#define END(x) }

BEGIN(bindtest)
int add(int x,int y){
    return x+y;
}
void add1(int &x){
	x++;
    cout<<x<<endl;//里面却自增了，保持自增的记录，无名对象的自增
}
void show(int n,char *msg){
    cout<<n<<":"<<msg<<endl;
}
int main(){
    int m=3,n=4;
    auto t1=bind(add,m,n);
    cout<<t1()<<endl;
    cout<<t1()<<endl;//变成了一个函数对象
    cout<<t1()<<endl;
    
    auto t2=bind(add1,m);
    //auto t2=bind(add1,ref(m));
    t2();
    t2();
    t2();
    cout<<m<<endl;//外面并没有自增，这个是bind的特点,传进去的是一个无名对象
    
    auto t3=bind(show,placeholders::_2,placeholders::_1);
    t3("hello",4);
    auto t4=bind(show,placeholders::_5,placeholders::_1);
    t4("world",3.4,"he",3,1);

    return 0;
}

END(bindtest)
```

> bind()把一个函数变成了一个函数对象
>
> - 可以改变参数的个数、顺序placeholders::_1
>
> 外面并没有自增，里面却自增了，保持自增的记录，这个是bind的特点
>
> 想要外面也改变就需要传一个ref(m)是m真正变成一个引用。

> printf("%s\n","hello",1,2,3)后面的参数也可以传，但是没有意义。

### 定义自己的高级函数指针

既能值普通函数，又能指函数对象。

既然谁都能指，那你的类型一定很特别喽

```c++
BEGIN(functest)

int add(int x,int y){
    return x+y;
}
class ADD{
public:
    int operator()(int x,int y){
        return x+y;
    }
};

int main(){
    ADD a;
    function<int(int,int)> p=add;
    cout<<p(1,2)<<endl;
    
    function<int(int,int)> p2=a;
    cout<<p2(3,4)<<endl;
    
    return 0;
}
END(functest)
int main(){
    functest::main();
    
    return 0;
}
```

2:17:39

```c++
#include <iostream>
#include <cmath>
#include <stack>
#include <queue>
#include <vector>
#include <cstdio>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
using namespace std;
#define BEGIN(x) namespace x{
#define END(x)}
BEGIN(bindtest)
int add(int x,int y){
    return x+y;
}
void add1(int &x){
    x++;
    cout<<x<<endl;
}
void show(int n,const char *msg){
    cout<<n<<":"<<msg<<endl;
}
int main(){
    int m=3,n=4;
    auto t1=bind(add,m,n);
    cout<<t1()<<endl;
    cout<<t1()<<endl;
    cout<<t1()<<endl;

    auto t2=bind(add1,ref(m));
    t2();
    t2();
    t2();
    cout<<m<<endl;

    auto t3=bind(show,placeholders::_2,placeholders::_1);
    t3("hello",4);
    auto t4=bind(show,placeholders::_5,placeholders::_1);
    t4("world",3.4,"he",3,1);
    
    return 0;
}
END(bindtest)
BEGIN(functest)
int add(int x,int y){
    return x+y;
}
class ADD{
public:
    int operator()(int x,int y){
        return x+y;
    }
};
template <typename T,typename ...ARGS> 
class Base{
public:
    virtual T run(ARGS...)=0;  
    virtual Base *getCopy(ARGS...)=0;
};
template <typename T,typename ...ARGS> 
class NormalFunc:public Base<T,ARGS...>{
private:
    T (*ptr)(ARGS...);//对于子类最重要的也还是里面的这个ptr指针，这里对应的是add函数
public:
    NormalFunc(T (*p)(ARGS...)):ptr(p){}//拿函数指针构造我的子类
    T run(ARGS ...args)override{//不定参定义了不定参数...args
        return ptr(foeward<ARGS>(args)...);//往后传的时候保持类型不变，左值引用依然是左值引用，右值引用依然是右值引用
    }
    Base<T,ARGS...> *getCopy(){
        return new NormalFunc(*this);
    }
};

template <typename CLASS_T,typename T,typename ...ARGS>
class functor:public: Base<T,ARGS...>{
private:
    CLASS_T obj;
public:
    functor(CLASS_T &obj):obj(obj){}
    T run(ARGS ...args)override{
        return obj(forward<ARGS>(args)...);
    }
    Base<T,ARGS...> *getCopy(){
        return new functor(*this);
    }
};

template <typename T,typename ...ARGS> class function;
template <typename T,typename ...ARGS> 
class function<T(ARGS...)>{
private:
    Base<T,ARGS...> * ptr;//目的把基类的ptr构造好，但由于父类是没有对象的，所以先new一个子类出来，把构造好的子类地址给他，ptr作为指针指向子类
public:
    function(T (*p)(ARGS...)):ptr(new NormalFunc<T,ARGS...>(p)){}
    template <typename CLASS_T>//任意类型
    function(CLASS_T obj):ptr(new functor<CLASS_T,T,ARGS...>(obj)){}
        
    T operator()(ARGS... args){
        ptr->run(forward<ARGS>(args)...); 
    }
    function &operator=(const function &f){
        delete ptr;
        ptr=f.ptr->getCopy();
        return *this;
    }
    ~function(){
        delete ptr;
    }
};

int main(){
    
    function<int(int,int)>p1=add;//add传给p1调用的是构造
    cout<<p1(3,5)<<endl;
    
    ADD a;
    function<int(int,int)>p2=a;
    cout<<p2(3,4)<<endl;

    p=p2;
    cout<<p(5,6)<<endl;
    return 0;
}

END(functest)
int main(){
    //bindtest::main();
    functest::main();
    return 0;
}
```

> args ...第一次使用放前面，后面使用放后面

![image-20220324162125984](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220324162125984.png)

**double free**



学习方法：从底层，我能不能实现类似的工具呢？

### 多线程

#### 计算五千万内有多少个素数：

```c++
int cnt=0;
int pd(int x){
	for(int i=2,I=(int)sqrt(y);i<=I;i++){
        if(x%i==0){
            return 0;
        }
    }
    return 1;
}
void calc(int x,int y){
    for(int i=x;i<=y;i++){
        if(pd(i))cnt++;
    }
}
int main(){
    thread t1(calc(pd,2,10000000));
    thread t2(calc(pd,10000001,20000000));
    thread t3(calc(pd,20000001,30000000));
    thread t4(calc(pd,30000001,40000000));
    thread t5(calc(pd,40000001,50000000));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    cout<<cnt<<endl;
    return 0;
}
```

#### 线程如何传参：

```c++
void func(int x,string msg){
    cout<<x<<":"<<msg<<endl;
}
int main(){
    thread t1(func,3,"hello");
    t1.join();
    
    return 0;
}
```

#### 加锁：unique_lock<mutex> lock(mtx);

```c++
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;
bool is_prime(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0)
            return false;
    }
    return true;
}
int cnt=0;
mutex mtx;
int count_prime(int l,int r){
    for(int i=l;i<=r;i++){
        int r=is_prime(i);
        //unique_lock<mutex> lock(mtx);
        //cnt+=r;
        __sync_fetch_and_add(&cnt,r);//进行一次原子操作

        //lock.unlock();
    }
    return cnt;
}
void worker(int l,int r){
    cout<<this_thread::get_id()<<":begin"<<endl;
    count_prime(l,r);
    cout<<this_thread::get_id()<<":end"<<endl;
    return ;
}
int main(){
    worker(1,10000);
    worker(10001,20000);
    cout<<cnt<<endl;

    return 0;
}
```

> - __sync_fetch_and_add(&cnt,r);//进行一次原子操作

#### 线程池

技师对客户----->技师对任务

```c++
#include <functional>
#include <unordered_map>
#include <queue>
#include <mutex>
#include <condition_variable>
class Task{//把参数和函数打包成一个任务,其实就是存一个函数对象，那么用高级指针
private:
    function<void()> func;//高级函数指针
public:
    template <typename FUNC_T typename ...ARGS>
    Task(FUNC_T f,ARGS ...args){
        func=bind(f,forward<ARGS>(args)...);//保持这个类型继续向后传,避免左右值得转换。
    }
    void run(){//函数指针封装好了，下一步就是运行。
        func();
    }
};
class TheradPool{
private:
    //作为一个线程池，首先得有一池子线程得坑位：
    vector <thread *> trr;
    unordered_map<thread::id,bool> running;
    void stop_running(){
        auto id=this_thread::get_id();//把你的工牌拿过来
        running[id]=false;//对照着工牌，在表上打个勾，表示你可以下班了。
        return ;
    }
    queue<Task *>task_q;
    mutex mtx;
    condition_variable condi;
    Task *get_task(){
        unique_lock<mutex> lock(mtx);
        while(task_q.empty()){//睡醒了但是不一定能够抢得到
            condi.wait(lock);//等待这个条件的发生并把锁给扔出去。
        }
        Task *t=task_q.front();
        task_q.pop();
        return t;
    }
    bool starting;
    
public:
    ThreadPool(int n=1):trr(n),starting(false){
        //有了一池子存放线程的位置之后，就得给添加线程并分配任务了
        this->start();
    }
    void woker(){
        //开始干之前得拿工牌，表示自己开干了，之后会有人来收走工牌，那就可以结束了。
        thread::id id=this_thread::get_id();
        running[id]=true;//false表示工牌被人给收走了，收工
        while(running[id]){//开关
            //获取
            Task *t=get_task();//干活期间，去拿取任务
            //执行
            t->run();
            delete t;
        }
        return ;
    }
    void start(){
        if(starting==true){
            return ;
        }
        for(int i=0;i<trr.size();i++){
			trr[i]=new thread(&ThreadPool::worker,this);
        }
        starting =true;
    }
    void stop(){
        if(starting==false){
            return ;
        }
        for(int i=0;i<trr.size();i++){//主管人员依次去把每个线程的工牌给取下来。
			add_task(ThreadPool::stop_running,this);
        }
        for(int i=0;i<trr.size();i++){
            trr[i]->join();//等线程全部都下班，要关门了。
        }
        for(int i=0;i<trr.size();i++){
            delete trr[i];//原先申请的时候相当于给你那块空间的使用权，使用权没收之后，你虽然还指着那块内存，但是已经不属于你了，需要给你指一块空地。防止报错。
            trr[i]=nullptr;
        }
        starting =false;
    }
    template <typename FUNC_T,typename ...ARGS>
    void add_task(FUNC_T f,ARGS ...args){
        //上锁
        unique_lock<mutex> lock(mtx);
        task_q.push(new Task(f,forward<ARGS>(args)...));
        //解锁
        condi.notify_one();
        return ;
    }
    virtual ~ThreadPool(){
        this->stop();
        while(!task_q.empty()){
            delete task_q.front();
            task_q.pop();
        }
    }
};
bool is_prime(int x){
    for(int i=2;i*i<=x;i++){
        if(x%i==0)
            return false;
    }
    return true;
}

mutex mtx;
int count_prime(int l,int r){
    intcnt=0;
    for(int i=l;i<=r;i++){
        cnt+=is_prime(i);
    }
    return cnt;
}
void worker(int l,int r,int &ret){
    cout<<this_thread::get_id()<<":begin"<<endl;
    ret=count_prime(l,r);
    cout<<this_thread::get_id()<<":end"<<endl;
    return ;
}
int main(){
    const int batch=5000000;
    int ret[10];//记录返回值
   	ThreadPool tp(5);
    for(int i=0;j=1;i<10;i++,j+=batch){
        tp.add_task(worker,j,j+batch-1,ref(ret[i]));
    }
    tp.stop();
    int ans=0;
    for(auto x:ret){
        ans+=x;
    }
    cout<<ans<<endl;
    return 0;
}
```

> - bind的作用就是不用去管具体参数的个数

> 毒药方法，任务谁执行谁结束。





### 异常处理

#### exception.cpp

```c++
#include <iostream>
#include <vector>
#include <cstdlib>
#include <exception>
#include <stdexcept>
using namespace std;
class ZeroDivException:public runtime_error{
public:
    ZeroDivException(const string &msg="zero div"):runtime_error(msg){}
    const char *what()const noexcept override{
        return "__what_zero__div";
    }

};

int suml2r(int l,int r,vector<int> v)noexcept{
    int sum=0;
    for(int i=l;i<r;i++){
        sum+=v.at(i);
    }
    return sum;
}
int main(){
    try{
        try{/*
            vector<int> v(10);
            for(int i=0;i<10;i++){
                v[i]=rand();
            }
            suml2r(-1,100,v);

            cout<<v[-1]<<endl;
            cout<<"keep going"<<endl;
            cout<<v.at(-1)<<endl;
            cout<<"keep going"<<endl;
*/
            int n;
            cin>>n;
            if(n==0){
                throw(ZeroDivException());
            }
            cout<<10/n<<endl;
        }catch(out_of_range &e){
            cout<<e.what()<<endl;
            throw(e);
        }catch(ZeroDivException &e){
            cout<<e.what()<<endl;
        }
    

    }catch(string &e){
        cout<<"string"<<endl;
    }catch(const char *&e){
        cout<<"char *"<<endl;
    }catch(int &e){
        cout<<"int:"<<endl;
    }catch(...){
        cout<<"..."<<endl;
    }
    cout<<"keep going"<<endl;
    return 0;
}
```

> try 尝试执行有错误的代码,catch(...)抓捕异常

> throw(3)
>
> 子函数中告诉别人throw
>
> noexcept不会异常

### lambda表达式

![image-20220325172213713](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220325172213713.png)

> 本质还是函数对象。
>
> ![image-20220325172620392](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220325172620392.png)

#### for_each

```

```

### 虚继承

virtual public：<img src="C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220325173639405.png" alt="image-20220325173639405" style="zoom:50%;" />
