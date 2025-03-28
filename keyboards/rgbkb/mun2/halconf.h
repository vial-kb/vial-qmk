/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#pragma once

#undef HAL_USE_I2C
#define HAL_USE_I2C TRUE

#undef HAL_USE_SIO
#define HAL_USE_SIO TRUE

#include_next "halconf.h"
