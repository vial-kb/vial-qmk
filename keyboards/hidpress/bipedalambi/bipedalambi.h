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

// Layout macro for the Left Side (29 keys) based on Raw Data
// Renamed to LAYOUT_bipedalambi to avoid QMK data-driven conflict
#define LAYOUT_bipedalambi( \
    k03, \
    k02, k04, \
    k00, k01, k05, \
    k13, \
    k12, k14, \
    k10, k11, k15, k07, \
    k23, \
    k22, k24, \
    k20, k21, k25, k26, k27, k36, k37, \
    k33, \
    k32, k34, \
    k31, k35, k17 \
) { \
    { k00, k01, k02, k03, k04, k05, KC_NO, k07 }, \
    { k10, k11, k12, k13, k14, k15, KC_NO, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26,   k27 }, \
    { KC_NO, k31, k32, k33, k34, k35, k36,   k37 } \
}
