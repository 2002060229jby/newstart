## 数据提取操作

cut 切分

sort 排序

uniq 去重

split 文件切分

tr 替换、压缩和删除

grep 检索

wc 统计字符、字数、行数

tee 双向重定向

xargs 参数代换

- #### cut

  - -d c:以c字符分割
  - -f num:显示num字段的内容【n-;n-m;-m;m,n】
  - -b num:字节
  - -c num:字符

```shell
cut -d : -f 7 /etc/passwd
cut -b 1-10 /etc/passwd
cut -c 1-10 /etc/passwd
```

- #### grep

  - -c统计搜寻到的次数
  - -i忽略大小写
  - -n顺序输出行号
  - -v反向输出（输出没找到的）
  - -w匹配整个单词，而不是单词的一部分

```shell
ps -ef | BaiDu
apt-cache search vsftp | grep vsftp
```

- #### sort

  - -f忽略大小写
  - -M以月份名称排序
  - -n根据数值进行排序
  - -r反向排序
  - -u:uniq
  - -c检查文件是否有序
  - -t分割字符：制定排序时用的栏位分隔字符
  - -k以哪个区间排序
  - +排序栏位，第一栏为0，按顺序优先排序

```shell
cat \etc\passwd | sort -t : -k 3 -n -r

#最近有那些人登录
last | grep -v wtmp | grep -v "^$" | cut -d " " -f 1 |sort -u
```

- #### wc

  - -l仅列出行号
  - -w仅列出多少字
  - -m仅列出多少字符
  - -c仅列出多少字节
  - -L列出最长一行的字符长度

```shell
last | grep suyelu | wc -l
echo "Hello kaikeba" | wc -l
echo "Hello kaikeba" | wc -w
echo "Hello kaikeba" | wc -c
echo "Hello kaikeba" | wc -m
```

- #### uniq

  - -i忽略大小写字符的不同
  - -c进行计数
  - -u只输出无重复的行

```shell
last | grep -v wtmp | grep -v "^$" | cut -d " " -f 1 | sort | uniq -c
```

- #### tee

  - -a: append （追加）

```shell
cat ls.log > aaa
cat ls.log | tee aaa 双向重定向
```

- #### split（切分文件）

  - -b size:切分为size大小的文件
  - -l num:以num行,为大小切分

```shell
split -l 10 ls.log split_ //制定前缀
cat ls.log | split -l 10 //不能再写前缀了
cat ls.log | split -b 128 
rm x[a-z][a-z] //通配符
rm split_a*
```

- #### xargs

  - -eEOF当xargs读到EOF时停止
  - -p执行指令前询问
  - -n num每次执行command时需要的参数个数

```shell
echo "/etc/" | xargs ls # 前面的标准输入作为ls的参数

echo "aaa a.out bbb " xargs ls
echo "aaa a.out bbb " xargs -eaaa ls
echo "aaa a.out bbb " xargs -ea.out ls
echo "aaa aaa aaa a.out bbb " xargs -n 3 -ea.out ls
```

- #### tr

  - -c取代所有不属于第一字符集的字符
  - -d删除所有属于第一字符集的字符
  - -s将连续重复的字符以单独一个字符表示
  - -t 对应替换，第一字符集较第二字符集多出的字符就不管（不替换）了。

```shell
echo "aaa aaa aaa aaa a.out bbb" | tr -c '[0-9a-zA-Z]' '@'

echo "aaa aaa aaa aaa a.out bbb" | tr -d '[0-9a-zA-Z]'

echo "aaa \n aaa aaa a.out bbb ..." | tr -d '[0-9a-zA-Z]'

echo "aaa \n aaa aaa a.out bbb ..." | tr -c -s '[0-9a-zA-Z]' '0'

echo "aaa \n aaa aaa a.out bbb ..." | tr -t 'a-z' '0-9'
```



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









nvidia-smi 查看GPU使用情况



top 查看cpu使用情况
