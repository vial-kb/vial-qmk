/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xBF, 0x59, 0x7D, 0x4C, 0xDF, 0x1C, 0xBC, 0x81}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 7 }
#define VIAL_UNLOCK_COMBO_COLS { 2, 7 }

// Reduce the firmware size!
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define LAYER_STATE_8BIT
