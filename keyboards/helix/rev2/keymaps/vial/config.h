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

#define VIAL_KEYBOARD_UID {0xE4, 0x99, 0x35, 0x98, 0xBC, 0xC5, 0xA0, 0x11}
#define VIAL_UNLOCK_COMBO_ROWS {4, 9}
#define VIAL_UNLOCK_COMBO_COLS {4, 4}

#if defined(LED_ANIMATIONS)
   #define RGBLIGHT_EFFECT_BREATHING

   #undef RGBLIGHT_EFFECT_RGB_TEST
   #undef RGBLIGHT_EFFECT_ALTERNATING
   #undef RGBLIGHT_EFFECT_TWINKLE
#endif

// none of the other builds have enough room for anything else
#if !defined(KEYBOARD_helix_rev2)
   #undef RGBLIGHT_EFFECT_RAINBOW_MOOD
   #undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #undef RGBLIGHT_EFFECT_SNAKE
   #undef RGBLIGHT_EFFECT_KNIGHT
   #undef RGBLIGHT_EFFECT_CHRISTMAS
#endif
