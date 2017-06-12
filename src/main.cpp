#include "Arduino.h"
#include <motor.h>
#include <cstdio>

int main(){
	Motor motor1;
	motor1.setup(10, 9, 8);
	motor1.move(255, 1);
	return 0;
}