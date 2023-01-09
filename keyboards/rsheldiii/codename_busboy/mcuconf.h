#pragma once

#include_next <mcuconf.h>

// for Pico
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

// for Seeed
// #undef RP_I2C_USE_I2C1
// #define RP_I2C_USE_I2C1 TRUE