// Copyright 2023 Dane Lipscombe (@dlip)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "os_detection.h"

enum custom_keycodes {
    KC_COMBO = SAFE_RANGE,
    KC_CUDO,
    KC_CCUT,
    KC_CCPY,
    KC_CPST,
};


enum mylayers {
    _BSE,
    _NNM,
    _MED,
    _SYS,
    _GM1,
    _GM2,
};

#define KC_SFT_C MT(MOD_LSFT, KC_C)
#define KC_ALT_R MT(MOD_LALT, KC_R)
#define KC_GUI_S MT(MOD_LGUI, KC_S)
#define KC_CTL_T MT(MOD_LCTL, KC_T)
#define KC_CAG_V LCAG_T(KC_V)
#define KC_CAG_SCLN LCAG_T(KC_SCLN)
#define KC_SFT_H MT(MOD_LSFT, KC_H)
#define KC_CTL_N MT(MOD_LCTL, KC_N)
#define KC_GUI_E MT(MOD_LGUI, KC_E)
#define KC_ALT_I MT(MOD_LALT, KC_I)
#define KC_SFT_A MT(MOD_LSFT, KC_A)

#define KC_MED MO(_MED)

#define KC_ALT_LFT MT(MOD_LALT, KC_LEFT)
#define KC_GUI_DWN MT(MOD_LGUI, KC_DOWN)
#define KC_CTL_RGT MT(MOD_LCTL, KC_RIGHT)
#define KC_SFT_END MT(MOD_LSFT, KC_END)
#define KC_CAG_PGDN LCAG_T(KC_PGDN)

#define KC_CAG_2 LCAG_T(KC_2)
#define KC_CTL_4 MT(MOD_LCTL, KC_4)
#define KC_GUI_5 MT(MOD_LGUI, KC_5)
#define KC_ALT_6 MT(MOD_LALT, KC_6)
#define KC_SFT_0 MT(MOD_LSFT, KC_0)

#define KC_SFT_UDO MT(MOD_LSFT, C(KC_Z))
#define KC_ALT_CUT MT(MOD_LALT, C(KC_X))
#define KC_GUI_CPY MT(MOD_LGUI, C(KC_C))
#define KC_CTL_PST MT(MOD_LCTL, C(KC_V))

#define KC_SFT_PSC MT(MOD_LALT, KC_PSCR)
#define KC_ALT_PRV MT(MOD_LALT, KC_MPRV)
#define KC_GUI_PLY MT(MOD_LGUI, KC_MPLY)
#define KC_CTL_NXT MT(MOD_LCTL, KC_MNXT)

#define KC_CTL_F4 MT(MOD_LCTL, KC_F4)
#define KC_GUI_F5 MT(MOD_LGUI, KC_F5)
#define KC_ALT_F6 MT(MOD_LALT, KC_F6)
#define KC_SFT_F10 MT(MOD_LSFT, KC_F10)

#define KC_SFT_BSPC MT(MOD_LSFT, KC_BSPC)
#define KC_NNM_TAB LT(_NNM, KC_TAB)
#define KC_MED_SPC MT(MOD_LSFT, KC_SPC)
#define KC_SYS MO(_SYS)
#define KC_GM1 TO(_GM1)
#define KC_GM2 MO(_GM2)
#define KC_BSE TO(_BSE)

#define KC_COMBO_SFT KC_SFT_BSPC
#define KC_COMBO_ALT1 KC_NNM_TAB
#define KC_COMBO_ALT2 KC_MED_SPC

