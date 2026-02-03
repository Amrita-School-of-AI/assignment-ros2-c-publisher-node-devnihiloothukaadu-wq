#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class PublisherNode : public rclcpp::Node
{
public:
    PublisherNode() : Node("publisher_node"), counter_(0)
    {
        // Create publisher on topic "/counter"
        publisher_ = this->create_publisher<std_msgs::msg::String>(
            "/counter", 10);

        // Create timer that triggers every 500ms
        timer_ = this->create_wall_timer(
            500ms,
            std::bind(&PublisherNode::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "Publisher Node Started!");
    }

private:
    void timer_callback()
    {
        // Create message
        std_msgs::msg::String msg;

        // Format: "Count: X"
        msg.data = "Count: " + std::to_string(counter_);

        // Log output
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", msg.data.c_str());

        // Publish message
        publisher_->publish(msg);

        // Increment counter
        counter_++;
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    int counter_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<PublisherNode>());

    rclcpp::shutdown();
    return 0;
}
