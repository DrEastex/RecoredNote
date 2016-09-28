#Astyle
##astyle不但可以对C/C++进行格式优化，还可以处理Java和C#
###Windows
`for /R %f in (*.cpp;*.c;*.h) do astyle --style=ansi  "%f"`

##Common Use
--style=allman
--style=ansi
--style=bsd
--style=break
-A1

--style=java
--style=attach
-A2

--style=kr
--style=k&r
--style=k/r
-A3

--style=stroustrup
-A4

--style=whitesmith
-A5

--style=banner
-A6

--style=gnu
-A7

--style=linux
-A8

--style=horstmann
-A9

--style=1tbs
-A10

--style=pico
-A11

--style=lisp
-A12

##Other Opt

-C

类中public,pretected,private关键字，一个tab的缩进

-S

switch中case关键字，一个tab的缩进

-K

switch中case关键字，无缩进

-N

被namespace包含的block，一个tab的缩进

-w

格式化多行的宏定义

-c

将tab转化为对应个数的空格

--mode=c

格式化的是C/C++的源文件或者头文件（缺省值）

--mode=java

格式化的是JAVA的源文件

--suffix=####

将原始文件保存为“####”后缀，而不是“orig”

--suffix=none

不保存原始文件

--exclude=####

优化时不包含“####”文件或目录

-Z

修改后保持文件的修改时间不变

-X

将错误信息输出到标准输出设备（stdout），而不是标准错误设备（stderr）

-Q

只显示格式化前后发生变化的文件

-q

不输出任何信息

-z1

使用windows版本的回车符(CRLF)

-z2

使用linux版本的回车符(LF)

--help

显示帮助信息

-v

显示版本信息
