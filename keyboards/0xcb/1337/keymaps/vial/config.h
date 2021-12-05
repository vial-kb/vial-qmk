/*
Copyright 2021 0xCB - Conor Burns

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

#define VIAL_KEYBOARD_UID {0xCB, 0x13, 0x37, 0x12, 0xD7, 0x51, 0x50, 0xFF}
#define VIAL_UNLOCK_COMBO_ROWS { 2, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 2 }
#define VIAL_ENCODER_DEFAULT { KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, RGB_VAD, RGB_VAI, BL_DEC, BL_INC }
// reduce firmware size
#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RAINBOW_MOOD