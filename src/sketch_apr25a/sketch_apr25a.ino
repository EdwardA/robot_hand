#include <PID_v1.h>

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  }
  

int fingerJointOne[] = {900, 10, 15, 0, 1, 0, 512, 0, 23}; //control properties for single joint: Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle, analog sensor pin

double Setpoint, Input, Output;
double Kp=2, Ki=5, Kd=1;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() {
  Serial.begin(9600);
  myPID.SetMode(AUTOMATIC);
  SetOutputLimits(-255, 255);
}

void loop() {
  Kp = fingerJointOne[0];
  Ki = fingerJointOne[1];
  Kd = fingerJointOne[2];
  Input = analogRead(fingerJointOne[8]);
  Serial.print("INPUT   ");
  Serial.print(Input);
  myPID.Compute();
  Serial.print("    OUTPUT   ");
  Serial.print(Output);
  pwmOut(Output, fingerJointOne[3], fingerJointOne[4]);
}
