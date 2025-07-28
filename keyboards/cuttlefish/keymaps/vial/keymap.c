#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
                     KC_W,        KC_F,        KC_P,        KC_G,      KC_J,    KC_L,        KC_Y,         KC_U,
        GUI_T(KC_A), ALT_T(KC_R), CTL_T(KC_S), SFT_T(KC_T), KC_D,      KC_H,    SFT_T(KC_N), RCTL_T(KC_E), ALT_T(KC_I), RGUI_T(KC_O),
        KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,      KC_K,    KC_M,        KC_COMM,      KC_DOT,      KC_SLSH,
                                  KC_ENT,      KC_TAB,      KC_SPC,    KC_BSPC, QK_GESC,     KC_DEL
    ),
};
