> **using** 是把命名空间的所有东西导入到当前。

### 命名空间、this指针

```c++
namespace kkb{
    class Washer{
    private://类内，Washer大括号里面都是类内空间,大括号之外的都是类外//只有类内成员才可以访问
        string brand;//属性
        int vol;
    public://所有类外的人都可以去访问  
        void getBrand(){//实现类的方法，一种是直接在类内定义
            cout<<brand<<endl;
        }
        void wash();//成员方法
    protected:

    };//末尾分号

    void Washer::getBrand(this){//类外定义，说明是属于哪个类的,//还悄咪咪穿了一个this指针，调用这个方法的对象的地址传进来
        cout<<brand<<endl;
        cout<<this->brand<<endl;//等价
        cout<<this<<endl;//和类的地址是一样的。
    }
    Washer xte;//命名空间也可以定义对象
    
}//定义命名空间kkb,这时候，下面的代码都需要指明是kkb的——kkb::Washer
//也可以令写一条://using namespace kkb,就不需要每条前面都加kkb::了，//但是一般工程开发的时候不要用，因为不同命名空间的命名也许又会撞车。而是用前一种方法，在前面加上"空间名::"

void getBrand(Washer *const self){//普通函数，光明正大传参。
    cout<<self->brand<<endl;
    cout<<self<<endl;//最终输出效果都是一样的
}

int main(){
    Washer ddy;//类+对象
    ddy.brand='大地鸭';//会报错，对象处于类外，不能访问private的内容。如果不写private,默认私有
    ddy.getBrand();//'大地鸭'
    cout<<&ddy<<endl;
    
    Washer xmz;
    xmz.brand='西门子';
    xmz.getBrand();
    
    getBrand(&ddy);//替换this指针，最终输出效果都是一样的。
}

```

### cout

```c++
#include<iostream>
#include<cstdio>
#define BEGINS(x) namespace x{
#define ENDS(x) }
BEGINS(kkb)
    
class Ostream{
public:
    Ostream &operator<<(int x){//运算符重载，原来<<是左移操作，现在变为输出操作
        printf("%d",x);
        return *this;//返回它自己的引用
    }
    Ostream &operator<<(const char *x){//运算符重载，原来<<是左移操作，现在变为输出操作
        printf("%s",x);
        return *this;//返回它自己的引用
    }
};

Ostream cout;//对象定义时候就分配内存了

ENDS(kkb)

int main(){
	int n=333;
    std::cout<<n;//cout是负责输出的类  << 是一个对象，左移运算符，是一个操作
	std::cout<<std::endl;
    kkb::cout<<n;//自己实现了一个cout
	std::cout<<std::endl;
}
```

## 