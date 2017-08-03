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
	90	|       |   270
			\______/
			   180
*/

// MotorController motor;
// TSOP tsop;
Compass compass;


void setup(){
	Serial.begin(9600);
	Wire.begin();
	Serial.println("1");
	compass.compassSetup();
	Serial.println("2");
	compass.calibrate();
	Serial.println("3");
	// motor.Setup();
	// tsop.Setup();
}

void loop(){
	compass.updateGyro();
	Serial.println("Test");
	Serial.println(compass.heading);
	Serial.println(compass.calibration);
	delay(1000);
	// tsop.Read();
	// tsop.FilterValues();
	// tsop.GetAngle(3);
	// if(DEBUG_MODE){
	// 	for (int i = 0; i < TSOP_NUM; i++) {
	// 		Serial.println(tsop.SORTEDFILTEREDVAL[i]);
	// 		Serial.println(tsop.SORTEDINDEX[i]);
	// 		Serial.println(tsop.angle);
	// 	}
	// }
	// motor.Move(255,tsop.angle);
}
