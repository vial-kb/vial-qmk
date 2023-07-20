/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

/* Matrix config */

#define MATRIX_ROWS 5
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { E6, B4, B5, B2, NO_PIN }
#define MATRIX_COL_PINS { B3, B1, F7, F6, F5, F4, C6, D4, D0, D1, D2, D3 }

#define DIODE_DIRECTION ROW2COL

// Max 32
#define JOYSTICK_BUTTON_COUNT 0
// Max 6: X, Y, Z, Rx, Ry, Rz
#define JOYSTICK_AXIS_COUNT 2
