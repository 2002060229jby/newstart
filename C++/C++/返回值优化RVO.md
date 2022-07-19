# 第四章

### 返回值优化RVO

```c++
#include<iostream>
using namespace std;

class A{
    int x;
public:
    A(){
        cout<<this<<"default cons"<<endl;
    }
    A(int x):x(x){
        cout<<this<<"param cons"<<endl;
    }
    A(const A &a):x(a.x){
        cout<<this<<"copy"<<endl;
    }
    ~A(){
        cout<<this<<"destructor"<<endl;
    }
};
A func(){
    A tmp(100);
    cout<<"tmp:"<<&tmp<endl;
    return tmp;
}
int main(){
    A a(10);
    A b(a);//基本实现没问题
    int d=444;
    A c=func();//我不是要拿这个新的对象给c构造嘛，那么拷贝构造函数参数最好加一个const，意思是：我不会去改变你给我的这个tmp的内容，只是把这个tmp的内容读出来
    //最后只会输出转换构造的内容
    //那为什么不是先转换构造，后拷贝构造呢？函数返回了一个匿名对象，又由于A c=匿名对象 <==> A c(匿名对象)
    //原因是编译器做了优化，
    cout<<"&a:"<<&a<<endl;//之后发现tmp的地址和a的完全相同。也就是引用，使用了同一块内存，这是编译器做的优化，省的你传对象回来之后，还要进行一批构造。提高效率。
    int e=555;
    return 0;
}
```

- 在定义的时候`A a(b)` 完全等价于`A a=b`,拷贝构造

- `g++ test1.cpp -S` 查看编译代码，找到444和555

```c
rbp是64位的，e是32位的，bp是基址寄存器

ax, bx, cx, dx 都可以理解为临时变量

di寄存器//获得a的地址

si寄存器

func(di,si)一般di作为函数第一个参数，si作为第二个参数

call 指令 掉一个函数
```

![image-20220309162044334](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309162044334.png)

```c++
class A{
    int x;
public:
    A(){
        cout<<this<<"default cons"<<endl;
    }
    A(int x):x(x){//这样一来带参数构造的this指针指的就是a
        cout<<this<<"param cons"<<endl;
    }
    A(const A &a):x(a.x){
        cout<<this<<"copy"<<endl;
    }
    ~A(){
        cout<<this<<"destructor"<<endl;
    }
};
A func(){
    A tmp(100);
    cout<<"tmp:"<<&tmp<endl;
    return tmp;//本来是有两轮拷贝构造的，但是聪明的编译器为我们做了优化，就是把a的地址死命往里传。。。
}
int main(){
    int b=444;
    A a=func();  //先是把a的地址传给了func,func又把a的地址通过tmp传给了有参构造函数，直接对a进行了一个构造。  
    int c=555;
    cout<<"&a:"<<&a<<endl;//a地址和tmp地址构造函数的地址完全一样。
    return 0;
}
```

能不能告诉编译器不要帮我优化呢？

`g++ test1.cpp -fno-elide-constructors`

关闭优化：![image-20220309164307157](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309164307157.png)

三次析构，三个对象。

![image-20220309164405331](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309164405331.png)

a一开始无法进行构造，需要借助func()的返回值进行拷贝构造

第一步肯定是带参数的构造tmp 9c90

函数返回的是A 类的匿名对象，并且这个匿名对象要拿tmp进行拷贝构造（初始化）。

值得一提的是这里函数返回值不能传引用，因为tmp的内存在函数结束后会被释放。就算引用记住了那段地址也无济于事了。因此绝对不能返回一个局部变量的引用。

main函数return之前完成a的析构

### 函数传参

![image-20220309165256463](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309165256463.png)

返回值优化：

![image-20220309165315423](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309165315423.png)



我们不应该去赋予拷贝构造别的含义，因为在不同的编译选项下，拷贝构造的次数不同。

![image-20220309165553642](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309165553642.png)

比如说：

![image-20220309165757120](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309165757120.png)

