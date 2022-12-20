// Copyright 2022 t (@RoastPotatoes)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
/* USB Device descriptor parameter */
#define VENDOR_ID    0xFEED
#define PRODUCT_ID   0x0000
#define DEVICE_VER   0x0001
#define MANUFACTURER RoastPotatoes
#define PRODUCT      IBM Model M SSK
/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 16

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG
/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B9, B8, B7, B6, B5, B4, B3, A15 }
#define MATRIX_COL_PINS { B15,  B14,  B13,  B12,  B10,  B1,  B0,  A7,  A4,  A3,  A2,  A1, A0, C15, C14, C13 }
#define UNUSED_PINS

/* disable print */
//#define NO_PRINT
#define DEBOUNCE 5

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION ROW2COL

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
