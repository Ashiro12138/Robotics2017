#include "apexCommon.h"

int sign(int value) {
    return value >= 0 ? 1 : -1;
}

int sign(double value) {
    return value >= 0 ? 1 : -1;
}

double doubleAbs(double value) {
    return value * sign(value);
}

int mod(int x, int y){
  int z = x % y;
  return z < 0 ? z + y : z;
}
