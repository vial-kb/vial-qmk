// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,         KC_W, KC_E, KC_R,    KC_T,
        KC_ENT,  KC_A,         KC_S, KC_D, KC_F,    KC_G,
        KC_LSFT, LSFT_T(KC_Z), KC_X, KC_C, KC_V,    KC_B,
                                           KC_LALT, KC_SPC, KC_TAB
    )
};