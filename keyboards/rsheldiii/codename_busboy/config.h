#pragma once

#include "config_common.h"


// #define DEBUG_MATRIX_SCAN_RATE
// #define HAL_USE_I2C TRUE

// #undef RP_I2C_USE_I2C0
// #define RP_I2C_USE_I2C0 TRUE


// #define USE_I2CV1

#define F_SCL 100000L


// for Pico
// #define I2C_DRIVER I2CD1
// #define I2C1_SCL_PIN GP5           //The pin number for SCL
// #define I2C1_SDA_PIN GP4           //The pin number for SDA

// for Seed Xaio RP2040
#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN GP7           //The pin number for SCL
#define I2C1_SDA_PIN GP6           //The pin number for SDA
