/* Copyright 2019 gtips
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layer_names {
    _BASE,
    _FNNO,
    _ADJUST,
};

#define TAPPING_TOGGLE 3
#define _BASE 0
#define _FNNO 1
#define _ADJUST 2

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_reviung39(
                            QK_GESC, KC_Q, KC_D, KC_R, KC_W, KC_B, KC_J, KC_F, KC_U, KC_P, KC_SCLN, KC_BSPC, \
                            LSFT_T(KC_TAB), KC_A, KC_S, LGUI_T(KC_H), LALT_T(KC_T), KC_G, KC_Y, RALT_T(KC_N), KC_E, KC_O, KC_I, KC_QUOT, \
                            KC_LCTL, KC_Z, KC_X, KC_M, KC_C, KC_V, KC_K, KC_L, KC_COMM, KC_DOT, KC_SLSH, RSFT_T(KC_ENT), \
                            TT(1), KC_SPC, TT(2)
                            ),
  
  [_FNNO] = LAYOUT_reviung39(
                            KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_LBRC, KC_RBRC, KC_7, KC_8, KC_9, KC_0, KC_DEL, \
                            KC_TRNS, KC_F5, KC_F6, KC_F7, KC_F8, KC_MINS, KC_EQL, RALT_T(KC_4), RGUI_T(KC_5), KC_6, KC_HOME, KC_END, \
                            KC_TRNS, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_BSLS, KC_1, KC_2, KC_3, KC_TRNS, KC_TRNS, 
                            KC_TRNS, KC_BSPC, KC_PDOT
                            ),
  
  [_ADJUST] = LAYOUT_reviung39(
                            QK_GESC, KC_NUM, KC_P7, KC_P8, KC_P9, KC_P0, KC_NO, KC_PGUP, KC_UP, KC_PGDN, KC_NO, KC_DEL, \
                            KC_TRNS, KC_NO, KC_P4, LGUI_T(KC_P5), LALT_T(KC_P6), KC_BRIU, KC_VOLU, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_NO, \
                            KC_LCTL, KC_NO, KC_P1, KC_P2, KC_P3, KC_BRID, KC_VOLD, KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS, \
                            KC_TRNS, KC_NO, KC_TRNS
                            ),
};
