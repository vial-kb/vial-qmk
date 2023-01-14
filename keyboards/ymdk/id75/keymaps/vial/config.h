/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x32, 0x5D, 0xA4, 0xC4, 0xA5, 0x41, 0xB7, 0xA7}

#define VIAL_UNLOCK_COMBO_ROWS {0, 1}
#define VIAL_UNLOCK_COMBO_COLS {0, 1}

#define DYNAMIC_KEYMAP_LAYER_COUNT 4
#define DYNAMIC_KEYMAP_MACRO_COUNT 32
#define VIAL_COMBO_ENTRIES 32               // number of combos used, each entry take 10 byte in EEPROM
#define VIAL_TAP_DANCE_ENTRIES 48           // number of tap dances used, each entry take 10 byte in EEPROM
#define VIAL_KEY_OVERRIDE_ENTRIES 8         // number of key override used, each entry take 10 byte in EEPROM
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
