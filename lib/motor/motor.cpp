#include "motor.h"
#include <cstdio>

void Motor::Setup(int enA, int in1, int in2){
	enAPin = enA;
	in1Pin = in1;
	in2Pin = in2;
	pinMode(enAPin, OUTPUT);
	pinMode(in1Pin, OUTPUT);
	pinMode(in2Pin, OUTPUT);
	printf("PIN %d has been set to OUTPUT\n", enAPin);
	printf("PIN %d has been set to OUTPUT\n", in1Pin);
	printf("PIN %d has been set to OUTPUT\n", in2Pin);
}

void Move(int speed, int direction){
    if(direction==1){
		digitalWrite(in1Pin, LOW);
		digitalWrite(in2Pin, HIGH);
		analogWrite(enAPin, speed);
		printf("Running positive at speed %d\n", speed);
	} else if(direction==-1){
		digitalWrite(in1Pin, HIGH);
		digitalWrite(in2Pin, LOW);
		analogWrite(enAPin, speed);
		printf("Running negative at speed %d\n", speed);
    }
}