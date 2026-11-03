#include"rclcpp/rclcpp.hpp" 
#include "std_msgs/msg/string.hpp"
#include<sstream>
#include<vector>
 
    class Listener:public rclcpp::Node{
    public:
      Listener():Node("listener_node_cpp")
     {
 
      subscription_= this->create_subscription<std_msgs::msg::String>("topic",10,std::bind(&Listener::do_cb,this,std::placeholders::_1));
      
        }
  private:
        void do_cb(const std_msgs::msg::String::SharedPtr msg)
        {
          std::vector<int> recv_vec;
          std::stringstream ss(msg->data);//把收到的字符串放进字符串流里
          std::string num_str;//临时变量，存放切割出来的一小段字符串
          while(std::getline(ss,num_str,','))//循环，以逗号，为分隔截取一段字符串
          {
            if(!num_str.empty())//如果截取的字符串不为空
            {
              recv_vec.push_back(std::stoi(num_str));//字符串转为int，存入ector
            }
          }

          for(auto it = recv_vec.begin(); it != recv_vec.end();it++)
          RCLCPP_INFO(this->get_logger(),"订阅的消息是: %d",*it);
        }
         rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
   };
 
 
     int main(int argc, char const *argv[])
   {
       rclcpp::init(argc,argv);
       rclcpp::spin(std::make_shared<Listener>());
       rclcpp::shutdown();
       return 0;
  }