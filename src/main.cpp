#include <Arduino.h>
#include "motor.h"
#include "motorController.h"

int main(){
	MotorController motor;
	motor.Move(255,0);
	return 0;
}
