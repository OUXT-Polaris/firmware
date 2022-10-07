#include "EthernetInterface.h"
#include "mbed.h"
#include "mros2.h"
#include "std_msgs/msg/u_int8.hpp"

#define IP_ADDRESS ("192.168.11.2")      /* IP address */
#define SUBNET_MASK ("255.255.255.0")    /* Subnet mask */
#define DEFAULT_GATEWAY ("192.168.11.1") /* Default gateway */

int main()
{
  EthernetInterface network;
  network.set_dhcp(false);
  network.set_network(IP_ADDRESS, SUBNET_MASK, DEFAULT_GATEWAY);
  nsapi_size_or_error_t result = network.connect();
  mros2::init(0, NULL);
  mros2::Node node = mros2::Node::create_node("battery_monitor_node");
  mros2::Publisher pub = node.create_publisher<std_msgs::msg::Unit8>("battery_state", 1);
}