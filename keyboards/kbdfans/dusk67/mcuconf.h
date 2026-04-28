// Copyright 2026 Sarah Helmbrecht (@skhelmbrecht)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_HSE_ENABLED
#define STM32_HSE_ENABLED FALSE

#undef STM32_PLLSRC
#define STM32_PLLSRC STM32_PLLSRC_HSI

#undef STM32_PLLXTPRE
#define STM32_PLLXTPRE STM32_PLLXTPRE_DIV1

#undef STM32_PLLMUL_VALUE
#define STM32_PLLMUL_VALUE 12

#undef STM32_USBPRE
#define STM32_USBPRE STM32_USBPRE_DIV1

#undef STM32_RTCSEL
#define STM32_RTCSEL STM32_RTCSEL_NOCLOCK
