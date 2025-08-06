/*
Copyright 2023 sporewoh

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

/* USB Device descriptor parameter */
// #define VENDOR_ID       0xBEAF
// #define PRODUCT_ID      0x000A
// #define DEVICE_VER      0x0000
// #define MANUFACTURER    sporewoh
// #define PRODUCT         bunchiez40

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 10

/* pin-out for PCB */
// #define MATRIX_ROW_PINS { GP5, GP7, GP8, GP14 } // config for my borked board :((
#define MATRIX_ROW_PINS { GP6, GP7, GP8, GP14 }
#define MATRIX_COL_PINS { GP4, GP3, GP2, GP1, GP0, GP15, GP26, GP27, GP28, GP29 }

#define OLED_DISPLAY_128X32
#define I2C1_SCL_PIN        GP13
#define I2C1_SDA_PIN        GP12
#define I2C_DRIVER I2CD1
#define OLED_BRIGHTNESS 128
// #define OLED_FONT_H "keyboards/1upkeyboards/pi40/lib/glcdfont.c"

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* COL2ROW or ROW2COL */
// #define DIODE_DIRECTION COL2ROW

#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// 200 is the default
#define TAPPING_TERM 250

// #define PERMISSIVE_HOLD

#define QUICK_TAP_TERM 100
