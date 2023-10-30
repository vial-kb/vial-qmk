#include "sun20pro.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        TG(1), KC_PSLS, KC_PAST, KC_PMNS, KC_MUTE,
        KC_7,  KC_8,    KC_9,
        KC_4,  KC_5,    KC_6,    KC_PPLS,
        KC_1,  KC_2,    KC_3,
        KC_0,  KC_DOT,  KC_PENT),

    LAYOUT(
        _______, _______, _______, _______, _______,
        KC_HOME, KC_UP,   KC_PGUP,
        KC_LEFT, KC_NO,   KC_RGHT, _______,
        KC_END,  KC_DOWN, KC_PGDN,
        KC_INS,  KC_DEL,  _______)

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(_______, _______) }
};
#endif
