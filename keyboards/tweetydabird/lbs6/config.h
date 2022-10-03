// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// USB Device descriptor parameter
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x23B0
#define DEVICE_VER   0x0110
#define MANUFACTURER TweetyDaBird
#define PRODUCT      LittleBigScroll 6

// Key matrix size
#define MATRIX_ROWS 3
#define MATRIX_COLS 3

// Assign pins
#define DIRECT_PINS { { NO_PIN, F5, NO_PIN }, { D4, D7, B4 }, { C6, E6, B5 } }
#define ENCODERS_PAD_A { F7 }
#define ENCODERS_PAD_B { F6 }
#define ENCODER_RESOLUTION 2

// RGB
#define RGB_DI_PIN D2

#ifdef RGB_DI_PIN
#   define RGBLED_NUM 8
#	define DRIVER_LED_TOTAL 8

#   define RGBLIGHT_HUE_STEP 8
#   define RGBLIGHT_SAT_STEP 8
#   define RGBLIGHT_VAL_STEP 8

#   define RGBLIGHT_LIMIT_VAL 200 // The maximum brightness level
#   define RGBLIGHT_SLEEP  // If defined, the RGB lighting will be switched off when the host goes to sleep?

//== Choose animations ==
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING

#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define BOOTMAGIC_LITE_ROW 2
#define BOOTMAGIC_LITE_COLUMN 0

// reduce memory
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
#define LAYER_STATE_8BIT