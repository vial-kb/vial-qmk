// Copyright 2021 Joric (@joric)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define VIAL_KEYBOARD_UID {0x80, 0x41, 0x59, 0xF5, 0x4B, 0xF3, 0x50, 0x97}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

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
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

// If you are using an Elite C rev3 on the slave side, uncomment the lines below:
// #define SPLIT_USB_DETECT
// #define NO_USB_STARTUP_CHECK
