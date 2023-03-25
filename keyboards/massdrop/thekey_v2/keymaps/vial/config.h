/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x5E, 0x62, 0xD5, 0x7B, 0x88, 0xD7, 0x45, 0xA5}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 2 }

/* Reduce keymap mem usage by capping to 6 */
#define LAYER_STATE_8BIT
#define DYNAMIC_KEYMAP_LAYER_COUNT 6