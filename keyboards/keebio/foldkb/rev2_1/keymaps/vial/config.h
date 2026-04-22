/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xA6, 0xD7, 0x59, 0x7B, 0x6E, 0x98, 0x14, 0x68}

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// ECS + BACKSPACE = UNLOCK
#define VIAL_UNLOCK_COMBO_ROWS { 0, 5 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 7 }
#define TAPPING_TOGGLE 2
#define VIAL_COMBO_ENTRIES 24
#define TAPPING_TERM 150
#define COMBO_TERM 30

#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_LED_COUNT
#    define RGBLIGHT_ANIMATIONS
#    define RGBLIGHT_LED_COUNT 89
#    undef RGBLED_SPLIT
#    define RGBLED_SPLIT { 44, 45 }
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP  10
#    define RGBLIGHT_SAT_STEP  17
#    define RGBLIGHT_VAL_STEP  17
#endif