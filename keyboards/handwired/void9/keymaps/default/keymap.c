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
     * ┌───┬───┬───┐
     * │ 7 │ 8 │ 9 │
     * ├───┼───┼───┤
     * │ 4 │ 5 │ 6 │
     * ├───┼───┼───┤
     * │ 1 │ 2 │ 3 │
     * └───┴───┴───┘
     */
    [_BASE] = LAYOUT_ortho_3x3(
        KC_7,       KC_8,       KC_9,
        KC_4,       KC_5,       KC_6,
        KC_1,       KC_2,       KC_3
    ),

    [_FN1] = LAYOUT_ortho_3x3(
        KC_7,       KC_8,       KC_9,
        KC_4,       KC_5,       KC_6,
        KC_1,       KC_2,       KC_3
    ),

    [_FN2] = LAYOUT_ortho_3x3(
        KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_TRNS,       KC_TRNS,       KC_TRNS
    ),

    [_FN3] = LAYOUT_ortho_3x3(
        KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_TRNS,       KC_TRNS,       KC_TRNS,
        KC_TRNS,       KC_TRNS,       KC_TRNS
    )
};

/*
 * ROTARY ENCODER
 */

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] =   { ENCODER_CCW_CW(KC_MS_WH_UP, KC_MS_WH_DOWN),   ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [_FN1] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI),               ENCODER_CCW_CW(RGB_SAD, RGB_SAI)  },
    [_FN2] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),               ENCODER_CCW_CW(RGB_SPD, RGB_SPI)  },
    [_FN3] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),               ENCODER_CCW_CW(KC_RIGHT, KC_LEFT) },
};
#endif
