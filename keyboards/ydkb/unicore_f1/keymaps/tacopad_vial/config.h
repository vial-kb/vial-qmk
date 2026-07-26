#pragma once

#undef  PRODUCT_ID
#define PRODUCT_ID    0x2302
#undef  PRODUCT
#define PRODUCT     TacoPad (FW_VER)
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define FLASH_KEYMAP_COUNT    2
#define VIAL_KEYBOARD_UID    {0x2E, 0xE6, 0x0E, 0x23, 0x34, 0xEF, 0x99, 0x37}

#undef  RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_LIMIT_VAL    192
#undef  RGBLED_NUM
#define RGBLED_NUM    7
#define PHY_INDICATOR_NUM    1
#define INDICATOR_FUNCT    {(1<<USB_LED_NUM_LOCK)}
//#define INDICATOR_VAL      128
