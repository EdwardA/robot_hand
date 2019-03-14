void setup() {
  myPID.SetMode(AUTOMATIC);
  myPID.SetSampleTime(1);
  myPID.SetOutputLimits(-255, 255);

  myPID2.SetMode(AUTOMATIC);
  myPID2.SetSampleTime(1);
  myPID2.SetOutputLimits(-255, 255);
  //Serial.begin (115200);
  //analogReadResolution(12);
  //analogWriteResolution(12);
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
