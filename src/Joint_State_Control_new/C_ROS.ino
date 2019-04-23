void ROSsetup() {
  nh.initNode();
  nh.advertise(hand_state);


}
void ROSloop(float joint1, float joint2, float joint3, float joint4) {
  pos[0] = mapfloat(joint1, 0, 1023, 0, ((3 * PI) / 2)); //joint
  pos[1] = mapfloat(joint2, 0, 1023, 0, ((3 * PI) / 2)); //joint
  pos[2] = 1;
  pos[3] = 1;


  long interval = 100;
  unsigned long currentMillis = millis();

  // put your main code here, to run repeatedly:
  hand.header.frame_id = id;
  hand.name_length = 4;
  hand.position_length = 4;
  hand.effort_length = 4;
  hand.header.stamp = nh.now();

  hand.name = a;
  hand.position = pos;
  hand.effort = eff;

  if (currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    hand_state.publish( &hand );
  }

  nh.spinOnce();


}
