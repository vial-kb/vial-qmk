#include QMK_KEYBOARD_H

#define KC_JAPANESE_EISUU KC_LNG2
#define KC_JAPANESE_KANA KC_LNG1

#define KC_JEIS KC_JAPANESE_EISUU
#define KC_JKAN KC_JAPANESE_KANA

#define LT_L1ES LT(1, KC_ESC)
#define MT_LGJE MT(MOD_LGUI, KC_JEIS)
#define MT_RAJK MT(MOD_RALT, KC_JKAN)

#define KC_MUTE KC_KB_MUTE
#define KC_VOLM KC_KB_VOLUME_DOWN
#define KC_VOLP KC_KB_VOLUME_UP

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
		LT_L1ES, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    MO(2),   MO(3),
		KC_LCTL, MT_LGJE, KC_SPC,  MT_RAJK, KC_RCTL
	),

	[1] = LAYOUT(
		_______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,  _______,
		XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, _______,
		_______, _______, _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
		_______, _______, _______, _______, _______
	),

	[2] = LAYOUT(
		_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, _______, _______, _______, _______,
		KC_CAPS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_UP,   KC_DOWN, _______, _______, _______,
		_______, _______, _______, _______, _______, _______, KC_LEFT, KC_RGHT, XXXXXXX, KC_RSFT,
		_______, _______, _______, _______, _______
	),

	[3] = LAYOUT(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
		KC_CAPS, KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  _______,
		_______, KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  KC_MUTE, KC_VOLM, KC_VOLP, XXXXXXX,
		_______, _______, _______, _______, _______
	)
};