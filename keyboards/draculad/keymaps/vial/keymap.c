/*
Copyright 2021 @mangoiv

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#define ____ KC_TRNS


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] =  LAYOUT(
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                                                 KC_Y,             KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,         KC_S,    KC_D,    KC_F,    KC_G,                                                 KC_H,             KC_J,    KC_K,    KC_L,    KC_QUOT,
        LSFT_T(KC_Z), KC_X,    KC_C,    KC_V,    KC_B,                                                 KC_N,             KC_M,    KC_COMM, KC_DOT,  RSFT_T(KC_SLSH),
                                                 KC_MUTE,                                              KC_N,
                                        KC_LCTL, MO(1), KC_SPC,    KC_BACKSPACE, MO(2), KC_RALT
    ),
    [1] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_TAB,    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,      _______, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,
        KC_LCTL, KC_GRV,  KC_LGUI, KC_LALT, _______,      _______, _______, _______, KC_BSLS,  KC_SCLN,
                                            XXXXXXX,                      KC_NO,
                                   _______, _______, _______,      KC_ENT, MO(4), _______
    ),
    [2] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_ESC,  _______, _______, _______, _______,      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,
        KC_CAPS, KC_TILD, _______, _______, _______,      _______, _______, _______, KC_PIPE,  KC_COLN,
                                            XXXXXXX,                      KC_NO,
                                   _______, MO(4), _______,      KC_ENT,  _______, KC_DEL
    ),

    [3] = LAYOUT(
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_ESC,  _______, _______, _______, _______,      _______, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,
        KC_CAPS, KC_TILD, _______, _______, _______,      _______, _______, _______, KC_PIPE,  KC_COLN,
                                            XXXXXXX,                      KC_NO,
                                   _______, _______, _______,      KC_ENT,  _______, KC_DEL
    ),

    [4] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_F11,  KC_F12,  _______, _______, _______,      _______, _______, LCTL(LALT(KC_END)), LCTL(LALT(KC_DEL)), LCTL(LALT(KC_DEL)),
        RESET,   _______, _______, _______, _______,      _______, _______, _______, _______,  _______,
                                            XXXXXXX,                      _______,
                                   XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
    )
};



#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 2) {
      if(clockwise) {
        tap_code(KC_PGUP);
      }
      else{
        tap_code(KC_PGDN);
      }
    }
    else if (index == 3  ) {
        // Page up/Page down
        if (clockwise) {
          tap_code(KC_WH_U);
        } else {
          tap_code(KC_WH_D);
        }
    }
    return true;
}
#endif



