#pragma once

#define VIAL_KEYBOARD_UID {0xDA, 0x2A, 0xE5, 0x70, 0xD4, 0x00, 0xE5, 0x44}
#define VIAL_UNLOCK_COMBO_ROWS { 1, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 2 }
#define DYNAMIC_KEYMAP_LAYER_COUNT 16
#define DYNAMIC_KEYMAP_MACRO_COUNT 109

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED_MASK 0U // Specify a optional status led which blinks when entering the bootloader

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#define I2C1_SCL_PIN        GP11
#define I2C1_SDA_PIN        GP10
#define OLED_BRIGHTNESS 128
#define I2C_DRIVER I2CD1
#endif
