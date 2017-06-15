#include <Arduino.h>
#include "motor.h"
#include "motorController.h"
//#include "motorController.h"

// 13 12 11 Front Left   Positive -true-> Negative    COSINE
// 10 9  8  Back Left    Negative -false-> Negative   SINE
// 7  6  5  Back Right   Positive -false-> Positive   COSINE
// 4  3  2  Front Right  Negative -true-> Positive    SINE

/*
      	 	 0
					_  _
				/	 V	\
	90	|       |   270
			\______/
			   180
*/

MotorController motor;

void setup(){
	motor.Setup();
	motor.Move(255, 0);
}


/*void loop(){
	for (int i = 1; i < 256; i++) {
		motor1.Move(i,1);
		motor2.Move(i,-1);
		motor3.Move(i,1);
		motor4.Move(i,-1);
		delay(10);
	}
	for (int i = i; i > 0; i--) {
		motor1.Move(i,-1);
		motor2.Move(i,1);
		motor3.Move(i,-1);
		motor4.Move(i,1);
		delay(10);
	}
	for (int i = 1; i < 256; i++) {
		motor1.Move(i,1);
		motor2.Move(i,-1);
		motor3.Move(i,1);
		motor4.Move(i,-1);
		delay(10);
	}
	for (int i = i; i > 0; i--) {
		motor1.Move(i,1);
		motor2.Move(i,-1);
		motor3.Move(i,1);
		motor4.Move(i,-1);
		delay(10);
	}
}
*/
void loop(){
}
