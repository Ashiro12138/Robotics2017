#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor{
public:
  Motor(int enA, int in1, int in2);
  Motor(){}
  void Turn(int speed, int direction);
  void motorSetup();
private:
  int enAPin, in1Pin, in2Pin, motorSpeed, motorDirection;
};

#endif
