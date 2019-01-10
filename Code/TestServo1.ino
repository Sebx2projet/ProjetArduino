#include <Servo.h>
Servo Servo1;
int angle1;

void setup() {
  Serial.begin(9600);
  Servo1.attach(11,544,2400);
}

void loop() {
  Servo1.write(60);
  angle1=Servo1.readMicroseconds();
  Serial.println(angle1);
  delay(10000);
  
}
