// Copyright 2022 xia0 (@xia0)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_ESC , KC_SPC , MO(2)  ,
    KC_MPRV, KC_MNXT, KC_ENT ,
    KC_MUTE,          KC_MPLY
  ),
  [1] = LAYOUT(
    QK_LOCK, KC_UP  , _______,
    KC_LEFT, KC_DOWN, KC_RGHT,
    MS_BTN1,          MS_BTN2
  ),
  [2] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    TO(0)  ,          TO(1)
  ),
  [3] = LAYOUT(
    _______, _______, _______,
    _______, _______, _______,
    _______,          _______
  )
};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MEDIA_REWIND, KC_MEDIA_FAST_FORWARD) },
    [1] = { ENCODER_CCW_CW(MS_DOWN, MS_UP), ENCODER_CCW_CW(MS_LEFT, MS_RGHT) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
