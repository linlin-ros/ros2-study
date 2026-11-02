

/*需求：以某个固定频率发送文本“helloworld！”，文本后缀编号，每发送一条信息，编号递增1
步骤：
      1.包含头文件；
      2.初始化ros2客户端
      3.定义节点类；
        3-1.创建发布方；
        3-2.创建定时器；
        3-3.组织消息并发布。
      4.调用spin函数，并传入自定义类节点对象指针；
      5.释放资源*/

      //包含头文件
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"         

using namespace std::chrono_literals;//开启时间字面量后缀，可以直接写500ms

//3.定义节点类；
class MyNode:public rclcpp::Node
{
public:
  MyNode()
  : Node("mynode_node_cpp"),count_(0)
  {
    //3-1.创建发布方；
    /*
    模板：被发布的消息类型；
    参数：
    1.话题名称；
    2.QOS（消息队列长度）。
    返回值：发布对象指针。
    */
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic",10);
    //3-2.创建定时器；
    /*
    参数：
        1.时间间隔；
        2.回调函数；
        返回值：定时器对象指针。*/
    timer_ = this->create_wall_timer(500ms,std::bind(&MyNode::timer_callback,this));
  }
private:
  void timer_callback()
  {
    //3-3.组织消息并发布。
    auto message = std_msgs::msg::String();
    message.data = "Hello,world!" + std::to_string(count_++);
    RCLCPP_INFO(this->get_logger(),"发布的消息：'%s'",message.data.c_str());
    publisher_->publish(message);//把messages这条消息发布到话题上
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};
int main(int argc,char * argv[])
{
  //2.初始化ros2客户端；
  rclcpp::init(argc,argv);
  //4.调用spin函数，并传入节点对象指针。
  rclcpp::spin(std::make_shared<MyNode>());
  //5.释放资源；
  rclcpp::shutdown();
  return 0;
}

//假如要将整形数字  拼接起来

std::vector<int>v;//这个放private下
v.push_back(10);
v.push_back(20);
v.push_back(30);
v.push_back(40);
v.push_back(50);//这个放构造函数中
void timer_callback()
{
    auto message = std_msgs::msg::String();
    
    // 1. 准备一个空的字符串，用来装拼接后的结果
    std::string result_str = ""; 
    
    // 2. 遍历 vector 中的每一个数字
    for (size_t i = 0; i < v.size(); ++i) //v.size()的意思就是该容器的大小  有多少数据
    {
        // 把数字转成字符串，加到 result_str 后面
        result_str = result_str + std::to_string(v[i]); 
        
        // 如果当前不是最后一个数字，就在后面加个逗号和空格
        if (i < v.size() - 1) {
            result_str = result_str + ", ";
        }
    }
    
    // 3. 把拼好的长字符串赋值给消息的 data
    message.data = result_str;
    
    // 4. 打印日志并发布
    RCLCPP_INFO(this->get_logger(), "发布的消息: '%s'", message.data.c_str());
    publisher_->publish(message);
}

