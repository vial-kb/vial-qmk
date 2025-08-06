#include QMK_KEYBOARD_H

#define KC_JAPANESE_EISUU KC_LNG2
#define KC_JAPANESE_KANA KC_LNG1

#define KC_JEIS KC_JAPANESE_EISUU
#define KC_JKAN KC_JAPANESE_KANA

#define MT_LGJE MT(MOD_LGUI, KC_JEIS)
#define MT_RAJK MT(MOD_RALT, KC_JKAN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
		KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    XXXXXXX, KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    XXXXXXX, XXXXXXX, KC_N,    KC_M,    XXXXXXX, KC_RSFT,
		KC_LCTL, MT_LGJE, KC_SPC,  KC_SPC,  MT_RAJK, KC_RCTL
	)
};