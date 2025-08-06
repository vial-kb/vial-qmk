#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,     KC_O,   KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,     KC_L,   KC_BSPC,
        LSFT_T(KC_Z),    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,  KC_DOT, RSFT_T(KC_ENT),
        KC_LCTL, KC_LGUI, KC_SPC, KC_SPC,  MO(1),  MO(2),  KC_RALT
    ),
    [1] = LAYOUT( /* NAV */
        KC_ESC,  _______, _______, KC_TAB,  _______, KC_PGUP, KC_HOME, KC_UP,   KC_END,  _______,
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT( /* SYM */
        KC_QUOT, KC_DQUO, KC_CIRC, KC_QUES, KC_GRV,  KC_LBRC, KC_LABK, KC_EQL,  KC_RABK, KC_RBRC,
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_LCBR, KC_LPRN, KC_COLN, KC_RPRN, KC_RCBR,
        KC_BSLS, KC_TILD, KC_PIPE, KC_AMPR, KC_SCLN, KC_SLSH, KC_ASTR, KC_MINS, KC_PLUS, KC_UNDS,
        _______, _______, _______, _______, _______, _______, _______
    ),
};