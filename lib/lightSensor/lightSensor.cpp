#include "lightSensor.h"

void LightSensor::Setup(){
  pinMod(inPin, INPUT);

  int calibrateTotal = 0;

  for (int i = 0; i < LS_CALIBRATE_COUNT; i++){
    Read();
    calibrateTotal += readValue;
  }
}

void LightSensor::SetThreshold(int thresh){

}

void LightSensor::Read(){

}

bool LightSensor::OnWhite(){

  return true;
}
