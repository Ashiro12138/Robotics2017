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
