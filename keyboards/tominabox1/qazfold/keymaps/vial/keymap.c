#include QMK_KEYBOARD_H
#include "quantum.h"
//REPLACE THIS WITH YOUR KEYBOARD.h 
#include "qazfold.h"

// #include "combos.c"
// #include "macros.c"



layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case _COLEMAKDH:
        rgblight_sethsv (  0, 255,  69);  // green
        break;
    case _NUM_SYM:
        rgblight_sethsv (201, 255,  69);  // cyan
        break;
    case _NAV:
        rgblight_sethsv (169, 255,  69);  // blue
        break;
    case _QWERTY:
        rgblight_sethsv ( 85, 255,  69);  // red
        break;
    default: //  for any other layers, or the default layer
        rgblight_sethsv (  0,   0,  69);  // white

        break;
    }
  return state;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAKDH] = LAYOUT_split_space(
    KC_Q,   KC_W,   KC_F,   KC_P,   KC_B,   KC_J,   KC_L,    KC_U,   KC_Y,     KC_QUOT,
MT(MOD_LGUI,KC_A), MT(MOD_LALT,KC_R), MT(MOD_LCTL,KC_S), MT(MOD_LSFT,KC_T), KC_G, KC_M, MT(MOD_LSFT,KC_N), MT(MOD_LCTL,KC_E), MT(MOD_LALT,KC_I), MT(MOD_LGUI,KC_O),
    KC_X,   KC_C,   KC_D, KC_V, KC_Z,  KC_K,   KC_H,   KC_COMMA, KC_DOT,
    KC_TAB, KC_BSPC, KC_NO, KC_NO,  LT(_NUM_SYM,KC_SPACE),  KC_NO, KC_ENT, KC_DEL,
    KC_F13, KC_F14, MO(_NAV), MO(_QWERTY)
),

  [_QWERTY] = LAYOUT_split_space(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
MT(MOD_LGUI,KC_A), MT(MOD_LALT,KC_S), MT(MOD_LCTL,KC_D), MT(MOD_LSFT,KC_F), KC_G, KC_H, MT(MOD_LSFT,KC_J), MT(MOD_LCTL,KC_K), MT(MOD_LALT,KC_L), MT(MOD_LGUI,KC_QUOT),
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M, KC_COMMA, KC_DOT,
    KC_TAB, KC_BSPC, KC_NO, KC_NO,  LT(_NUM_SYM,KC_SPACE),  KC_NO, KC_ENT, KC_DEL,
    KC_F13, KC_F14, MO(_NAV), KC_TRNS
  ),

  [_NUM_SYM] = LAYOUT_split_space(
    
    KC_GRV, KC_F2,   KC_TRNS, KC_TRNS, KC_F5,   KC_BSLS, KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,
    KC_1,   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,   KC_9,    KC_0,
    KC_TRNS,KC_TRNS, KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCLN,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_VAI, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_NAV] = LAYOUT_split_space(
KC_TRNS, KC_TRNS, LSG(KC_4),  LSG(KC_S),  KC_TRNS, KC_HOME, KC_HOME, KC_UP,   KC_TRNS, KC_PGUP,
KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_TRNS, KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
C(KC_Z),    C(KC_X),    C(KC_C),    C(KC_V),    C(KC_Y),    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),






};
