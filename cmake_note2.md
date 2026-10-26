#日志
在cmake中可以用户显示一条消息，该命令名字为messgae
message（STATUS|WARNING|AUTHOR_WARNING|SEND_ERROR|FATAL_ERROR]"message to display"...)
(无)：重要消息
STATUS:非重要消息
WARNING：CMake警告，会继续执行
AUTHOR_WARNING：CMake警告，会继续执行
SEND_ERROR：CMake错误，继续执行，但是会跳过生成步骤
FATAL_ERROR：CMake错误，终止所有过程
-------------------------------------------------------------------------
#变量操作
使用set拼接
如果使用set进行字符串拼接，对应命令格式如下：
set(变量名 ${变量名1} ${变量名2}...)
#使用list拼接
list(APPEND <list> [<element>....]
list命令的功能set强大，字符串拼接只是它的其中一个功能，所以需要它在第一个参数的位置指定出我们要做的操作，APPEND表示进行数据追加，后边的参数和set一样
参数中的list是变量名<>也不用写[]一样
------------
字符串移除
list(ROMOVE_ITEM  变量名  [<value>...] []里是要删除的东西删除时要带上绝对路径
---------------------------------------------------------------------------------------
#list其他命令
1.获取list长度
list(LENGTH <list> <output variable>
LENGTH:子命令LENGTH用于读取列表长度
<list> ：当前操作的列表
<output variable>:创建新的变量，用于存储列表的长度
2.读取列表中指定索引的元素，可以指定多个索引
list（GET <list> <element index> [<element index>...] <output variable>)
<list>：当前操作列表
<element index>:列表元素索引
从0开始编号，索引0的元素为列表的第一个元素
索引也可以是负数，-1表示列表的最后一个元素，-2表示列表倒数第二个元素，以此类推
当索引（不管是正还是负）超过列表长度，运行会报错
<output variable>:新创建的变量，存储指定索引元素返回结果，也是一个列表
3.将列表中的元素用连接符（字符串）连接起来组成一个字符串
list(JOIN <list> <glue> <outout variable>)
<list>:当前操作的列表
<glue>:指定的连接符（字符串）
<output variable>:新创建的变量，存储返回的字符串
4.查找列表是否存在指定元素，如果未找到，返回-1
list(FIND <list> <value> <outout variable>)
list:同上
<value>:需要在列表中搜索的元素
<outout variable>:新创建变量
如果列表<list>中存在<value> ,那么返回<value>在列表中的索引
如果未找到则返回-1
5.在list中指定位置插入若干元素
list(INSERT <list> <element_index> <element> [.....])
<list>:同上
<element_index>:要插入的位置
<element>:插入的元素
6.将元素插入列表的0索引位置
list(PREPEND <list> [<element>])
<list>:同上
element:插入若干元素
7.将列表中最后一个元素移除
list(POP_BACK <list> [out]
<list>:同上
[out]:变量 将移除来的元素存储到其中       如果不用知道被移除1元素可以不写
8.将列表第一个元素移除
list（POP_FRONT <list> [out]
同上
9.将指定索引的元素从列表移除
list(REMOVE_AT <list> <index> [index........])
<index>:元素对应索引
10.移除列表重复元素
list(REMOVE_DUPLICATES <list>)
11.列表翻转
list(REVERSE <list>)
12.列表排序
list(SORT <list> [COMPARE <compare>] [CASE <case>] [ORDER <order>])
#COMPARE:指定排序方法。有如下几种值可选
STRING:按照字母顺序 为默认
FILE_BASENAME:如果是一系列路径名，会使用basename进行排序
NATURAL:使用自然数顺序排序
#CASE:指明是否大小写敏感。有如下几种值可选：
SENSITIVE:按照大小写敏感方式进行排序为默认
INSENSITIVE:按照大小写不敏感方式进行排序
#ORDER:指明排序的舒徐。有如下几点
ASCENDING:按照升序排序为默认
DESCENDING:按照降序排列
---------------------------------------------------------------
#宏定义
在进行程序测试的时候，我们可以在代码中添加一些宏定义，通过这些宏来控制这些代码是否生效，
在cmake中的命令为
add_definitions(-D宏名称）
