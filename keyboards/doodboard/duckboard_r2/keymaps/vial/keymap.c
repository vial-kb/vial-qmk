/* Copyright 2022 doodboard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
                 TG(1),   KC_PSLS, KC_PAST, KC_PMNS,
                 KC_7,    KC_8,    KC_9,    KC_PPLS,
                 KC_4,    KC_5,    KC_6,    KC_PPLS,
        KC_MUTE, KC_1,    KC_2,    KC_3,    KC_ENT,
        KC_BSPC, KC_0,    KC_0,    KC_DOT,  KC_ENT),

    [1] = LAYOUT(
                 TG(1),   KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_HOME, KC_UP,   KC_PGUP, KC_TRNS,
                 KC_LEFT, KC_TRNS, KC_RGHT, KC_TRNS,
        KC_TRNS, KC_END,  KC_DOWN, KC_PGDN, KC_TRNS,
        TG(2),   KC_TRNS, KC_INS,  KC_DEL,  KC_TRNS),

    [2] = LAYOUT(
                 KC_TRNS, RGB_TOG, RGB_MOD, KC_TRNS,
                 RGB_HUI, RGB_SAI, RGB_VAI, KC_TRNS,
                 RGB_HUD, RGB_SAD, RGB_VAD, KC_TRNS,
        RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        TG(2),   RESET,   KC_TRNS, KC_TRNS, KC_TRNS),

    [3] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [4] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [5] = LAYOUT(
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
#define XX NO_LED

led_config_t g_led_config = { 
    {
        // Key Matrix to LED Index
        { XX, 7,  XX, 6,  XX },
        { 0,  XX, XX, XX, 5  },
        { XX, XX, XX, XX, XX },
        { 1,  XX, XX, XX, 4  },
        { XX, 2,  XX, 3,  XX } 
    }, {
        // LED Index to Physical Position
        { 0, 16 }, { 0, 48 }, { 56, 64 }, { 168, 64 }, { 224, 48 }, {  224, 16 }, { 168, 0 }, { 56, 0 }
    }, {
        // LED Index to Flag
        2, 2, 2, 2, 2, 2, 2, 2
    } 
};
#endif
