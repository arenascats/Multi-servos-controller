#include "servo.h"


#define MyServo 5
#define MyServo2 4
MultiServo servos;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(5, OUTPUT);
  servos.ServoInit(MyServo,MyServo2);
  servos.SetAngle(0, 150);
  servos.SetAngle(1,180);
}

void loop() {
  // put your main code here, to run repeatedly:
  servos.ServoRunning();
}
