/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x38, 0x44, 0x95, 0x0E, 0x18, 0xF1, 0x64, 0x24}
#define VIAL_UNLOCK_COMBO_ROWS {0,7}
#define VIAL_UNLOCK_COMBO_COLS {1,5}

// Since the outer columns can be broken off, redefine the bootmagic keys as second column from outside
#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 1

#undef BOOTMAGIC_COLUMN_RIGHT
#undef BOOTMAGIC_ROW_RIGHT
#define BOOTMAGIC_ROW_RIGHT 4
#define BOOTMAGIC_COLUMN_RIGHT 1
