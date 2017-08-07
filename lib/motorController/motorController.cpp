#include <Arduino.h>
#include <defines.h>
#include "motorController.h"


void MotorController::Setup(){
  motor1.Setup(13,12,11,true);
  motor2.Setup(10,9,8,false);
  motor3.Setup(7,6,5,true);
  motor4.Setup(4,3,2,false);
}

void MotorController::Move(double speed, double direction, int rotation){
	vector1 = sin(2*pi*((direction+45)/360))*speed;
	vector2 = cos(2*pi*((direction+45)/360))*speed;

	if(abs(vector1) > abs(vector2)){
		off = speed / abs(vector1);
		vector1 *= off;
		vector2 *= off;
	} else{
		off = speed / abs(vector2);
		vector1 *= off;
		vector2 *= off;
	}

  motor1.Move(vector1 + rotation);
  motor2.Move(vector2 + rotation);
  motor3.Move(-vector1 + rotation);
  motor4.Move(-vector2 + rotation);

}

void MotorController::Turn(int speed){
  motor1.Move(speed);
  motor2.Move(speed);
  motor3.Move(speed);
  motor4.Move(speed);
}

void MotorController::Brake(){
  motor1.Move(0);
  motor2.Move(0);
  motor3.Move(0);
  motor4.Move(0);
}
