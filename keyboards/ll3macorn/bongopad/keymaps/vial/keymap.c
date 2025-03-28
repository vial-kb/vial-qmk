// Copyright 2021 Ll3macorn (@ll3macorn)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include <stdio.h>

enum layers {
    Layer1,
    Layer2,
    Layer3,
    Layer4
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[Layer1] = LAYOUT(
		KC_MUTE,
		KC_7, KC_8, KC_9,
		KC_4, KC_5, KC_6,
		KC_1, KC_2, KC_3),

    [Layer2] = LAYOUT(
		KC_SPC,
		KC_SPC, KC_SPC, KC_SPC,
		KC_SPC, KC_SPC, KC_SPC,
		KC_SPC, KC_SPC, KC_SPC),

    [Layer3] = LAYOUT(
		KC_SPC,
		KC_SPC, KC_SPC, KC_SPC,
		KC_SPC, KC_SPC, KC_SPC,
		KC_SPC, KC_SPC, KC_SPC),

    [Layer4] = LAYOUT(
		KC_SPC,
		KC_SPC, KC_SPC, KC_SPC,
		KC_SPC, KC_SPC, KC_SPC,
		KC_SPC, KC_SPC, KC_SPC)

};

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
