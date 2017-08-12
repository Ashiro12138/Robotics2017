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
	270	|       |   90
			\______/
			   180
*/

MotorController motor;
TSOP tsop;
Compass compass;

#define GoalAcc 7
#define LightDelay 75

void setup(){
	Serial.begin(9600);
	motor.Setup();
	tsop.Setup();
	Wire.begin();
	compass.compassSetup();
	compass.calibrate();
	// pinMode(A0,INPUT);
	// pinMode(A1,INPUT);
	// pinMode(A2,INPUT);
	// pinMode(A3,INPUT);
}

void loop(){
	compass.updateGyro();
	tsop.Read();
	tsop.FilterValues();
	tsop.GetAngle(3);
	tsop.GetStrength(6);
	int LightFront = analogRead(A0);
	int LightLeft = analogRead(A1);
	int LightBack = analogRead(A2);
	int LightRight = analogRead(A3);

	int LightFrontMid = (LightFrontG + LightFrontW) / 2;
	int LightLeftMid = (LightLeftG + LightLeftW) / 2;
	int LightBackMid = (LightBackG + LightBackW) / 2;
	int LightRightMid = (LightRightG + LightRightW) / 2;

	bool LightFrontOn = LightFront > LightFrontMid;
	bool LightLeftOn = LightLeft > LightLeftMid;
	bool LightBackOn = LightBack > LightBackMid;
	bool LightRightOn = LightRight > LightRightMid;

	if(LightFrontOn&&LightLeftOn){
		motor.Move(255,135);
		delay(LightDelay);
	}else if(LightFrontOn&&LightRightOn){
		motor.Move(255,225);
		delay(LightDelay);
	}if(LightBackOn&&LightLeftOn){
		motor.Move(255,45);
		delay(LightDelay);
	}else if(LightBackOn&&LightRightOn){
		motor.Move(255,315);
		delay(LightDelay);
	}else{
		if(LightFrontOn){
			motor.Move(255,180);
			delay(LightDelay);
		}else if(LightLeftOn){
			motor.Move(255,90);
			delay(LightDelay);
		}else if(LightBackOn){
			motor.Move(255,0);
			delay(LightDelay);
		}else if(LightRightOn){
			motor.Move(255,270);
			delay(LightDelay);
		}else{
			if(compass.heading < 360-GoalAcc && compass.heading > 180){
				motor.Turn(40,1);
			}else if(compass.heading > GoalAcc && compass.heading <= 180){
				motor.Turn(40,-1);
			}else{
				if(tsop.strength==0){
					motor.Brake();
				} else if(tsop.strength < 60){
					motor.Move(255,tsop.angle);
				}else{
					if(tsop.angle <= 180){
						if(tsop.angle >= 150){
							motor.Move(255,270);
						}else if(tsop.angle >= 60){
							motor.Move(255,180);
						}else if(tsop.angle >= 30){
							motor.Move(180,90);
						}else{
							motor.Move(255,0);
						}
					}else{
						if(tsop.angle <= 210){
							motor.Move(255,90);
						}else if(tsop.angle <= 300){
							motor.Move(255,180);
						}else if(tsop.angle <= 330){
							motor.Move(180,270);
						}else{
							motor.Move(255,0);
						}
					}
				}
			}
		}
	}


	Serial.print(LightFront);
	Serial.print(" ");
	Serial.print(LightLeft);
	Serial.print(" ");
	Serial.print(LightBack);
	Serial.print(" ");
	Serial.println(LightRight);


}
