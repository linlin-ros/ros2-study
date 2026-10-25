#最低cmake版本
cmake_minimum_required(VERSION 3.12)
#项目名
projiect(.....)
#设置c++标准
set(CMAKE_CXX_STANDARD ***)
#找头文件
include_directories(./)
#生成可执行文件：名字    源码
add_execytable(名字  源码）

-------------------------------

#终端执行的命令
#c创建编译文件夹并且进入
makdir build && cd build
#读取上级CMakeLists，生成构建文件
cmake ..
#编译，j4 4线程加速
make -j4
#运行程序
./main
#清空缓存，报错优先用这个
#rm -rf build/
