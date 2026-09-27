// Copyright 2023 Colin Kinloch (@ColinKinloch)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        LGUI(KC_1), LGUI(KC_2), LGUI(KC_3), LGUI(KC_4),
        LGUI(KC_5), LGUI(KC_6), KC_MRWD,    KC_MFFD,
        RGB_HUI,    RGB_HUD,    KC_MPLY,    KC_MNXT,
        KC_MUTE,    KC_END,     KC_PSCR,    KC_END
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {
        ENCODER_CCW_CW(KC_VOLD,  KC_VOLU),
        ENCODER_CCW_CW(KC_DOWN,  KC_UP),
        ENCODER_CCW_CW(RM_VALD,  KC_UP),
        ENCODER_CCW_CW(KC_PGDN,  KC_PGUP)
    },
};
#endif

#ifndef MAGIC_ENABLE
uint16_t keycode_config(uint16_t keycode) {
    return keycode;
}

uint8_t mod_config(uint8_t mod) {
    return mod;
}
#endif
