#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_BASE] = LAYOUT(
        // Row 1
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y,             KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,

        // Row 2
        MO(_ADJUST), KC_A, KC_S, KC_D, KC_F, KC_G,              KC_MPLY, KC_H, KC_J, KC_K, KC_L, KC_QUOT, KC_ENT,

        // Row 3
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                  KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_RSFT,

        // Row 4
        KC_LCTL, MO(_RAISE), KC_LALT, MO(_LOWER),               KC_MUTE, KC_SPC, KC_RCTL, MO(_RAISE), KC_RALT
    ),

    [_LOWER] = LAYOUT(
        // Row 1
        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,             KC_6, KC_7, KC_8, KC_9, KC_0, KC_DEL,

        // Row 2
        _______, _______, _______, _______, _______, _______,   KC_LBRC, KC_RBRC, KC_EQL, KC_MINUS, _______, KC_SCLN, _______,

        // Row 3
        _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, KC_SLSH, _______,

        // Row 4
        _______, _______, _______, _______,                     _______, _______, _______, _______, _______
    ),

    [_RAISE] = LAYOUT(
        // Row 1
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,       KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,

        // Row 2
        _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______, _______,

        // Row 3
        _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, _______, _______,

        // Row 4
        _______, _______, _______, _______,                     _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT(
        // Row 1
        _______, _______, KC_UP, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______,

        // Row 2
        _______, KC_LEFT, KC_DOWN, KC_RIGHT, _______, _______,  _______, _______, _______, _______, _______, _______, _______,

        // Row 3
        _______, _______, _______, _______, _______, KC_DEL,    _______, _______, _______, _______, _______, _______,

        // Row 4
        _______, _______, _______, _______,                     _______, _______, _______, _______, _______
    )
};

#if defined(ENCODER_MAP_ENABLE)

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE]   = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_LOWER]  = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_RAISE]  = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_ADJUST] = { ENCODER_CCW_CW(KC_VOLU, KC_VOLD) }
};

#endif