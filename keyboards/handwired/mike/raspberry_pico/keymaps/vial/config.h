#pragma once
// #include "config_common.h"

// -------------------------
// Keyboard Matrix
// -------------------------
#define MATRIX_ROWS 6
#define MATRIX_COLS 18

// Define the GPIO pins for rows and columns
/*
Connector Rows Left             Connector Rows Right
-------------------             --------------------
R0: Green:   GP5                 R0: Black:  GP5
R1: Orange:  GP4                 R1: Red:    GP4
R2: Yellow:  GP3                 R2: White:  GP3
R3: White:   GP2                 R3: Yellow: GP2
R4: Red:     GP0                 R4: Orange: GP0
R5: Black:   GP1                 R5: Green:  GP1

Connector Columns Left          Connector Columns Right
----------------------          -----------------------
C0: Black:  GP8                 C17: Gray:   GP27
C1: Red:    GP9                 C16: Purple: GP22
C2: White:  GP7                 C15: Blue:   GP26
C3: Yellow: GP10                C14: Green:  GP21
C4: Orange: GP11                C13: Orange: GP20
C5: Green:  GP12                C12: Yellow: GP19
C6: Blue:   GP13                C11: White:  GP18
C7: Purple: GP15                C10: Red:    GP16
C8: Gray:   GP14                C9:  Black:  GP17

Free: GP6, GP28
*/



#define MATRIX_ROW_PINS { GP5, GP4, GP3, GP2, GP0, GP1 }
#define MATRIX_COL_PINS { GP8, GP9, GP7, GP10, GP11, GP12, GP13, GP15, GP14,        GP17, GP16, GP18, GP19, GP20, GP21, GP26, GP22, GP27 }

// Diode direction
#define DIODE_DIRECTION COL2ROW

// -------------------------
// RGB LED (WS2812B / WS2813)
// -------------------------
// #define RGB_DI_PIN GP26   // Connect data through 330–470Ω resistor
#define WS2812_DI_PIN GP6 // Alias for WS2812B compatibility
// #define RGBLED_NUM 1      // Single LED for layer indication
// #define WS2812_LED_COUNT 1
#define RGBLIGHT_LED_COUNT 1

// #define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8

// -------------------------
// Features
// -------------------------
// #define NKRO_ENABLE         // Enable full n-key rollover
#define NO_USB_STARTUP_CHECK // Skip USB startup check for Pico

// -------------------------
// Tap-hold timing
// -------------------------
#define TAPPING_TERM 200 // ms for dual-function keys (tap = toggle, hold = momentary)

// -------------------------
// Vial-specific configuration
// -------------------------
#define VIAL_KEYBOARD_UID {0xE6, 0xCB, 0xCD, 0x5A, 0x4D, 0x1F, 0xCD, 0xFE}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }
