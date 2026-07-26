#pragma once

#undef  PRODUCT_ID
#define PRODUCT_ID    0x2409
#undef  PRODUCT
#define PRODUCT    Uni88 (FW_VER)
#define DYNAMIC_KEYMAP_LAYER_COUNT    6
#define FLASH_KEYMAP_COUNT    2
#define VIAL_KEYBOARD_UID    {0x2E, 0xE6, 0x0E, 0x23, 0x34, 0xEF, 0x99, 0x37}

#undef  RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL    50
#undef  RGBLED_NUM
#define RGBLED_NUM    1
#define INDICATOR_NUM    2
#define INDICATOR_0_FUNCT    (1<<USB_LED_CAPS_LOCK)
#define INDICATOR_0_COLOR    (LED_TYPE){ .r = 64, .g = 0, .b = 64 }
#define INDICATOR_0_VAL      64
#define INDICATOR_1_FUNCT    (1<<USB_LED_SCROLL_LOCK)
#define INDICATOR_1_COLOR    (LED_TYPE){ .r = 0, .g = 64, .b = 64 }
#define RGB_ORDER_FIX