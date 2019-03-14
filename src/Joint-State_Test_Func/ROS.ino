void ROSsetup() {
  nh.initNode();
  nh.advertise(hand_state);
  
  
}
void ROSloop() {
  pos[1] = mapfloat(analogRead(A8), 0, 1023, 0, ((3*PI)/2)); //joint
  pos[0] = mapfloat(analogRead(A9), 0, 1023, 0, ((3*PI)/2)); //joint
  // put your main code here, to run repeatedly:
  hand.header.frame_id = id;
  hand.name_length = 4;
  hand.position_length = 4;
  hand.effort_length = 4;
  hand.header.stamp = nh.now();

  hand.name = a;
  hand.position = pos;
  hand.effort = eff;
  hand_state.publish( &hand );
  nh.spinOnce();  
  
  
}
