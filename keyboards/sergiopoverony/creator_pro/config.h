#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x8b1e // "AR"
#define PRODUCT_ID      0x0C00 // "OF"
#define DEVICE_VER      0x0001
#define MANUFACTURER    SergioPoverony
#define PRODUCT         Creator Pro

#define VIAL_KEYBOARD_UID {0x2A, 0xA3, 0x6B, 0x57, 0x59, 0xB3, 0x55, 0xC6}

#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 3 }

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 9
#define DIRECT_PINS {   \
    { D1, D4, C6, D7, E6, F7, B1, B3, B2} \
}

/*led layout indication*/ 
#define LED_PIN_ON_STATE 0
#define GREEN_LED B5
#define BLUE_LED D0
#define RED_LED B6

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 12

/* encoder */
#define ENCODERS_PAD_A { D2 }
#define ENCODERS_PAD_B { D3 }
#define ENCODER_RESOLUTION 1

#define UNUSED_PINS
