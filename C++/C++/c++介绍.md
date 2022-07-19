![image-20220415211420262](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220415211420262.png)

[数据类型](https://en.cppreference.com/w/cpp/language/types)

### c++介绍：

![image-20220307235951475](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220307235951475.png)

- 非标准头文件：不能跨平台。
- 标准头文件：可以跨平台。

> <unistd.h> unix系统，放在window不行，那就是非标准头文件。



### c语言的29个标准库头文件：[header.c](https://en.cppreference.com/w/c/header).

![image-20220307235336238](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220307235336238.png)

- c11：2011年的版本
- c99：1999年的版本

> 不要去抵触某种编程语言，要去融会，化为己用。



### c++的130多个标准库头文件：[header.cpp](https://en.cppreference.com/w/cpp/header)

同样的思想可以用不同的语言来表达，同样的语言可以表达不同的思想。

面向过程怎么去体现：画流程图！是面向过程最佳的体现。



### C++优势：

![image-20220308001115444](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220308001115444.png)



### efective c++:

- 宁肯以编译器替换预处理器。（const/enums (inline)替换#define）





### const

```c
void test(const int b){
	b=4;//会报错
}
const int a;//这个时候a在内存的read-only data.段,全局变量在data.段,这个时候修改a的值会发生段错误。代码段和栈段是不同的片区。
int main(){
    const int a=33;//这个位置是栈段所有的局部变量，子函数形参都在这里，还不是read-only data.段,所以修改值不会段错误。
    int *p=&a;//会报错
    int *p=(int *)&a;//强制类型转换：const int* ->int *
    *p=3;
    cout<<*p<<endl;//*p=3
    cout<<a<<endl;//a=33
    //为什么a还是33呢，地址对应的值确实改成3了，但a已经不是原来那个a了
    cout<<p<<endl;
    cout<<&a<<endl;//但是输出的地址和p的地址还是一样的
    //其实c++引入了一张符号表，a这个符号被const修饰之后，赋值为33，那么a去读的时候对应的就是33.而无关它的地址。也就是说a这个符号和33进行等价，也是在编译阶段去做修改，也就是从c语言到汇编语言那个阶段。编译器没有读那块内存，那块内存确实是3了。
    
    const int *p;//第一种第二种是一样的，表示指针所指的那块内存的值，不能修改。
    int const*q;
    int *const k=NULL;//必须初始化，表示指针本身存的地址不能修改。
	const int * const k=NULL;//表示既不能修改指针存的地址，也不能修改指的那块地址的值 
}
```

> - 但是如果k指向的是一个变量的地址，值如果是由变量直接发生修改的，而不是由*k间接修改的，前者不会报错，后者会报错。

![image-20220308091527535](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220308091527535.png)

```c++
class A{
public:
    int x;
    mutable int y;//这样在const{}里卖就可以修改y的值了
    A(){x=123,y=0;}//构造函数，简单初始化，但最好不要在构造函数本体内使用赋值操作
    A():x(123),y(0){}//构造函数最好使用这样的，成员初值列，本质是c++的构造、初始化和赋值还是有本质区别的。
    A():y(124),x(y-1){}//初值列表列出的成员变量x和y的顺序应该和定义的顺序相同，初始化的顺序还是按照定义的顺序进行的，如果先执行x(y-1)那么x就废了
    void say1()const{//const定义这个函数是只读的，不能去写它
        cout<<x<<endl;//不会报错
        x=3;//会报错，前面说了，不能去写它
        y++;//加入y是老化过程，数据意义上是必须要改的，但不影响我在意义上把它当作一个常的事物看待。
    }
    void say2(){
        
    }
}
int main(){
    const A a;//A这个对象a为常对象，意味着对象中的值是不能变的,只读的。
    a.say1();//不会报错，因为函数定义为只读了const{}
    a.say2();//会报错，因为没有const的限制，你有可能去写。
    
    return 0;
}
```

- 再跨文件的赋值操作时，把依赖的变量放到同一个文件里面，防止编译的时候依赖变量还没编译造成未知。

### 双击esc自动显示代码错误

### 排序实现

```c++
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;
int main(){
    vector<int >v;
    int n;
    int t;
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>t,v.push_back(t);
    sort(v.begin(),v.end());//排序
    int pos=v[n/2],sum=0;
    //或者pos=nth_element(v.begin(),v.begin() + v.size()/2,v.end())
    for(int i=0;i<n;i++){
        sum+=abs(v[i]-pos);
    }
    cout<<sum<<endl;
    return 0;
}
```

### 字符串操作

```c++
#include<algorithm>
#include<vector>
#include<iostream>
using namespace std;
int main(){
    string s1,s2;
    int n;
    cin>>s1>>n>>s2;
    int len=s1.size();//size()
    len=len>100?100:len;
    cout<<len<<endl;
    s1.insert(n-1,s2);//插入
    cout<<s1<<endl;
    cout<<s1.size()-s1.rfind("x")<<endl;//查找最后一个出现的
    return 0;
}
```

**风暴事件分析法：**

找名词（对象）、找动词（操作）