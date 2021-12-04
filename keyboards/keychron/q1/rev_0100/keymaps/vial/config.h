/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 59
#define DRIVER_2_LED_TOTAL 23
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

//enable RGB Matrix Effects for Vial
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

//Vial Keyboard UID
#define VIAL_KEYBOARD_UID {0x49, 0x5F, 0x9C, 0xB8, 0x0F, 0x67, 0x4D, 0xE6}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }
