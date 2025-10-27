/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xE3, 0xFD, 0x75, 0x4F, 0xFA, 0xB8, 0xF2, 0x00}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

/* Reduce firmare size */
#define DYNAMIC_KEYMAP_LAYER_COUNT 2
#define VIAL_TAP_DANCE_ENTRIES 4

#ifndef NO_DEBUG
#define NO_DEBUG
#endif

#ifndef NO_PRINT
#define NO_PRINT
#endif

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
