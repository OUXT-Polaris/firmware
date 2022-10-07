#include "std_msgs/msg/u_int8.hpp"

template mros2::Publisher mros2::Node::create_publisher<std_msgs::msg::UInt8>(
  std::string topic_name, int qos);
template void mros2::Publisher::publish(std_msgs::msg::UInt8 & msg);