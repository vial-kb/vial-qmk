#include QMK_KEYBOARD_H
#include "analog.h"
#include "qmk_midi.h"

#define ____ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        TO(1),
        KC_1,    KC_2,    KC_3,
        KC_4,    KC_5,    KC_6,    KC_0
    ),
    [1] = LAYOUT(
        TO(2),
        RGB_MOD, RGB_HUI,  RGB_VAI,
        RGB_RMOD,  RGB_HUD, RGB_VAD, RGB_TOG
    ),
    [2] = LAYOUT(
        TO(3),
        KC_VOLD, KC_VOLU, KC_F24,
        KC_MRWD, KC_MFFD, KC_F23, KC_MPLY
    ),
    [3] = LAYOUT(
        TO(0),
        ____,    ____,    ____,
        ____,    ____,    ____,    ____
    )
};