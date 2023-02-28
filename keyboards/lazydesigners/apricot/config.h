/*
Copyright 2022 LAZYDESIGNERS

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
#define VENDOR_ID       0x4C44 // "LD"
#define PRODUCT_ID      0x0031
#define DEVICE_VER      0x0001
#define MANUFACTURER    LAZYDESIGNERS
#define PRODUCT         apricot

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

#define MATRIX_ROW_PINS { B7, B2, D5, F7 }
#define MATRIX_COL_PINS { E6, D3, C7, D4, D6, D7, B4, B5, B6, C6 }

#define DIODE_DIRECTION COL2ROW

/* RBG underglow */
#define RGB_DI_PIN B3
#ifdef RGB_DI_PIN
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD   
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
/* #define RGBLIGHT_EFFECT_CHRISTMAS       */
#define RGBLIGHT_EFFECT_STATIC_GRADIENT  
/* #define RGBLIGHT_EFFECT_KNIGHT           */
/* #define RGBLIGHT_EFFECT_RGB_TEST         */
/* #define RGBLIGHT_EFFECT_ALTERNATING      */ 
/* #define RGBLIGHT_EFFECT_TWINKLE          */


#define RGBLIGHT_SLEEP
#define RGBLED_NUM 4
/* #define RGBLIGHT_HUE_STEP 8 */
/* #define RGBLIGHT_SAT_STEP 8 */
/* #define RGBLIGHT_VAL_STEP 8 */
#endif
