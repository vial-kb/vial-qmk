#pragma once

#include "quantum.h"

// Define pointing device modes if not already defined in quantum
enum pointing_device_mode {
    MODE_MOUSE,
    MODE_SCROLLING,
    MODE_CUSTOM_KEYS,
    MODE_COUNT  // Keeps track of the total number of modes
};

#define ACTUATION_DISPLAY_DURATION 1000  // Show actuation bar for 1 second

extern enum pointing_device_mode current_mode;
extern int actuation;
extern bool showing_actuation;
extern uint32_t actuation_display_timer;

void register_oled_activity(void);

// Unified layout macro for both halves (54 keys)
// Left keys (L_) → rows 0-3, Right keys (R_) → rows 4-7
#define LAYOUT_bipedalambi( \
    L03, L02, L04, L00, L01, L05, \
    L13, L12, L14, L10, L11, L15, L07, \
    L23, L22, L24, L20, L21, L25, L26, L27, L36, L37, \
    L33, L32, L34, L31, L35, L17, \
    R03, R04, R02, R05, R01, R00, \
    R13, R14, R12, R15, R11, R10, \
    R23, R24, R22, R26, R25, R21, R20, \
    R36, R33, R34, R32, R35, R31 \
) { \
    { L00, L01, L02, L03, L04, L05, KC_NO, L07 }, \
    { L10, L11, L12, L13, L14, L15, KC_NO, L17 }, \
    { L20, L21, L22, L23, L24, L25, L26,   L27 }, \
    { KC_NO, L31, L32, L33, L34, L35, L36, L37 }, \
    { R00, R01, R02, R03, R04, R05, KC_NO, KC_NO }, \
    { R10, R11, R12, R13, R14, R15, KC_NO, KC_NO }, \
    { R20, R21, R22, R23, R24, R25, R26,   KC_NO }, \
    { KC_NO, R31, R32, R33, R34, R35, R36, KC_NO } \
}
