/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

// x-bows knight vial uid
#define VIAL_KEYBOARD_UID {0xA0, 0x52, 0x04, 0xCE, 0x23, 0x45, 0x71, 0x6D}

// esc and enter
#define VIAL_UNLOCK_COMBO_ROWS {0, 3}
#define VIAL_UNLOCK_COMBO_COLS {0, 13}


#ifdef RGB_MATRIX_ENABLE
/*
 * 17 RGB effects are pre-defined in /keyboards/xbows/nature/config.h
 * add a #undef line below to disable unused RGB effect to release space, e.g.,
//  #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL     // Single hue spinning spiral fades brightness

 * See https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects for all QMK RGB effects
 * add a #define line below to enable other RGB effect, e.g.,
 #define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL     // Single hue spinning spiral fades brightness
*/
//  #undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL     // Single hue spinning spiral fades brightness
#endif
