#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

class Motor{
public:
  int enAPin, in1Pin, in2Pin;

  void Setup(int enA, int in1, int in2){
    enAPin = enA;
    in1Pin = in1;
    in2Pin = in2;
    pinMode(enAPin, OUTPUT);
    pinMode(in1Pin, OUTPUT);
    pinMode(in2Pin, OUTPUT);
  }

  void Move(int speed, int direction){
    if(direction==1){
      digitalWrite(in1Pin, LOW);
      digitalWrite(in2Pin, HIGH);
      analogWrite(enAPin, speed);
    }
    else if(direction==-1){
      digitalWrite(in1Pin, HIGH);
      digitalWrite(in2Pin, LOW);
      analogWrite(enAPin, speed);
    }
  }
};

#endif
