/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x7A, 0x81, 0xDD, 0x5D, 0x97, 0x23, 0x12, 0xB2}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }  /* ESC   */
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 } /* Enter */

/* Reduce firmare size (default: 4) */
#define DYNAMIC_KEYMAP_LAYER_COUNT 2

/* Reduce firmare size */
#define VIAL_TAP_DANCE_ENTRIES 4

#ifndef NO_DEBUG
#define NO_DEBUG
#endif

#ifndef NO_PRINT
#define NO_PRINT
#endif

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION

