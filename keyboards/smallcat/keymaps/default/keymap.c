#include QMK_KEYBOARD_H

/* default generic keymap */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
              KC_W, KC_F, KC_P,                     KC_L, KC_U,    KC_Y,
        KC_A, KC_R, KC_S, KC_T, KC_G,         KC_M, KC_N, KC_E,    KC_I, KC_O,
              KC_Q, KC_C, KC_D,                     KC_H, KC_COMM, KC_DOT,
                       KC_TRNS, KC_SPC,    KC_BSPC, KC_ENT
    )
};

/* combo definitions */
const uint16_t PROGMEM combo_x[] = {KC_W, KC_F, COMBO_END};
const uint16_t PROGMEM combo_b[] = {KC_F, KC_P, COMBO_END};
const uint16_t PROGMEM combo_z[] = {KC_Q, KC_C, COMBO_END};
const uint16_t PROGMEM combo_v[] = {KC_C, KC_D, COMBO_END};
const uint16_t PROGMEM combo_j[] = {KC_L, KC_U, COMBO_END};
const uint16_t PROGMEM combo_k[] = {KC_H, KC_COMM, COMBO_END};
combo_t key_combos[] = {
    COMBO(combo_x, KC_X),
    COMBO(combo_b, KC_B),
    COMBO(combo_z, KC_Z),
    COMBO(combo_v, KC_V),
    COMBO(combo_j, KC_J),
    COMBO(combo_k, KC_K),
};
