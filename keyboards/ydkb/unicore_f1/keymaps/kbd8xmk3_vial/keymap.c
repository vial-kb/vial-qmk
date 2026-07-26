#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = {
    {KC_ESCAPE, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7},
    {KC_GRAVE, KC_7, KC_6, KC_5, KC_4, KC_3, KC_2, KC_1},
    {KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_CAPSLOCK},
    {KC_LSHIFT, KC_H, KC_G, KC_F, KC_D, KC_S, KC_A, KC_NONUS_BSLASH},
    {KC_LCTRL, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_LALT, KC_LGUI},
    {KC_SPACE, KC_N, KC_M, KC_COMMA, KC_NO, KC_NO, KC_RALT, KC_RGUI},
    {KC_LEFT, KC_RCTRL, LT(1, KC_APPLICATION), KC_DOT, KC_SLASH, KC_RSHIFT, KC_KP_2, KC_UP},
    {KC_NO, KC_QUOTE, KC_SCOLON, KC_L, KC_K, KC_J, KC_ENTER, KC_NO},
    {KC_BSLASH, KC_U, KC_I, KC_O, KC_P, KC_LBRACKET, KC_RBRACKET, KC_DELETE},
    {KC_INSERT, KC_KP_1, KC_BSPACE, KC_EQUAL, KC_MINUS, KC_0, KC_9, KC_8},
    {KC_PSCREEN, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, KC_NO},
    {KC_END, KC_PGDOWN, KC_HOME, KC_PGUP, KC_SCROLLLOCK, KC_PAUSE, KC_DOWN, KC_RIGHT},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO}
  }, 
  [1] = {
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, RGB_MOD, KC_TRNS, KC_TRNS},
    {KC_TRNS, RGB_VAI, RGB_SAI, RGB_HUI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC, RGB_HUD, RGB_SAD, KC_TRNS, KC_TRNS},
    {KC_TRNS, RGB_VAD, KC_TRNS, KC_TRNS, KC_NO, KC_NO, KC_TRNS, KC_TRNS},
    {KC_MUTE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLU},
    {KC_NO, KC_TRNS, KC_TRNS, KC_TRNS, KC_CALC, KC_TRNS, KC_TRNS, KC_NO},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO},
    {KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD, KC_VOLU},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO},
    {KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO}
  }, 
};

#include "led.h"
#include "rgblight.h"
extern uint8_t indicator_color_config[3];
extern uint8_t indicator_state;
void rgb_extra_process(LED_TYPE *rgbled) {
    if (indicator_color_config[2] & 1) {
        if (indicator_state & 1) {
            for (uint8_t i=2; i<6; i++) {
                rgbled[i] = rgbled[0];
            }
        }
    }
}