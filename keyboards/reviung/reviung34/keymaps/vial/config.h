#pragma once

#define VIAL_KEYBOARD_UID {0xB8, 0x68, 0xB9, 0x6C, 0x13, 0x2E, 0xA7, 0xDD}
#define VIAL_UNLOCK_COMBO_ROWS {0, 3}
#define VIAL_UNLOCK_COMBO_COLS {0, 5}

// the non split version
#define WS2812_DI_PIN D3
#ifdef WS2812_DI_PIN
  #define RGBLED_NUM 9
  #define RGBLIGHT_HUE_STEP 16
  #define RGBLIGHT_SAT_STEP 16
  #define RGBLIGHT_VAL_STEP 16
  #define RGBLIGHT_LIMIT_VAL 255
  #define RGBLIGHT_SLEEP
// /*== all animations enable ==*/
//  #define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_MODE_BREATHING
//#define RGBLIGHT_MODE_RAINBOW_MOOD
//#define RGBLIGHT_MODE_RAINBOW_SWIRL
#endif
