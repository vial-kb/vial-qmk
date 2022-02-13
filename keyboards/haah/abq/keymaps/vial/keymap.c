#include QMK_KEYBOARD_H
#include "quantum_keycodes.h"
#include "../../tap_dance.h"

enum combo_events {
  COMBO_BSPC,
  COMBO_NUMBAK,
  COMBO_TAB,
  COMBO_ESC,
  COMBO_DEL,
};

#define KC_A_CTL LCTL_T(KC_A)
#define KC_S_OPT LOPT_T(KC_S)
#define KC_D_CMD LCMD_T(KC_D)
#define KC_F_SFT LSFT_T(KC_F)
#define KC_J_SFT RSFT_T(KC_J)
#define KC_K_CMD RCMD_T(KC_K)
#define KC_L_OPT ROPT_T(KC_L)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
      KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC, \
      MT(MOD_LCTL, KC_ESC), KC_A_CTL,  KC_S_OPT,  KC_D_CMD,  KC_F_SFT,   KC_G,   KC_H,  KC_J_SFT, KC_K_CMD, KC_L_OPT, KC_SCLN, KC_ENT, \
      KC_LSFT, KC_Z, KC_X,  KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, MT(MOD_RSFT, KC_SLSH), \
      KC_ALGR, KC_LCMD, LT(1, KC_BSPC), LT(2, KC_SPC), MOD_LSFT, KC_MPLY \
    ),

    [1] = LAYOUT(
      TD(KC_TILD), KC_EXLM, KC_UP, KC_UP, KC_DLR, KC_PERC, KC_CIRC, KC_LCBR, KC_RCBR, KC_AMPR, KC_HASH, KC_UNDS, \
      KC_HOME, KC_LEFT, KC_LEFT, KC_DOWN, KC_RIGHT, KC_SPC, KC_BSPC, SFT_T(KC_LPRN), CMD_T(KC_RPRN), OPT_T(KC_EQL), KC_COLN, KC_DQUO, \
      KC_PIPE, KC_BSLS, KC_AT, KC_ASTR, KC_MINUS, KC_PLUS, KC_LBRC, KC_RBRC, KC_LT, KC_GT, KC_QUES, \
      _______, _______, _______, _______, _______, _______ \
    ),

    [2] = LAYOUT(
      KC_0, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_DOT, \
      _______, KC_LEFT, KC_DOWN, KC_DEL, KC_RIGHT, KC_SPC, KC_BSPC, KC_PLUS, KC_MINUS, KC_ASTR, KC_COLN, KC_COMM,  \
      RESET, _______, _______, _______, KC_CIRC, KC_SLSH, KC_AMPR, KC_PIPE, KC_COMM, KC_PERC, KC_EXLM,  \
      _______, _______, _______, _______, _______, _______ \
    ),
};

//#ifdef COMBO_ENABLE
//    const uint16_t PROGMEM combo_bspc[] = {KC_O, KC_P, COMBO_END};
//    const uint16_t PROGMEM combo_numbak[] = {KC_0, KC_9, COMBO_END};
//    const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
//    const uint16_t PROGMEM combo_esc[] = {KC_E, KC_W, COMBO_END};
//    const uint16_t PROGMEM combo_del[] = {KC_MINS, KC_EQL, COMBO_END};
//
//    combo_t key_combos[COMBO_COUNT] = {
//      [COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
//      [COMBO_NUMBAK] = COMBO(combo_numbak,KC_BSPC),
//      [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
//      [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
//      [COMBO_DEL] = COMBO(combo_del,KC_DEL),
//    };
//#endif
