#include "servo.h"
#include <stdint.h>
#include <Arduino.h>
//名称:ServoMode
//功能:设置Servo的运行模式,ONCE单次,CIRCLE循环
void MultiServo::ServoMode(int servomode)
{
  DriveMode = servomode;
}
//名称:CheckPinwhether
//功能:测试该pin是否存在
//返回值:bool型
bool MultiServo::CheckPinwhether(int pin)
{
  if (pin > 0 && pin < 18)
  {
    return true;
  }
  else
  {
    return  false;
  }
}

//名称:ServoInit
//功能:对Servo进行初始化,放置在setup位置


void MultiServo::ServoInit(int servo0)
{
  if (CheckPinwhether(servo0))
  {
    servo[0] = servo0;
    pinMode(servo[0], OUTPUT);
    numofServo = 1;
  }

}

void MultiServo::ServoInit(int servo1, int servo2)
{
  if (CheckPinwhether(servo1) && CheckPinwhether(servo2))
  {
    servo[0] = servo1;
    servo[1] = servo2;
    pinMode(servo[0], OUTPUT);
    pinMode(servo[1], OUTPUT);
    numofServo = 2;
  }

}
void MultiServo::ServoInit(int servo1, int servo2, int servo3)
{
  if (CheckPinwhether(servo1) && CheckPinwhether(servo2) && CheckPinwhether(servo3))
  {
    servo[0] = servo1;
    servo[1] = servo2;
    servo[2] = servo3;
    pinMode(servo[0], OUTPUT);
    pinMode(servo[1], OUTPUT);
    pinMode(servo[2], OUTPUT);
    numofServo = 3;
  }
}
void MultiServo::ServoInit(int servo1, int servo2, int servo3, int servo4)
{
  if (CheckPinwhether(servo1) && CheckPinwhether(servo2) && CheckPinwhether(servo3) && CheckPinwhether(servo4))
  {
    servo[0] = servo1;
    servo[1] = servo2;
    servo[2] = servo3;
    servo[3] = servo4;
    pinMode(servo[0], OUTPUT);
    pinMode(servo[1], OUTPUT);
    pinMode(servo[2], OUTPUT);
    pinMode(servo[3], OUTPUT);
    numofServo = 4;

  }
}
//功能:设置指定编号servo的角度
void MultiServo::SetAngle(int servonum, int Angle)
{
  angle[servonum] = Angle;
}


//功能:设置指定端口servo的角度
void MultiServo::SetServoAngle(int servo, int Angle)
{

}

//功能:驱动设置完成后的舵机的循环函数,根据设置的角度对影响舵机的2000微秒以内的高电平时间进行调整
void MultiServo::DriveServos(int Servonum)
{
//  int t = 2000 / 270 * angle[Servonum];
   int  t = angle[Servonum];
  digitalWrite(servo[Servonum], LOW);
  digitalWrite(servo[Servonum], HIGH);
  delayMicroseconds(t);
  digitalWrite(servo[Servonum], LOW);
  delayMicroseconds(2000 - t);
  newTime = millis();
}

//功能:接收来自于串口的指令
void MultiServo::SerialCommand()
{
  int inputdate = 0;
   int mark = 0;
   String Command = {""};
  while (Serial.available() > 0)
    {
      Command += char(Serial.read());//读入单次收到的所有指令
      delay(2);
      mark = 1;
  }
   if(mark == 1) 
    {
      //Serial.println(Command);//----------调试语句回传
    if (Command.length() > 0)
    {
       for (int i = 1; i < Command.length() ; i++)
      {
        if( i ==1 && Command[0] == 'a')
        inputdate += (Command[i] - '0');
        else
        {
          inputdate = inputdate*10 + (Command[i]-'0');
        }
      }
      if(Command[0] == 'a')//设置指定角度
        {
        SetAngle(0, inputdate);
        Serial.print("Angle: ");
        Serial.println(inputdate);
        }
        else if(Command[0] == 'A')//设置指定角度
        {
        SetAngle(1, inputdate);
        Serial.print("Angle: ");
        Serial.println(inputdate);
        }
        
    }
    
    }
}

//功能:执行已经被定义角度的函数
void MultiServo::ServoRunning()
{
  const int minus = 700;
  const int maxus = 2700;
  const int offset = 0;
  for (int Servonum = 0; Servonum < numofServo; Servonum++)
  {
    double td =(( maxus - minus) / 180.0) * angle[Servonum];
    int ti = (int)td;
    digitalWrite(servo[Servonum], LOW);
    digitalWrite(servo[Servonum], HIGH);
    delayMicroseconds(minus);
    delayMicroseconds(ti);
    digitalWrite(servo[Servonum], LOW);
    delayMicroseconds(maxus - minus - ti);
    newTime = millis();
  }
  for (;;)//在时间间隔内执行的程序
  {
    if ( 18 + newTime < millis())  break;
    SerialCommand();
  }
 // Serial.print("T:");
 // Serial.println(newTime);
}


