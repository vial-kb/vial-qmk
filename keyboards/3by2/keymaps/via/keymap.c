#include QMK_KEYBOARD_H

#define ____ KC_TRNS
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
       	KC_F13 , KC_F14 , KC_F15,
        KC_F16 , KC_F17 , KC_F18
    ),

    [1] = LAYOUT(
        ____, ____, ____,
        ____, ____, ____
    ),

    [2] = LAYOUT(
        ____, ____, ____,
        ____, ____, ____
    ),

    [3] = LAYOUT(
        ____, ____, ____,
        ____, ____, ____ 
    ),

};