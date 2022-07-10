## 第一个shell脚本 hello.sh

```shell
vim hello.sh

#!/bin/bash     //第一行是固定用法声明解释器
#这是注释
echo "Hello Kaikeba"
```

添加可执行权限：

```shell
chmod +x       // 三个都加上可执行权限
./hello.sh

bash hello.sh  // 解释器直接解释文件
```

调试：

```shell
bash -x hello.sh  进入调试
bash +x hello.sh  退出调试

或者在文件里面写：
set -x //开始调试
...... //调试内容
set +x //关闭调试
```

## 变量

变量的定义：（弱类型/默认全局变量）

```shell
a=12
a=helloword
a=`pwd`
a=$a:a  # $取值  :加在后面
```

局部变量：

```shell
local a=12
```

```shell
vim 2.var.sh

declare a   //显示地声明一个变量a,不声明也没事
#!/bin/bash
a=12
b=avc
c=`pwd`
d=${a}:a
echo $a
echo $b
echo $c
echo $d

#输出结果：
12
avc
/home/jby2/script
12:a
```

> **在shell里面空格是一个敏感的东西，会导致shell无法理解**

### 特殊变量

- **位置变量：**
  - $0: 获取当前执行shell脚本的文件名，包括路径
  - $n:获取当前执行脚本的第n个参数，n=1...9,如果n大于9,则需要将n使用大括号括起来
  - $*:获取当前shell的所有参数，将所有命令行参数视为单个字符串，相当于"\$1\$2\$3"
  - $#:得到执行当前脚本的参数个数
  - \$@:获取这个程序所有参数,并保留参数之间的任何空白,相当于"\$1","\$2","\$3",这是将参数传给其他程序的最好办法

```shell
vim loc_var.sh

#!/bin/bash
echo "\$0 is $0"
echo "\$1 is $1"
echo "\$2 is $2"
echo "\$3 is $3"
echo "\$4 is $4"
echo "\$* is $*"
echo "\$# is $#"
echo "\$@ is $@"

# bash loc_var.sh 输出为：
$0 is loc_var.sh
$1 is 
$2 is 
$3 is 
$4 is 
$* is 
$# is 0
$@ is 
# bash loc_var.sh 1 2 3 4 输出为：
$0 is loc_var.sh
$1 is 1
$2 is 2
$3 is 3
$4 is 4
$* is 1 2 3 4
$# is 4
$@ is 1 2 3 4
```

> **在输入命令的时候按：ctrl + k 能够把后面的字符全部删掉。**

- **状态变量**
  - **$?**:判断上一指令是否成功执行,0为成功,非零为不成功
  - $$:取当前进程的PID
  - $!:上一个指令的PID

## 输入输出

- #### read

  - -a array:把输入赋值到数组array中,从索引号零开始。
  - -d delimiter:用字符串delimiter中的第一个字符只是输入结束,而不是一个换行符
  - -e: 使用Readline来处理输入。这使得与命令行相同的方式编辑输入。
  - -n num:读取num个输入字符,而不是整行。
  - -p prompt:为输入显示提示信息,
  - -r Raw mode 不把反斜杠字符解释为转义字符
  - -s Silent mode (盲眼模式)
  - -t seconds:超时
  - -u fd:使用文件描述符fd中的输入，而不是标准输入

```shell
vim read.sh

#!/bin/bash
read name
echo "name is ${name}"
read -s -p "Please input passwd:" passwd
echo "$name $passwd"
read -t 5 -p "Is this OK?[Y/n]"
```

- #### echo

```shell
bash  //切换到bash
echo -e 表示支持转义字符
例：
echo "\nsuyulu is 18 years old\!\n" //无换行
echo -e \nsuyulu is 18 years old\!\n" //有换行
exit //退出bash

echo -n abc //表示输出不要回车
```

- #### printf

```shell
printf "Hello %s, this is KKB\n" "KKBr"
#输出结果：
Hello KKBr, this is KKB

printf "%s is %d years old\n" suyuelu 18
#输出结果：
suyuelu is 18 years old
```

