/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
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
#include "analog.h"
#include "rgb_matrix_map.h"
#include <math.h>

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      NUM      /       *       -
//      7        8       9       +
//      4        5       6       CALC
//      1        2       3       RET
//      0                        .

  [_BASE] = LAYOUT(
    MO(1),   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,   KC_P8,     KC_P9,     KC_PPLS,
    KC_P4,   KC_P5,     KC_P6,     KC_CALC,
    KC_P1,   KC_P2,     KC_P3,     KC_PENT,
    KC_P0,                         KC_PDOT
  ),
  [_UTIL] = LAYOUT(
    _______,   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,     RGB_VAI,   KC_P9,     KC_PPLS,
    RGB_RMOD,  KC_P5,     RGB_MOD,   KC_CALC,
    KC_P1,     RGB_VAD,   KC_P3,     KC_PENT,
    RGB_TOG,                         QK_BOOT
  ),
  [_DRAW1] = LAYOUT(
    _______,   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,     RGB_VAI,   KC_P9,     KC_PPLS,
    RGB_RMOD,  KC_P5,     RGB_MOD,   KC_CALC,
    KC_P1,     RGB_VAD,   KC_P3,     KC_PENT,
    RGB_TOG,                         QK_BOOT
  ),
  [_DRAW2] = LAYOUT(
    _______,   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,     RGB_VAI,   KC_P9,     KC_PPLS,
    RGB_RMOD,  KC_P5,     RGB_MOD,   KC_CALC,
    KC_P1,     RGB_VAD,   KC_P3,     KC_PENT,
    RGB_TOG,                         QK_BOOT
  ),
  [4] = LAYOUT(
    _______,   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,     RGB_VAI,   KC_P9,     KC_PPLS,
    RGB_RMOD,  KC_P5,     RGB_MOD,   KC_CALC,
    KC_P1,     RGB_VAD,   KC_P3,     KC_PENT,
    RGB_TOG,                         QK_BOOT
  ),
  [5] = LAYOUT(
    _______,   KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_P7,     RGB_VAI,   KC_P9,     KC_PPLS,
    RGB_RMOD,  KC_P5,     RGB_MOD,   KC_CALC,
    KC_P1,     RGB_VAD,   KC_P3,     KC_PENT,
    RGB_TOG,                         QK_BOOT
  )
};
// clang-format on

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_UTIL] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_DRAW1] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_DRAW2] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [4] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [5] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
};

// Capslock, Scroll lock and Numlock indicator on Left side lights.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch (get_highest_layer(layer_state)) { // special handling per layer
        case _BASE: // on Fn layer select what the encoder does when pressed
            rgb_matrix_set_color(LED_NUM, RGB_LAYERCHANGE); //FN key
            break;
        case _UTIL: // on Fn layer select what the encoder does when pressed
            rgb_matrix_set_color(LED_NUM, RGB_LAYERCHANGE); //FN key
            rgb_matrix_set_color(LED_DIV, RGB_LAYERCHANGE);
            rgb_matrix_set_color(LED_STAR, RGB_LAYERCHANGE);
            rgb_matrix_set_color(LED_8, RGB_UTIL);
            rgb_matrix_set_color(LED_9, RGB_UTIL);
            rgb_matrix_set_color(LED_5, RGB_UTIL);
            rgb_matrix_set_color(LED_6, RGB_UTIL);
            rgb_matrix_set_color(LED_4, RGB_UTIL);
            rgb_matrix_set_color(LED_PLUS, RGB_UTIL);
            rgb_matrix_set_color(LED_1, RGB_UTIL);
            rgb_matrix_set_color(LED_0, RGB_UTIL);
            rgb_matrix_set_color(LED_MINUS, RGB_UTIL);
            for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_SIDES); i++) {
                rgb_matrix_set_color(LED_LIST_SIDES[i], RGB_LAYERCHANGE);
            }
            rgb_matrix_set_color(LED_7, RGB_BLACK);
            rgb_matrix_set_color(LED_2, RGB_BLACK);
            rgb_matrix_set_color(LED_3, RGB_BLACK);
            rgb_matrix_set_color(LED_DOT, RGB_BLACK);
            rgb_matrix_set_color(LED_ENTER, RGB_BLACK);
            break;
        case _DRAW1: // on Fn layer select what the encoder does when pressed
            for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_FULL); i++) {
                rgb_matrix_set_color(LED_LIST_FULL[i], RGB_DRAW1);
            }
            rgb_matrix_set_color(LED_DIV, RGB_BLACK);
            rgb_matrix_set_color(LED_STAR, RGB_BLACK);
            rgb_matrix_set_color(LED_MINUS, RGB_LAYERCHANGE);
            break;
        case _DRAW2: // on Fn layer select what the encoder does when pressed
            for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_FULL); i++) {
                rgb_matrix_set_color(LED_LIST_FULL[i], RGB_BLACK);
            }
            rgb_matrix_set_color(LED_MINUS, RGB_LAYERCHANGE);
            rgb_matrix_set_color(LED_5, RGB_DRAW2);
            rgb_matrix_set_color(LED_6, RGB_DRAW2);
            rgb_matrix_set_color(LED_PLUS, RGB_DRAW2);
            rgb_matrix_set_color(LED_ENTER, RGB_DRAW2);
            rgb_matrix_set_color(LED_0, RGB_DRAW2);
            rgb_matrix_set_color(LED_NUM, RGB_DRAW2);
            for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_SIDES); i++) {
                rgb_matrix_set_color(LED_LIST_SIDES[i], RGB_DRAW2);
            }
            break;
    }
}