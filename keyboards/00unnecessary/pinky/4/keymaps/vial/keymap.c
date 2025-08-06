/* Copyright 2018 'Masayuki Sunahara'
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
        KC_ESC , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_VOLU,    KC_MNXT, KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_BSPC,
        KC_GRV , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_VOLD,    KC_MPRV, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC,
        KC_TAB , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_MUTE,    KC_MPLY, KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_CALC,    KC_RGUI, KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,
                                   KC_LCTL, KC_LALT, MO(2)  , KC_SPC ,    KC_ENT , MO(1)  , KC_RALT, KC_RCTL
    ),
    [1] = LAYOUT(
        KC_GRV , KC_MPRV, KC_MPLY,    KC_MNXT,    LALT(KC_F4), _______, _______,    _______, KC_PSCR, _______, KC_PGUP, _______, KC_SCRL, KC_TRNS,
        KC_CAPS, _______, _______,    KC_PGUP,    _______,     _______, _______,    _______, KC_INS , KC_HOME, KC_UP  , KC_END , KC_NUM , _______,
        KC_TRNS, _______, LCTL(KC_X), LCTL(KC_C), LCTL(KC_V),  KC_BTN2, _______,    _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
        KC_TRNS, _______, _______,    KC_PGDN,    _______,     _______, _______,    _______, KC_CALC, KC_PGUP, KC_PGDN, KC_PGDN, KC_BRK , KC_TRNS,
                                      KC_TRNS,    KC_TRNS,     KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS, KC_F1  ,        KC_F2  ,    KC_F3  ,    KC_F4  ,    KC_F5  ,    _______,    _______, KC_F6  ,    KC_F7  ,    KC_F8  ,    KC_F9  ,    KC_F10 ,    KC_TRNS,
        KC_CAPS, LSFT(KC_1),     LSFT(KC_2), LSFT(KC_3), LSFT(KC_4), LSFT(KC_5), _______,    _______, LSFT(KC_6), LSFT(KC_7), LSFT(KC_8), LSFT(KC_9), LSFT(KC_0), KC_F11,
        KC_TRNS, KC_1   ,        KC_2   ,    KC_3   ,    KC_4   ,    KC_5   ,    _______,    _______, KC_6   ,    KC_7   ,    KC_8   ,    KC_9   ,    KC_0   ,    KC_F12,
        KC_TRNS, LSFT(KC_EQUAL), KC_MINUS,   KC_EQUAL,   KC_COMMA,   KC_DOT,     _______,    _______, KC_LBRC,    KC_RBRC,    KC_BSLS,    KC_DOT,     KC_SLSH,    KC_TRNS,
                                             KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS
    ),
    [3] = LAYOUT(
        KC_TRNS, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, KC_TRNS,
        KC_TRNS, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        KC_TRNS, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______,
        KC_TRNS, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, KC_TRNS,
                                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};
