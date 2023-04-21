/*
Copyright 2021 KnoblesseOblige

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
#define VENDOR_ID    0xAE7E
#define PRODUCT_ID   0x4F42 /* "OB" */
#define DEVICE_VER   0x0001
#define MANUFACTURER KnoblesseOblige
#define PRODUCT      Omnibus

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { B1, B0, D6, D4 }
#define MATRIX_COL_PINS { B4, B5, B6, C6, C7, F7, F6, F5, F4, F1, F0, D7 }

#define DIODE_DIRECTION COL2ROW

#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B3 }

#define RGB_DI_PIN B7
#ifdef RGB_DI_PIN
#    define RGBLED_NUM 22
#    define RGBLIGHT_ANIMATIONS
#endif

#define DEBOUNCE 5

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE
