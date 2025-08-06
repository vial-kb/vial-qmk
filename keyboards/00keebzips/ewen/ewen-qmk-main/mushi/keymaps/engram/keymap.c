// Copyright 2023 Dane Lipscombe (@dlip)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "os_detection.h"

enum custom_keycodes {
    KC_COMBO = SAFE_RANGE,
    KC_CALL,
    KC_CUDO,
    KC_CCUT,
    KC_CCPY,
    KC_CPST,
    KC_BSEN,
    KC_SEN,
    KC_MSCL,
    KC_GA1
};


enum mylayers {
    _BSE,
    _NAV,
    _NUM,
    _FUN,
    _MSE,
    _GA1,
    _GA2,
};

#define KC_SFT_C MT(MOD_LSFT, KC_C)
#define KC_ALT_I MT(MOD_LALT, KC_I)
#define KC_GUI_E MT(MOD_LGUI, KC_E)
#define KC_CTL_A MT(MOD_LCTL, KC_A)
#define KC_CAG_J LCAG_T(KC_J)
#define KC_CAG_M LCAG_T(KC_M)
#define KC_CTL_H MT(MOD_LCTL, KC_H)
#define KC_GUI_T MT(MOD_LGUI, KC_T)
#define KC_ALT_S MT(MOD_LALT, KC_S)
#define KC_SFT_N MT(MOD_LSFT, KC_N)

#define KC_SFT_Q MT(MOD_LSFT, KC_Q)
#define KC_ALT_QUO MT(MOD_LALT, KC_QUOTE)
#define KC_GUI_CMA MT(MOD_LGUI, KC_COMMA)
#define KC_CTL_DOT MT(MOD_LCTL, KC_DOT)
#define KC_CAG_LBC LCAG_T(KC_LBRC)
#define KC_CAG_2 LCAG_T(KC_2)
#define KC_CTL_4 MT(MOD_LCTL, KC_4)
#define KC_GUI_5 MT(MOD_LGUI, KC_5)
#define KC_ALT_6 MT(MOD_LALT, KC_6)
#define KC_SFT_0 MT(MOD_LSFT, KC_0)

#define KC_SFT_BSP MT(MOD_RSFT, KC_BSPC)
#define KC_ALT_DEL MT(MOD_LALT, KC_DEL)
#define KC_GUI_ESC MT(MOD_LGUI, KC_ESC)
#define KC_CTL_ENT MT(MOD_LCTL, KC_ENTER)
#define KC_CAG_NO LCAG_T(KC_NO)
#define KC_CTL_LFT MT(MOD_LCTL, KC_LEFT)
#define KC_GUI_DWN MT(MOD_LGUI, KC_DOWN)
#define KC_ALT_RGT MT(MOD_LALT, KC_RIGHT)
#define KC_SFT_PGD MT(MOD_LSFT, KC_PGDN)

#define KC_SFT_MUT MT(MOD_LSFT, KC_MUTE)
#define KC_ALT_PRV MT(MOD_LALT, KC_MPRV)
#define KC_GUI_PLY MT(MOD_LGUI, KC_MPLY)
#define KC_CTL_NXT MT(MOD_LCTL, KC_MNXT)
#define KC_CAG_BRD LCAG_T(KC_BRID)
#define KC_CAG_F2 LCAG_T(KC_F2)
#define KC_CTL_F4 MT(MOD_LCTL, KC_F4)
#define KC_GUI_F5 MT(MOD_LGUI, KC_F5)
#define KC_ALT_F6 MT(MOD_LALT, KC_F6)
#define KC_SFT_F10 MT(MOD_LSFT, KC_F10)

#define KC_FUN MO(_FUN)
#define KC_GA2 MO(_GA2)
#define KC_COMBO_SFT MT(MOD_LSFT, KC_BSPC)
#define KC_COMBO_ALT1 LT(_NUM, KC_TAB)
#define KC_COMBO_ALT2 LT(_NAV, KC_SPC)

