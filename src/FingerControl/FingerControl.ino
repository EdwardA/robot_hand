#include <PID_v1.h>
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
  //potPrint(1, pot1);
  //potPrint(2, pot2);
  //potPrint(3, pot3);
  //potPrint(4, pot4);
  input = pot1;
  double pot1SP = map(pot1, 1023, 0, 530, 240);
  double pot2SP = map(pot2, 1023, 0, 530, 240);
  potPrint(1, pot1SP);
  potPrint(3, pot3);
  input = pot3;
  setpoint = pot1SP;
  myPID.Compute();
  pwmOut(output, 2, 3);
  //pwmOut(output, 4, 5);
  
  input2 = pot4;
  if (digitalRead(6) == LOW){
    setpoint2 = pot2SP;
    //Serial.println("independant mode");
  }else{
    setpoint2 = setpoint;
    //Serial.println("curl mode");
  }
  //setpoint2 = pot2SP;
  myPID2.Compute();
  pwmOut(output2, 5, 4);
  //PIDControl(pot3, pot1SP, 2, 3);
  //PIDControl(pot4, pot2SP, 4, 5);
  potPrint(2, pot2SP);
  potPrint(4, pot4);

  //Serial.print("output1: ");
  //Serial.println(output);
  //Serial.print("output2: ");
  //Serial.println(output2);

  //Serial.println();
  //delay(100);
  ROSloop(pot1, pot2, pot3, pot4);

}
