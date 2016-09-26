//更新日期:20160923

#include <Arduino.h>
#ifndef SERVO_H_
#define SERVO_H_

#define ONCE 0
#define CIRCLE 1

class MultiServo
{
  private:
    int DriveMode;
    int servo[4];
    int angle[4];
    int lastTime;
    long newTime;
    int numofServo;
  public:
    void ServoMode(int);
    bool CheckPinwhether(int);
    void ServoInit(int);
    void ServoInit(int,int);
    void ServoInit(int,int,int);
    void ServoInit(int,int,int,int);
    void SetAngle(int servonum,int angle);
    void SetServoAngle(int servo,int angle);
    void DriveServos(int Servonum);
    void ServoRunning();
    void SerialCommand();

};

#endif

