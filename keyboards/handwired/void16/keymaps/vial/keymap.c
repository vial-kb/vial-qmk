#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │ 7 │ 8 │ 9 │ BS│
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ESC│
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │TAB│
     * ├───┼───┼───┼───┤
     * │FN │ 0 │ . │RET│
     * └───┴───┴───┴───┘
     */
    [_BASE] = LAYOUT_ortho_4x4(
        KC_P7,    KC_P8,  KC_P9,    KC_BSPC,
        KC_P4,    KC_P5,  KC_P6,    KC_ESC,
        KC_P1,    KC_P2,  KC_P3,    KC_TAB,
        TT(_FN1), KC_P0,  KC_PDOT,  KC_ENTER
    ),

    [_FN1] = LAYOUT_ortho_4x4(
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS
    ),

    [_FN2] = LAYOUT_ortho_4x4(
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS
    ),

    [_FN3] = LAYOUT_ortho_4x4(
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,
        KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS
    )
};

/*
 * ROTARY ENCODER
 */

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN)},
    [_FN1] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_FN2] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_FN3] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
};
#endif
