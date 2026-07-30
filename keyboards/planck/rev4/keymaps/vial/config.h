// Copyright 2024 OLKB
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Generated with: python3 util/vial_generate_keyboard_uid.py
#define VIAL_KEYBOARD_UID {0x4F, 0x2B, 0x0A, 0xD8, 0x17, 0xC3, 0x7F, 0x99}

// Unlock combo: hold Esc (row 0, col 0) + Space (row 3, col 5) for 5 seconds.
// These matrix positions work for both MIT (1x2u) and GRID (2x1u) bottom rows.
#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 5 }

// 4 layers fits comfortably in the ATmega32u4's 1KB EEPROM and is the standard
// for Planck-class boards. Each additional layer costs MATRIX_ROWS*MATRIX_COLS*2
// bytes of EEPROM.
#define DYNAMIC_KEYMAP_LAYER_COUNT 4
