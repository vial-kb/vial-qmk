#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───────┐ ┌───┬───┐
     * │       │ │ < │ / │
     * │  Ent  │ ├───┼───┤
     * │       │ │ > │ * │
     * └───────┘ └───┴───┘
     * ┌───┬───┬───┐ ┌───┐
     * │ 7 │ 8 │ 9 │ │   │
     * ├───┼───┼───┤ │ + │
     * │ 5 │ 6 │ 7 │ │   │
     * ├───┼───┼───┤ ├───┤
     * │ 1 │ 2 │ 3 │ │ - │
     * ├───┼───┼───┤ ├───┤
     * │ALT│ 0 │ . │ │Bs │
     * └───┴───┴───┘ └───┘
     */

    [0] = LAYOUT_all(
        KC_PENT,          KC_LEFT, KC_PSLS,
                          KC_RGHT, KC_PAST,

        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6, 
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_LALT, KC_P0,   KC_PDOT, KC_BSPC
    ),
        /*
     * ┌───────┐ ┌───┬───┐
     * │       │ │ < │ / │
     * │  Ent  │ ├───┼───┤
     * │       │ │ > │ * │
     * └───────┘ └───┴───┘
     * ┌───┬───┬───┐ ┌───┐
     * │ 7 │ 8 │ 9 │ │   │
     * ├───┼───┼───┤ │ + │
     * │ 5 │ 6 │ 7 │ │   │
     * ├───┼───┼───┤ ├───┤
     * │ 1 │ 2 │ 3 │ │ - │
     * ├───┼───┼───┤ ├───┤
     * │ALT│ 0 │ . │ │Bs │
     * └───┴───┴───┘ └───┘
     */

    [1] = LAYOUT_all(
        KC_PENT,          KC_LEFT, KC_PSLS,
                          KC_RGHT, KC_PAST,

        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6, 
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_LALT, KC_P0,   KC_PDOT, KC_BSPC
    ),
        /*
     * ┌───────┐ ┌───┬───┐
     * │       │ │ < │ / │
     * │  Ent  │ ├───┼───┤
     * │       │ │ > │ * │
     * └───────┘ └───┴───┘
     * ┌───┬───┬───┐ ┌───┐
     * │ 7 │ 8 │ 9 │ │   │
     * ├───┼───┼───┤ │ + │
     * │ 5 │ 6 │ 7 │ │   │
     * ├───┼───┼───┤ ├───┤
     * │ 1 │ 2 │ 3 │ │ - │
     * ├───┼───┼───┤ ├───┤
     * │ALT│ 0 │ . │ │Bs │
     * └───┴───┴───┘ └───┘
     */

    [2] = LAYOUT_all(
        KC_PENT,          KC_LEFT, KC_PSLS,
                          KC_RGHT, KC_PAST,

        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6, 
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_LALT, KC_P0,   KC_PDOT, KC_BSPC
    ),
        /*
     * ┌───────┐ ┌───┬───┐
     * │       │ │ < │ / │
     * │  Ent  │ ├───┼───┤
     * │       │ │ > │ * │
     * └───────┘ └───┴───┘
     * ┌───┬───┬───┐ ┌───┐
     * │ 7 │ 8 │ 9 │ │   │
     * ├───┼───┼───┤ │ + │
     * │ 5 │ 6 │ 7 │ │   │
     * ├───┼───┼───┤ ├───┤
     * │ 1 │ 2 │ 3 │ │ - │
     * ├───┼───┼───┤ ├───┤
     * │ALT│ 0 │ . │ │Bs │
     * └───┴───┴───┘ └───┘
     */

    [3] = LAYOUT_all(
        KC_PENT,          KC_LEFT, KC_PSLS,
                          KC_RGHT, KC_PAST,

        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6, 
        KC_P1,   KC_P2,   KC_P3,   KC_PMNS,
        KC_LALT, KC_P0,   KC_PDOT, KC_BSPC
    )
};
