#include <PID_v1.h>
#include <ros.h>
#include <ros/time.h>
#include <std_msgs/String.h>
#include <sensor_msgs/JointState.h>

char* id = "/robot_hand";
char *a[] = {"base_to_thumb" , "thumb_meta_to_proximal_zero" , "thumb_meta_to_proximal"}; // F: Front - B: Back - R: Right - L: Left
float pos[4]; /// stores arduino time
float vel[4];
float eff[4];

ros::NodeHandle  nh;

sensor_msgs::JointState hand;


ros::Publisher hand_state("/joint_states", &hand);

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

char potOne;
char potTwo;        //positional control pots
char potThree;

int fingerJointOne[] = {9, 5, 17, 1, 2, 0, 0, 0}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle
int fingerJointTwo[] = {9, 5, 17, 3, 4, 0, 0, 0}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle
int fingerJointThree[] = {9, 5, 17, 5, 6, 0, 0, 0}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle

int thumbJointOne[] = {9, 5, 17, 7, 8, 0, 0, 0}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle
int thumbJointTwo[] = {9, 5, 17, 9, 10, 0, 0, 0}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle
int thumbJointThree[] = {9, 5, 17, 11, 12, 0, 0, 0}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle

double kp = 9, ki = 5 , kd = 17, input, output, setpoint;             // PID values for control
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

long previousMillis = 0;

void setup() {
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(1);
  myPID.SetOutputLimits(-255, 255);
  analogWriteFrequency(2, 234375);
  analogWriteFrequency(3, 234375);
  analogWriteFrequency(4, 234375);
  analogWriteFrequency(5, 234375);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, INPUT);

  ROSsetup();

}
