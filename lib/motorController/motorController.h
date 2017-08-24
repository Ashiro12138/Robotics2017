#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Arduino.h"
#include <motor.h>
#include <apexCommon.h>

class MotorController{
public:
  double vector1, vector2, off;
  Motor motorFrontLeft;
  Motor motorFrontRight;
  Motor motorBackLeft;
  Motor motorBackRight;
  void Setup(int robot);
  void Move(int angle, int rotation, int speed);
  void Turn(int speed);
  void Brake();
};


#endif
