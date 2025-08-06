#pragma once

#include "config_common.h"

#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0604
#define DEVICE_VER      0x0001
#define MANUFACTURER	"ch604"
#define PRODUCT		"Crisco"
#define VERSION		"0.1"

#define DEBOUNCE 5
#define FORCE_NKRO

#define MATRIX_ROWS 2
#define MATRIX_COLS 10
#define MATRIX_ROW_PINS { F7, B1 }
#define MATRIX_COL_PINS { F6, F5, F4, B3, B2, B6, E6, D7, D4, C6 }
#define UNUSED_PINS { D2, B4, B5 }

#define DIODE_DIRECTION COL2ROW

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 11
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255
  #define RGBLIGHT_SLEEP
  #define RGBLIGHT_ANIMATIONS
#endif

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
