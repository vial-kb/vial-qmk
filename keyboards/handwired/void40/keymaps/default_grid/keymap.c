#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RAISE,
    _LOWER,
    _ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Tab│ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │Bsp│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Esc│ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Sft│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │Sft│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Ctl│   │GUI│Alt│Lwr│Spc│Ent│Rse│ ← │ ↓ │ ↑ │ → │
     * └───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┴───┘
     */
    [_BASE] = LAYOUT_ortho_4x12(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,       KC_T,     KC_Y,     KC_U,       KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,       KC_G,     KC_H,     KC_J,       KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,       KC_B,     KC_N,     KC_M,       KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
        KC_LCTL, KC_NO,   KC_LGUI, KC_LALT, MO(_LOWER), KC_SPC,   KC_ENT,   MO(_RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT
    ),

    [_LOWER] = LAYOUT_ortho_4x12(
        KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_TRNS,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE,
        KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  KC_ENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MPLY, KC_TRNS,    KC_MPRV,    KC_VOLD, KC_VOLU, KC_MNXT
    ),

    [_RAISE] = LAYOUT_ortho_4x12(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_TRNS,
        KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, KC_ENT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY, KC_MPLY, KC_TRNS, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT
    ),

    [_ADJUST] = LAYOUT_ortho_4x12(
        KC_NO,    KC_NO,    RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  RGB_SAI,  RGB_SAD,  RGB_VAI,  RGB_VAD,  KC_NO, KC_DEL,
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, KC_NO,
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO, KC_NO,
        KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_TRNS,  KC_NO,    KC_NO,    KC_TRNS,  KC_NO,    KC_NO,    KC_NO, KC_NO
    )
};

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

/*
 * ROTARY ENCODER
 */

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [_LOWER] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [_RAISE] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [_ADJUST] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD)},
};
#endif
