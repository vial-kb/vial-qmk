#include QMK_KEYBOARD_H

#define LAYOUT_mf17( \
    k00, k01, k02, k03, \
    k10, k11, k12, k13, \
    k20, k21, k22, k23, \
    k30, k31, k32, k33, \
    k40, k41, k42, k43 \
) { \
    { k00, k01, k02, k03 }, \
    { k10, k11, k12, k13 }, \
    { k20, k21, k22, k23 }, \
    { k30, k31, k32, k33 }, \
    { k40, k41, k42, k43 }  \
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_mf17(
        KC_NUM_LOCK,    KC_PSLS,    KC_PAST,    LT(1, KC_PMNS),
        KC_P7,          KC_P8,      KC_P9,      KC_NO,
        KC_P4,          KC_P5,      KC_P6,      KC_PPLS,
        KC_P1,          KC_P2,      KC_P3,      KC_NO,
        KC_NO,          KC_P0,      KC_PDOT,    KC_PENT),
    [1] = LAYOUT_mf17(
        KC_TRNS,    KC_CALCULATOR,  KC_BSPC,    KC_TRNS,
        RM_NEXT,    RM_VALU,        RM_HUEU,    KC_NO,
        RM_SPDD,    RM_TOGG,        RM_SPDU,    QK_BOOTLOADER,
        RM_PREV,    RM_VALD,        RM_HUED,    KC_NO,
        KC_NO,      KC_TRNS,        KC_TRNS,    KC_TRNS),
};
