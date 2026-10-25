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

#搜索文件
方式1：
#在cmak中使用aux_source_directory命令可以茶盅某个路径下所有文件 命令格式为：
aux_source_directory（<dir> <variable>)
#dir:要搜索的目录       variable：将从dir目录搜索到的源文件列表储存到该变量中
aux_source_directory（${PROJECT_SOURCE_DIR} src)
#PROJECT_SOURCE_DIR: 就是执行cmake命令时后面携带的路径就是CMakeLisit.txt这个文件的路径



#方式2：
file(GLOB/GLOB_RECURSE  变量名  要搜索的文件路径和文件类型）
GLOB：将指定目录下搜索到的满总条件的所有文件生成一个列表，并将其存储到变量中
GLOB_RECURSE:递归搜索指定目录，将搜索到的满总条件的文件名生成一个列表，并将其存储到变量中
#CMAKE_CURRENT_SOURCE_DIR这个宏对应的路径就是CMakeLisit.txt这个文件的路径

#包含头文件  在编译项目源文件时，狠很多时候都需要将源文件对应的头文件路径指定出来
通过include_directories
include_directories()        ()里就是头文件对应的路径了 
${...} = 拿变量...里面存的数据

tree树状打印目录

#制作库文件
静态库需要使用的命令
add_library(库名字  STATIC [源文件] [源文件2]......)  //动态库就将static 改为shared
在linux中 静态库名字分为三部分：lib+库名字+.a,此处只要指出库名字就好，另外两部分在生成该文件的时候会自动填充，动态库后面是.so
动态库有执行权限，静态库没有
library_output_path这个宏对静态和动态都适用
