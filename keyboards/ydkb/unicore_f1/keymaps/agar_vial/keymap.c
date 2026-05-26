#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  {
    {KC_ESCAPE, KC_TAB, KC_Q, KC_W, KC_1, KC_2, KC_3, KC_E},
    {KC_Z, KC_LALT, KC_S, KC_LCTRL, KC_R, KC_LSHIFT, KC_A, KC_LCTRL},
    {KC_4, KC_R, KC_5, KC_T, KC_6, KC_7, KC_Y, KC_U},
    {KC_B, KC_G, KC_V, KC_C, KC_LGUI, KC_X, KC_F, KC_D},
    {KC_8, KC_I, KC_9, KC_0, KC_MINUS, KC_O, KC_P, KC_LBRACKET},
    {KC_L, KC_COMMA, KC_M, KC_SPACE, KC_N, KC_K, KC_J, KC_H},
    {KC_EQUAL, KC_BSLASH, KC_GRAVE, KC_RBRACKET, KC_BSPACE, KC_ENTER, KC_RSHIFT, KC_NO},
    {MO(1), KC_NO, KC_RALT, KC_RGUI, KC_SLASH, KC_DOT, KC_QUOTE, KC_SCOLON},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO}
  },
  {
    {KC_GRAVE, KC_CAPSLOCK, KC_TRNS, KC_UP, KC_1, KC_2, KC_3, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_VOLU, KC_TRNS, KC_NO, KC_TRNS, KC_VOLD, KC_TRNS},
    {KC_4, RGB_TOG, KC_5, RGB_MOD, KC_6, KC_7, KC_TRNS, KC_TRNS},
    {KC_TRNS, RGB_SAI, KC_TRNS, KC_CALC, KC_TRNS, KC_TRNS, RGB_HUI, KC_MUTE},
    {KC_8, KC_PSCREEN, KC_9, KC_0, KC_MINUS, KC_SCROLLLOCK, KC_PAUSE, KC_UP},
    {KC_HOME, KC_END, KC_TRNS, KC_TRNS, KC_TRNS, KC_KP_SLASH, KC_TRNS, RGB_VAI},
    {KC_EQUAL, KC_INSERT, KC_DELETE, KC_PAUSE, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO},
    {KC_TRNS, KC_NO, KC_TRNS, KC_TRNS, KC_DOWN, KC_PGDOWN, KC_RIGHT, KC_PGUP},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO}
  },
};

#include "led.h"
#include "rgblight.h"

extern uint8_t indicator_color_config[];
void rgb_extra_process(LED_TYPE *rgbled) {
    if ((indicator_color_config[1] & 1) == 1) { //disable Bottom RGB, set them to 0
        memset(&rgbled[PHY_INDICATOR_NUM], 0, RGBLED_NUM*3);
    }
}