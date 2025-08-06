#include QMK_KEYBOARD_H

enum combo_events {
  COMBO_BSPC,
  COMBO_NUMBAK,
  COMBO_TAB,
  COMBO_ESC,
  COMBO_DEL,
  COMBO_QUES,
  COMBO_ENTER,
};

#define KC_CTSC RCTL_T(KC_SCLN)
#define LOWER_SPC LT(2, KC_SPC)
#define RASE_BACK LT(1, KC_BSPC)
#define SHFT_Z MT(MOD_LSFT, KC_Z)
#define SHIFT_SLASH MT(MOD_RSFT,KC_SLSH)
#define RASE_ENT LT(_RAISE, KC_ENT)
#define CTRL_A MT(MOD_LCTL,KC_A)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,     KC_O,   KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,     KC_L,   KC_BSPC,
        LSFT_T(KC_Z),    KC_X,    KC_C,    KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,  KC_DOT, RSFT_T(KC_ENT),
        MT(MOD_LGUI, KC_ESC), MT(MOD_LALT, KC_ENT), LT(2, KC_SPC),  KC_SPC, LT(1, KC_SPC),     KC_LSFT, MT(MOD_RSFT, KC_TAB)
    ),
    [1] = LAYOUT( /* NUM */
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        KC_MUTE, KC_VOLD, KC_VOLU, KC_COPY, KC_PSTE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_BSLS,
        KC_NO,   KC_GRV,  KC_F11,  KC_F12,  KC_NO,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DQUO,
        _______, _______, _______, _______, _______, _______, _______
    ),
    [2] = LAYOUT( /* SYM */
        KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
        KC_CAPS, KC_LGUI, KC_INS,  KC_DEL,  KC_BSPC, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_QUOT,
        _______, KC_LGUI, KC_ENT,  KC_SPC,  KC_BSPC, KC_SPC,  _______
    ),
};

#ifdef COMBO_ENABLE
const uint16_t PROGMEM combo_bspc[] = {KC_O, KC_P, COMBO_END};
const uint16_t PROGMEM combo_numbak[] = {KC_0, KC_9, COMBO_END};
const uint16_t PROGMEM combo_tab[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM combo_esc[] = {KC_E, KC_W, COMBO_END};
const uint16_t PROGMEM combo_del[] = {KC_MINS, KC_EQL, COMBO_END};
const uint16_t PROGMEM combo_ques[] = {KC_COMM, KC_M, COMBO_END};
const uint16_t PROGMEM combo_enter[] = {KC_K, KC_L, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [COMBO_BSPC] = COMBO(combo_bspc,KC_BSPC),
  [COMBO_NUMBAK] = COMBO(combo_numbak,KC_BSPC),
  [COMBO_TAB] = COMBO(combo_tab,KC_TAB),
  [COMBO_ESC] = COMBO(combo_esc,KC_ESC),
  [COMBO_DEL] = COMBO(combo_del,KC_DEL),
  [COMBO_QUES] = COMBO(combo_ques,KC_QUES),
  [COMBO_ENTER] = COMBO(combo_enter,KC_ENTER),
};
#endif
