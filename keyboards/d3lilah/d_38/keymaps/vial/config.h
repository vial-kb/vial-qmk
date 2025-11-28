#define TAPPING_TERM 235
#define PERMISSIVE_HOLD

// RGB Matrix stability improvements
#define RGB_MATRIX_LED_PROCESS_LIMIT 4
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define USB_SUSPEND_WAKEUP_DELAY 200
#define DYNAMIC_KEYMAP_MACRO_COUNT 56
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE 8192
#define VIAL_TAP_DANCE_ENTRIES 32
#define VIAL_COMBO_ENTRIES 32
#define DYNAMIC_KEYMAP_LAYER_COUNT 8
// VIAL Security
#define VIAL_KEYBOARD_UID {0x8B, 0x7C, 0x4D, 0x3E, 0x2F, 0x1A, 0x9B, 0x5C}

/*
 * Security unlock disabled for troubleshooting
 * TODO: Re-enable when board is physically complete
 *
 * Currently set to ESC + ESC (same key) to effectively disable security
 * For production, change to: Top-left and bottom-right keys
 * #define VIAL_UNLOCK_COMBO_ROWS { 0, 3 }
 * #define VIAL_UNLOCK_COMBO_COLS { 0, 9 }
 */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0 }
#define VIAL_INSECURE
