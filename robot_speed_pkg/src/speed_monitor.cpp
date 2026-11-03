#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include <queue>
#include <vector>
#include <cmath>

// 任务三：编写函数模板
template<typename T>
T absoluteDifference(T a, T b) {
    return std::abs(a - b);
}

class SpeedMonitor : public rclcpp::Node
{
public:
    SpeedMonitor() : Node("speed_monitor"), previous_speed_(0), first_process_(true)
    {
        // 创建订阅者
        subscription_ = this->create_subscription<std_msgs::msg::Int32>(
            "/robot_speed", 10, std::bind(&SpeedMonitor::topic_callback, this, std::placeholders::_1));
            
        // 验证函数模板 int 和 double
        RCLCPP_INFO(this->get_logger(), "Template Test - int abs(5-2): %d", absoluteDifference(5, 2));
        RCLCPP_INFO(this->get_logger(), "Template Test - double abs(5.5-2.2): %.2f", absoluteDifference(5.5, 2.2));
    }

private:
    void topic_callback(const std_msgs::msg::Int32::SharedPtr msg)
    {
        RCLCPP_INFO(this->get_logger(), "Received speed: %d", msg->data);
        
        // 任务二：使用 queue 实现指令缓存
        speed_queue_.push(msg->data);
        
        // 队列中只有一条速度时，暂不处理
        if (speed_queue_.size() < 2) {
            RCLCPP_INFO(this->get_logger(), "Queue size < 2, waiting for next speed...");
            return;
        }
        
        // 取出最早收到的速度进行处理
        int current_speed = speed_queue_.front();
        speed_queue_.pop();
        
        RCLCPP_INFO(this->get_logger(), "Processing speed: %d", current_speed);
        
        // 任务三：速度异常检测
        if (first_process_) {
            previous_speed_ = 0;
            first_process_ = false;
        }
        
        // 计算绝对差值
        int delta_v = absoluteDifference(current_speed, previous_speed_);
        
        // 判断 WARNING 或 NORMAL
        if (delta_v >= 3) {
            RCLCPP_WARN(this->get_logger(), "WARNING");
        } else {
            RCLCPP_INFO(this->get_logger(), "NORMAL");
        }
        
        // 更新上一次处理的速度
        previous_speed_ = current_speed;
        
        // 保存最近 4 次速度变化值
        delta_history_.push_back(delta_v);
        if (delta_history_.size() > 4) {
            delta_history_.erase(delta_history_.begin()); // 删除最早的数据
        }
        
        // 统计 WARNING 次数
        int warning_count = 0;
        for (int val : delta_history_) {
            if (val >= 3) {
                warning_count++;
            }
        }
        
        // 输出系统状态
        if (warning_count >= 2) {
            RCLCPP_ERROR(this->get_logger(), "System State: UNSTABLE");
        } else {
            RCLCPP_INFO(this->get_logger(), "System State: STABLE");
        }
        RCLCPP_INFO(this->get_logger(), "-----------------------------");
    }

    rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr subscription_;
    std::queue<int> speed_queue_;
    std::vector<int> delta_history_;
    int previous_speed_;
    bool first_process_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SpeedMonitor>());
    rclcpp::shutdown();
    return 0;
}