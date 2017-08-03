#ifndef LIGHTSENSOR_H
#define LIGHTSENSOR_H

#include <Arduino.h>
#include <defines.h>

class LightSensor {
public:

  int readValue;
  int inPin;
  int threshholdValue;

  void Setup();
  void SetThreshold(int thresh);
  void Read();
  bool OnWhite();
};

#endif
