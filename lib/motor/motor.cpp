#include "motor.h"

Motor::Motor(int enA, int in1, int in2){
  enAPin = enA;
  in1Pin = in1;
  in2Pin = in2;
}

void Motor::Turn(int speed, int direction){
  if(direction==1){
    digitalWrite(in1Pin, LOW);
    digitalWrite(in2Pin, HIGH);
    analogWrite(enAPin, speed);
  }
  else{
    digitalWrite(in1Pin, HIGH);
    digitalWrite(in2Pin, LOW);
    analogWrite(enAPin, speed);
  }
}

void Motor::motorSetup(){
  pinMode(enAPin, OUTPUT);
  pinMode(in1Pin, OUTPUT);
  pinMode(in2Pin, OUTPUT);
}
