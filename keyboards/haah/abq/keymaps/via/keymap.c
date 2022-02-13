#include QMK_KEYBOARD_H
#include "quantum_keycodes.h"
#include "../../tap_dance.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINUS, \
      MT(MOD_LCTL, KC_ESC), KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, \
      KC_LSFT, KC_Z, KC_X,  KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_RSFT, KC_SLSH), \
      KC_LGUI, KC_ALGR, LT(1, KC_SPC), LT(2, KC_ENT), MOD_LSFT, _______ \
    ),

    [1] = LAYOUT(
      TD(GRV_TILD), KC_EXLM, KC_UP, KC_END, KC_DLR, KC_PERC, KC_CIRC, KC_LCBR, KC_RCBR, KC_AMPR, KC_HASH, KC_UNDS, \
      KC_HOME, KC_LEFT, KC_DOWN, KC_DEL, KC_RIGHT, KC_SPC, KC_BSPC, KC_LPRN, KC_RPRN, KC_EQL, KC_COLN, KC_DQUO, \
      KC_PIPE, KC_BSLS, KC_AT, KC_ASTR, KC_MINUS, KC_PLUS, KC_LBRC, KC_RBRC, KC_LT, KC_GT, KC_QUES, \
      _______, _______, _______, _______, _______, _______ \
    ),

    [2] = LAYOUT(
      KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DOT, \
      _______, KC_LEFT, KC_DOWN, KC_DEL, KC_RIGHT, KC_SPC, KC_BSPC, KC_PLUS, KC_MINUS, KC_ASTR, KC_COLN, KC_COMM,  \
      RESET, _______, _______, _______, KC_CIRC, KC_SLSH, KC_AMPR, KC_PIPE, KC_COMM, KC_PERC, KC_EXLM,  \
      _______, _______, _______, _______, _______, _______ \
    )
};
