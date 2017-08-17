#include "lightSensorArray.h"

void LightSensorArray::Setup(){
  lsFront.Setup(LS_FRONT);
  lsLeft.Setup(LS_LEFT);
  lsBack.Setup(LS_BACK);
  lsRight.Setup(LS_RIGHT);
}

void LightSensorArray::SetThresh(){
  lsFront.SetThresh(42);
  lsLeft.SetThresh(35);
  lsBack.SetThresh(45);
  lsRight.SetThresh(50);
  thresholds[0] = 42;
  thresholds[1] = 35;
  thresholds[2] = 45;
  thresholds[3] = 50;
}

void LightSensorArray::GetVal(){
  lightValues[0] = lsFront.GetVal();
  lightValues[1] = lsLeft.GetVal();
  lightValues[2] = lsBack.GetVal();
  lightValues[3] = lsRight.GetVal();
  onWhite[0] = lsFront.onWhite();
  onWhite[1] = lsLeft.onWhite();
  onWhite[2] = lsBack.onWhite();
  onWhite[3] = lsRight.onWhite();
}

double LightSensorArray::LightAngle(){
  for (int i = 0; i < 4; i++) {
    if(onWhite[i]){
      vectori += iComp + iCords[i];
      vectorj += iComp + jCords[i];
    }
  }

  if(vectori!=0||vectorj!=0){
    double escape = atan2(vectorj,vectori);
    escape = escape * 180/pi;
    angle = mod(escape+270,360);
  } else{
    return angle = -30;
  }
  return mod(angle+180,360);
}
