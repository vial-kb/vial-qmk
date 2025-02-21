// Copyright 2024 LAZDESIGNERS
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define LT1_SPC LT(1, KC_SPC)

// For testing only
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
               KC_ESC,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,      KC_BSPC,    KC_DEL,   KC_HOME,
               KC_TAB,   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,   KC_ENT,
               KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLASH,  MO(2),      KC_UP,    
               KC_LCTL,  KC_LALT, KC_LGUI, KC_NO,   KC_SPC,  LT1_SPC,                   KC_NO,   KC_LEFT,  KC_DOWN,   KC_LEFT,    KC_DOWN,  KC_RGHT
             ),
    [1] = LAYOUT(
               KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,      KC_NO,    KC_NO,
               KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,
               KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,      KC_NO,    
               KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,    KC_NO,     KC_NO,      KC_NO,    KC_NO
             ),
    [2] = LAYOUT(
               KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,      KC_NO,    KC_NO,
               KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,
               KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,     KC_NO,      KC_NO,    
               KC_NO,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,                     KC_NO,   KC_NO,    KC_NO,     KC_NO,      KC_NO,    KC_NO
             ),
};


