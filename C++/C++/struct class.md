struct 与class

![image-20220309153702580](C:\Users\adam\AppData\Roaming\Typora\typora-user-images\image-20220309153702580.png)

- struct 也可以自己定义private

两种模式：

- struct 对应黑名单。
- class对应白名单

那为什么还要使用struct呢？

c++是新语言，得兼容C语言，就比如javascript跟java关系并不大，只是蹭一波热度。

# 

```
#include<stdio.h>
int main(){
    int a=345;
    char *p;
    p=(char *)&a;
    printf("addr = %p,val = %#x\n",p,p[0]);
    printf("addr = %p,val = %#x\n",p,p[1]);
    printf("addr = %p,val = %#x\n",p,p[2]);
    printf("addr = %p,val = %#x\n",p,p[3]);
    printf("%#x\n",345);
    return 0;
}
```

