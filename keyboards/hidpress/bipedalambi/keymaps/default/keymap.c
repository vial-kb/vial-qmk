#include QMK_KEYBOARD_H
#include "bipedalambi.h"

// Simple default keymap using the 29-key LAYOUT_bipedalambi macro
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_bipedalambi(
        KC_ESC,                       // k03 - Top center
        KC_1, KC_2,                   // k02, k04
        KC_Q, KC_W, KC_E,             // k00, k01, k05
        KC_R,                         // k13
        KC_A, KC_S,                   // k12, k14
        KC_TAB, KC_D, KC_F, KC_NO,    // k10, k11, k15, k07
        KC_T,                         // k23
        KC_Z, KC_X,                   // k22, k24
        KC_LSFT, KC_C, KC_V, KC_B, KC_SPC, KC_NO, KC_NO,  // k20, k21, k25, k26, k27, k36, k37
        KC_G,                         // k33
        KC_Y, KC_H,                   // k32, k34
        KC_N, KC_ENT, KC_NO           // k31, k35, k17
    ),
    [1] = LAYOUT_bipedalambi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_bipedalambi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_bipedalambi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
    } else {
        tap_code(KC_VOLD);
    }
    return true;
}
#endif
