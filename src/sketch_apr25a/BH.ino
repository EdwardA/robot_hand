void pwmOut(int out, int M1, int M2) {  // to H-Bridge board
  if (out > 1) {
    analogWrite(M1, out);                             // drive motor CW
    analogWrite(M2, 0);
    Serial.print("    forward   ");
    Serial.println(out);


  }
  else if (out < 1) {
    analogWrite(M1, 0);
    analogWrite(M2, abs(out));  // drive motor CCW
    Serial.print("    backwards   ");
    Serial.println(out);
  }
  else {
    analogWrite(M1, 255);
    analogWrite(M2, 255);
    Serial.println("    STOP");

  }
}
