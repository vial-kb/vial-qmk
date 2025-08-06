#include QMK_KEYBOARD_H

#define KC_JAPANESE_EISUU KC_LNG2
#define KC_JAPANESE_KANA KC_LNG1

#define KC_JEIS KC_JAPANESE_EISUU
#define KC_JKAN KC_JAPANESE_KANA

#define LT_L1TB LT(1, KC_TAB)
#define LT_L2ES LT(2, KC_ESC)
#define LT_L4EN LT(4, KC_ENT)
#define MT_LGJE MT(MOD_LGUI, KC_JEIS)
#define MT_RAJK MT(MOD_RALT, KC_JKAN)

#define LS_MINS LSFT(KC_MINS)
#define LS_EQL LSFT(KC_EQL)
#define LS_BSLS LSFT(KC_BSLS)
#define LS_GRV LSFT(KC_GRV)
#define LS_LBRC LSFT(KC_LBRC)
#define LS_RBRC LSFT(KC_RBRC)
#define LS_SCLN LSFT(KC_SCLN)
#define LS_QUOT LSFT(KC_QUOT)
#define LS_COMM LSFT(KC_COMM)
#define LS_DOT LSFT(KC_DOT)
#define LS_SLSH LSFT(KC_SLSH)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[0] = LAYOUT(
		LT_L2ES, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
		LT_L1TB, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    LT_L4EN,
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    MO(5),   MO(3),
		KC_LCTL, MT_LGJE, KC_SPC,  MT_RAJK, KC_RCTL
	),

	[1] = LAYOUT(
		KC_LSFT, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, _______, _______, KC_MINS, KC_EQL,  KC_BSLS, KC_GRV,
		XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, _______,
		_______, _______, _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
		_______, _______, _______, _______, _______
	),

	[2] = LAYOUT(
		XXXXXXX, _______, _______, _______, _______, _______, _______, _______, LS_MINS, LS_EQL,  LS_BSLS, LS_GRV,
		XXXXXXX, _______, _______, _______, _______, _______, LS_LBRC, LS_RBRC, LS_SCLN, LS_QUOT, _______,
		_______, _______, _______, _______, _______, _______, LS_COMM, LS_DOT,  LS_SLSH, _______,
		_______, _______, _______, _______, _______
	),

	[3] = LAYOUT(
		_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
		_______, _______, _______, _______, _______, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_QUOT, KC_RSFT,
		_______, _______, _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_SLSH, XXXXXXX,
		_______, _______, _______, _______, _______
	),

	[4] = LAYOUT(
		_______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), _______,
		_______, _______, _______, _______, _______, _______, LS_LBRC, LS_RBRC, LS_SCLN, LS_QUOT, XXXXXXX,
		_______, _______, _______, _______, _______, _______, LS_COMM, LS_DOT,  LS_SLSH, XXXXXXX,
		_______, _______, _______, _______, _______
	),

	[5] = LAYOUT(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______, _______, _______, _______, _______, _______, _______,
		_______, KC_F5,   KC_F6,   KC_F7,   KC_F8,   _______, _______, _______, _______, _______, _______,
		_______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, XXXXXXX, _______,
		_______, _______, _______, _______, _______
	)
};