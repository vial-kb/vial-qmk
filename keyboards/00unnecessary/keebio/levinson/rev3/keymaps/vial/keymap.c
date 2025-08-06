/*
Copyright 2020 Danny Nguyen <danny@keeb.io>
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC,
    LCTL_T(KC_ESC), KC_A, KC_R, KC_S,   KC_T,    KC_G,    KC_K,    KC_N,    KC_E,    KC_I,    KC_O,    RSFT_T(KC_ENT),
    LSFT_T(KC_GRV), KC_Z, KC_X, KC_C,   KC_D,    KC_V,    KC_M,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_QUOT,
    MO(2), SGUI(KC_LBRC), TG(1), KC_LGUI, _______, LT(3, KC_ENT), LT(1, KC_SPC), _______, RALT_T(KC_LEFT), RSFT_T(KC_DOWN), RGUI_T(KC_UP), RCTL_T(KC_RIGHT)
  ),

  [1] = LAYOUT_ortho_4x12(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
    KC_TAB,  KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, KC_TRNS, KC_PLUS, KC_1, KC_2, KC_3, KC_ASTR, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _______, KC_0, KC_SPC, _______, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [2] = LAYOUT_ortho_4x12(
    KC_BTN1, KC_BTN2, _______, SGUI(KC_LBRC), SGUI(KC_RBRC), _______, KC_PGUP, KC_HOME, KC_UP, KC_END, KC_COLN, RALT(KC_BSPC),
    KC_TRNS, _______, _______, _______, KC_BSPC, _______, KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_ENT, RALT(KC_D),
    KC_TRNS, _______, _______, _______, _______, _______, _______, RALT(KC_LEFT), RALT(KC_RIGHT), _______, RALT(KC_B), RALT(KC_F),
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, _______, LALT(KC_DEL), KC_DEL, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R
  ),

  [3] = LAYOUT_ortho_4x12(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, _______, KC_TRNS, KC_TRNS,
    KC_CAPS, KC_LBRC, KC_RBRC, KC_LPRN, KC_RPRN, _______, KC_PLUS, KC_DLR, KC_PIPE, KC_BSLS, KC_DQT, KC_TRNS,
    KC_TRNS, KC_BRID, KC_BRIU, KC_VOLD, KC_VOLU, KC_MUTE, KC_MINS, KC_EQL, KC_LT, KC_GT, KC_QUES, KC_TRNS,
    KC_TRNS, KC_TRNS, QK_BOOT, _______, _______, KC_TRNS, KC_UNDS, _______, KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R
  )

};
