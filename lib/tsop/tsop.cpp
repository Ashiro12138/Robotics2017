#include <Arduino.h>
#include "tsop.h"

void TSOP::Setup(){
  pinMode(TSOP_POWER, OUTPUT);

  for(int i = 0; i < 12; i++){
    pinMode(TSOPPINS[i], INPUT);
  }

  digitalWrite(TSOP_POWER, HIGH);
}

void TSOP::ReadOnce(){
  for(int i = 0; i < 12; i++){
    TSOPVAL[i] += digitalRead(TSOPPINS[i])^1;
  }
  count++;
}

void TSOP::Refresh(){
  digitalWrite(TSOP_POWER, LOW);
  delay(2);
  digitalWrite(TSOP_POWER, HIGH);
}

void TSOP::Read(){
  while(count<200){
    ReadOnce();
  }
}

void TSOP::FinishRead(){

}
