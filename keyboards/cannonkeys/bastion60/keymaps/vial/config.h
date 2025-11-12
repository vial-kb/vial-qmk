/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xCF, 0x22, 0x6C, 0x3D, 0x8A, 0x91, 0xB6, 0x01}

/* Vial unlock combo - ESC + Enter */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

/* Increase tap dance, combo, and macro counts for RP2040's large memory */
#define VIAL_TAP_DANCE_ENTRIES 32
#define VIAL_COMBO_ENTRIES 32
#define DYNAMIC_KEYMAP_MACRO_COUNT 64