#include QMK_KEYBOARD_H
#include <stdio.h>

enum layer_number {
    _FIRST = 0,
    _FN,
    _SECOND,
    _THIRD,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_FIRST] = LAYOUT(
    // ,-------+-------+-------|
                KC_A ,
    // |-------+-------+-------|
        KC_B   ,KC_C   ,KC_D
    // `-------+-------+-------'
    ),
    [_FN] = LAYOUT(
    // ,-------+-------+-------|
                KC_A ,
    // |-------+-------+-------|
        KC_B   ,KC_C   ,KC_D
    // `-------+-------+-------'
    ),
    [_SECOND] = LAYOUT(
    // ,-------+-------+-------|
                KC_A ,
    // |-------+-------+-------|
        KC_B   ,KC_C   ,KC_D
    // `-------+-------+-------'
    ),
    [_THIRD] = LAYOUT(
    // ,-------+-------+-------|
                KC_A ,
    // |-------+-------+-------|
        KC_B   ,KC_C   ,KC_D
    // `-------+-------+-------'
    ),
};

