#ifndef LIGHTSENSOR_H_
#define LIGHTSENSOR_H_

#include <Arduino.h>

class LightSensor {
public:
  int threshold;
  int pin;
  int val;
  void Setup(int inPin);
  void SetThresh(int thresh);
  void SetThresh(int low, int high);
  int GetVal();
  int onWhite();

};

#endif
