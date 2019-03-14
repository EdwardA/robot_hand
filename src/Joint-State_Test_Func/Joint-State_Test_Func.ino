#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>

char* id = "/myBot";
char *a[] = {"fore_finger_joint_one_pitch", "fore_finger_joint_one_yaw", "fore_finger_joint_two", "fore_finger_joint_three"}; // F: Front - B: Back - R: Right - L: Left
float pos[4]; /// stores arduino time
float vel[4];
float eff[4];

ros::NodeHandle  nh;

sensor_msgs::JointState hand;


ros::Publisher hand_state("bob", &hand);

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void setup() {
  ROSsetup();

}

void loop() {
  ROSloop();

}
