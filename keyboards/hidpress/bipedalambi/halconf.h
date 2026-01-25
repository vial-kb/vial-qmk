#pragma once

#define HAL_USE_I2C TRUE
#define HAL_USE_ADC TRUE
#define HAL_USE_SIO TRUE  // Required for serial communication

#include_next <halconf.h>
