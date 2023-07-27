// Copyright 2023 Vial Contributors (@vial-kb)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#if defined(__AVR_ATmega32U4__)
    #undef RGBLIGHT_EFFECT_ALTERNATING
    #undef RGBLIGHT_EFFECT_CHRISTMAS
    #undef RGBLIGHT_EFFECT_KNIGHT
    #undef RGBLIGHT_EFFECT_RGB_TEST
    #undef RGBLIGHT_EFFECT_SNAKE
    #undef RGBLIGHT_EFFECT_TWINKLE
#endif

/* VIAL Specific definitions */
#define VIAL_KEYBOARD_UID {0x9D, 0x69, 0x43, 0x11, 0x7A, 0x22, 0xE7, 0x0B}
#define VIAL_UNLOCK_COMBO_ROWS { 2, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 5 }
