#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Arduino.h"
#include <motor.h>

class MotorController{
public:
  double vector1, vector2, off;
  Motor motor1;
  Motor motor2;
  Motor motor3;
  Motor motor4;
  void Setup();
  void Move(double speed, double direction);
  void Turn(int speed, int direction);
  void Brake();
};


#endif
