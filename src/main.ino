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
const int MoveSpd = 255;

unsigned long previousMillis = 0;
const long interval	= 200;
bool voiding = false;

unsigned long compMillis = 0;
int previousHeading = 0;
const double kp = 6;
const double kd = -8;


void setup(){
	Serial.begin(9600);
	Wire.begin();
	compass.compassSetup();
	compass.calibrate();
	Motor.Setup(1);
	tsop.Setup();
	lights.Setup();
	lights.GetVal();
	if(true){
		lights.SetThresh(40,120,100,150);
	} else{
		lights.SetThresh(20,50,50,120);
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
	int correctionRotation = relativeHeading * 3;

	double diffTime = ((double)(currentMillis - compMillis))/100.0;
	double difference = ((double)(previousHeading - relativeHeading)) / diffTime;
	compMillis = currentMillis;
	//Serial.print((previousHeading-relativeHeading));
	//Serial.print("\t");
	// Serial.println(difference);
	previousHeading = relativeHeading;

	int correction = round(kp*((double)relativeHeading) + kd*difference);


	//Motor.Move(0, correction , 0);
	// Serial.print(relativeHeading);
	// Serial.print("\t");
	// Serial.println(correction);

	//Serial.println(relativeHeading);
	if(!voiding){
		if (true){//light == -30){
			// We are not touching a line!
			if (angle == -30){
				// There is no ball around, just compass correct
				Motor.Move(0,correction,0);
			} else{
				// Orbit Code Here
				if (strength<=90){
					// Too far away, move directly toward the ball
					Motor.Move(angle,correction,MoveSpd);
				} else{
					// Close enough to orbit now
					if (angle>=180){
						// Ball on left side, no code required in this section; just a place holder
						if (angle<215){
							// Move right to make back clear
							Motor.Move(90,correction,MoveSpd);
						} else if (angle<300){
							// Back is now clear, move back
							Motor.Move(180,correction,MoveSpd);
						} else if (angle<355){
							// Ball is at front left, now move left
							Motor.Move(270,correction,MoveSpd);
						} else{
							// Ball at front, now shoot!
							Motor.Move(0,correction,MoveSpd);
						}
					} else if (angle<180){
						// Ball on right side, this is just a place holder
						if (angle>145){
							// Move left to make back clear
							Motor.Move(270,correction,MoveSpd);
						} else if (angle>60){
							// Back clear, move back
							Motor.Move(180,correction,MoveSpd);
						} else if (angle>5){
							// Ball is at front right, move right
							Motor.Move(90,correction,MoveSpd);
						} else{
							// Ball infront, now shoot!
							Motor.Move(0,correction,MoveSpd);
						}
					}
				}
			}
		} else {
			previousMillis = currentMillis;
			voiding = true;
			Motor.Move(light, correction, 255);
		// delay(500);
	}
}else{
	if(currentMillis - previousMillis >= interval){
		voiding = false;
	}
}

	// for(int i;i<4;i++){
	// 	Serial.print(lights.lightValues[i]);
	// 	Serial.print("\t");
	// }
	// Serial.println();


	// Serial.print(tsop.strength);

	// Motor.Move(0, 0, 120);
}
