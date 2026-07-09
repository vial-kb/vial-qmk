// Copyright 2024 Tustation
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// USB VID/PID, manufacturer, product are in keyboard.json
// Vial UID and unlock combo are consumed by Vial CI tools
#define VIAL_KEYBOARD_UID {0x07, 0x1A, 0xBE, 0xEF, 0x64, 0x00, 0x00, 0x01}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 4 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0


#define BACKLIGHT_GPT_DRIVER GPTD4

// Caps Lock is active-low (B5); backlight on PB4 uses on_state=1 from keyboard.json
#define LED_PIN_ON_STATE 0
