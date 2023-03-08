#include QMK_KEYBOARD_H


#define _BASE 0
#define _RAISE 1
#define _LOWER 2
#define _ADJUST 3

// Fillers to make layering more clear

#define ____ KC_TRNS

#define SFT_ESC  SFT_T(KC_ESC)
#define CTL_BSPC CTL_T(KC_BSPC)
#define ALT_SPC  ALT_T(KC_SPC)
#define SFT_ENT  SFT_T(KC_ENT)

#define KC_ML KC_MS_LEFT
#define KC_MR KC_MS_RIGHT
#define KC_MU KC_MS_UP
#define KC_MD KC_MS_DOWN
#define KC_MB1 KC_MS_BTN1
#define KC_MB2 KC_MS_BTN1

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BASE] = LAYOUT( \
    KC_ESC,  KC_Q,  KC_W,   KC_E,   KC_R,   KC_T,           KC_Y,   KC_U,   KC_I,    KC_O,   KC_P,    KC_BSPC,   \
    KC_TAB,  KC_A,  KC_S,   KC_D,   KC_F,   KC_G,           KC_H,   KC_J,   KC_K,    KC_L,   KC_SCLN, KC_QUOT,   \
    KC_LSFT, KC_Z,  KC_X,   KC_C,   KC_V,   KC_B,           KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLSH, KC_BSLASH, \
                    KC_GRV, KC_HYPR,                                        KC_LBRC, KC_RBRC,                    \
                                    KC_LCTL, _______,       _______, KC_RALT,                                    \
                                    KC_DEL,  RAISE,         LOWER,  KC_PGUP,                                     \
                                    KC_LGUI, KC_SPC,        KC_ENT, KC_PGDN                                      \
),

[_LOWER] = LAYOUT(
    KC_ESC,  KC_EXLM, KC_AT,  KC_HASH, KC_DLR,   KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN,  KC_RPRN, KC_BSPC, \
    KC_TAB,  KC_CAPS, KC_INS, KC_HOME, KC_END,   KC_PSCR,   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_MINS, KC_EQL,  \
    KC_LSFT, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, _______,   _______, _______, _______, _______,  KC_UNDS, KC_PLUS, \
                      _______, _______,                                       KC_LCBR, KC_RCBR,                    \
                                        _______, _______,   _______, _______,                                      \
                                        _______, ADJUST,    _______, _______,                                      \
                                        _______, _______,   RESET,   _______                                       \
),

[_RAISE] = LAYOUT(
    
    KC_ESC,  KC_1,   KC_2,    KC_3,    KC_4,   KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
    KC_TAB, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, _______,          _______, _______, _______, _______, _______, _______, \
    KC_LSFT, KC_F1,  KC_F2,   KC_F3,   KC_F4,  KC_F5,            KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
                      _______, _______,                                            KC_F11,  KC_F12,                    \
                                        _______, _______,   _______, _______,                                          \
                                        _______, _______,   ADJUST,  C(KC_RIGHT),                                      \
                                        _______, RESET,     _______, C(KC_LEFT)                                        \
),

[_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, \
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, _______, _______,          _______, KC_VOLD, KC_MUTE, KC_VOLU, _______, _______, \
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, _______, _______,          _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, \
                      _______, _______,                                     _______, _______,                            \
                                        _______, _______,   _______, _______,                                            \
                                        _______, _______,   _______, _______,                                            \
                                        _______, _______,   _______, _______                                             \
)
};
