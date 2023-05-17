#include <ros.h>
#include <std_msgs/String.h>

// UART pins
#define UART_RX_PIN 2
#define UART_TX_PIN 3
#define BAUD_RATE 115200

// ROS parameters
const char* host = "your_ros_master_ip";
const uint16_t port = 11411;  // Change if necessary

ros::NodeHandle_<ArduinoHardware> nh;
std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

void setup() {
  Serial.begin(115200);  // For debugging

  nh.getHardware()->setBaud(BAUD_RATE);
  nh.initNode();
  nh.advertise(chatter);
}

void loop() {
  // Generate a string message
  str_msg.data = "Hello, world!";

  // Publish the message to the "chatter" topic
  chatter.publish(&str_msg);
  nh.spinOnce();

  // Wait for 1 second
  delay(1000);
}
