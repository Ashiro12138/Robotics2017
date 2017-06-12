#include <Arduino.h>
#include "motor.h"

int main(){
	Motor motor1;
	motor1.Setup(10, 9, 8);
	motor1.Move(255, 1);
	return 0;
}
