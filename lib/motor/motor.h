#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor{
public:
  int enAPin, in1Pin, in2Pin;
  void Setup(int enA, int in1, int in2);
  void Move(int speed, int direction);  
};

#endif
