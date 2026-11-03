 #include "rclcpp/rclcpp.hpp" 
 #include "std_msgs/msg/string.hpp"
 #include<vector>
 
 using namespace std::chrono_literals;

//3.自定义节点类；
class MyNode: public rclcpp::Node{ 
public:

    MyNode():Node("mynode_node_cpp"){ 
      v.push_back(10);
      v.push_back(20);
      v.push_back(30);
      v.push_back(40);
      v.push_back(50);
      publisher_ = this->create_publisher<std_msgs::msg::String>("topic",10);      

      timer_ = this->create_wall_timer(500ms,std::bind(&MyNode::timer_callback,this));
               
     }
private:
  void timer_callback()
  {
    auto message = std_msgs::msg::String();
    std::string result_str = "";
    for(int i = 0; i < v.size();i++)
    {
      result_str = result_str + std::to_string(v[i]);
      if(i<v.size()-1)
      {
        result_str = result_str + ", ";

      }
    }
    message.data = result_str;
    RCLCPP_INFO(this->get_logger(),"发布的消息: '%s",message.data.c_str());
    publisher_->publish(message);

  }
  std::vector<int>v;
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
        
};
  
int main(int argc, char const * argv[]) 
{
   //2.初始化ROS2客户端； 
   rclcpp::init(argc,argv); 
   //4.调用spin函数，并传入节点对象指针； 
   rclcpp::spin(std::make_shared<MyNode>()); 
   //5.资源释放。 
   rclcpp::shutdown(); 
   return 0; 
} 
