/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
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

/* Vial-specific settings */
#define VIAL_KEYBOARD_UID {0x36, 0x50, 0x55, 0xB7, 0x3C, 0xA7, 0x9A, 0xE8}
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* Unlock key combo for Vial (top left + top right keys) */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 4 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }

/* Tap dance settings */
#define VIAL_TAP_DANCE_ENTRIES 4
#define TAPPING_TERM 200

/* Combo settings */
#define VIAL_COMBO_ENTRIES 3
#define COMBO_TERM 50

/* One shot key settings */
#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 5000

/* Caps word settings */
#define CAPS_WORD_IDLE_TIMEOUT 5000

/* Enable features */
#define TAP_CODE_DELAY 10
