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
char potTwo;
char potThree;
char potFour;

double kp = 9, ki = 5 , kd = 17;             // modify for optimal performance
double kp2 = 5, ki2 = 2 , kd2 = 10; 
double input = 0, output = 0, setpoint = 512;
double input2 = 0, output2 = 0, setpoint2 = 512;
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);
PID myPID2(&input2, &output2, &setpoint2, kp2, ki2, kd2, DIRECT);

void loop() {
  int pot1 = analogRead(A0); //setoint
  int pot2 = analogRead(A1); //setpoint
  int pot3 = analogRead(A2); //joint
  int pot4 = analogRead(A3); //joint
  input = pot1;
  double pot1SP = map(pot1, 1023, 0, 530, 240);
  double pot2SP = map(pot2, 1023, 0, 530, 240);
  potPrint(1, pot1SP);
  potPrint(3, pot3);
  input = pot3;
  setpoint = pot1SP;
  myPID.Compute();
  pwmOut(output, 2, 3);
  
  input2 = pot4;
  if (digitalRead(6) == LOW){
    setpoint2 = pot2SP;
  }else{
    setpoint2 = setpoint;
  }
  myPID2.Compute();
  pwmOut(output2, 5, 4);
  potPrint(2, pot2SP);
  potPrint(4, pot4);

  ROSloop(pot1, pot2, pot3, pot4);

}
