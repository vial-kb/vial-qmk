#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
  _COLEMAK,
  _LOWER,
  _RAISE,
  _ADJUST,
};

enum custom_keycodes {
  COLEMAK= SAFE_RANGE,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_COLEMAK] = LAYOUT_all(
  KC_TAB,           KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
  LCTL_T(KC_ESC),   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,       SGUI(KC_RBRC),          KC_K,    KC_N,    KC_E,    KC_I,    KC_O,    RSFT_T(KC_ENT),
  LSFT_T(KC_GRV),   KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,        KC_SPC,          KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
  MO(2),         SGUI(KC_LBRC),   TT(1), LGUI_T(KC_SPC), _______, LT(3, KC_ENT), KC_MUTE, LT(1, KC_SPC), _______, RALT_T(KC_LEFT), RSFT_T(KC_DOWN), RGUI_T(KC_UP), RCTL_T(KC_RIGHT)
),

[_LOWER] = LAYOUT_all(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_TRNS,
  KC_TAB,  KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_TRNS, KC_TRNS, KC_PLUS, KC_KP_1, KC_KP_2, KC_KP_3, KC_ASTR, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_ESC,  KC_MINS,  KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _______, KC_KP_0, KC_TRNS, _______, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

[_RAISE] = LAYOUT_all(
  KC_BTN1, KC_BTN2, _______, SGUI(KC_LBRC), SGUI(KC_RBRC), _______, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_COLN, RALT(KC_BSPC),
  KC_TRNS, _______, _______, _______, KC_BSPC, _______, KC_TRNS, KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT, RALT(KC_D),
  KC_TRNS, _______, _______, _______, _______, _______, KC_TRNS, _______, RALT(KC_LEFT), RALT(KC_RIGHT), _______, RALT(KC_B), RALT(KC_F),
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _______, LALT(KC_DEL), KC_TRNS, KC_DEL, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
),


[_ADJUST] = LAYOUT_all(
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, _______, KC_TRNS, KC_TRNS,
  KC_CAPS, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, _______, KC_TRNS, KC_PLUS, KC_DLR, KC_PIPE, KC_BSLS, KC_DQT, KC_TRNS,
  KC_TRNS, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, KC_TRNS, KC_MINS, KC_EQL, KC_LT, KC_GT, KC_QUES, KC_TRNS,
  KC_TRNS, KC_TRNS, QK_BOOT, _______, _______, KC_TRNS, KC_TRNS, KC_UNDS, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R
)

};

/* layer_state_t layer_state_set_user(layer_state_t state) { */
/*     return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST); */
/* } */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            break;
    }
    return true;
}

/* bool encoder_update_user(uint8_t index, bool clockwise) { */
/*     if (clockwise) { */
/*       tap_code16(S(KC_VOLD)); */
/*     } else { */
/*       tap_code16(KC_VOLU); */
/*     } */
/*     return true; */
/* } */

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLU, KC_VOLD),   },
    [1] =   { ENCODER_CCW_CW(KC_BRIU, KC_BRID),   },
    [2] =   { ENCODER_CCW_CW(KC_WH_L, KC_WH_R),   },
    [3] =   { ENCODER_CCW_CW(KC_WH_U, KC_WH_D),   },
};
#endif
