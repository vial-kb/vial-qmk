/* Copyright 2022 Binepad (@binpad) */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID {0xFB, 0xB1, 0x1A, 0xCD, 0x1F, 0x3A, 0x54, 0x28}

#define VIAL_UNLOCK_COMBO_ROWS { 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0 }


#define TAPPING_TERM 175

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
    #undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 2
