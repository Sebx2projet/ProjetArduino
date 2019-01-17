#include <Servo.h>
Servo Servo1;
int angle1;
Servo Servo2;
int angle2;
Servo Servo3;
int angle3;

void setup() {
  Serial.begin(9600);
  Servo1.attach(18,544,2400);
  Servo2.attach(19,544,2400);
  Servo3.attach(17,544,2400);

  Servo1.write(60);
  delay(1000);
  Servo2.write(180);
  delay(1000);
  Servo3.write(73);
  delay(1000);
}

void loop() {

/*
  Servo1.write(120);
  delay(1000);
  Servo2.write(180);
  delay(3000);

  Servo1.write(15);
  delay(3000);

  Servo1.write(60);
  Servo2.write(86);
  delay(1000);
  Servo3.write(73);
  delay(500);
  Servo3.write(10);
  delay(500);
  Servo3.write(73);
  delay(500);
  Servo3.write(10);
  delay(5000);
*/
  Servo2.write(180);
  delay(1000);
  Servo1.write(90);
  delay(3000);
  Servo1.write(30);
  delay(3000);

  Servo1.write(60);
  delay(1000);
  Servo2.write(90);
  delay(1000);
  Servo3.write(73);
  delay(500);
  Servo3.write(20);
  delay(500);
  Servo3.write(73);
  delay(500);
  Servo3.write(20);
  delay(500);
  Servo3.write(73);
  delay(500);
  Servo3.write(20);
  delay(500);
  
  
}
