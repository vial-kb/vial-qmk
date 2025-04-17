#pragma once

#define VIAL_KEYBOARD_UID {0xE3, 0x16, 0x88, 0xB2, 0xC8, 0xE5, 0x11, 0x6A}
// To unlock in VIAL, use the top left and bottom left corners when encoders are north
#define VIAL_UNLOCK_COMBO_ROWS { 1, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 1, 3 }

#define RGBLIGHT_SLEEP

//To save some memory, adding some functionality limitations
#define VIAL_TAP_DANCE_ENTRIES 4
#define VIAL_COMBO_ENTRIES 4
#define VIAL_KEY_OVERRIDE_ENTRIES 4
#define DYNAMIC_KEYMAP_LAYER_COUNT 4