#include "g/keymap_combo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BSE] = LAYOUT_split_3x5_3(
         KC_W,     KC_L,     KC_Y,     KC_P,       KC_B,             KC_Z,        KC_F,       KC_O,        KC_U,     KC_QUOT,
         KC_SFT_C, KC_ALT_R, KC_GUI_S, KC_CTL_T,   KC_G,             KC_M,        KC_CTL_N,   KC_GUI_E,    KC_ALT_I, KC_SFT_A,
         KC_Q,     KC_J,     KC_CAG_V, KC_D,       KC_K,             KC_X,        KC_H,       KC_CAG_SCLN, KC_COMMA, KC_DOT,
                             QK_BOOT,  KC_NNM_TAB, KC_MED_SPC,       KC_SFT_BSPC, KC_COMBO,   QK_REPEAT_KEY
    ),
    [_NNM] = LAYOUT_split_3x5_3(
         KC_GRV,      KC_ESC,     KC_UP,       KC_ENT,     KC_DEL,         KC_BSLS,  KC_7,     KC_8,     KC_9,     KC_SLSH,
         KC_SFT_BSPC, KC_ALT_LFT, KC_GUI_DWN,  KC_CTL_RGT, KC_LBRC,        KC_EQL,   KC_CTL_4, KC_GUI_5, KC_ALT_6, KC_SFT_0,
         KC_HOME,     KC_PGUP,    KC_CAG_PGDN, KC_SFT_END, KC_RBRC,        KC_MINUS, KC_1,     KC_CAG_2, KC_3,     KC_DOT,
                                  KC_TRNS,     KC_TRNS,    KC_SYS,         KC_TRNS,  KC_TRNS,  KC_TRNS
    ),
    [_MED] = LAYOUT_split_3x5_3(
         KC_CUDO,    KC_CCUT,    KC_CCPY,    KC_CPST,     KC_BTN1,        KC_NO,    KC_F7,     KC_F8,     KC_F9,     KC_F11,
         KC_SFT_PSC, KC_ALT_PRV, KC_GUI_PLY, KC_CTL_NXT,  KC_VOLU,        KC_NO,    KC_CTL_F4, KC_GUI_F5, KC_ALT_F6, KC_SFT_F10,
         C(KC_Z),    C(KC_X),    C(KC_C),    C(KC_V),     KC_VOLD,        KC_NO,    KC_F1,     KC_F2,     KC_F3,     KC_F12,
                                 QK_BOOT,    KC_SYS,      KC_TRNS,        KC_TRNS,  KC_TRNS,   KC_TRNS
    ),
    [_SYS] = LAYOUT_split_3x5_3(
         QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_GM1,  KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                         KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO
    ),
    [_GM1] = LAYOUT_split_3x5_3(
         KC_TAB,     KC_Q,       KC_W,       KC_E,        KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_LSFT,    KC_A,       KC_S,       KC_D,        KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_LCTL,    KC_Z,       KC_X,       KC_V,        KC_NO,        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                                 KC_NO,      KC_GM2,      KC_SPC,       KC_NO, KC_NO, KC_NO
    ),
    [_GM2] = LAYOUT_split_3x5_3(
         KC_RETN, KC_4,  KC_5,  KC_6,  KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_ESC,  KC_1,  KC_2,  KC_3,  KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
         KC_BSE,  KC_7,  KC_8,  KC_9,  KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                         KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO
    ),
    // [_BLANK] = LAYOUT_split_3x5_3(
    //      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //                    KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO
    // ),
};

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SFT_BSPC:
            return 0;
        case KC_MED_SPC:
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_SFT_BSPC:
        case KC_NNM_TAB:
            return true;
        default:
            return false;
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_COMBO:
            if (record->event.pressed) {
                switch(detected_host_os()) {
                    case OS_MACOS:
                        tap_code16(A(KC_BSPC));
                        break;
                    default:
                        tap_code16(C(KC_BSPC));
                        break;
                }
            }
            break;
        case KC_CUDO:
            if (record->event.pressed) {
                switch(detected_host_os()) {
                    case OS_MACOS:
                        tap_code16(G(KC_Z));
                        break;
                    default:
                        tap_code16(C(KC_Z));
                        break;
                }
            }
            break;
        case KC_CCUT:
            if (record->event.pressed) {
                switch(detected_host_os()) {
                    case OS_MACOS:
                        tap_code16(G(KC_X));
                        break;
                    default:
                        tap_code16(C(KC_X));
                        break;
                }
            }
            break;
        case KC_CCPY:
            if (record->event.pressed) {
                switch(detected_host_os()) {
                    case OS_MACOS:
                        tap_code16(G(KC_C));
                        break;
                    default:
                        tap_code16(C(KC_C));
                        break;
                }
            }
            break;
        case KC_CPST:
            if (record->event.pressed) {
                switch(detected_host_os()) {
                    case OS_MACOS:
                        tap_code16(G(KC_V));
                        break;
                    default:
                        tap_code16(C(KC_V));
                        break;
                }
            }
            break;
    }

    return true;
};
