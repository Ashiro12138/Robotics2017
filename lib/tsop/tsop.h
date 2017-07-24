#ifndef TSOP_H
#define TSOP_H

#include <defines.h>

class TSOP{
public:
  int TSOPPINS[12] = {TSOP_0,TSOP_1,TSOP_2,TSOP_3,TSOP_4,TSOP_5,TSOP_6,TSOP_7,TSOP_8,TSOP_9,TSOP_10,TSOP_11};
  int TSOPTEMPVAL[12] = {0};
  int TSOPVAL[12] = {0};
  int TEMPFILTEREDVAL[12] = {0};
  int FILTEREDVAL[12] = {0};
  int SORTEDFILTEREDVAL[12] = {0};
  int SORTEDINDEX[12] = {0};
  int count = 0;
  int angle = 0;
  int simpleAngle = 0;
  int strength = 0;
  int simpleStrength = 0;
  int print = 10;

  void Setup();
  void ReadOnce();
  void Read();
  void FinishRead();
  void Refresh();
  void FilterValues();
  void GetAngleSimple();
  void GetAngle(int n);
  void GetStrengthSimple();
  void GetStrength(int n);
};

#endif
