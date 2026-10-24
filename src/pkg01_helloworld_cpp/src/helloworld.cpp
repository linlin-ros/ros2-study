/*
需求：在终端输出文本helloworld。
流程：
      1.包含头文件；
      
      
*/
#include "rclcpp/rclcpp.hpp"



//方式（不推荐）
/*int main(int argc, char **argv)
{
      //2.初始化ros2客户端；
      rclcpp::init(argc,argv);
      //3,创建节点指针；
      auto node = rclcpp::Node::make_shared("helloworld_node_cpp");
      //4.输出日志；
      RCLCPP_INFO(node->get_logger(),"hello world!");
      //5.释放资源。
      rclcpp::shutdown();
     

   return 0;

}*/
//方式二（推荐）

//自定义类 继承node
class MyNode :public rclcpp::Node
      {
            public:
            MyNode():Node("hello_node_cpp"){
                  RCLCPP_INFO(this->get_logger(),"helloworld!(继承的方式)");

            }

      };

      /*
            问题：初始化与资源释放在程序中起什么作用？
            答：
                  1.前提：构建的程序可能由若干步骤或阶段组成
                  初始化--->节点对象-->日志输出-->数据发布-->数据订阅-->资源释放
                  2.不同步骤或阶段之间涉及数据的传递
                  3.怎么实现数据传递？
                    使用context（上下文）对象。这是一个容器，可以存储数据也可以从中读取数据。
                  4。初始化其实就是要创建context对象，资源释放就是销毁context对象。
      
      */
int main(int argc,char const *argv[])
{
      //初始化
      rclcpp::init(argc,argv);


      //实例化自定义类
      auto node = std::make_shared<MyNode>();
      //....

      //资源释放
      rclcpp::shutdown();


      return 0;
}
