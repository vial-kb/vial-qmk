/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xDA, 0x11, 0xEA, 0x7A, 0x00, 0x00, 0x00, 0x00}

/* Unlock with 0 and . keys */
#define VIAL_UNLOCK_COMBO_ROWS { 4, 4 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 2 }

/* Memory options - 8 layers and 64 macros */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define DYNAMIC_KEYMAP_MACRO_COUNT 64
#define VIAL_TAP_DANCE_ENTRIES 16
#define VIAL_COMBO_ENTRIES 16
#define VIAL_KEY_OVERRIDE_ENTRIES 8