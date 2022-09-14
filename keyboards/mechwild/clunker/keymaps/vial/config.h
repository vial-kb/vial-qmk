// Copyright 2022 Vial Contributors (@vial-kb)
// SPDX-License-Identifier: GPL-2.0-or-later

#define VIAL_KEYBOARD_UID {0xFF, 0x41, 0x73, 0x4D, 0x02, 0x8F, 0x64, 0x28}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 5 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 3 }

#if defined(__AVR_ATmega32U4__)
    #define NO_ACTION_ONESHOT
#endif
