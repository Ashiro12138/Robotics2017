#include <Arduino.h>
#include <defines.h>
#include "motorController.h"


void MotorController::Setup(){
  motor1.Setup(13,12,11,true);
  motor2.Setup(10,9,8,false);
  motor3.Setup(7,6,5,false);
  motor4.Setup(4,3,2,true);
}

void MotorController::Move(double speed, double direction){
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

  motor1.Move(abs(vector1),(vector1>0)-(vector1<0));
  motor2.Move(abs(vector2),(vector2>0)-(vector2<0));
  motor3.Move(abs(vector1),(vector1>0)-(vector1<0));
  motor4.Move(abs(vector2),(vector2>0)-(vector2<0));

}

void MotorController::Turn(int speed, int direction){
  if(direction==1){
    motor1.Move(speed, 1);
    motor2.Move(speed, 1);
    motor3.Move(speed, -1);
    motor4.Move(speed, -1);
  }else{
    motor1.Move(speed,-1);
    motor2.Move(speed,-1);
    motor3.Move(speed, 1);
    motor4.Move(speed, 1);
  }
}

void MotorController::Brake(){
  motor1.Brake();
  motor2.Brake();
  motor3.Brake();
  motor4.Brake();
}
