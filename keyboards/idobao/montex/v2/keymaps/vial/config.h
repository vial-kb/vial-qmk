// Copyright 2023 Oleg Titov <oleg.titov@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0x1A, 0xC2, 0xE7, 0x4C, 0xE4, 0x37, 0xF3, 0x6A}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 4 }

// Enable all available RGB Matrix effects
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

// Firmware size optimization
// disable Lock Key support
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
