#include "Arduino.h"
#include <tsop.h>

void TSOP::Setup(){
  pinMode(TSOP_POWER, OUTPUT);

  for(int i = 0; i < TSOP_NUM; i++){
    pinMode(TSOPPINS[i], INPUT);
  }

  digitalWrite(TSOP_POWER, HIGH);
}

void TSOP::ReadOnce(){
  for(int i = 0; i < TSOP_NUM; i++){
    TSOPTEMPVAL[i] += digitalRead(TSOPPINS[i])^1;
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
  FinishRead();
}

void TSOP::FinishRead(){
  for (int i = 0; i < TSOP_NUM; i++) {
    Serial.println("TSOP"+String(i)+": "+String(TSOPTEMPVAL[i]));
    TSOPVAL[i] = TSOPTEMPVAL[i];
    TSOPTEMPVAL[i] = 0;
  }
  Serial.println();
  count = 0;
  Refresh();
}

/*void TSOP::FilterValues(){
  //Remove Noise
  for (int i = 0; i < TSOP_NUM; i++) {
    #if TSOP_FILTER_NOISE
      if(TSOPVAL[i] < 5 || TSOPVAL[i] > 200){
        TEMPFILTEREDVAL[i] = 0;
      } else{
        TEMPFILTEREDVAL[i] = TSOPVAL[i];
      }
    #else
      TEMPFILTEREDVAL[i] = TSOPVAL[i];
    #endif
  }

  // a rather efficient way to filter data by scoring each data by the tsop by it's adjacent tsops
  for (int i = 0; i < TSOP_NUM; i++){
      #if TSOP_FILTER_SURROUNDING
          int temp = TSOP_K1 * tempFilteredValues[i] +
          TSOP_K2 * (tempFilteredValues[mod(i - 1, TSOP_NUM)] +
          tempFilteredValues[mod(i - 1, TSOP_NUM)]) +
          TSOP_K3 * (tempFilteredValues[mod(i - 2, TSOP_NUM)] +
          tempFilteredValues[mod(i - 2, TSOP_NUM)]);
      #else
          int temp = tempFilteredValues[i] << 4;
      #endif

      // TSOP_K1 + 2 * TSOP_K2 + 2 * TSOP_K3 = 16 so we must divide the value by 16

      filteredValues[i] = temp >> 4;
  }

  //Filter By Surrounding
  for (int i = 0; i < TSOP_NUM; i++) {
    #if TSOP_FILTER_SURROUNDING
      int temp = 0;
    #else
      int temp = 0;
    #endif

    FILTEREDVAL[i] = temp >> 4;

  }

  //Sorting TSOP Values
  for (int i = 0; i < TSOP_NUM; i++) {
    int maxVal = 0;
    int maxInd = 0;
    for (int j = 0; j < TSOP_NUM; j++) {
      if (FILTEREDVAL[j]>maxVal) {
        maxVal = FILTEREDVAL[j];
        maxInd = j;
      }
    }
    SORTEDFILTEREDVAL[i] = maxVal;
    FILTEREDVAL[maxInd] = -1;
  }


}

void TSOP::GetAngleSimple(){

}

void TSOP::GetAngle(){

}

void TSOP::GetStrengthSimple(){

}

void TSOP::GetStrength(){

}
*/
