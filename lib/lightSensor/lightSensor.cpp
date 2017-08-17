#include "lightSensor.h"

void LightSensor::Setup(int inPin){
  pin = inPin;
  pinMode(pin,INPUT);
}

void LightSensor::SetThresh(int thresh){
  threshold = thresh;
}

void LightSensor::SetThresh(int low, int high){
  threshold = (low + high) / 2;
}

int LightSensor::GetVal(){
  val = analogRead(pin);
  return val;
}

int LightSensor::onWhite(){
  return  val > threshold ? 1 : 0;
}
