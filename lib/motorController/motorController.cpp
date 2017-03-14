/*
The angle for 4 wheels is: {60, 120, 240, 300}
Angle and Speed required
*/
#include "motorController.h"

#include <defines.h>

MotorController::MotorController(){
  motor1 = Motor(enAPin_1, in1Pin_1, in2Pin_1, Angle_1);
  motor2 = Motor(enAPin_2, in1Pin_2, in2Pin_2, Angle_2);
  motor3 = Motor(enAPin_3, in1Pin_3, in2Pin_3, Angle_3);
  motor4 = Motor(enAPin_4, in1Pin_4, in2Pin_4, Angle_4);
}

void MotorController::updateDirection(int angle, int speed, int rotate){
  if (angle != currentAngle || speed != currentSpeed || rotate != currentRotate){
    moveDirection(angle, speed, rotate);
  }
}

void MotorController::moveDirection(int angle, int speed, int rotate){

  double directionAngleRadians = angle * RADIANS;

  double values[MOTOR_NUM] = {
    cos((motor1.getAngle()+90)*RADIANS - directionAngleRadians),
    cos((motor2.getAngle()+90)*RADIANS - directionAngleRadians),
    cos((motor3.getAngle()+90)*RADIANS - directionAngleRadians),
    cos((motor4.getAngle()+90)*RADIANS - directionAngleRadians)
  };

  double maxValue = (double)max(values[0]*(values[0] >= 0 ? 1 : -1),max(values[1]*(values[1] >= 0 ? 1 : -1),max(values[2]*(values[2] >= 0 ? 1 : -1),values[3]*(values[3] >= 0 ? 1 : -1))));

  double realPower = (double)speed/(double)(maxValue);

  for (int i = 0; i < MOTOR_NUM; i++){
    values[i] = round((values[i]*realPower)) + rotate;
  }

  motor1.move(constrain((int)round(values[0]), -255, 255), 255);
  motor2.move(constrain((int)round(values[0]), -255, 255), 255);
  motor3.move(constrain((int)round(values[0]), -255, 255), 255);
  motor4.move(constrain((int)round(values[0]), -255, 255), 255);
}
