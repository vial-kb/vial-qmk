/* Copyright 2022 Jan Lindblom (@janlindblom)
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
#include "keymap_swedish.h"
#include "sendstring_swedish.h"

enum layer_names {
    _BASE = 0,
    _LOWER,
    _RAISE,
    _ADJUST,
};

enum custom_keycodes {
    SK_NOT_EQL = SAFE_RANGE,
    SK_LEQ,
    SK_GEQ,
};

enum unicode_names {
    NDASH,
    MDASH,
};

const uint32_t PROGMEM unicode_map[] = {
    [NDASH] = 0x2013,
    [MDASH] = 0x2014,
};

// Some defines for the keys below
#define CK_ESC LT(2, KC_ESC)
#define CK_BSPC LCTL_T(KC_BSPC)
#define CK_ENT1 LT(1, KC_ENT)
#define CK_DEL LALT_T(KC_DEL)
#define CK_ENT2 LT(2, KC_ENT)
#define CK_TAB RALT_T(KC_TAB)
#define CK_ADIA RCTL_T(SE_ADIA)
#define CK_QUOT RSFT_T(SE_QUOT)
#define CK_SPC LGUI_T(KC_SPC)
#define CK_WRGT C(KC_RGHT)
#define CK_WLFT C(KC_LEFT)
// Unicode keys
#define K_NDASH X(NDASH)
#define K_MDASH X(MDASH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_rev41lp(
    CK_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,               KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,  SE_ARNG,
    CK_BSPC,  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,               KC_H,     KC_J,     KC_K,     KC_L,  SE_ODIA,  CK_ADIA,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,               KC_N,     KC_M,  SE_COMM,   SE_DOT,  SE_MINS,  CK_QUOT,
                                          CK_DEL,   CK_ENT1,  CK_SPC,   CK_ENT2,   CK_TAB
  ),

  [_LOWER] = LAYOUT_rev41lp(
 SK_NOT_EQL,  SE_EXLM,    SE_AT,  SE_LCBR,  SE_RCBR,   SE_PIPE,             SE_PND,  SE_EURO,  SE_QUES,  SE_SECT,  SE_CURR,  SE_DIAE,
     SK_LEQ,  SE_HASH,   SE_DLR,  SE_LPRN,  SE_RPRN,    SE_GRV,            SE_PLUS,  SE_MINS,  SE_SLSH,  SE_ASTR,  SE_PERC,  SE_DQUO,
     SK_GEQ,  SE_PERC,  SE_CIRC,  SE_LBRC,  SE_RBRC,   SE_ACUT,            SE_AMPR,   SE_EQL,  SE_SCLN,  SE_COLN,  SE_BSLS,  SE_TILD,
                                            _______,   _______,  SE_LABK,  _______,  SE_RABK
  ),

  [_RAISE] = LAYOUT_rev41lp(
    SE_SECT,     SE_1,     SE_2,     SE_3,     SE_4,     SE_5,                 SE_6,    SE_7,    SE_8,    SE_9,    SE_0,  KC_MPLY,
      KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,              KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_PGUP,  KC_VOLU,
      KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,   KC_F12,              CK_WLFT, CK_WRGT, KC_HOME,  KC_END, KC_PGDN,  KC_VOLD,
                                            KC_BSPC,  _______,  KC_ENT,  _______,  _______
  ),

  [_ADJUST] = LAYOUT_rev41lp(
    XXXXXXX,   XXXXXXX, XXXXXXX,   BL_OFF,   BL_DEC,   BL_TOGG,            BL_BRTG,   BL_INC,    BL_ON,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   XXXXXXX, XXXXXXX,  XXXXXXX,  XXXXXXX,   BL_STEP,            XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
    XXXXXXX,   UC_M_WC, UC_M_WI,  UC_M_MA,  UC_M_LN,   XXXXXXX,            QK_BOOT,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX,
                                               _______, _______, _______,  _______,  _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

// Custom send_string keys
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SK_NOT_EQL:
            if (record->event.pressed) {
                SEND_STRING("!=");
            }
            break;
        case SK_LEQ:
            if (record->event.pressed) {
                SEND_STRING("<=");
            }
            break;
        case SK_GEQ:
            if (record->event.pressed) {
                SEND_STRING(">=");
            }
            break;
    }
    return true;
}
