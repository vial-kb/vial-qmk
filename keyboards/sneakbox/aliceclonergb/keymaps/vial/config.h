/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xCD, 0x6D, 0xFB, 0xBE, 0x43, 0x43, 0xD2, 0x7E}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 9 }
#define VIAL_UNLOCK_COMBO_COLS {  0, 3 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* Space-saving measures */
#define LAYER_STATE_8BIT
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
