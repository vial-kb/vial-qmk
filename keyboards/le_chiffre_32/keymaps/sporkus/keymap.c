#pragma once

#include QMK_KEYBOARD_H
#include "quantum/keycodes.h"
#include "layout.h"
#include "../../rgb.c"

// This file should not be called [keyboard].h as it will cause conflict with qmk
// layout to be used in [keyboard].json | exact layout name defined in keyboards/[keyboard]/info.json
#define LAYOUT_w(...)        LAYOUT(__VA_ARGS__)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_w(
        LEFT_ROW1(_BASE),           KC_MUTE,             RIGHT_ROW1(_BASE),       \
        HRML(LEFT_ROW2(_BASE)),                          HRMR(RIGHT_ROW2(_BASE)), \
        BRML(LEFT_ROW3(_BASE)),                          BRMR(RIGHT_ROW3(_BASE)), \
        LEFT_THUMB(_BASE),                               RIGHT_THUMB(_BASE)
    ),
    [1] = LAYOUT_w(
        LEFT_ROW1(_NUM),            _______,             RIGHT_ROW1(_NUM),    \
        LEFT_ROW2(_NUM),                                 RIGHT_ROW2(_NUM),    \
        LEFT_ROW3(_NUM),                                 RIGHT_ROW3(_NUM),    \
        LEFT_THUMB(_NUM),                                RIGHT_THUMB(_NUM)
    ),
    [2] = LAYOUT_w(
        LEFT_ROW1(_NAV),            _______,             RIGHT_ROW1(_NAV),    \
        LEFT_ROW2(_NAV),                                 RIGHT_ROW2(_NAV),    \
        LEFT_ROW3(_NAV),                                 RIGHT_ROW3(_NAV),    \
        LEFT_THUMB(_NAV),                                RIGHT_THUMB(_NAV)
    ),
    [3] = LAYOUT_w(
        LEFT_ROW1(_FN),             _______,             RIGHT_ROW1(_FN),    \
        LEFT_ROW2(_FN),                                  RIGHT_ROW2(_FN),    \
        LEFT_ROW3(_FN),                                  RIGHT_ROW3(_FN),    \
        LEFT_THUMB(_FN),                                 RIGHT_THUMB(_FN)
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] =   { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [2] =   { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [3] =   { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif

