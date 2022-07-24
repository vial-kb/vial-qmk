#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0001
#define MANUFACTURER    Johan von Konow
#define PRODUCT         3DPCB Keyboard

/* Vial */
#define VIAL_KEYBOARD_UID {0x5E, 0x87, 0x5B, 0x94, 0x49, 0x4C, 0xED, 0x6D}
#define VIAL_UNLOCK_COMBO_ROWS {0,0};
#define VIAL_UNLOCK_COMBO_COLS {0,5};


/* Layers */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 7

/* key matrix pins */
#define MATRIX_ROW_PINS { D7, E6, B1, B2, B6 }
#define MATRIX_COL_PINS { D4, C6, F6, B5, F7, B4, B3 }
#define UNUSED_PINS

// Leds definition
#define LED_NUM_LOCK_PIN B0
#define LED_CAPS_LOCK_PIN D5
#define LED_PIN_ON_STATE 0
#define LAYER_BLINK_TIME 200

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Define MIDI level */
#define MIDI_ADVANCED

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Use 1000hz polling */
#define USB_POLLING_INTERVAL_MS 1
