#pragma once

#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64

// Split
#define SERIAL_USART_FULL_DUPLEX
#define SELECT_SOFT_SERIAL_SPEED 2
#define EE_HANDS
#define SPLIT_USB_DETECT
#define SPLIT_USB_TIMEOUT 2000

// Write handedness to EEPROM at compile time (matches SIDE=right build flag)
#ifdef RIGHT_SIDE
#    define INIT_EE_HANDS_RIGHT
#else
#    define INIT_EE_HANDS_LEFT
#endif
#define SERIAL_DEBUG
#define SPLIT_LAYER_STATE_ENABLE

// Double-tap reset to bootloader
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

// Bootmagic — hold key while plugging in to enter bootloader
// Left: (0,0) = top-left 1.25u key, Right: (4,0) = top-right 1.25u key
#define BOOTMAGIC_ROW 0
#define BOOTMAGIC_COLUMN 0
#define BOOTMAGIC_ROW_RIGHT 4
#define BOOTMAGIC_COLUMN_RIGHT 0

// Serial pins differ per side
#ifdef RIGHT_SIDE
#    define SERIAL_USART_TX_PIN GP16
#    define SERIAL_USART_RX_PIN GP17
#else
#    define SERIAL_USART_TX_PIN GP0
#    define SERIAL_USART_RX_PIN GP1
#endif

// WS2812
#define WS2812_DI_PIN GP24
// Left side uses GP24 for matrix col 0, so no RGB on left
#ifndef RIGHT_SIDE
#    undef WS2812_DI_PIN
#endif

// OLED
#define OLED_DISPLAY_128X32
#define OLED_TIMEOUT 0
#define OLED_FONT_H "keyboards/hidpress/bipedalambi/glcdfont.c"

// I2C — left uses I2C0 (GP12/GP13), right uses I2C1 (GP18/GP19)
#ifdef RIGHT_SIDE
#    define I2C_DRIVER I2CD1
#    define I2C1_SDA_PIN GP18
#    define I2C1_SCL_PIN GP19
#else
#    define I2C_DRIVER I2CD0
#    define I2C1_SDA_PIN GP12
#    define I2C1_SCL_PIN GP13
#endif

// Joystick / Pointing device
#define ANALOG_JOYSTICK_AUTO_AXIS
#define ANALOG_JOYSTICK_SPEED_REGULATOR 20
#define ANALOG_JOYSTICK_CUTOFF
#define ANALOG_JOYSTICK_X_AXIS_PIN GP29
#define ANALOG_JOYSTICK_Y_AXIS_PIN GP28
#define ANALOG_JOYSTICK_ENABLE
#define POINTING_DEVICE_LEFT
#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_INVERT_X

// Encoder (right side only)
#define ENCODER_RESOLUTION 4
#define ENCODERS_PAD_A_RIGHT { GP28 }
#define ENCODERS_PAD_B_RIGHT { GP29 }

// Matrix
#define MATRIX_ROWS 8
#define MATRIX_COLS 8
#define MATRIX_ROW_PINS_RIGHT { GP0, GP11, GP25, GP26 }
#define MATRIX_COL_PINS_RIGHT { GP1, GP2, GP3, GP4, GP5, GP10, GP27, NO_PIN }
