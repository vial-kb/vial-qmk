// Copyright 2024 JP Roemer (@0rax)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
     _MAIN,
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [_MAIN] = {
    ENCODER_CCW_CW(KC_2, KC_1), /* First encoder*/
    ENCODER_CCW_CW(KC_4, KC_3), /* Second encoder*/
    ENCODER_CCW_CW(KC_6, KC_5), /* Third encoder*/
    ENCODER_CCW_CW(KC_8, KC_7), /* Fourth encoder*/
    ENCODER_CCW_CW(KC_0, KC_9)  /* Fifth encoder*/
  }
};
#endif

//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //buttion closest to usb is first
  [_MAIN] = LAYOUT_ortho_1x5(
     KC_A, KC_B, KC_C, KC_D, KC_E
  )
};
