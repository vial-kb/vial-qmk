// Copyright 2022 Michael McCoyd (@mmccoyd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Some boards have issues detecting handedness using the vbus voltage,
// such as Elite-C v3, but not v3.1 on, and apparently some ProMicro boards.
// For those boards, use usb detection instead.
// #define SPLIT_USB_DETECT
#define DYNAMIC_KEYMAP_LAYER_COUNT 6
#define VIAL_KEYBOARD_UID {0x3E, 0x98, 0xD7, 0x2B, 0x56, 0xC3, 0xFF, 0xB9}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 2, 3 }
