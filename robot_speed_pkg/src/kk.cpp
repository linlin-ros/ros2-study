#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <vector>
#include <chrono>

using namespace std::chrono_literals;

class SpeedPublisher : public rclcpp::Node
{
public:
    SpeedPublisher() : Node("speed_publisher"), index_(0)
    {
        // 创建发布者，话题名为 /robot_speed，消息类型为 std_msgs::msg::Int32
        publisher_ = this->create_publisher<std_msgs::msg::Int32>("/robot_speed", 10);
        
        // 设置 1Hz 的定时器
        timer_ = this->create_wall_timer(1s, std::bind(&SpeedPublisher::timer_callback, this));
        
        // 初始化速度序列
        speeds_ = {2, 5, 4, 8, 3, 6};
    }

private:
    void timer_callback()
    {
        auto message = std_msgs::msg::Int32();
        message.data = speeds_[index_];
        
        RCLCPP_INFO(this->get_logger(), "Publishing speed: %d", message.data);
        publisher_->publish(message);
        
        // 循环索引
        index_ = (index_ + 1) % speeds_.size();
    }

    rclcpp::Publisher<std_msgs::msg::Int32>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    std::vector<int> speeds_;
    size_t index_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SpeedPublisher>());
    rclcpp::shutdown();
    return 0;
}
