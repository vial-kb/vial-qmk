#pragma once

#include_next <mcuconf.h>

#undef STM32_PWM_USE_TIM3
#define STM32_PWM_USE_TIM3 TRUE
#define WS2812_PWM_DRIVER PWMD3
#define WS2812_PWM_CHANNEL 3