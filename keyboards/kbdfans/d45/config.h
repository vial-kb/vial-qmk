#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID 0x4B42
#define PRODUCT_ID 0x0010
#define DEVICE_VER 0x0001
#define MANUFACTURER KBDFANS
#define PRODUCT D45

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 16
#define MATRIX_ROW_PINS { B5, B4, D6, D4 }
#define MATRIX_COL_PINS { D7, F7, F6, F5, F4, F1, F0, E6, B0, B1, B2, B3, B7, D2, D3, D5}
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
#define VIAL_KEYBOARD_UID {0xC0, 0x17, 0xF0, 0x89, 0xD6, 0x68, 0xC4, 0xEA}

#define RGB_DI_PIN B6
#define RGBLED_NUM 72

#define DRIVER_LED_TOTAL RGBLED_NUM

#define RGBLIGHT_ANIMATIONS

#ifdef RGB_MATRIX_ENABLE
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_DISABLE_WHEN_USB_SUSPENDED true // turn off effects when suspended
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
#define RGB_MATRIX_HUE_STEP 8
#define RGB_MATRIX_SAT_STEP 8
#define RGB_MATRIX_VAL_STEP 8
#define RGB_MATRIX_SPD_STEP 10
#endif