/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0x71, 0xE4, 0x34, 0x62, 0x9C, 0x8E, 0x31, 0x68}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 7 }
#define VIAL_UNLOCK_COMBO_COLS { 2, 7 }

// Reduce the firmware size!
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
