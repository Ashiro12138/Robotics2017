#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Arduino.h"

#include <motor.h>

class MotorController{
public:
  MotorController();

  void moveDirection(int angle, int speed, int rotate);
  void updateDirection(int angle, int speed, int rotate);
  void brake();

  Motor motor1;
  Motor motor2;
  Motor motor3;
  Motor motor4;

  int currentAngle = 0;
  int currentSpeed = 0;
  int currentRotate = 0;
};

#endif
