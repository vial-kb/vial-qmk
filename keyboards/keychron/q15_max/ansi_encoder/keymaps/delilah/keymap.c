/* Copyright 2024 @ Delilah
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
#include "d3lilah_qmk.h"

// Layer names for clarity
enum layers {
    MAC_BASE,
    MAC_FN1,
    MAC_FN2,
    LAYER_3,
    LAYER_4,
    LAYER_5,
    LAYER_6,
    LAYER_7
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Your custom base layout */
    [MAC_BASE] = LAYOUT_ansi_66(
        KC_MUTE, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC, KC_EQL,
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_UP,   KC_RSFT, KC_RSFT,
        G(KC_V), KC_LCTL, KC_LOPT, KC_LCMD, KC_BSPC,          KC_SPC,           MO(1),   KC_LEFT, KC_DOWN, KC_RGHT, MO(2)
    ),

    /* Layer 1: Function keys and media controls */
    [MAC_FN1] = LAYOUT_ansi_66(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
        KC_GRV,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, _______, _______, _______, _______, KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_DEL,
        RGB_TOG, RGB_MOD, RGB_VAI, RGB_HUI, RGB_SAI, RGB_SPI, _______, _______, _______, _______, _______, _______,          KC_INS,
        _______, RGB_RMOD,RGB_VAD, RGB_HUD, RGB_SAD, RGB_SPD, _______, _______, KC_MPRV, KC_MNXT, KC_MPLY, _______, KC_PGUP, _______,
        _______, _______, _______, _______, _______,          _______,          _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

    /* Layer 2: Your FN2 layer - customize as needed */
    [MAC_FN2] = LAYOUT_ansi_66(
        KC_TILD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, AC_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______,
        _______, _______, _______, _______, _______,          _______,          _______, _______, KC_MUTE, KC_VOLD, KC_MPLY
    ),

    /* Layer 3: Available for customization */
    [LAYER_3] = LAYOUT_ansi_66(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______
    ),

    /* Layer 4: Available for customization */
    [LAYER_4] = LAYOUT_ansi_66(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______
    ),

    /* Layer 5: Available for customization */
    [LAYER_5] = LAYOUT_ansi_66(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______
    ),

    /* Layer 6: Available for customization */
    [LAYER_6] = LAYOUT_ansi_66(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______
    ),

    /* Layer 7: Available for customization */
    [LAYER_7] = LAYOUT_ansi_66(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______
    )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [MAC_FN1]  = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [MAC_FN2]  = { ENCODER_CCW_CW(RGB_HUD, RGB_HUI) },
    [LAYER_3]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_4]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_5]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_6]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [LAYER_7]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif // ENCODER_MAP_ENABLE

// Process custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_d3lilah(keycode, record);
}

// Initialize autocorrect to be ON by default
void keyboard_post_init_user(void) {
    autocorrect_enable();
}