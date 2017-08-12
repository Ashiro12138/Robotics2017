#include <Arduino.h>
#include "motor.h"

void Motor::Setup(int enA, int in1, int in2, bool reversed){
	enAPin = enA;
	in1Pin = in1;
	in2Pin = in2;
	reversedDirection = reversed;
	pinMode(enAPin, OUTPUT);
	pinMode(in1Pin, OUTPUT);
	pinMode(in2Pin, OUTPUT);
}

void Motor::Move(int speed, int direction){
	if(reversedDirection){
		if(direction==1){
			digitalWrite(in1Pin, HIGH);
			digitalWrite(in2Pin, LOW);
			analogWrite(enAPin, speed);
		} else if(direction==-1){
			digitalWrite(in1Pin, LOW);
			digitalWrite(in2Pin, HIGH);
			analogWrite(enAPin, speed);
    }
	}else{
    if(direction==1){
			digitalWrite(in1Pin, LOW);
			digitalWrite(in2Pin, HIGH);
			analogWrite(enAPin, speed);
		} else if(direction==-1){
			digitalWrite(in1Pin, HIGH);
			digitalWrite(in2Pin, LOW);
			analogWrite(enAPin, speed);
	  }
	}
}

void Motor::Brake(){
	digitalWrite(in1Pin, LOW);
	digitalWrite(in2Pin, LOW);
	analogWrite(enAPin, 0);
}
