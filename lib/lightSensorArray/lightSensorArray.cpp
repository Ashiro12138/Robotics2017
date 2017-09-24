#include "lightSensorArray.h"

void LightSensorArray::Setup(){
  lsFront.Setup(LS_FRONT);
  lsLeft.Setup(LS_LEFT);
  lsBack.Setup(LS_BACK);
  lsRight.Setup(LS_RIGHT);
}

void LightSensorArray::SetThresh(int front, int left, int back, int right){
  lsFront.SetThresh(front);
  lsLeft.SetThresh(left);
  lsBack.SetThresh(back);
  lsRight.SetThresh(right);
  thresholds[0] = lsFront.threshold;
  thresholds[1] = lsLeft.threshold;
  thresholds[2] = lsBack.threshold;
  thresholds[3] = lsRight.threshold;
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
  for (int i; i < 4; i++){
		if (onWhite[i]){
			vectori += iCords[i];
			vectorj += jCords[i];
		}
	}
	if(vectori!=0||vectorj!=0){
		escape = atan2(vectorj, vectori);
		escape = escape * 180/pi;
		angle = mod(escape + 270,360);
  }else{
    angle = -30;
    vectori = 0;
    vectorj = 0;
    escape = 0;
    return angle;
  }
  vectori = 0;
  vectorj = 0;
  escape = 0;
  return mod(angle+180,360);
}
