#pragma once

// Common Configuration for Bipedal Ambi
// Specific configuration (Pins, Matrix, I2C) is in keymaps/vial_left and keymaps/vial_right

// #define SERIAL_USART_FULL_DUPLEX  // DIAG-02: disabled for half-duplex test
#define SPLIT_USB_DETECT
#define SERIAL_PIO_USE_PIO1  // Use PIO1 for serial (PIO0 used by WS2812)
#define SPLIT_LAYER_STATE_ENABLE
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

// OLED Common
#define OLED_DISPLAY_128X32
#define OLED_TIMEOUT 0
#define SCREENSAVER_TIMEOUT 60000
#define OLED_FONT_H "keyboards/hidpress/bipedalambi/glcdfont.c"

// RGB
#define WS2812_DI_PIN GP24

// Joystick Common
#define ANALOG_JOYSTICK_AUTO_AXIS
#define ANALOG_JOYSTICK_SPEED_REGULATOR 20
#define ANALOG_JOYSTICK_CUTOFF

// Matrix Configuration
#define MATRIX_ROWS 8  // 4 rows per hand * 2 hands
#define MATRIX_COLS 8  // Increased to 8 to support virtual Joystick columns (Col 7)
