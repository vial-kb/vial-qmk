/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xA7, 0x4B, 0x92, 0x3F, 0x6D, 0x8C, 0xE1, 0x02}

/* Vial unlock combo - ESC + Enter */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

/* Increase tap dance, combo, and macro counts for RP2040's large memory */
#define VIAL_TAP_DANCE_ENTRIES 32
#define VIAL_COMBO_ENTRIES 32
#define DYNAMIC_KEYMAP_MACRO_COUNT 16