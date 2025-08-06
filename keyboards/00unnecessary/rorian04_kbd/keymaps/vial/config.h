//copyright info

#pragma once

// Define options
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define VIAL_KEYBOARD_UID {0x7C, 0x3D, 0x40, 0xD2, 0xE4, 0x39, 0xF9, 0xBB}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 5 }
#define WS2812_PIO_USE_PIO1 // Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral
#define RGBLIGHT_LAYERS
#define WS2812_DI_PIN GP16
#define RGBLIGHT_LED_COUNT 1
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
#define RGBLIGHT_SLEEP
#define USB_SUSPEND_WAKEUP_DELAY 500
#define FORCE_NKRO
#define HOLD_ON_OTHER_KEY_PRESS
