#include "motor.h"

Motor::Motor(int enA, int in1, int in2, int angle){
  enAPin = enA;
  in1Pin = in1;
  in2Pin = in2;
  dirAngle = angle;

  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}

void Motor::move(double speed, int max){

}

void Motor::move(int speed, int max){
  move((double)speed, max);
}

int Motor::getAngle(){
  return dirAngle;
}
