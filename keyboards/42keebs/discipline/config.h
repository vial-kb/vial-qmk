/*Copyright 2019 coseyfannitutti

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

#define VENDOR_ID       0x6B62
#define PRODUCT_ID      0x6869
#define DEVICE_VER      0x0001
#define MANUFACTURER    "coseyfannitutti"
#define PRODUCT         "DISCIPLINE"

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

#define MATRIX_ROW_PINS { B2, A1, B1, A0, B0 }
#define MATRIX_COL_PINS { A2, B3, A3, B4, A4, D5, D6, C6, C5, C4, C3, C2, C1, C0, D7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

#define USB_MAX_POWER_CONSUMPTION 100

#define ENCODERS_PAD_A { D0 }
#define ENCODERS_PAD_B { D1 }
#define ENCODER_DIRECTION_FLIP
#define ENCODER_RESOLUTION 4
#define TAP_CODE_DELAY 10

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

