/*
Copyright 2024 @yuting wang

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
#define MANUFACTURER "Yuting Wang"
#define WS2812_DI_PIN D3
#define SOFT_SERIAL_PIN D2

#define VIAL_KEYBOARD_UID {0xE8, 0x8C, 0xEF, 0x50, 0x0A, 0xD0, 0x3C, 0xAF}
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

#define DYNAMIC_KEYMAP_LAYER_COUNT 5
#define TAPPING_TERM 180
    
/* Select hand configuration */
#define MASTER_LEFT
#define LED_ANIMATIONS

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_LIMIT_VAL 120
#    define RGBLIGHT_HUE_STEP  10
#    define RGBLIGHT_SAT_STEP  17
#    define RGBLIGHT_VAL_STEP  17
#endif

// place overrides here
// Selection of RGBLIGHT MODE to use.
#if defined(LED_ANIMATIONS)
   #define RGBLIGHT_EFFECT_BREATHING
   #define RGBLIGHT_EFFECT_RAINBOW_MOOD
   #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
   #define RGBLIGHT_EFFECT_SNAKE
   #define RGBLIGHT_EFFECT_KNIGHT
   #define RGBLIGHT_EFFECT_CHRISTMAS
   #define RGBLIGHT_EFFECT_STATIC_GRADIENT
   //#define RGBLIGHT_EFFECT_RGB_TEST
   //#define RGBLIGHT_EFFECT_ALTERNATING
#endif

#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"
#define SPLIT_POINTING_ENABLE
#ifdef SPLIT_POINTING_ENABLE
#       define POINTING_DEVICE_RIGHT
#       define ANALOG_JOYSTICK_X_AXIS_PIN F4
#       define ANALOG_JOYSTICK_Y_AXIS_PIN F5
#       define ANALOG_JOYSTICK_CLICK_PIN B6
#       define ANALOG_JOYSTICK_SPEED_REGULATOR 6
#       define ANALOG_JOYSTICK_SPEED_MAX 20
#endif

#ifdef ENCODER_ENABLE
#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTIONS_LEFT { 2 }
#define ENCODERS_PAD_A_RIGHT { }
#define ENCODERS_PAD_B_RIGHT { }
#define ENCODER_RESOLUTIONS_RIGHT { }
#endif

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
// only required if not setting mouse layer elsewhere
#define AUTO_MOUSE_DEFAULT_LAYER 4
#define AUTO_MOUSE_TIME 650