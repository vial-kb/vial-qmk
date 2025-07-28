// Copyright 2022 Diego Palacios (@diepala)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY = 0,
    _DVORAK,
    _COLEMAK_DH,
    _NAV,
    _SYM,
    _MODS,
};

// Aliases for readability
#define QWERTY   DF(_QWERTY)
#define COLEMAK  DF(_COLEMAK_DH)
#define DVORAK   DF(_DVORAK)

#define SYM      MO(_SYM)
#define NAV      MO(_NAV)
#define MODS     MO(_MODS)

#define CTL_ESC  MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT  MT(MOD_LALT, KC_ENT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
      * Base Layer: QWERTY
      * ┌───┬───┬───┬───┬───┬───┐       ┌───┬───┬───┬───┬───┬───┐
      * │Tab│ Q │ W │ E │ R │ T │       │ Y │ U │ I │ O │ P │Bsp│
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Ctl│ A │ S │ D │ F │ G │       │ H │ J │ K │ L │ ; │ ' │
      * ├───┼───┼───┼───┼───┼───┤       ├───┼───┼───┼───┼───┼───┤
      * │Sft│ Z │ X │ C │ V │ B │       │ N │ M │ , │ . │ / │Sft│
      * └───┴───┴───┴───┴───┴───┘       └───┴───┴───┴───┴───┴───┘
      *               ┌───┐                   ┌───┐
      *               │GUI├───┐           ┌───┤Alt│
      *               └───┤   ├───┐   ┌───┤   ├───┘
      *                   └───┤Bsp│   │Ent├───┘
      *                       └───┘   └───┘
      */
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        CTL_ESC, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, CTL_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                            KC_BSPC, ALT_ENT, NAV,              SYM, KC_SPC, MODS
    ),
     /*
      * Base Layer: Dvorak
      */
    [_DVORAK] = LAYOUT_split_3x6_3(
        KC_TAB, KC_QUOTE,  KC_COMM,  KC_DOT,   KC_P ,   KC_Y,                            KC_F,   KC_G ,  KC_C ,   KC_R ,  KC_L , KC_BSPC,
        CTL_ESC, KC_A ,  KC_S   ,  KC_D  ,   KC_F ,   KC_G,                               KC_D,   KC_H ,  KC_T ,   KC_N ,  KC_S , CTL_MINS,
        KC_LSFT, KC_Z ,  KC_X   ,  KC_C  ,   KC_V ,   KC_B,                               KC_B,   KC_M ,  KC_W ,   KC_V ,  KC_Z , KC_RSFT,
                                            KC_BSPC, ALT_ENT, NAV,              SYM, KC_SPC, MODS
    ),
     /*
     * Base Layer: Colemak DH
     */
    [_COLEMAK_DH] = LAYOUT_split_3x6_3(
        KC_TAB  , KC_Q ,  KC_W   ,  KC_F  ,   KC_P ,   KC_B,                               KC_J,   KC_L ,  KC_U ,   KC_Y ,KC_SCLN, KC_BSPC,
        CTL_ESC , KC_A ,  KC_R   ,  KC_S  ,   KC_T ,   KC_G,                               KC_M,   KC_N ,  KC_E ,   KC_I ,  KC_O , CTL_QUOT,
        KC_LSFT , KC_Z ,  KC_X   ,  KC_C  ,   KC_D ,   KC_V,                               KC_K,   KC_H ,KC_COMM, KC_DOT ,KC_SLSH, KC_RSFT,
                                            KC_BSPC, ALT_ENT, NAV,              SYM, KC_SPC, MODS
    ),
     /*
      * Nav Layer: Fn, navigation
      */
    [_NAV] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_F9 ,  KC_F10,  KC_F11,  KC_F12,   KC_TRNS,                               KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, KC_DEL,
        KC_TRNS, KC_F5 ,  KC_F6 ,  KC_F7 ,  KC_F8,    KC_TRNS,                               KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, KC_INS,
        KC_TRNS, KC_F1 ,  KC_F2 ,  KC_F3 ,  KC_F4,    KC_TRNS,                               KC_PAUSE, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_PSCR,
                                            KC_TRNS, KC_TRNS, KC_TRNS,          KC_RGUI, KC_RALT, KC_TRNS
    ),
     /*
      * Symboles
      */
    [_SYM] = LAYOUT_split_3x6_3(
        KC_GRV ,   KC_1 ,   KC_2 ,   KC_3 ,   KC_4 ,   KC_5,                                 KC_6 ,   KC_7 ,   KC_8 ,   KC_9 ,   KC_0 , KC_EQL,
        KC_TILD , KC_EXLM,  KC_AT , KC_HASH,  KC_DLR, KC_PERC,                               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PLUS,
        KC_PIPE , KC_BSLS, KC_COLN, KC_SCLN, KC_MINS, KC_LBRC,                               KC_RBRC, KC_UNDS, KC_COMM,  KC_DOT, KC_SLSH, KC_QUES,
                                            KC_CAPS, KC_LCBR, KC_RCBR,          KC_TRNS, KC_TRNS, KC_TRNS
    ),
     /*
      * Layer for mods
      */
    [_MODS] = LAYOUT_split_3x6_3(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,                              KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, QWERTY,
        KC_TRNS, KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT,    KC_TRNS,                              KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, DVORAK,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,    KC_TRNS,                               KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS, COLEMAK,
                                            KC_QUOTE, KC_CIRC, KC_SCLN,          KC_TRNS, KC_TRNS, KC_TRNS
    )
};

