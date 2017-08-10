#include <Arduino.h>
#include <defines.h>
#include "motorController.h"


void MotorController::Setup(){
  motorFrontLeft.Setup(13,12,11,true);
  motorBackLeft.Setup(10,9,8,false);
  motorBackRight.Setup(7,6,5,true);
  motorFrontRight.Setup(4,3,2,false);
}

void MotorController::Move(int angle, int rotation, int speed){
  angle = mod(90 - angle, 360);

  double a = cos(degreesToRadians(angle)) / sin(degreesToRadians(45));
  double b = sin(degreesToRadians(angle)) / cos(degreesToRadians(45));

  double motorRightValue = a - b;
  double motorBackRightValue = -a - b;
  double motorBackLeftValue = b - a;
  double motorLeftValue = a + b;

  double updatedSpeed = (double) speed / doubleAbs(fmax(fmax(fmax(doubleAbs(motorLeftValue), doubleAbs(motorRightValue)), doubleAbs(motorBackRightValue)), doubleAbs(motorBackLeftValue)));

  int motorRightSpeed = (int) round(motorRightValue * updatedSpeed) + rotation;
  int motorLeftSpeed = (int) round(motorLeftValue * updatedSpeed) + rotation;
  int motorBackRightSpeed = (int) round(motorBackRightValue * updatedSpeed) + rotation;
  int motorBackLeftSpeed = (int) round(motorBackLeftValue * updatedSpeed) + rotation;

  double updatedSpeed2 = (double) 255 / doubleAbs(fmax(fmax(fmax(doubleAbs(motorLeftSpeed), doubleAbs(motorRightSpeed)), doubleAbs(motorBackRightSpeed)), doubleAbs(motorBackLeftSpeed)));

  if (updatedSpeed2 < 1) {
    int motorRightSpeed = (int) round(motorRightSpeed * updatedSpeed2);
    int motorLeftSpeed = (int) round(motorLeftSpeed * updatedSpeed2);
    int motorBackRightSpeed = (int) round(motorBackRightSpeed * updatedSpeed2);
    int motorBackLeftSpeed = (int) round(motorBackLeftSpeed * updatedSpeed2);
  }

  motorFrontRight.Move(motorRightSpeed);
  motorFrontLeft.Move(motorLeftSpeed);
  motorBackRight.Move(motorBackRightSpeed);
  motorBackLeft.Move(motorBackLeftSpeed);
}

void MotorController::Turn(int speed){
  motorFrontLeft.Move(speed);
  motorFrontRight.Move(speed);
  motorBackLeft.Move(speed);
  motorBackRight.Move(speed);
}

void MotorController::Brake(){
  motorFrontLeft.Move(0);
  motorFrontRight.Move(0);
  motorBackLeft.Move(0);
  motorBackRight.Move(0);
}
