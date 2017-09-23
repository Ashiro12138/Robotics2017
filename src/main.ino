#include <Arduino.h>
#include <defines.h>
#include <apexCommon.h>
#include <Motor.h>
#include <MotorController.h>
#include <tsop.h>
#include <MotorController.h>
#include <I2C.h>
#include <Compass.h>
#include <lightSensor.h>
#include <lightSensorArray.h>

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

MotorController Motor;
TSOP tsop;
Compass compass;
LightSensorArray lights;

const int GoalAcc = 7;
const int MoveSpd = 100;

unsigned long previousMillis = 0;
const long interval	= 200;
bool voiding = false;
int oldLight = 0;

unsigned long compMillis = 0;
int previousHeading = 0;
const double kp = 4.5;
const double kd = 9;//-8;


void setup(){
	Serial.begin(9600);
	Wire.begin();
	compass.compassSetup();
	compass.calibrate();
	Motor.Setup(1);
	tsop.Setup();
	lights.Setup();
	lights.GetVal();
	int robot = 3;
	if(robot==1){
		lights.SetThresh(50,120,80,100);
	} else if(robot==2){
		lights.SetThresh(30,70,50,100);
	} else{
		lights.SetThresh(999,999,999,999);
	}
	//int range = 20;
	//lights.SetThresh(lights.lightValues[0]+range,lights.lightValues[1]+range,lights.lightValues[2]+range,lights.lightValues[3]+range);
}

void loop(){
	compass.updateGyro();
	tsop.Read();
	tsop.FilterValues();
	tsop.GetAngle(3);
	tsop.GetStrength(3);
	lights.GetVal();
	int angle = tsop.angle;
	int strength = tsop.strength;
	int light = lights.LightAngle();
	unsigned long currentMillis = millis();


	int relativeHeading = compass.heading > 180 ? (360 - compass.heading) : -compass.heading;

	double diffTime = ((double)(currentMillis - compMillis))/100.0;
	double difference = ((double)(relativeHeading - previousHeading)) / diffTime;
	compMillis = currentMillis;

	previousHeading = relativeHeading;

	int correction = round(kp*((double)relativeHeading) + kd*difference);

	Motor.Move(0,correction,0);

	// if(angle>=180){
	// 	if(angle<200){
	// 		Motor.Move(90,correction,MoveSpd);
	// 	} else if(angle<260){
	// 		Motor.Move(180,correction,MoveSpd);
	// 	} else if(angle<346){
	// 		Motor.Move(225,correction,MoveSpd);
	// 	} else{
	// 		Motor.Move(360,correction,MoveSpd);
	// 	}
	// } else{
	// 	if(angle>160){
	// 		Motor.Move(270,correction,MoveSpd);
	// 	} else if(angle>100){
	// 		Motor.Move(180,correction,MoveSpd);
	// 	} else if(angle>14){
	// 		Motor.Move(135,correction,MoveSpd);
	// 	} else{
	// 		Motor.Move(0,correction,MoveSpd);
	// 	}
	// }

}
