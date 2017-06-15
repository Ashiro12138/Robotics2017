#include <Arduino.h>
#include "motorController.h"

#define pi 3.141592653

void MotorController::Setup(){
  motor1.Setup(13,12,11,true);
  motor2.Setup(10,9,8,false);
  motor3.Setup(7,6,5,false);
  motor4.Setup(4,3,2,true);
}

void MotorController::Move(double speed, double direction){
	vector1 = cos(2*pi*((direction+45)/360))*speed;
	vector2 = sin(2*pi*((direction+45)/360))*speed;

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
