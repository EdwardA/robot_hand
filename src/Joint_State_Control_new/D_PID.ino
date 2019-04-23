double motorPID(int Kp, int Ki, int Kd, double Setpoint, double angle){
  //PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);
  input = angle;
  kp = Kp;
  ki = Ki;
  kd = Kd;
  setpoint = Setpoint;
  myPID.Compute();
  return output;
}

//Kp, Ki, Kd, Motor pin 1, Motor pin 2, output, setpoint, angle
