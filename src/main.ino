#include <Arduino.h>
#include "motor.h"
//#include "motorController.h"

Motor motor1;
Motor motor2;
Motor motor3;
Motor motor4;

void setup(){
	motor1.Setup(13,12,11);
	motor2.Setup(10,9,8);
	motor3.Setup(7,6,5);
	motor4.Setup(4,3,2);
}


void loop(){
	for (int i = 1; i < 256; i++) {
		motor1.Move(i,1);
		motor2.Move(i,1);
		motor3.Move(i,1);
		motor4.Move(i,1);
		delay(10);
	}
	for (int i = i; i > 0; i--) {
		motor1.Move(i,1);
		motor2.Move(i,1);
		motor3.Move(i,1);
		motor4.Move(i,1);
		delay(10);
	}
	for (int i = 1; i < 256; i++) {
		motor1.Move(i,-1);
		motor2.Move(i,-1);
		motor3.Move(i,-1);
		motor4.Move(i,-1);
		delay(10);
	}
	for (int i = i; i > 0; i--) {
		motor1.Move(i,-1);
		motor2.Move(i,-1);
		motor3.Move(i,-1);
		motor4.Move(i,-1);
		delay(10);
	}
}
