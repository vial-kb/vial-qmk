/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers {
    MAC_BASE,
    WIN_BASE,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: MAC_BASE
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Mut│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │Bsp│Mut│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │LShift │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RSh│ ↑ │Del│
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│Opt│Cmd│   │     Space         │FN1│FN3│ ← │ ↓ │ → │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     */
    [MAC_BASE] = LAYOUT_ansi_66(
        KC_MUTE,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_BSPC,  KC_MUTE,
        KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_DEL,
        KC_LCTL,  KC_LOPT,  KC_LCMD,  XXXXXXX,  KC_SPC,                       KC_SPC,             MO(_FN1), MO(_FN3), KC_LEFT,  KC_DOWN,  KC_RGHT),

    /* Layer 1: WIN_BASE
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Mut│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │Bsp│Mut│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Esc│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │ \ │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │Cap│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │ Enter │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │LShift │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │RSh│ ↑ │Del│
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│Win│Alt│   │     Space         │FN2│FN3│ ← │ ↓ │ → │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     */
    [WIN_BASE] = LAYOUT_ansi_66(
        KC_MUTE,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_BSPC,  KC_MUTE,
        KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,
        KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_DEL,
        KC_LCTL,  KC_LGUI,  KC_LALT,  XXXXXXX,  KC_SPC,                       KC_SPC,             MO(_FN2), MO(_FN3), KC_LEFT,  KC_DOWN,  KC_RGHT),

    /* Layer 2: _FN1 (Mac Function Layer)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │BrD│BrU│MCt│LPd│RGB│   │Prv│Ply│Nxt│Mut│VoD│VoU│   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ ` │RMD│RMI│   │   │   │   │   │   │   │Ins│PgU│Hom│   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │   │SPD│SPI│   │   │   │   │   │   │   │PgD│End│       │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │       │HUD│HUI│SAD│SAI│VAD│VAI│NKR│   │   │Del│   │   │   │
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │                   │   │   │   │   │   │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     */
    [_FN1] = LAYOUT_ansi_66(
        _______,  KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_TOG,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,
        KC_GRV,   RGB_RMOD, RGB_MOD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_INS,   KC_PGUP,  KC_HOME,  _______,
        _______,  RGB_SPD,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PGDN,  KC_END,   _______,
        _______,  RGB_HUD,  RGB_HUI,  RGB_SAD,  RGB_SAI,  RGB_VAD,  RGB_VAI,  NK_TOGG,  _______,  _______,  KC_DEL,   _______,  _______,  _______,
        _______,  _______,  _______,  XXXXXXX,  _______,                      _______,            _______,  _______,  _______,  _______,  _______),

    /* Layer 3: _FN2 (Windows Function Layer)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │BrD│BrU│App│PSc│RGB│   │Prv│Ply│Nxt│Mut│VoD│VoU│   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ ` │RMD│RMI│   │   │   │   │   │   │Scr│Ins│PgU│Hom│   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │   │SPD│SPI│   │   │   │   │   │   │   │PgD│End│       │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │       │HUD│HUI│SAD│SAI│VAD│VAI│NKR│   │   │Del│   │   │   │
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │                   │   │   │   │   │   │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     */
    [_FN2] = LAYOUT_ansi_66(
        _______,  KC_BRID,  KC_BRIU,  KC_APP,   KC_PSCR,  RGB_TOG,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,
        KC_GRV,   RGB_RMOD, RGB_MOD,  _______,  _______,  _______,  _______,  _______,  _______,  KC_SCRL,  KC_INS,   KC_PGUP,  KC_HOME,  _______,
        _______,  RGB_SPD,  RGB_SPI,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  KC_PGDN,  KC_END,   _______,
        _______,  RGB_HUD,  RGB_HUI,  RGB_SAD,  RGB_SAI,  RGB_VAD,  RGB_VAI,  NK_TOGG,  _______,  _______,  KC_DEL,   _______,  _______,  _______,
        _______,  _______,  _______,  XXXXXXX,  _______,                      _______,            _______,  _______,  _______,  _______,  _______),

    /* Layer 4: _FN3 (Universal F-key Layer)
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │   │F1 │F2 │F3 │F4 │F5 │F6 │F7 │F8 │F9 │F10│F11│F12│   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ ~ │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┴───┤
     * │   │   │   │   │   │   │   │   │   │   │   │   │       │
     * ├───┴───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┬───┼───┐
     * │       │   │   │   │   │   │   │   │   │   │   │   │   │   │
     * ├───┬───┼───┼───┼───┴───┴───┴───┴───┼───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │                   │   │   │   │   │   │
     * └───┴───┴───┴───┴───────────────────┴───┴───┴───┴───┴───┘
     */
    [_FN3] = LAYOUT_ansi_66(
        _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,
        KC_TILD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  XXXXXXX,  _______,                      _______,            _______,  _______,  _______,  _______,  _______),
};

// clang-format on

/* Process user keycodes */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // No special processing needed for Vial-only build
    return true;
}

/* Encoder map for both knobs (positions 0,0 and 0,13) */
#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][2][2] = {
    [MAC_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1]     = { ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_FN2]     = { ENCODER_CCW_CW(KC_BRID, KC_BRIU), ENCODER_CCW_CW(KC_BRID, KC_BRIU) },
    [_FN3]     = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif