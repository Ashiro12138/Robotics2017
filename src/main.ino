
#include "Arduino.h"
#include <defines.h>
#include <apexCommon.h>
#include <motor.h>
#include <motorController.h>
#include <tsop.h>
#include "motorController.h"

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
TSOP tsop;

void setup(){
	Serial.begin(9600);
	motor.Setup();
	tsop.Setup();
}

void loop(){
	tsop.Read();
	//motor.Move(255,0);
	delay(1000);
}
