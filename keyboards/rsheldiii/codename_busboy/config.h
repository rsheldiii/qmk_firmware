#pragma once

#include "config_common.h"


// #define DEBUG_MATRIX_SCAN_RATE
// #define HAL_USE_I2C TRUE

// #undef RP_I2C_USE_I2C0
// #define RP_I2C_USE_I2C0 TRUE


// #define USE_I2CV1

#define I2C_DRIVER I2CD2
// #define I2C_DRIVER I2C1      //I2C peripheral to use
#define I2C1_SCL_PIN GP7           //The pin number for SCL
#define I2C1_SDA_PIN GP6           //The pin number for SDA
// #define I2C0_SCL_PIN GP7           //The pin number for SCL
// #define I2C0_SDA_PIN GP6           //The pin number for SDA
// #define I2C2_SCL_PIN GP7           //The pin number for SCL
// #define I2C2_SDA_PIN GP6           //The pin number for SDA