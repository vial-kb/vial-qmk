#pragma once

#define VIAL_KEYBOARD_UID {0x63, 0x72, 0x6B, 0x62, 0x64, 0x56, 0x31, 0x01}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 7
#define DYNAMIC_KEYMAP_MACRO_COUNT 0

#define TAPPING_TERM 200
#define PERMISSIVE_HOLD
#define QUICK_TAP_TERM 0
#define TAPPING_FORCE_HOLD

/* Split Keyboard Settings */
#define USE_SERIAL
#define SOFT_SERIAL_PIN D2
#define EE_HANDS
#define SPLIT_USB_DETECT

/* Space Optimization - Set to minimum valid values */
#define VIAL_TAP_DANCE_ENTRIES 1
#define VIAL_COMBO_ENTRIES 1
#define VIAL_KEY_OVERRIDE_ENTRIES 1
