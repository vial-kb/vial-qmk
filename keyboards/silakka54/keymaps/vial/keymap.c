// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "qmk_settings.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                                            KC_LGUI, MO(1), KC_SPC,           KC_ENT,  KC_RCTL,  KC_RALT
    ),
    [1] = LAYOUT(
        KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                              KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_PGUP, KC_PGDN, KC_HOME, KC_END,  KC_DEL,  KC_F12,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LBRC, KC_RBRC,
        KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                            KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS,  KC_TRNS,  KC_TRNS
    )
};

static bool is_home_row_mod_tap_key(uint16_t keycode) {
    switch (get_tap_keycode(keycode)) {
        case KC_A:
        case KC_S:
        case KC_D:
        case KC_F:
        case KC_J:
        case KC_K:
        case KC_L:
        case KC_SCLN:
            return true;
    }

    return false;
}

static bool is_home_row_ctrl_tap_key(uint16_t keycode) {
    switch (get_tap_keycode(keycode)) {
        case KC_D:
        case KC_K:
            return true;
    }

    return false;
}

static bool is_thumb_key_position(keyrecord_t *record) {
    switch (record->event.key.row) {
        case 4:
            return record->event.key.col >= 3 && record->event.key.col <= 5;
        case 9:
            return record->event.key.col >= 3 && record->event.key.col <= 5;
    }

    return false;
}

uint16_t get_flow_tap_term(uint16_t keycode, keyrecord_t *record, uint16_t prev_keycode) {
    if (is_home_row_mod_tap_key(keycode)) {
        return 0;
    }

    if (is_flow_tap_key(keycode) && is_flow_tap_key(prev_keycode)) {
#ifdef QMK_SETTINGS
        return QS.flow_tap_term;
#else
        return FLOW_TAP_TERM;
#endif
    }

    return 0;
}

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
#ifdef QMK_SETTINGS
    if (!QS_tapping_chordal_hold) {
        return true;
    }
#endif

    if (is_thumb_key_position(tap_hold_record)) {
        return true;
    }

    if (is_home_row_ctrl_tap_key(tap_hold_keycode)) {
        return true;
    }

    return get_chordal_hold_default(tap_hold_record, other_record);
}
