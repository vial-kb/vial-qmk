#pragma once

#define VIAL_KEYBOARD_UID {0x4D, 0xC0, 0x40, 0x44, 0x27, 0xBF, 0x7D, 0x3A}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 7 }

// Tapping term settings
#undef TAPPING_TERM
// #define TAPPING_TERM_PER_KEY       // not used
#define TAPPING_TERM 150
#define PERMISSIVE_HOLD
// #define IGNORE_MOD_TAP_INTERRUPT   // deprecated
// #define RETRO_TAPPING

// Combos
//#undef COMBO_COUNT
//#define COMBO_COUNT
#define COMBO_VARIABLE_LEN
#define COMBO_TERM 20
#define TAPPING_FORCE_HOLD
#define COMBO_ALLOW_ACTION_KEYS
#define COMBO_MUST_HOLD_MODS

/* Mousekey stuff */
#ifdef MOUSEKEY_ENABLE
  #define MOUSEKEY_INTERVAL 12
  #define MOUSEKEY_MAX_SPEED 6
  #define MOUSEKEY_TIME_TO_MAX 50
  #define MOUSEKEY_DELAY 20
#endif

#ifdef DYNAMIC_MACRO_ENABLE
#   define DYNAMIC_MACRO_NO_NESTING
#   define DYNAMIC_MACRO_SIZE 128
#endif

//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION


