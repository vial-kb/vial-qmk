#pragma once

// RIGHT side firmware
// Flash this to the right half only

// Vial UID - must match left side
#define VIAL_KEYBOARD_UID {0x89, 0x4D, 0x6E, 0x12, 0x33, 0x56, 0x78, 0x90}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

// RIGHT Serial (GP17 TX, GP16 RX) - B2B_USART
#undef SERIAL_USART_TX_PIN
#undef SERIAL_USART_RX_PIN
#define SERIAL_USART_TX_PIN GP17
#define SERIAL_USART_RX_PIN GP16

// RIGHT I2C (GP18 SDA, GP19 SCL) - I2C0
#undef I2C_DRIVER
#define I2C_DRIVER I2CD0
#undef I2C1_SDA_PIN
#undef I2C1_SCL_PIN
#define I2C1_SDA_PIN GP18
#define I2C1_SCL_PIN GP19

// RIGHT Matrix Pins
// Rows: GP0, GP11, GP25, GP26
// Cols: GP1, GP2, GP3, GP4, GP5, GP10, GP27
#undef MATRIX_ROW_PINS
#undef MATRIX_COL_PINS
#define MATRIX_ROW_PINS { GP0, GP11, GP25, GP26 }
#define MATRIX_COL_PINS { GP1, GP2, GP3, GP4, GP5, GP10, GP27, NO_PIN }

// RIGHT Encoder (GP28 A, GP29 B)
#define ENCODERS_PAD_A { GP28 }
#define ENCODERS_PAD_B { GP29 }
#define ENCODER_RESOLUTION 4

// Pointing device disabled in rules.mk for right side

// Enable split pointing to receive joystick data from left side
#define SPLIT_POINTING_ENABLE
