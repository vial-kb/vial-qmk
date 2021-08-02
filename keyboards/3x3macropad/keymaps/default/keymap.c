#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT( \
  KC_1,       KC_2,      KC_3,       \
  KC_4,       KC_5,      KC_6,       \
  KC_7,       KC_8,      LT(1, KC_9) \
),

[1] = LAYOUT( \
  KC_ESC,   KC_PLUS, KC_MINS, \
  KC_ENTER, KC_ASTR, KC_SLSH, \
  KC_0,     KC_DOT,  KC_TRNS  \
)

};
