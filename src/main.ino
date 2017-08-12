#include <Arduino.h>
#include <defines.h>
#include <apexCommon.h>
#include <motor.h>
#include <motorController.h>
#include <tsop.h>
#include <motorController.h>
#include <Compass.h>
#include <I2C.h>

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
Compass compass;

#define GoalAcc 7

void setup(){
	Serial.begin(9600);
	motor.Setup();
	tsop.Setup();
	Wire.begin();
	compass.compassSetup();
	compass.calibrate();
}

void loop(){
	compass.updateGyro();
	tsop.Read();
	tsop.FilterValues();
	tsop.GetAngle(3);
	tsop.GetStrength(3);

	if(compass.heading < 360-GoalAcc && compass.heading > 180){
		motor.Turn(255,1);
	}else if(compass.heading > GoalAcc && compass.heading <= 180){
		motor.Turn(255,-1);
	}else{
		if(tsop.strength < 80){
			motor.Move(255,tsop.angle);
		}else{
			
		}
	}

	Serial.println(compass.heading);

}
