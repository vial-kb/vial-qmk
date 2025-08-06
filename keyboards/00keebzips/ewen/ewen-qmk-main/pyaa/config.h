/* Copyright 2018-2020 ENDO Katsuhiro <ka2hiro@curlybracket.co.jp> David Philip Barr <@davidphilipbarr> Pierre Chevalier <pierrechevalier83@gmail.com>

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

#define FORCE_NKRO
// #define NO_ACTION_FUNCTION
// #define NO_ACTION_ONESHOT
// #define NO_ACTION_MACRO
// #define IGNORE_MOD_TAP_INTERRUPT

/* USB Device descriptor parameter
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    konomu
#define PRODUCT         pyaa */

/* key matrix size
#define MATRIX_ROWS 6
#define MATRIX_COLS 6 */

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *                  NO_DIODE = switches are directly connected to AVR pins
 *
*/
#define DIRECT_PINS { \
    { B1, F7, F6, F5, F4, B6 }, \
    { B2, D0, D4, C6, D7, B3 }, \
    { B5, B4, E6, NO_PIN, NO_PIN, NO_PIN } \
}

#define DIRECT_PINS_RIGHT  { \
    { B6, F4, F5, F6, F7, B1 }, \
    { B3, D7, C6, D4, D0, B2 }, \
    { E6, B4, B5, NO_PIN, NO_PIN, NO_PIN } \
}


/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Serial settings */
#define USE_SERIAL
/* serial.c configuration for split keyboard */
#define SOFT_SERIAL_PIN D1

// #define MASTER_LEFT
#define SPLIT_USB_DETECT
