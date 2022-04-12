/* Copyright 2022 bdtc123
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

enum my_keycodes {
    RMT = SAFE_RANGE,
    RMS,
    RMIH,
    RMDH,
    RMIS,
    RMDS,
    RMIV,
    RMDV
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RMT:
      if (record->event.pressed)
      {rgb_matrix_toggle();
      }
      return false;
    case RMS:
      if (record->event.pressed)
      {rgb_matrix_step();
      }
      return false;
      case RMIH:
      if (record->event.pressed)
      {rgb_matrix_increase_hue();
      }
      return false;
      case RMDH:
      if (record->event.pressed)
      {rgb_matrix_decrease_hue();
      }
      return false;
      case RMIS:
      if (record->event.pressed)
      {rgb_matrix_increase_sat();
      }
      return false;
      case RMDS:
      if (record->event.pressed)
      {rgb_matrix_decrease_sat();
      }
      return false;
      case RMIV:
      if (record->event.pressed)
      {rgb_matrix_increase_val();
      }
      return false;
      case RMDV:
      if (record->event.pressed)
      {rgb_matrix_decrease_val();
      }
      return true;
      default:
      return true;
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT_planck_mit(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,   KC_ENT,
        KC_CAPS, KC_LCTL, KC_LALT, KC_LGUI, MO(1),   KC_SPC,           MO(2), KC_LEFT, KC_DOWN, KC_UP, KC_RGHT
    ),

    [1] = LAYOUT_planck_mit(
        RESET,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, _______,  RMT,    RMS,
        _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
        KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
        KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS, _______, _______, _______, _______, KC_PGUP, KC_PGDN
    ),
    [2] = LAYOUT_planck_mit(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT_planck_mit(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),

};
