#include QMK_KEYBOARD_H

#define KC_JAPANESE_EISUU KC_LNG2
#define KC_JAPANESE_KANA KC_LNG1

#define KC_JEIS KC_JAPANESE_EISUU
#define KC_JKAN KC_JAPANESE_KANA

#define LT_L1JE LT(1, KC_JEIS)
#define MT_LCJE MT(MOD_LGUI, KC_JEIS)
#define MT_RCJK MT(MOD_RGUI, KC_JKAN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSPC,
		LT_L1JE, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(2),
		KC_LCTL, KC_LOPT, MT_LCJE, KC_SPC,  MT_RCJK, KC_ROPT
	),

	[1] = LAYOUT(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
		_______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, KC_BSPC, _______, _______, _______, _______, _______, _______,
		XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_ENT,  KC_JKAN, _______, _______, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XXXXXXX,
		_______, _______, _______, _______, _______, _______
	),

	[2] = LAYOUT(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______,
		KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_RGHT, _______,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DOWN, _______, XXXXXXX,
		_______, _______, _______, _______, _______, _______
    )
};
