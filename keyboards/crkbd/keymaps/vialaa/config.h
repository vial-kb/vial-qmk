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

#define VIAL_KEYBOARD_UID {0xC8, 0xDD, 0xCD, 0x5C, 0x5D, 0x58, 0xF6, 0x04}

//#define USE_MATRIX_I2C
#define SPLIT_USB_DETECT
//#define QUICK_TAP_TERM 0
#define TAPPING_TERM 250
#pragma once

#define OLED_TIMEOUT 120000
#define OLED_BRIGHTNESS 120
#define SPLIT_WPM_ENABLE

#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define VIAL_TAP_DANCE_ENTRIES 9
#define DYNAMIC_KEYMAP_MACRO_COUNT 2

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_ACTION_ONESHOT
#define NO_MUSIC_MODE
    #ifndef NO_DEBUG
    #define NO_DEBUG
    #endif // !NO_DEBUG
    #if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
    #define NO_PRINT
    #endif // !NO_PRINT