#include QMK_KEYBOARD_H
#include "keymap_swiss_de.h"
#include "sendstring_swiss_de.h"


// -------------------------
// Custom keycodes for macros
// -------------------------
enum custom_keycodes {
  M11 = SAFE_RANGE,
  M12,
  M21,
  M22,
  M31,
  M32,
  M41,
  M42,
  M51,
  M52,
  M61,
  M62
};

// -------------------------
// Layer definitions
// -------------------------
enum layers {
  _BASE,  // Typing layer
  _FN,   // Media keys layer
  _FN1    // Custom macros layer
};

// -------------------------
// 6x18 Keymaps
// -------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base Layer (_BASE) */
  [_BASE] = LAYOUT_6x18(
    // Row 0: ESC + F1–F12
    M11, M12, KC_ESCAPE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                                KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PRINT_SCREEN, KC_INSERT, KC_DELETE, 
    
    // Row 1: Numbers row (Swiss German)
    M21, M22, CH_SECT, CH_1, CH_2, CH_3, CH_4, CH_5, CH_6,                                        CH_7, CH_8, CH_9, CH_0, CH_QUOT, CH_CIRC, KC_BACKSPACE, KC_NO, KC_HOME,
        
    // Row 2: QWERTZ row
    M31, M32, KC_TAB, KC_NO, CH_Q, CH_W, CH_E, CH_R, CH_T,                                        CH_Z, CH_U, CH_I, CH_O, CH_P, CH_UDIA, CH_DIAE, KC_NO, KC_PAGE_UP,
    
    // Row 3: Home row
    M41, M42, KC_CAPS_LOCK, KC_NO, CH_A, CH_S, CH_D, CH_F, CH_G,                                  CH_H, CH_J, CH_K, CH_L, CH_ODIA, CH_ADIA, CH_DLR, KC_ENT, KC_PAGE_DOWN,
    
    // Row 4: Bottom row
    M51, M52, KC_LEFT_SHIFT, CH_LABK, CH_Y, CH_X, CH_C, CH_V, CH_B,                               CH_N, CH_M, CH_COMM, CH_DOT, CH_MINS, KC_NO, KC_RIGHT_SHIFT, KC_UP, KC_END,
    
    // Row 5: Modifiers / spacebar
    M61, M62, KC_LEFT_CTRL, MO(_FN), KC_LGUI, KC_LEFT_ALT, KC_NO, KC_SPACE, KC_NO,         KC_NO, KC_SPACE, KC_NO, KC_RIGHT_ALT, LT(_FN1, KC_APPLICATION), KC_RIGHT_CTRL, KC_LEFT, KC_DOWN, KC_RIGHT
  ),

  /* FN Layer (_FN) - Media Keys */
  [_FN] = LAYOUT_6x18(
    KC_NO, KC_NO, KC_NO, KC_BRIGHTNESS_DOWN, KC_BRIGHTNESS_UP, KC_NO, KC_NO, RGB_VAD, RGB_VAI,    KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, KC_AUDIO_MUTE, KC_AUDIO_VOL_DOWN, KC_AUDIO_VOL_UP, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
  ),

  /* FN1 Layer (_FN1) - Custom macros */
  [_FN1] = LAYOUT_6x18(
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
  )
};

// -------------------------
// process_record_user for custom macros
// -------------------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) return true;

  switch (keycode) {
    case M11: send_string_with_delay("Macro M11", 5); return false;
    case M12: send_string_with_delay("Macro M12", 5); return false;
    case M21: send_string_with_delay("Macro M21", 5); return false;
    case M22: send_string_with_delay("Macro M22", 5); return false;
    case M31: send_string_with_delay("Macro M31", 5); return false;
    case M32: send_string_with_delay("Macro M32", 5); return false;
    case M41: send_string_with_delay("Macro M41", 5); return false;
    case M42: send_string_with_delay("Macro M42", 5); return false;
    case M51: send_string_with_delay("Macro M51", 5); return false;
    case M52: send_string_with_delay("Macro M52", 5); return false;
    case M61: send_string_with_delay("Macro M61", 5); return false;
    case M62: send_string_with_delay("Macro M62", 5); return false;
  }

  return true;
}
