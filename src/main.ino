#include "Arduino.h"
#include <motor.h>

Motor motor1;

void setup(){
  motor1.Setup(10,9,8);
}

void loop(){
  motor1.Move(255,1)
}
