void PIDONE() {
  myPIDOne.SetMode(AUTOMATIC);
  myPIDOne.SetControllerDirection(DIRECT);
  myPIDOne.SetOutputLimits(-255, 255);
  myPIDOne.SetSampleTime(100); //200ms is default
}
void PIDTWO() {
  myPIDTwo.SetMode(AUTOMATIC);
  myPIDTwo.SetControllerDirection(DIRECT);
  myPIDTwo.SetOutputLimits(-255, 255);
  myPIDTwo.SetSampleTime(100); //200ms is default
}
void PIDTHREE() {
  myPIDThree.SetMode(AUTOMATIC);
  myPIDThree.SetControllerDirection(DIRECT);
  myPIDThree.SetOutputLimits(-255, 255);
  myPIDThree.SetSampleTime(100); //200ms is default
}

void PIDFOUR() {
  myPIDFour.SetMode(AUTOMATIC);
  myPIDFour.SetControllerDirection(DIRECT);
  myPIDFour.SetOutputLimits(-255, 255);
  myPIDFour.SetSampleTime(100); //200ms is default
}

void PIDFIVE() {
  myPIDFive.SetMode(AUTOMATIC);
  myPIDFive.SetControllerDirection(DIRECT);
  myPIDFive.SetOutputLimits(-255, 255);
  myPIDFive.SetSampleTime(100); //200ms is default
}

void PIDSIX() {
  myPIDSix.SetMode(AUTOMATIC);
  myPIDSix.SetControllerDirection(DIRECT);
  myPIDSix.SetOutputLimits(-255, 255);
  myPIDSix.SetSampleTime(100); //200ms is default
}
