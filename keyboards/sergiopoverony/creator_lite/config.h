#pragma once
#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x8b1e // "AR"
#define PRODUCT_ID      0x0D00 // "OF"
#define DEVICE_VER      0x0001
#define MANUFACTURER    SergioPoverony
#define PRODUCT         Creator Lite 

#define VIAL_KEYBOARD_UID {0x1D, 0x91, 0xC3, 0x9B, 0x4D, 0xEF, 0x8B, 0x58}

/* key matrix size */
#define MATRIX_ROWS 1
#define MATRIX_COLS 7
#define DIRECT_PINS {   \
    { D7, C6, B3, B2, E6, D2, D3} \
}

#define LED_PIN_ON_STATE 0
#define GREEN_LED B6
#define BLUE_LED B5
#define RED_LED D0 

#define UNUSED_PINS

/* encoder */
#define ENCODERS_PAD_A { D3 }
#define ENCODERS_PAD_B { D2 }
#define ENCODER_RESOLUTION 1

#define USB_POLLING_INTERVAL_MS 1
#define QMK_KEYS_PER_SCAN 12

#define UNUSED_PINS
