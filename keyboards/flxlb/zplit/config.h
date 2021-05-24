/*
Copyright 2021 fluxlab
	Vial port (c) 2021 kaznai kaz#3304

Copyright 2015 Jack Humbert

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

#define VIAL_KEYBOARD_UID {0x0C, 0x86, 0xE4, 0xBD, 0xD1, 0xC8, 0x8C, 0xEF}
#define VIAL_ENCODER_KEYCODE_DELAY 10
/* USB Device descriptor parameter */
#define VENDOR_ID       0x7076
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0002
#define MANUFACTURER    FluxLab
#define PRODUCT         Zplit (Vial port by kaz)

/* key matrix size */
// Rows are doubled-up
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

// wiring of each half
#define MATRIX_ROW_PINS { D4, F5, F4, F1 }
#define MATRIX_COL_PINS { B2, B3, D6, D7, B4, B5 }
// #define MATRIX_COL_PINS { B6, B2, B3, B1, F7, F6 }
// uncomment line above if you need to reverse left-to-right key order;

#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
// #define MATRIX_HAS_GHOST

/* number of backlight levels */
// #define BACKLIGHT_LEVELS 3

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Select hand configuration. Defaults to MASTER_LEFT */
// #define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

/* configuration for split keyboard */
#define SOFT_SERIAL_PIN D0
#define SELECT_SOFT_SERIAL_SPEED 1
// #define USE_I2C
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 500

#ifdef ENCODER_ENABLE
#define ENCODERS_PAD_A { B0 }
#define ENCODERS_PAD_B { D2 }
#endif

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
// #define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
// #define LOCKING_RESYNC_ENABLE

#ifdef RGBLIGHT_ENABLE
/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#define RGBLED_NUM 16
#define RGBLIGHT_LED_MAP { 0, 1, 2, 3, 4, 5, 6, 7, 15, 14, 13, 12, 11, 10, 9, 8}
#define RGBLED_SPLIT { 8, 8 }
#define RGBLIGHT_SPLIT
#define RGBLIGHT_ANIMATIONS
#endif

/* Feature disable options
 * These options are also useful to firmware size reduction.

 disable debug print
// #define NO_DEBUG

 disable print
// #define NO_PRINT

 disable action features
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT
// #define NO_ACTION_MACRO
// #define NO_ACTION_FUNCTION
 */