#include "g/keymap_combo.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BSE] = LAYOUT_split_3x4_2(
         KC_B,     KC_Y,     KC_O,          KC_U,             KC_L,         KC_D,        KC_W,     KC_V,
         KC_SFT_C, KC_ALT_I, KC_GUI_E,      KC_CTL_A,         KC_CTL_H,     KC_GUI_T,    KC_ALT_S, KC_SFT_N,
         KC_G,     KC_X,     KC_CAG_J,      KC_K,             KC_R,         KC_CAG_M,    KC_F,     KC_P,
                             KC_COMBO_ALT1, KC_COMBO_ALT2,    KC_COMBO_SFT, KC_COMBO
    ),
    [_NUM] = LAYOUT_split_3x4_2(
         KC_GRV,       KC_SCLN,    KC_MINUS,   KC_EQUAL,      KC_7,       KC_8,     KC_9,     KC_BSLS,
         KC_SFT_Q,     KC_ALT_QUO, KC_GUI_CMA, KC_CTL_DOT,    KC_CTL_4,   KC_GUI_5, KC_ALT_6, KC_SFT_0,
         KC_Z,         KC_SPC,     KC_CAG_LBC, KC_RBRC,       KC_1,       KC_CAG_2, KC_3,     KC_SLSH,
                                   KC_TRNS,    KC_FUN,        KC_TRNS,    KC_TRNS
    ),
    [_NAV] = LAYOUT_split_3x4_2(
         KC_CUDO,      KC_CCUT,    KC_CCPY,    KC_CPST,       KC_HOME,    KC_UP,      KC_END,     KC_PGUP,
         KC_SFT_BSP,   KC_ALT_DEL, KC_GUI_ESC, KC_CTL_ENT,    KC_CTL_LFT, KC_GUI_DWN, KC_ALT_RGT, KC_SFT_PGD,
         KC_PSCR,      KC_NO,      KC_CAG_NO,  KC_NO,         KC_NO,      KC_CAG_NO,  KC_NO,      KC_NO,
                                   KC_FUN,     KC_TRNS,       KC_TRNS,    KC_TRNS
    ),
    [_FUN] = LAYOUT_split_3x4_2(
         QK_BOOT,    KC_NO,      KC_VOLD,     KC_VOLU,       KC_F7,     KC_F8,     KC_F9,     KC_F11,
         KC_SFT_MUT, KC_ALT_PRV, KC_GUI_PLY,  KC_CTL_NXT,    KC_CTL_F4, KC_GUI_F5, KC_ALT_F6, KC_SFT_F10,
         KC_GA1,     KC_NO,      KC_CAG_BRD,  KC_BRIU,       KC_F1,     KC_CAG_F2, KC_F3,     KC_F12,
                                 KC_TRNS,     KC_TRNS,       KC_TRNS,   KC_TRNS
    ),
    [_MSE] = LAYOUT_split_3x4_2(
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_BTN3, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_MSCL, KC_TRNS, KC_TRNS, KC_TRNS,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                           KC_TRNS, KC_TRNS,    KC_BTN1, KC_BTN2
    ),
    [_GA1] = LAYOUT_split_3x4_2(
         KC_TAB,  KC_Q,  KC_W,   KC_E,      KC_NO, KC_NO, KC_NO, KC_NO,
         KC_LSFT, KC_A,  KC_S,   KC_D,      KC_NO, KC_NO, KC_NO, KC_NO,
         KC_LCTL, KC_Z,  KC_X,   KC_C,     KC_NO, KC_NO, KC_NO, KC_NO,
                       KC_GA2, KC_SPC,    KC_NO, KC_NO
    ),
    [_GA2] = LAYOUT_split_3x4_2(
         KC_NO,  KC_7, KC_8,  KC_9,     KC_NO, KC_NO, KC_NO, KC_NO,
         KC_NO,  KC_4, KC_5,  KC_6,     KC_NO, KC_NO, KC_NO, KC_NO,
         KC_GA1, KC_1, KC_2,  KC_3,     KC_NO, KC_NO, KC_NO, KC_NO,
                       KC_NO, KC_NO,    KC_NO, KC_NO
    ),
    // [_BLANK] = LAYOUT_split_3x4_2(
    //      KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO,
    //      KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO,
    //      KC_NO, KC_NO, KC_NO, KC_NO,    KC_NO, KC_NO, KC_NO, KC_NO,
    //                    KC_NO, KC_NO,    KC_NO, KC_NO
    // ),
};

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_COMBO_SFT:
            return 0;
        case KC_COMBO_ALT2:
            return 0;
        default:
            return QUICK_TAP_TERM;
    }
}

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_COMBO_SFT:
        case KC_COMBO_ALT1:
            return true;
        default:
            return false;
    }
}

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
#ifdef POINTING_DEVICE_COMBINED
    // Hack to fix slave side being a lower sensitivity
    // if (!is_keyboard_master()) {
    //     pointing_device_set_cpi_on_side(is_keyboard_left(), PMW33XX_CPI + 1000);
    // }
    pointing_device_set_cpi_on_side(false, PMW33XX_CPI);
    pointing_device_set_cpi_on_side(true, PMW33XX_CPI * 2);
