/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

/* key matrix pins */
#define MATRIX_ROW_PINS { D3, D2, B3, B2, B1, B0 }
#define MATRIX_COL_PINS { D5, D4, D6, D7, B4, B5, B6, C6, C7, F7, F6, F5, F4, F1, F0 }

/* RGB Matrix Configuration */
#define DRIVER_1_LED_TOTAL 59
#define DRIVER_2_LED_TOTAL 23
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)

//enable RGB Matrix Effects for Vial
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES

//Vial Keyboard UID
#define VIAL_KEYBOARD_UID {0x49, 0x5F, 0x9C, 0xB8, 0x0F, 0x67, 0x4D, 0xE6}
