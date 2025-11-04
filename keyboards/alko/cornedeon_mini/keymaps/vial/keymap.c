/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
  [0] = LAYOUT(
  //,--------------------------------------------.    ,-------------------------------------------.
       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+-------|
       KC_A,    KC_S,    KC_D,    KC_F,    KC_G,         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+-------|
       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, 
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+-------|
      XXXXXXX,XXXXXXX, KC_LSFT, TL_LOWR,  KC_SPC,        KC_SPC, TL_UPPR, KC_RCTL, XXXXXXX, XXXXXXX
  //`--------------------------------------------'   `--------------------------------------------'
  ),
  [1] = LAYOUT(
  //,--------------------------------------------.    ,--------------------------------------------.
       KC_ESC, KC_LPRN, KC_RPRN, KC_PLUS,KC_MINUS,         KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------|
       KC_TAB, KC_LBRC, KC_RBRC,KC_DQUO, KC_SLASH,         KC_4,    KC_5,    KC_6,KC_KP_DOT,KC_SLSH,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------|
      KC_LALT, KC_LCBR, KC_RCBR,   KC_LT,   KC_GT,         KC_1,    KC_2,    KC_3, KC_UNDS, KC_BSLS, 
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_LSFT, KC_TRNS,  KC_SPC,       KC_ENT, KC_TRNS, KC_RGUI, XXXXXXX, XXXXXXX
  //`--------------------------------------------'    `--------------------------------------------'
  ),
  [2] = LAYOUT(
  //,--------------------------------------------.    ,--------------------------------------------.
      KC_PSLS, KC_KP_0, KC_KP_7, KC_KP_8, KC_KP_9,        KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_PSCR,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------|
      KC_PMNS, KC_PDOT, KC_KP_4, KC_KP_5, KC_KP_6,        KC_F4,   KC_F5,   KC_F6,  KC_F11,  KC_NUM,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------|
      XXXXXXX, KC_PEQL, KC_KP_1, KC_KP_2, KC_KP_3,        KC_F1,   KC_F2,   KC_F3,  KC_F12,  KC_APP,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_CALC, KC_TRNS, KC_PENT,       KC_ENT, KC_TRNS, KC_CAPS, XXXXXXX, XXXXXXX
  //`--------------------------------------------'    `--------------------------------------------'
  ),
  [3] = LAYOUT(
  //,--------------------------------------------.    ,---------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, KC_CALC, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------|    |--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, KC_TRNS, XXXXXXX,      XXXXXXX, KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX
  //`--------------------------------------------'    `--------------------------------------------'
  )
};

