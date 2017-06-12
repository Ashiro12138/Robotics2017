#include <Arduino.h>
#include "motorController.h"

const float s2 = 1.414213562;
const float pi = 3.141592653;

Motor motor1;
// Motor motor2;
// Motor motor3;
// Motor motor4;


void setup(){
  motor1.Setup(10,9,8);
  // motor2.Setup(10,9,8);
  // motor3.Setup(10,9,8);
  // motor4.Setup(10,9,8);
}

void MotorController::Move(int speed, int direction){
  vector1 = cos(2*pi*((direction+45)/360))*(speed);
  vector2 = sin(2*pi*((direction+45)/360))*(speed);

  if(abs(vector1) > abs(vector2)){
    off = speed / abs(vector1);
    vector1 *= off;
    vector2 *= off;
  } else{
    off = speed / abs(vector2);
    vector1 *= off;
    vector2 *= off;
  }

  motor1.Move(abs(vector2),(vector1>0)-(vector1<0));
  // motor2.Move(abs(vector1),(vector1>0)-(vector1<0));
  // motor3.Move(abs(vector2),-((vector1>0)-(vector1<0)));
  // motor4.Move(abs(vector1),-((vector1>0)-(vector1<0)));
}
