## 直接查看汇编代码

```shell
g++ -help
gcc 0.reference.cpp -S
ls
vim 0.reference.s

:vsplit
:e 0.reference.cpp
```

.LFB971表示函数的入口

局部变量在内存的**栈段**

- 栈段用到哪里了呢？

我们压栈出栈最重要的是操作**栈顶**（记录栈用到哪了）

- SP指针就是栈顶指针。

栈是从高地址用到地地址。

- bp就是基址寄存器

基址加上偏移量就能访问到一块内存

- rax临时寄存器

```
pushq %rbp  保护线程
popq %rbp   释放线程

movq 是把内存里存的值丢过去
leaq 是把内存的地址丢过去
```

我们不能同时读写内存，这也是临时寄存器存在的意义。

%eax存放返回值的寄存器（%rax）表示访问里面的内存

![image-20220711163239158](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220711163239158.png)

## 如何理解引用

**引用**有点像文件的**硬链接**

给变量取一个别名，底层实现还是用指针。语法糖。

## define 和typedef的区别

define，宏定义在预处理阶段就会被替换掉。

typedef 是给类型起别名。

## 常量存放在哪

常量存在代码段，所以**常引用**实际上是开辟了一块空间来存放代码段里的一条指令里的一个**常量**。

## 类=数+操作（数据结构）

- **概念：**
  - 类和对象
  - 成员属性和方法
  - 访问权限
    - public
    - private
    - protected

## 声明和定义是不一样的。

`collect2: error: ld returned 1 exit status`是在链接阶段报的错误。

`undefined reference to Washer::getBrand()'`

有人不见了。只声明未定义。



## this指针

调用这个函数的对象的地址指针，会悄悄地传给成员函数/方法.

## gdb调试

```shell
g++ 4.reference.cpp -g
gdb a.out
l  查看多行
b main 打断点
r  运行程序
n  运行下一行
s  进入到函数里面
p this  打印变量  
#$1 = (Washer * const) 0x0 #const说明this指针不能改变指向
q 退出 y确定
```

## 命名空间

```c++
namespace kkb{
	
}
using namespace kkb; //kkb中的所有内容都导入过来。尽量不使用这个。

//工程里这样子干
#define BEGINS(x) namespace x{
#define ENDS(x) }
BEGINS(kkb)

ENDS(kkb)
```

就像一个局域网。

## 实现一个cout(d2)

cout是一个对象

<<是一个操作

## 对象的诞生和终结

构造函数：（初始化）

- 默认构造
- 转换构造
- 拷贝构造

析构函数：（释放）

> 无参拷贝析构函数，默认都给你写好了。

**先构造的东西后析构，先定义的东西先构造。**

- 局部变量在栈段。但是即便放在全局变量里也是这样
- 为了防止后面的变量依赖前面的变量。所以统一规定这样的顺序。

**工程上申请大块内存的时候，通常不在构造函数里申请。**后面异常处理不方便（伪构造和析构）

## 转换构造

访问变量遵循**就近原则**。

编译器在比较的时候会把等式两边转化成相同类型。一般长度低的向长度高的转化（缺位补零），更安全，编译器也是这么做的。

计算机中存的是**补码**。

- 第一步生成**匿名对象**
- 进行赋值操作。