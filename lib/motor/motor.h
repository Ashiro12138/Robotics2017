#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor{
public:
  Motor(int motor1, int motor2, int motor3, int motor4);
  Motor(){}
private:
  int motor1Pin, motor2Pin, motor3Pin, motor4Pin;
};

#endif
