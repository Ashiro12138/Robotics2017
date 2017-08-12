#include <Arduino.h>
#include <defines.h>
#include <apexCommon.h>
#include <Motor.h>
#include <MotorController.h>
#include <tsop.h>
#include <MotorController.h>
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

MotorController Motor;
TSOP tsop;
Compass compass;

int lastLight = 0;

const int GoalAcc = 7;

double lightAngle(){
	int onWhite[4];
	double angle;
	int iComp = 0;
	int jComp = 0;
	int vectori, vectorj;
	int iCords[4] = {0, -1, 0, 1};
	int jCords[4] = {1, 0, -1, 0};
	int lightValues[4]={analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3)};
	// Serial.println(lightValues[3]);
	int thresholds[4] = {70,70,125,140};
	for (int i; i < 4; i++){
		if (lightValues[i] > thresholds[i]) onWhite[i] = 1;
		else onWhite[i] = 0;
	}
	for (int i; i < 4; i++){
		if (onWhite[i]){
			//Serial.println(jCords[i]);
			vectori += iComp + iCords[i];
			vectorj += jComp + jCords[i];
		}
	}

	if(vectori!=0||vectorj!=0){
		double fuckKnows = atan2(vectorj, vectori);
		fuckKnows = fuckKnows * 180/pi;
		//Serial.println(fuckKnows);
		angle = mod(fuckKnows + 270,360);
    // if(vectori==0){
    //   angle = vectorj > 0 ? 0 : 180;
    // }else{
    //   if(vectori<0){
    //     angle = (int)(round(270-atan(vectorj/vectori)*180/pi));
		// 		angle = 360 - angle;
    //   } else{
    //     angle = (int)(round(90-atan(vectorj/vectori)*180/pi));
		// 		angle = 360 - angle;
    //   }
    // }
  }else{
    return angle = -30;
  }
	//Serial.println(angle);
	//delay(500);
	return mod(angle+180,360);
}

void setup(){
	Serial.begin(9600);
	Wire.begin();
	compass.compassSetup();
	compass.calibrate();
	Motor.Setup(1);
	tsop.Setup();
	lastLight = -30;
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
	tsop.GetStrength(3);
	int angle = tsop.angle;
	int light = lightAngle();

	// int LightFront = analogRead(A0);
	// int LightLeft = analogRead(A1);
	// int LightBack = analogRead(A2);
	// int LightRight = analogRead(A3);

	int relativeHeading = compass.heading > 180 ? (360 - compass.heading) :-compass.heading;
	int correctionRotation = 0;
	if (abs(relativeHeading) > GoalAcc) {
		correctionRotation = constrain(relativeHeading * 7, -80, 80);
	}
	if (light == -30)
	{
		if (angle == -30)
		{
			Motor.Move(0,correctionRotation,0);
		}
		else
		{
			angle = map(angle, 0, 360, 360, 0);
			if (angle >= 350 || angle <= 10){
				Motor.Move(0,correctionRotation,220);
			}else{
				if(tsop.strength<110){
					Motor.Move(angle,correctionRotation,220);
				}else{
					if(angle <= 180){
						if(angle >= 120){
							Motor.Move(270,correctionRotation,220);
						}else if(angle >= 60){
							Motor.Move(180,correctionRotation,220);
						}else{
							Motor.Move(90,correctionRotation,220);
						}
					}else{
						if(angle <= 210){
							Motor.Move(90,correctionRotation,220);
						}else if(angle <= 300){
							Motor.Move(180,correctionRotation,220);
						}else{
							Motor.Move(270,correctionRotation,220);
						}
					}
				}
			}
		}
	}
	else
	{
		Motor.Move(light, correctionRotation, 200);
	}


	// Serial.print(tsop.strength);

	// Motor.Move(0, 0, 120);
}