#endif
}

bool set_scrolling = false;
#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MSE); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
    set_auto_mouse_timeout(1000);

}
// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 100.0
#define SCROLL_DIVISOR_V 100.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
//     if (set_scrolling) {
//         mouse_report.h = mouse_report.x;
//         mouse_report.v = mouse_report.y;
//         mouse_report.x = 0;
//         mouse_report.y = 0;
//     }
//     return mouse_report;
// }
#endif

#ifdef POINTING_DEVICE_COMBINED
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    if (set_scrolling) {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)right_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)right_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        right_report.h = (int8_t)scroll_accumulated_h;
        right_report.v = -(int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        // Clear the X and Y values of the mouse report
        right_report.x = 0;
        right_report.y = 0;
    } else {
        // Calculate and accumulate scroll values based on mouse movement and divisors
        scroll_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (float)left_report.y / SCROLL_DIVISOR_V;

        // Assign integer parts of accumulated scroll values to the mouse report
        left_report.h = (int8_t)scroll_accumulated_h;
        left_report.v = -(int8_t)scroll_accumulated_v;

        // Update accumulated scroll values by subtracting the integer parts
        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;
    }

    // Clear the X and Y values of the mouse report
    left_report.x = 0;
    left_report.y = 0;
    return pointing_device_combine_reports(left_report, right_report);
}
#endif

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
                return false;
            }
            break;
        case KC_CALL:
            if (record->event.pressed) {
                switch(detected_host_os()) {
                    case OS_MACOS:
                        tap_code16(G(KC_A));
                        break;
                    default:
                        tap_code16(C(KC_A));
                        break;
                }
                return false;
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
                return false;
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
                return false;
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
                return false;
            }
            break;
        // case KC_CAG_CPY:
        //     if (record->tap.count && record->event.pressed) {
        //         switch(detected_host_os()) {
        //             case OS_MACOS:
        //                 tap_code16(G(KC_C));
        //                 break;
        //             default:
        //                 tap_code16(C(KC_C));
        //                 break;
        //         }
        //         return false;
        //     }
        //     break;
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
                return false;
            }
            break;
        case KC_SEN:
            if (record->event.pressed) {
                SEND_STRING(". ");
                set_oneshot_mods(MOD_BIT(KC_LSFT));
                return false;
            }
            break;
        case KC_BSEN:
            if (record->event.pressed) {
                SEND_STRING(SS_TAP(X_BSPC)". ");
                set_oneshot_mods(MOD_BIT(KC_LSFT));
                return false;
            }
            break;
        case KC_MSCL:
            if (record->event.pressed) {
                set_scrolling = true;
            } else {
                set_scrolling = false;
            }
            return false;
        case KC_GA1:
            if (record->event.pressed) {
                if (layer_state_is(_GA1)) {
                    layer_off(_GA1);
                } else {
                    layer_on(_GA1);
                }
                // Combos mess with game input
                combo_toggle();
                return false;
            }
            break;
    }

    return true;
};
