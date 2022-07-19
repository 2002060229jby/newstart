### static

![image-20220309153043277](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309153043277.png)

- **类属性**是描述这整个类的属性，而不单单是某个对象的，而**类方法**是专门操作类属性的方法。

### 

### static

```c++
#include<iostream>
class People{
public:
    People(){
        total_num++;
    }
    ~People(){
		total_num--;
    }
    static void showNum(){
		cout<<total_num<<endl;
    }
private:
    static int total_num;//全人类有多少人,而且这只是对类属性的声明，还未定义。它的定义必须在类外、在全局进行定义。
};
int People::total_num=0;//定义
int a=3;
int b=0;

int main(){
    People p1,p2;
    People::showNum();
    return 0;
}
```

![image-20220309170651164](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309170651164.png)

`g++ test.cpp -c` 生成目标.o文件

![image-20220309173227307](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309173227307.png)

### `nm test.o` 查看符号连接表

![image-20220309173315411](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309173315411.png)

看中间这段字母：

- D表示.data段（存的不是0）
- B表示.bss段（存的是0）
  - .bss段就在.data段后面
- U表示没实现
- T表示代码段.text段

### 匿名空间{}

```c++
People xp,klss;
People::showNum();
{
	People xp,klss;//我当前的对象。
   	People::showNum();
}//对象都死了
People::showNum();
```

![image-20220309175546274](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309175546274.png)

## const 对象只能调用const方法

## const方法想要修改值必须mutable

const方法想要调用别的方法也必须要是const，这时我们可以重载一个const的方法。![image-20220309180135254](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309180135254.png)

## 当我不希望编译器给我自动生成不带参数的构造：

```c++
public:
	A() = delete;
	A(const A &a)=delete;

public:
	A() = default;//只是给别人一种参照，并没有多大意义。

//不希望使用拷贝构造
```

`g++ test1.cpp -std=c++11`

