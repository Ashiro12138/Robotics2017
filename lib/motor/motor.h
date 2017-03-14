#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor{
public:
  Motor(int enA, int in1, int in2, int angle);
  Motor(){}
  void move(double speed, int max = 100);
  void move(int speed, int max = 100);
  int getAngle();
private:
  int enAPin, in1Pin, in2Pin, motorSpeed, dirAngle;
};

#endif
