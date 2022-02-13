#pragma once

#include "config_common.h"

#define VENDOR_ID       0x8AA8
#define PRODUCT_ID      0x0001
#define DEVICE_VER      0x0001
#define MANUFACTURER    HAAH
#define PRODUCT         ABQ
#define DESCRIPTION     HAAH ABQ

#define MATRIX_ROW_PINS { B4, B3, B5, D2 }
#define MATRIX_COL_PINS { B0, D6, D5, D4, B1, B2, C4, B6, C5, C6, B7, C7 }

#define MATRIX_ROWS 4
#define MATRIX_COLS 12
#define UNUSED_PINS
#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 5
#define TAPPING_TERM 175
#define LEADER_TIMEOUT 300
