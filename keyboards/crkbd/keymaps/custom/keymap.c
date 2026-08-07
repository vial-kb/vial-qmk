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

// Tap dance configured via Vial interface

/* Custom keycodes for macros */
enum custom_keycodes {
    M0 = SAFE_RANGE,
    M4,
    M5,
    M6,
    M7,
    M8,
    M9,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Base layer */
    [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_GRV,     KC_Q,    KC_W,    KC_L,    KC_D,    KC_P,                      KC_K,    KC_M,    KC_U,    KC_Y, KC_SCLN,SGUI(KC_GRV),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   QK_CAPS_WORD_TOGGLE,LCTL_T(KC_A),LALT_T(KC_S),LGUI_T(KC_R),LSFT_T(KC_T),KC_G,     KC_F,RSFT_T(KC_N),RGUI_T(KC_E),RALT_T(KC_I),RCTL_T(KC_O),RGUI(KC_GRV),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
  OSM(MOD_HYPR),KC_BSLS,  KC_Z,    KC_X,    KC_C,    KC_V,                      KC_J,    KC_B,    KC_H, KC_COMM,  KC_DOT,LCTL(KC_UP),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_ESC,LT(1,KC_TAB),LT(2,KC_ENT),  LT(3,KC_SPC),KC_BSPC,RGUI(KC_SPC)
                                      //`--------------------------'  `--------------------------'
    ),

    /* Layer 1: Numbers */
    [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC,                   KC_RBRC, KC_PPLS, KC_PMNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   OSM(MOD_MEH),KC_TRNS, KC_TRNS,S(KC_LBRC),S(KC_RBRC),S(KC_9),               S(KC_0), KC_PAST, KC_PSLS, KC_PEQL, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,RSFT_T(KC_BSPC),KC_TRNS
                                      //`--------------------------'  `--------------------------'
    ),

    /* Layer 2: Function keys */
    [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_BRID, KC_BRIU, KC_TRNS, KC_TRNS, KC_TRNS,               LGUI(KC_LEFT),LALT(KC_LEFT),KC_UP,RALT(KC_RGHT),RGUI(KC_RGHT),KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_VOLD, KC_MUTE, KC_VOLU, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS
                                      //`--------------------------'  `--------------------------'
    ),

    /* Layer 3: Special/Navigation */
    [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,SGUI(KC_4),KC_TRNS,                LCAG(KC_K),KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,LGUI(KC_LBRC),LGUI(KC_RBRC),KC_TRNS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,SGUI(KC_C),KC_NO,                    KC_TRNS,LCAG(KC_C),KC_TRNS, KC_TRNS, KC_TRNS,LCTL(KC_DOWN),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_NO
                                      //`--------------------------'  `--------------------------'
    ),




};

/* Macro handling */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M0:
            if (record->event.pressed) {
                tap_code(KC_RALT);
                tap_code(KC_RGUI);
                tap_code(KC_V);
            }
            return false;
        case M4:
            if (record->event.pressed) {
                tap_code(KC_RALT);
                tap_code(KC_RGUI);
                tap_code(KC_RSFT);
                tap_code(KC_K);
            }
            return false;
        case M5:
            if (record->event.pressed) {
                SEND_STRING(":ls");
                tap_code(KC_ENT);
            }
            return false;
        case M6:
            if (record->event.pressed) {
                SEND_STRING("dtim");
                tap_code(KC_ENT);
            }
            return false;
        case M7:
            if (record->event.pressed) {
                SEND_STRING("ddus");
                tap_code(KC_ENT);
            }
            return false;
        case M8:
            if (record->event.pressed) {
                SEND_STRING(":lt");
                tap_code(KC_ENT);
            }
            return false;
        case M9:
            if (record->event.pressed) {
                SEND_STRING(":apup");
                tap_code(KC_ENT);
            }
            return false;
    }
    return true;
}

// Vial manages combos
