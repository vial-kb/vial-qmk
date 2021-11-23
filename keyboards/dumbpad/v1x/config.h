/*
Copyright 2020 imchipwood

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0913
#define MANUFACTURER    imchipwood
#define PRODUCT         dumbpad

/* Column/Row IO definitions */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Reduce tapdance required taps from 5 to 2 */
#define TAPPING_TOGGLE 2

/* USB Device descriptor parameter */
#define DEVICE_VER      0x0010

/* Column/Row IO definitions */
#define MATRIX_ROWS 4
#define MATRIX_COLS 5
#define MATRIX_ROW_PINS { F4, F5, F6, F7 }
#define MATRIX_COL_PINS { C6, D7, E6, B4, B5 }
#define UNUSED_PINS

/* VIAL secure unlock */

#define VIAL_UNLOCK_COMBO_ROWS { 1, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 0 }


/* Rotary encoder */
#define ENCODERS_PAD_A { B2, D0 }
#define ENCODERS_PAD_B { D4, D1 }


/* LED layer indicators */
#define LAYER_INDICATOR_LED_0 B6
#define LAYER_INDICATOR_LED_1 B1
#define LED_NUM_LOCK_PIN B3

/* Bootmagic - hold down rotary encoder pushbutton while plugging in to enter bootloader */
#define BOOTMAGIC_LITE_ROW 3
#define BOOTMAGIC_LITE_COLUMN 0

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
    #define RGBLED_NUM 8
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_VAL_STEP 8
    #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
    #define RGBLIGHT_ANIMATIONS

#endif
