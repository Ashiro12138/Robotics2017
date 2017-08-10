#include <Arduino.h>
#include <defines.h>
#include <apexCommon.h>
#include <motor.h>
#include <motorController.h>
#include <tsop.h>
#include <motorController.h>
#include <I2C.h>
#include <Compass.h>

// 13 12 11 Front Left   Positive -true-> Negative    COSINE
// 10 9  8  Back Left    Negative -false-> Negative   SINE
// 7  6  5  Back Right   Positive -false-> Positive   COSINE
// 4  3  2  Front Right  Negative -true-> Positive    SINE

/*
      	 	 0
					_  _
				/	 V	\
270  	|       |   90
			\______/
			   180
*/

MotorController motor;
TSOP tsop;
Compass compass;

const int GoalAcc = 7;

void setup(){
	Serial.begin(9600);
	Wire.begin();
	compass.compassSetup();
	compass.calibrate();
	motor.Setup();
	tsop.Setup();
}

void loop(){
	compass.updateGyro();
	tsop.Read();
	tsop.FilterValues();
	tsop.GetAngle(3);
	tsop.GetStrength(3);

	int relativeHeading = compass.heading > 180 ? (360 - compass.heading) :-compass.heading;
	int correctionRotation = 0;
	if (abs(relativeHeading) > GoalAcc) {
		correctionRotation = constrain(relativeHeading * 7, -150, 150);
	}


	if (tsop.angle >= 350 || tsop.angle <= 10){
		motor.Move(0,correctionRotation,255);
	}else{
		if(tsop.strength<110){
			motor.Move(tsop.angle,correctionRotation,255);
		}else{
			if(tsop.angle <= 180){
				if(tsop.angle >= 150){
					motor.Move(270,correctionRotation,255);
				}else if(tsop.angle >= 60){
					motor.Move(180,correctionRotation,255);
				}else{
					motor.Move(90,correctionRotation,255);
				}
			}else{
				if(tsop.angle <= 210){
					motor.Move(90,correctionRotation,255);
				}else if(tsop.angle <= 300){
					motor.Move(180,correctionRotation,255);
				}else{
					motor.Move(270,correctionRotation,255);
				}
			}
		}
	}


	Serial.print(tsop.strength);

	// motor.Move(tsop.angle, correctionRotation, 255);
}
