// Copyright 2023 Binepad
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if defined(KEYBOARD_binepad_bn009_r1)
    #define VIAL_KEYBOARD_UID {0x48, 0x7D, 0x01, 0xAC, 0xB2, 0x33, 0x46, 0x83}
#else  // KEYBOARD_binepad_bn009_r2
    #define VIAL_KEYBOARD_UID {0x48, 0x7D, 0x01, 0xAC, 0xB2, 0x33, 0x46, 0x84}
#endif

#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 2 }
