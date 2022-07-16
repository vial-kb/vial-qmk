/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xED, 0x26, 0xCA, 0x6E, 0xC6, 0x33, 0x93, 0x24}
#define VIAL_UNLOCK_COMBO_ROWS {1, 4}
#define VIAL_UNLOCK_COMBO_COLS {0, 6}

/* Moves Bootmagic Lite key from "Esc" to "b" to avoid conflict with qmk-dfu
 * See https://docs.qmk.fm/#/flashing?id=qmk-dfu */
#define BOOTMAGIC_LITE_ROW 3
#define BOOTMAGIC_LITE_COLUMN 6
