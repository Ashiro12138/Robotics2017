#ifndef COMPASS_H
#define COMPASS_H

#include <I2C.h>
#include <defines.h>
#include <apexCommon.h>

class Compass {
public:
  double heading;
  double calibration = COMPASS_CALIBRATION;

  void compassSetup();

  Vector3D readAccelerometer();
  Vector3D readGyroscope();
  Vector3D readMagnetometer();

  void updateGyro();
  double calibrate();

  long previousTime;


};

#endif
