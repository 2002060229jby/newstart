### 查看汇编层代码

```c
gcc 0.reference.cpp -S
//-E 只预处理，不编译，不汇编，不链接    
//-S 只编译，不汇编，不链接
//-c 编译且汇编，但不链接
//-o 改名
```

> **编译**（compile）：是把c语言变成汇编语言。
>
> **汇编**（assemble）：是把汇编语言变成机器码，二进制的机器语言。

#### 查看帮助：

```
g++ --help
```



### gdb调式

```c++
g++ 4.reference.cpp -g //进入调试模式
gdb a.out//开始调试
b main //打一个断点
r //运行
n //执行一行
s //进入函数内部
p this // 显示，this的内容 （Washer * const） 0x7ffffe3d0//const在*后说明this不能改变指向
n
p &ddy //显示对象的地址。
```



## 申明和定义

![image-20220227100754608](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220227100754608.png)

以上程序：

对于编译器而言没错。

对于汇编器而言也没错。

```c++
g++ main.cpp -E //进行预处理
g++ main.cpp -S //生成汇编
g++ main.cpp -c //生成目标 .o文件
nm main.o //nm命令可以查看哪里出现问题
```

![image-20220227101411177](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220227101411177.png)

- T：实现；（在代码段已经实现好了）
- U：没实现

> 那具体实现在哪个位置由链接器去找。
>
> 比如再写一个add.cpp:

![image-20220227101728182](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220227101728182.png)

![image-20220227101705019](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220227101705019.png)

- 查看已经实现了。

## 链接器：

![image-20220227102135661](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220227102135661.png)



### 声明、链接器

```c++
vim main.cpp
int add(int x,int y);//不去实现前三个环节也不会报错。由链接器去找你的函数实现在哪里。
int main(){
	cout<<add(3,4)<<endl;
}
g++ main.cpp -c
nm main.o

vim add.cpp
int add(int a,int b){//函数实现
    return a+b;
}
g++ add.cpp -c
nm add.o

    
g++ add.o main.o//实现链接过程
```







### 查看预处理之后的代码：

```c
g++ hello.cpp -E -o hello.i
    
g++ --help//不清楚的查看命令
```

> 前面有**#**的命令都会在预处理阶段被替换。

