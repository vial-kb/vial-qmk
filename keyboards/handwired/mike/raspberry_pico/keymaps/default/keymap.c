#include QMK_KEYBOARD_H
#include "keymap_swiss_de.h"

enum layers {
  _BASE,
  _FN,
  _FN1
};

// -------------------------
// 6x18 Keymaps
// -------------------------
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Base Layer (_BASE) */
  [_BASE] = LAYOUT_6x18(
    // Row 0: ESC + F1–F12
    KC_NO, KC_NO, KC_ESCAPE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,                                KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PRINT_SCREEN, KC_INSERT, KC_DELETE, 
    
    // Row 1: Numbers row (Swiss German)
    KC_NO, KC_NO, CH_SECT, CH_1, CH_2, CH_3, CH_4, CH_5, CH_6,                                        CH_7, CH_8, CH_9, CH_0, CH_QUOT, CH_CIRC, KC_BACKSPACE, KC_NO, KC_HOME,
        
    // Row 2: QWERTZ row
    KC_NO, KC_NO, KC_TAB, KC_NO, CH_Q, CH_W, CH_E, CH_R, CH_T,                                        CH_Z, CH_U, CH_I, CH_O, CH_P, CH_UDIA, CH_DIAE, KC_NO, KC_PAGE_UP,
    
    // Row 3: Home row
    KC_NO, KC_NO, KC_CAPS_LOCK, KC_NO, CH_A, CH_S, CH_D, CH_F, CH_G,                                  CH_H, CH_J, CH_K, CH_L, CH_ODIA, CH_ADIA, CH_DLR, KC_ENT, KC_PAGE_DOWN,
    
    // Row 4: Bottom row
    KC_NO, KC_NO, KC_LEFT_SHIFT, CH_LABK, CH_Y, CH_X, CH_C, CH_V, CH_B,                               CH_N, CH_M, CH_COMM, CH_DOT, CH_MINS, KC_NO, KC_RIGHT_SHIFT, KC_UP, KC_END,
    
    // Row 5: Modifiers / spacebar
    KC_NO, KC_NO, KC_LEFT_CTRL, MO(_FN), KC_LGUI, KC_LEFT_ALT, KC_NO, KC_SPACE, KC_NO,         KC_NO, KC_SPACE, KC_NO, KC_RIGHT_ALT, LT(_FN1, KC_APPLICATION), KC_RIGHT_CTRL, KC_LEFT, KC_DOWN, KC_RIGHT
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