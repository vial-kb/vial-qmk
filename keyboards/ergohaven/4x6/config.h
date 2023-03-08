/*
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

#include "config_common.h"

#define VENDOR_ID 0xFEED
#define PRODUCT_ID 0x9336
#define DEVICE_VER 0x0001
#define MANUFACTURER Ergohaven
#define PRODUCT    Dactyl Manuform 4x6

#define VIAL_KEYBOARD_UID {0xD4, 0xAB, 0x98, 0xD1, 0xF7, 0xE3, 0xBE, 0x1C}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

/* Key matrix size (rows are doubled-up) */
#define MATRIX_ROWS 10
#define MATRIX_COLS 6

/* Wiring of each half */
#define MATRIX_COL_PINS { GP10, GP11, GP12, GP13, GP14, GP15 }
#define MATRIX_ROW_PINS { GP20, GP19, GP18, GP17, GP16 }

#define DIODE_DIRECTION COL2ROW

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U // Specify a optional status led which blinks when entering the bootloader

/* Serial settings */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define WS2812_PIO_USE_PIO1

/* RGB Defines */
#define RGB_DI_PIN GP22
#define DRIVER_LED_TOTAL 8
#define RGBLED_NUM 8
#define RGBLIGHT_SPLIT
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_MOOD
#define RGBLIGHT_SLEEP
#define RGBLIGHT_LAYERS
#define RGBLIGHT_LIMIT_VAL 150

/* RGB Effects */
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE

#define SPLIT_USB_TIMEOUT 5000 
#define SPLIT_USB_TIMEOUT_POLL 25
