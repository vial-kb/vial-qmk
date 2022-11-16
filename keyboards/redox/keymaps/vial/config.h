/*
Copyright 2018-2022 Mattia Dal Ben <matthewdibi@gmail.com>, Ben Williams @rufusw

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

/* Use I2C or Serial, not both */
#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */
#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

//#undef RGBLED_NUM
//#define RGBLIGHT_ANIMATIONS
//#define RGBLED_NUM 14
//#define RGBLIGHT_HUE_STEP 8
//#define RGBLIGHT_SAT_STEP 8
//#define RGBLIGHT_VAL_STEP 8

/* unique Vial keyboard ID and secure unlock combination Tab + Escape */
#define VIAL_KEYBOARD_UID {0xD4, 0x5F, 0x85, 0x16, 0x53, 0x2C, 0x47, 0xCB}
#define VIAL_UNLOCK_COMBO_ROWS {1, 2}
#define VIAL_UNLOCK_COMBO_COLS {0, 0}

/* For reducing RAM and EEPROM usage when using Vial*/
//#define VIAL_TAP_DANCE_ENTRIES 4
//#define VIAL_COMBO_ENTRIES 4
//#define VIAL_KEY_OVERRIDE_ENTRIES 4
