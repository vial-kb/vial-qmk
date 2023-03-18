/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

// wiring of each half
#define SPLIT_HAND_PIN F7

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGBLIGHT_LED_MAP { 1, 2, 3, 12, 13, 14, 15, 0, 7, 6, 5, 4, 11, 10, 9, 8 }
#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_MODE_RAINBOW_SWIRL + 2)

// Set right column, left macro, 1.75u shift, split spaces, and 5x1u on by default
#define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x00DE
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

#define VIAL_KEYBOARD_UID {0xFF, 0xCB, 0x4D, 0xFD, 0x58, 0x33, 0xC8, 0xA6}

// Esc + Enter. See: http://www.keyboard-layout-editor.com/#/gists/07a30619c76ab7d7be4932f94b3a7c06
#define VIAL_UNLOCK_COMBO_ROWS { 5, 8 }
#define VIAL_UNLOCK_COMBO_COLS { 2, 7 }

// Reducing firmware size: https://get.vial.today/docs/firmware-size.html
#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 0
