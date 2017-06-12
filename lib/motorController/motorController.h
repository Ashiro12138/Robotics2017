#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "Arduino.h"
#include <motor.h>

class MotorController{
public:
  int vector1, vector2, off;
  void Move(int speed, int direction);
};


#endif
