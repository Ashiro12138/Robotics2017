#include "Arduino.h"
#include <motor.h>

Motor motor1 = Motor(9, 8, 7);

void setup(){
  motor1.motorSetup();
}

void loop(){
  motor1.Turn(255,1);
}
