/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

/* VIAL UID for Pancake Rev1 */
#define VIAL_KEYBOARD_UID {0x35, 0x5B, 0xDC, 0xA2, 0x05, 0x8C, 0x2C, 0x5C}

/* VIAL secure unlock keystroke - top left and top right */
#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 11}

// to save space
// from https://github.com/qmk/qmk_firmware/issues/3224k
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION