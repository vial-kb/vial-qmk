// Copyright 2022 Copyright 2023 Pedro Quaresma <pedro.quaresma@gmail.com>
// With special thanks to Markus Knutsson <markus.knutsson@tweety.se>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off

#define LAYOUT_via(             \
      k17,     k15,    k16,     \
    k23,k22, k19,k18, k21,k20,  \
     k00, k01, k02, k03, k04,   \
     k05, k06, k07, k08, k09,   \
     k10, k11, k12, k13, k14    \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k20, k21, k22, k23 } \
}

#define U_LTESC LT(1, KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_via(
            KC_HOME,           KC_MUTE,           KC_MPLY,
        KC_PGUP, KC_PGDN,  KC_VOLD, KC_VOLU,  KC_MPRV, KC_MNXT,
             KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
             U_LTESC, KC_TAB,  KC_SPC,  KC_BSPC, KC_ENT
    ),
    [1] = LAYOUT_via(
            RGB_M_P,           RGB_M_B,           RGB_M_R,
        RM_HUED, RM_HUEU,  RM_SATD, RM_SATU,  RM_VALD, RM_VALU,
             RM_NEXT, RM_HUEU, RM_SATU, RM_VALU, RM_SPDU,
             RM_PREV,RM_HUED, RM_SATD, RM_VALD, RM_SPDD,
             KC_TRNS, RM_TOGG, RGB_M_P, RGB_M_B, RGB_M_R
    ),
};

// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },
    [1] = { ENCODER_CCW_CW(RM_HUED, RM_HUEU), ENCODER_CCW_CW(RM_SATD, RM_SATU), ENCODER_CCW_CW(RM_VALD, RM_VALU) }
};
#endif
