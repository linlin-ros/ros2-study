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
