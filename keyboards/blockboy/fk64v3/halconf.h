#pragma once

#include_next <halconf.h>


#undef HAL_USE_PAL
#define HAL_USE_PAL TRUE


#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE
