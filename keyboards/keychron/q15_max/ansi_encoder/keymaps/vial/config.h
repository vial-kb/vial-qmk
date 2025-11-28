/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

/* Vial Keyboard UID - Unique ID for Q15 Max */
#define VIAL_KEYBOARD_UID {0xB5, 0xBE, 0xB0, 0x9E, 0xFF, 0xD8, 0x80, 0x9E}

/* Vial unlock combo - ESC + Enter (top-left + main enter) */
#define VIAL_UNLOCK_COMBO_ROWS { 1, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 12 }

/* Five layers - Mac/Win base + 3 function layers */
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* Vial features - Macros, Tap Dance, Combos */
#define VIAL_MACRO_COUNT 16
#define VIAL_TAP_DANCE_ENTRIES 8
#define VIAL_COMBO_ENTRIES 8

/* Include expanded RGB effects from d3lilah's configuration */
#ifdef RGB_MATRIX_ENABLE
#include "rgb_effects_config.h"
#endif