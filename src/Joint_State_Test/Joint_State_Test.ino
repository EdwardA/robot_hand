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


void setup() {
  nh.initNode();
  nh.advertise(hand_state);
  
  
}
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void loop() {
  pos[1] = mapfloat(analogRead(A8), 0, 1023, 0, ((3*PI)/2)); //joint
  pos[0] = mapfloat(analogRead(A9), 0, 1023, 0, ((3*PI)/2)); //joint
  // put your main code here, to run repeatedly:
  hand.header.frame_id = id;
  hand.name_length = 4;
  hand.position_length = 4;
  hand.effort_length = 4;
  hand.header.stamp = nh.now();

  hand.name = a;
  hand.position = pos;
  hand.effort = eff;
  hand_state.publish( &hand );
  nh.spinOnce();  
  
  
}
