#include "Arduino.h"
#include <PID_v1.h>

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
//                         0  1  2  3   4   5  6   7   8
double fingerJointOne[] = {4, 1, 0, 21, 20, 0, 90, 0, 19}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle, analog sensor pin  //meta
double fingerJointTwo[] = {4, 1, 0, 6, 7, 0, 90, 0, 18}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle, analog sensor pin  //inter
double fingerJointThree[] = {4, 1, 0, 8, 9, 0, 100, 0, 17}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle, analog sensor pin  //distal

double thumbJointOne[] = {5, 1, 0, 3, 2, 0, 230, 0, 16}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle, analog sensor pin  //rotation
double thumbJointTwo[] = {6, 1, 0, 5, 4, 0, 100, 0, 15}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle, analog sensor pin  //inter
double thumbJointThree[] = {5, 1, 0, 23, 22, 90, 120, 0, 14}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle, analog sensor pin  //distal



PID myPIDOne(&fingerJointOne[7], &fingerJointOne[5], &fingerJointOne[6], fingerJointOne[0], fingerJointOne[1], fingerJointOne[2], DIRECT);
PID myPIDTwo(&fingerJointTwo[7], &fingerJointTwo[5], &fingerJointTwo[6], fingerJointTwo[0], fingerJointTwo[1], fingerJointTwo[2], DIRECT);
PID myPIDThree(&fingerJointThree[7], &fingerJointThree[5], &fingerJointThree[6], fingerJointThree[0], fingerJointThree[1], fingerJointThree[2], DIRECT);

PID myPIDFour(&thumbJointOne[7], &thumbJointOne[5], &thumbJointOne[6], thumbJointOne[0], thumbJointOne[1], thumbJointOne[2], DIRECT);
PID myPIDFive(&thumbJointTwo[7], &thumbJointTwo[5], &thumbJointTwo[6], thumbJointTwo[0], thumbJointTwo[1], thumbJointTwo[2], DIRECT);
PID myPIDSix(&thumbJointThree[7], &thumbJointThree[5], &thumbJointThree[6], thumbJointThree[0], thumbJointThree[1], thumbJointThree[2], DIRECT);

//PID myPIDOne(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);



void setup() {
  analogReadResolution(12);
  analogWriteFrequency(21, 234375);
  analogWriteFrequency(20, 234375);
  analogWriteFrequency(6, 234375);
  analogWriteFrequency(7, 234375);
  analogWriteFrequency(8, 234375);
  analogWriteFrequency(9, 234375);
  analogWriteFrequency(3, 234375);
  analogWriteFrequency(2, 234375);
  analogWriteFrequency(5, 234375);
  analogWriteFrequency(4, 234375);
  analogWriteFrequency(23, 234375);
  analogWriteFrequency(22, 234375);
  Serial.begin(9600);
  PIDONE();
  PIDTWO();
  PIDTHREE();
  PIDFOUR();
  PIDFIVE();
  PIDSIX();
}

void loop() {

  fingerJointOne[7] = mapfloat(analogRead(fingerJointOne[8]), 0, 4096, 0, 360); //maps the 12bit analog reading to degrees for human readable debuging and ROS
  fingerJointTwo[7] = mapfloat(analogRead(fingerJointTwo[8]), 0, 4096, 0, 360); //maps the 12bit analog reading to degrees for human readable debuging and ROS
  fingerJointThree[7] = mapfloat(analogRead(fingerJointThree[8]), 0, 4096, 0, 360); //maps the 12bit analog reading to degrees for human readable debuging and ROS

  thumbJointOne[7] = mapfloat(analogRead(thumbJointOne[8]), 0, 4096, 0, 360); //maps the 12bit analog reading to degrees for human readable debuging and ROS
  thumbJointTwo[7] = mapfloat(analogRead(thumbJointTwo[8]), 0, 4096, 0, 360); //maps the 12bit analog reading to degrees for human readable debuging and ROS
  thumbJointThree[7] = mapfloat(analogRead(thumbJointThree[8]), 0, 4096, 0, 360); //maps the 12bit analog reading to degrees for human readable debuging and ROS
  
  Serial.print("INPUT   ");
  Serial.print(thumbJointOne[7]);
  
  myPIDOne.Compute();
  myPIDTwo.Compute();
  myPIDThree.Compute();
  
  myPIDFour.Compute();
  myPIDFive.Compute();
  myPIDSix.Compute();
  
  Serial.print("    OUTPUT   ");
  Serial.println(thumbJointOne[5]);
  
  pwmOut(fingerJointOne[5], fingerJointOne[3], fingerJointOne[4]);
  pwmOut(fingerJointTwo[5], fingerJointTwo[3], fingerJointTwo[4]);
  pwmOut(fingerJointThree[5], fingerJointThree[3], fingerJointThree[4]);

  pwmOut(thumbJointOne[5], thumbJointOne[3], thumbJointOne[4]);
  pwmOut(thumbJointTwo[5], thumbJointTwo[3], thumbJointTwo[4]);
  pwmOut(thumbJointThree[5], thumbJointThree[3], thumbJointThree[4]);
  delay(10);
}
