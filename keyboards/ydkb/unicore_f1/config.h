#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define FW_VER_DATE     DPCH
#define CONTACT(x,y)    x##y
#define CONTACT2(x,y)   CONTACT(x,y)
#define FW_VER          CONTACT2(VIAL_, FW_VER_DATE)
#define VENDOR_ID       0x9D5B
#define PRODUCT_ID      0x23FA
#define DEVICE_VER      0x0001
#define MANUFACTURER    KBDFans
#if CONSOLE_ENABLE
#define PRODUCT         UniCore_F1 Uni Debug (FW_VER)
#else
#define PRODUCT         UniCore_F1 Uni(FW_VER)
#endif

#define USB_MAX_POWER_CONSUMPTION 350
#define WAIT_FOR_USB

/* debounce */
#define DEBOUNCE_DN 3 //default 5
#define DEBOUNCE_UP 5 //default 5

/* key matrix size */
#define MATRIX_ROWS 14 //max supported
#define MATRIX_COLS 8
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2 //default 1,  not enough for ec_ap and indicator color
//#define FORCE_NKRO //When FORCE_NKRO, Enable NKRO in QMK Settings will not be saved
//#define SOFTWARE_ESC_BOOTLOADER

#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_DEFAULT_MODE 7 // defaut: RAINBOW_MOOD

#define RGBLIGHT_LIMIT_VAL must_redefine
#define RGBLIGHT_SLEEP
#define RGB_DI_PIN B15
#define RGBLED_NUM must_redefine
//#define RGBLIGHT_DEFAULT_ON FALSE

//#define SUSPEND_ACTION

/* key combination for command */
#define IS_COMMAND() ( \
    (get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) || \
    (get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_LCTRL) | MOD_BIT(KC_RSHIFT))) \
)

