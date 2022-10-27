/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define MATRIX_ROWS 4
#define MATRIX_COLS 12

#define MATRIX_ROW_PINS { E6, B4, B5, B2 }
#define MATRIX_COL_PINS { B3, B1, F7, F6, F5, F4, C6, D4, D0, D1, D2, D3 }

#define JOY_X B6
#define JOY_Y D7

#define DIODE_DIRECTION ROW2COL

/* Use 1000hz polling */
#define USB_POLLING_INTERVAL_MS 1
