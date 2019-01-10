#include <Servo.h>
Servo Servo1;
int angle1;

void setup() {
  Serial.begin(9600);
  Servo1.attach(11,544,2400);
}

void loop() {
  Servo1.writeMicroseconds(2400);
  angle1=Servo1.read();
  Serial.println(angle1);
  delay(1500);
  
}
