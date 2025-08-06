// Copyright 2023 kushima8 (@kushima8)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
// #include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS         1
#define MATRIX_COLS         4
#define MATRIX_ROW_PINS     { D4 }
#define MATRIX_COL_PINS     { B5, F4, F5, B6 }
#define DEBOUNCE            5

#define DIODE_DIRECTION COL2ROW

// RGB LED settings
#define WS2812_DI_PIN          D3
#ifdef RGBLIGHT_ENABLE
#    define RGBLED_NUM      4
#    define RGBLIGHT_LIMIT_VAL  100 // limitated for power consumption
#endif


#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
#endif

#define TAP_CODE_DELAY 5

