#include "EthernetInterface.h"
#include "mbed.h"
#include "mros2.h"
#include "std_msgs/msg/u_int8.hpp"
#include "EthernetInterface.h"

#define IP_ADDRESS ("192.168.11.2") /* IP address */
#define SUBNET_MASK ("255.255.255.0") /* Subnet mask */
#define DEFAULT_GATEWAY ("192.168.11.1") /* Default gateway */

int main()
{
    EthernetInterface network;
    network.set_dhcp(false);
    network.set_network(IP_ADDRESS, SUBNET_MASK, DEFAULT_GATEWAY);
    nsapi_size_or_error_t result = network.connect();

    printf("mbed mros2 start!\r\n");
    printf("app name: pub_float32\r\n");
    mros2::init(0, NULL);
    MROS2_DEBUG("mROS 2 initialization is completed\r\n");

    mros2::Node node = mros2::Node::create_node("mros2_node");
    //mros2::Publisher pub = node.create_publisher<std_msgs::msg::UInt8>("battary_state", 10);
    osDelay(100);
    MROS2_INFO("ready to pub/sub message\r\n");

    std_msgs::msg::UInt8 msg;
    uint8_t publish_num = 1;
    while (true)
    {
        msg.data = publish_count;
        MROS2_INFO("publishing uint8 msg!!");
        //pub.publish(msg);

        publish_count = publish_count + 0.1;
        osDelay(1000);
    }
}