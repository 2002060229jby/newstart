### delete/new

```c++
#include<iostream>
#include<cstdlib>
using namespace std;
class A{
    int x;
public:
    A(){
        cout<<this<<"constructor"<<endl;
    }
    ~A(){
        cout<<this<<"destructor"<<endl;
    }
};

int main(){
    int n=10;
    
    //malloc free
    cout<<"malloc int "<<endl;
    int *p=(int *)malloc(sizeof(int)*10);
    free(p);
    //new delete
    cout<<"new int "<<endl;
    int *q=new int[10];
    delete[] q;
    
    cout<<"malloc A"<<endl;
    A *k=(A *)malloc(sizeof(A)*n);//malloc并没有进行初始化，而只是把这块内存给了你。
    for(int i=0;i<n;i++){
		new(k+i) A();//new + 每块地的首地址
        //实现原地构造；自己实现内存的初始化，也可以换不同的类
    }
    free(k);
        
	cout<<"new A"<<endl;
    A *s=new A[n];//但是new在申请空间的同时进行了初始化，即构造
    delete[] s;//delete默认调用destructor析构。
    
}
```

> - 栈段比堆段在高地址，相差甚远，
>