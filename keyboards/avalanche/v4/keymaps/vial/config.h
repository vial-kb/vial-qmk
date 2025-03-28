// Copyright 2022 Will Winder (@winder)
// SPDX-License-Identifier: GPL-2.0-or-later

#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2500

#pragma once

#    define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RAINBOW_SWIRL+2

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_TIMEOUT 30000
#endif

#define VIAL_KEYBOARD_UID {0x58, 0x8C, 0xA2, 0x28, 0x65, 0xFA, 0xE1, 0x58}
#define VIAL_UNLOCK_COMBO_ROWS { 2, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 4 }
