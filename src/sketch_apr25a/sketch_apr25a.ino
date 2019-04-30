#include "Arduino.h"
#include <PID_v1.h>

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  
              //            0   1   2    3  4  5   6   7   8
double fingerJointOne[] = {0.5, 5, 0.01, 0, 1, 0, 180, 0, 23}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle, analog sensor pin
double fingerJointTwo[] = {0.5, 5, 0.01, 2, 3, 0, 180, 0, 22}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle, analog sensor pin

double Setpoint, Input, Output;
double Kp=2, Ki=5, Kd=1;
PID myPIDOne(&fingerJointOne[7], &fingerJointOne[5], &fingerJointOne[6], fingerJointOne[0], fingerJointOne[1], fingerJointOne[2], DIRECT);
PID myPIDTwo(&fingerJointTwo[7], &fingerJointTwo[5], &fingerJointTwo[6], fingerJointTwo[0], fingerJointTwo[1], fingerJointTwo[2], DIRECT);
//PID myPIDOne(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);



void setup() {
  Serial.begin(9600);
  myPIDOne.SetMode(AUTOMATIC);
  myPIDOne.SetControllerDirection(DIRECT); 
  myPIDOne.SetOutputLimits(-255, 255);
  myPIDOne.SetSampleTime(100); //200ms is default

  myPIDTwo.SetMode(AUTOMATIC);
  myPIDTwo.SetControllerDirection(DIRECT); 
  myPIDTwo.SetOutputLimits(-255, 255);
  myPIDTwo.SetSampleTime(100); //200ms is default
  analogReadResolution(12);
  
}

void loop() {

  fingerJointOne[7] = mapfloat(analogRead(fingerJointOne[8]), 0, 4096, 0, 360); //maps the 12bit analog reading to degrees for human readable debuging and ROS
  fingerJointTwo[7] = mapfloat(analogRead(fingerJointTwo[8]), 0, 4096, 0, 360); //maps the 12bit analog reading to degrees for human readable debuging and ROS
  //Serial.print("INPUT   ");
  //Serial.print(fingerJointOne[7]);
  myPIDOne.Compute();
  myPIDTwo.Compute();
  //Serial.print("    OUTPUT   ");
  //Serial.print(fingerJointOne[5]);
  pwmOut(fingerJointOne[5], fingerJointOne[3], fingerJointOne[4]);
  pwmOut(fingerJointTwo[5], fingerJointTwo[3], fingerJointTwo[4]);
  delay(50);
}
