#ifndef DEFINES_H
#define DEFINES_H

// GENERAL
#define DEBUG_MODE false

// MATH
#define pi 3.141592653

// TSOPS
#define TSOP_NUM 12
#define TSOP_POWER 52
#define TSOP_DELAY 2
#define TSOP_0 50
#define TSOP_1 48
#define TSOP_2 46
#define TSOP_3 44
#define TSOP_4 42
#define TSOP_5 40
#define TSOP_6 38
#define TSOP_7 36
#define TSOP_8 34
#define TSOP_9 32
#define TSOP_10 30
#define TSOP_11 28


// K1 + 2 * K2 + 2 * K3 = 16
#define TSOP_K1 12
#define TSOP_K2 1
#define TSOP_K3 1

#define TSOP_NUM 12

#define TSOP_FILTER_NOISE true
#define TSOP_FILTER_SURROUNDING true

// Light Sensor
#define LS_FRONT A0
#define LS_LEFT A1
#define LS_BACK A2
#define LS_RIGHT A3

#define LS_FRONT_G
#define LS_FRONT_W
#define LS_LEFT_G
#define LS_LEFT_W
#define LS_BACK_G
#define LS_BACK_W
#define LS_RIGHT_G
#define LS_RIGHT_W

// Compass
#define MPU9250_ADDRESS 0x68
#define MAG_ADDRESS 0x0C

#define GYRO_FULL_SCALE_250_DPS 0x00
#define GYRO_FULL_SCALE_500_DPS 0x08
#define GYRO_FULL_SCALE_1000_DPS 0x10
#define GYRO_FULL_SCALE_2000_DPS 0x18

#define ACC_FULL_SCALE_2_G 0x00
#define ACC_FULL_SCALE_4_G 0x08
#define ACC_FULL_SCALE_8_G 0x10
#define ACC_FULL_SCALE_16_G 0x18

#define COMPASS_CALIBRATION 1.39
#define COMPASS_CALIBRATION_TIME 1000

#define MOTOR_ANGLE 45

#endif
