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
const int MoveSpd = 200;

// double lightAngle(){
// 	int onWhite[4];
// 	double angle;
// 	int iComp = 0;
// 	int jComp = 0;
// 	int vectori, vectorj;
// 	int iCords[4] = {0, 1, 0, -1};
// 	int jCords[4] = {1, 0, -1, 0};
// 	int lightValues[4]={analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3)};
// 	// Serial.print(lightValues[0]);
// 	// Serial.print("\t");
// 	// Serial.print(lightValues[1]);
// 	// Serial.print("\t");
// 	// Serial.print(lightValues[2]);
// 	// Serial.print("\t");
// 	// Serial.println(lightValues[3]);
// 	int thresholds[4] = {42,35,45,50};
// 	for (int i; i < 4; i++){
// 		if (lightValues[i] > thresholds[i]) onWhite[i] = 1;
// 		else onWhite[i] = 0;
// 	}
// 	for (int i; i < 4; i++){
// 		if (onWhite[i]){
// 			//Serial.println(jCords[i]);
// 			vectori += iComp + iCords[i];
// 			vectorj += jComp + jCords[i];
// 		}
// 	}
//
// 	if(vectori!=0||vectorj!=0){
// 		double escape = atan2(vectorj, vectori);
// 		escape = escape * 180/pi;
// 		//Serial.println(escape);
// 		angle = mod(escape + 270,360);
//     // if(vectori==0){
//     //   angle = vectorj > 0 ? 0 : 180;
//     // }else{
//     //   if(vectori<0){
//     //     angle = (int)(round(270-atan(vectorj/vectori)*180/pi));
// 		// 		angle = 360 - angle;
//     //   } else{
//     //     angle = (int)(round(90-atan(vectorj/vectori)*180/pi));
// 		// 		angle = 360 - angle;
//     //   }
//     // }
//   }else{
//     return angle = -30;
//   }
// 	//Serial.println(angle);
// 	//delay(500);
// 	return mod(angle+180,360);
// }

void setup(){
	Serial.begin(9600);
	Wire.begin();
	compass.compassSetup();
	compass.calibrate();
	Motor.Setup(1);
	tsop.Setup();
	lights.Setup();
	lights.SetThresh();
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

	// int LightFront = analogRead(A0);
	// int LightLeft = analogRead(A1);
	// int LightBack = analogRead(A2);
	// int LightRight = analogRead(A3);

	int relativeHeading = compass.heading > 180 ? (360 - compass.heading) :-compass.heading;
	int correctionRotation = 0;
	if (abs(relativeHeading) > GoalAcc) {
		correctionRotation = constrain(relativeHeading * 7, -80, 80);
	}
	// Serial.print(relativeHeading);
	// Serial.print('\t');
	// Serial.println(correctionRotation);

	if(true){
		if (light == -30){
			// We are not touching a line!
			if (angle == -30){
				// There is no ball around, just compass correct
				Motor.Move(0,correctionRotation,0);
			} else{
				// Orbit Code Here
				if (strength<=90){
					// Too far away, move directly toward the ball
					Motor.Move(angle,correctionRotation,MoveSpd);
				} else{
					// Close enough to orbit now
					if (angle>=180){
						// Ball on left side, no code required in this section; just a place holder
						if (angle<215){
							// Move right to make back clear
							Motor.Move(90,correctionRotation,MoveSpd);
						} else if (angle<300){
							// Back is now clear, move back
							Motor.Move(180,correctionRotation,MoveSpd);
						} else if (angle<355){
							// Ball is at front left, now move left
							Motor.Move(270,correctionRotation,MoveSpd);
						} else{
							// Ball at front, now shoot!
							Motor.Move(0,correctionRotation,255);
						}
					} else if (angle<180){
						// Ball on right side, this is just a place holder
						if (angle>145){
							// Move left to make back clear
							Motor.Move(270,correctionRotation,MoveSpd);
						} else if (angle>60){
							// Back clear, move back
							Motor.Move(180,correctionRotation,MoveSpd);
						} else if (angle>5){
							// Ball is at front right, move right
							Motor.Move(90,correctionRotation,MoveSpd);
						} else{
							// Ball infront, now shoot!
							Motor.Move(0,correctionRotation,255);
						}
					}
				}
			}
		} else {
		Motor.Move(light, correctionRotation, 170);
		delay(100);
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
