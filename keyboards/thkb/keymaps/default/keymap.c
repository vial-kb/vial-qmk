/* Copyright 2021 RoastPotatoes
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN0,
    _FN1,
    _FN2
};

#define _BASE 0
#define _FN0 1
#define _FN1 2
#define _FN2 3

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
	 KC_TAB,  KC_Q,   KC_W,  KC_E,  KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC, \
         KC_LCTL, KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_ENT,  \
         KC_LSFT, KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_SLSH,KC_RSFT,MO(_FN0),  \
                     KC_LGUI,  KC_SPC,  KC_LALT,  MO(_FN1), MO(_FN2)
    ),
      /*
    * Keymap 1: FN Layer 0
    */
 [_FN0] =  LAYOUT(
         KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_TRNS,   KC_INS,     KC_HOME, KC_END,  KC_TRNS,    KC_TRNS,   KC_DEL, \
         KC_LCTL, KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_TRNS,   KC_LEFT,   KC_DOWN, KC_UP,   KC_RIGHT,  KC_ENT,  \
         KC_LSFT, KC_F9,   KC_F10,  KC_F11,  KC_F12,   KC_TRNS,   KC_PGDN,   KC_PGUP, KC_TRNS, KC_RSFT,   MO(_FN0),  \
                           KC_LGUI, KC_SPC,  KC_LALT,  MO(_FN1),  MO(_FN2)
    ),

   /*
    * Keymap 2: FN Layer 1
    */
[_FN1] =   LAYOUT(
         KC_LBRC, KC_1,   KC_2,    KC_3,    KC_4,     KC_5,     KC_6,     KC_7,    KC_8,    KC_9,     KC_0,   KC_RBRC, \
         KC_LCTL, KC_FN10, KC_FN11, KC_TRNS, KC_TRNS,  KC_GRV,  KC_MINS,  KC_EQL, KC_SCLN, KC_QUOT, KC_BSLS,  \
         KC_LSFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,  MO(_FN0),     \
                        KC_LGUI, KC_SPC,  KC_RALT,  KC_TRNS,  MO(_FN2)
    ),

   /*
    * Keymap 3: FN Layer 2
    */
[_FN2] =   LAYOUT(
         KC_NUMLOCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_7, KC_KP_8, KC_KP_9,  KC_COMM,   KC_BSPC, \
         KC_LCTL,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_PLUS,     KC_KP_MINUS, KC_KP_4, KC_KP_5, KC_KP_6,  KC_KP_ENTER,  \
         KC_LSFT,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_ASTERISK, KC_KP_SLASH, KC_KP_1, KC_KP_2, KC_KP_3,  MO(_FN0),     \
                           KC_LGUI, KC_SPC,  KC_RALT, KC_DOT, KC_KP_0
    ),
        };

}
