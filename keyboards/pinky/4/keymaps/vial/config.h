/* Copyright 2018 'Masayuki Sunahara'
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

//#define USE_MATRIX_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

// Vial Support
#define VIAL_KEYBOARD_UID {0xE6, 0xB5, 0x80, 0x48, 0xB0, 0x2C, 0xBC, 0x11}

// The four corners
#define VIAL_UNLOCK_COMBO_ROWS { 0, 5, 3, 8 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0, 0, 0 }

// Tap dance slots
#define VIAL_TAP_DANCE_ENTRIES 10

// Dynamic macro slots
#define DYNAMIC_KEYMAP_MACRO_COUNT 14

// Dynamic key override slots
#define VIAL_KEY_OVERRIDE_ENTRIES 8

#define QUICK_TAP_TERM 0
#define TAPPING_TERM 200
#define RETRO_TAPPPING
