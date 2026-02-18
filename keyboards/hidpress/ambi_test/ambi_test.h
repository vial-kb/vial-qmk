#pragma once

#include "quantum.h"

// Pointing device modes
enum pointing_device_mode {
    MODE_MOUSE,
    MODE_SCROLLING,
    MODE_CUSTOM_KEYS,
    MODE_COUNT
};

#define ACTUATION_DISPLAY_DURATION 1000

extern enum pointing_device_mode current_mode;
extern int actuation;
extern bool showing_actuation;
extern uint32_t actuation_display_timer;

void register_oled_activity(void);

// Unified layout: 24 left keys (rows 0-3) + 24 right keys (rows 4-7)
#define LAYOUT( \
    L00, L01, L02, L03, L04, L05, \
    L10, L11, L12, L13, L14, L15, \
    L20, L21, L22, L23, L24, L25, L26, \
    L31, L32, L33, L34, L35, \
    R00, R01, R02, R03, R04, R05, \
    R10, R11, R12, R13, R14, R15, \
    R20, R21, R22, R23, R24, R25, R26, \
    R31, R32, R33, R34, R35 \
) { \
    { L00,   L01,   L02,   L03,   L04,   L05,   KC_NO, KC_NO }, \
    { L10,   L11,   L12,   L13,   L14,   L15,   KC_NO, KC_NO }, \
    { L20,   L21,   L22,   L23,   L24,   L25,   L26,   KC_NO }, \
    { KC_NO, L31,   L32,   L33,   L34,   L35,   KC_NO, KC_NO }, \
    { R00,   R01,   R02,   R03,   R04,   R05,   KC_NO, KC_NO }, \
    { R10,   R11,   R12,   R13,   R14,   R15,   KC_NO, KC_NO }, \
    { R20,   R21,   R22,   R23,   R24,   R25,   R26,   KC_NO }, \
    { KC_NO, R31,   R32,   R33,   R34,   R35,   KC_NO, KC_NO } \
}
