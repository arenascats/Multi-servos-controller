# Multi-servos-controller
The arduino lib could Init and control 1 to 4 servos,throw serial command,.Not need too many cpu time.Not need more arduino shield  or so.

#How to use the lib
<hr>

1.Add this lib to arduino library file path(In a new path)

or

Add to your project path




2.Include the lib in main file

<font color="blue">#include"servo.h"<font>





3.Init servo

[1]Instantiation :

<font color="blue">MultiServo servo</font>



[2]define and init servo port in setup()

#define MyServo 5
#define MyServo2 4
<font color="blue">servo.ServoInit(MyServo,MyServo2);</font>



[3]Set angle

<font color="blue">servos.SetAngle(0, 150);</font>
<font color="blue">servos.SetAngle(1,150);</font>



4.Use Serial port control servo

In this test

'a+number' is change servo 0 angle

'A+number' is change servo 1 angle




[[PS:Serial commmand could adjust in servo.cpp]]
[[PS2:You can add other function in function 'ServoRunning',and your function with  be run]]



You can look at my .ino file,as a example.
