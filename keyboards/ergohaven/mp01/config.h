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

#define VIAL_KEYBOARD_UID {0x03, 0xF0, 0x83, 0xA9, 0x6A, 0xD3, 0x40, 0x02}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }
#define DYNAMIC_KEYMAP_LAYER_COUNT 17
#define DYNAMIC_KEYMAP_MACRO_COUNT 32

#define BOOTMAGIC_LITE_ROW          0
#define BOOTMAGIC_LITE_COLUMN       0

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U // Specify a optional status led which blinks when entering the bootloader

// Caps Word
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD

//SPI Config
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11

// Display common config
#define DISPLAY_DC_PIN GP16
#define DISPLAY_CS_PIN GP18
#define DISPLAY_RST_PIN GP17

#define QUANTUM_PAINTER_PIXDATA_BUFFER_SIZE 1024
