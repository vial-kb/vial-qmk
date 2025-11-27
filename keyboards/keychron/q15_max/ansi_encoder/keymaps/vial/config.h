/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

/* Vial Keyboard UID - Unique ID for Q15 Max */
#define VIAL_KEYBOARD_UID {0xB5, 0xBE, 0xB0, 0x9E, 0xFF, 0xD8, 0x80, 0x9E}

/* Vial unlock combo - ESC + Enter (top-left + main enter) */
#define VIAL_UNLOCK_COMBO_ROWS { 1, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 12 }

/* Enable Vial features */
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 8