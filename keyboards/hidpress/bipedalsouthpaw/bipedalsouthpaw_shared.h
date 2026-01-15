#pragma once

#include <stdint.h>
#include <stdbool.h>

// Declare the variables as extern
extern uint32_t actuation_display_timer;
extern bool showing_actuation;
extern int actuation;

// Keep the constant define here
#define ACTUATION_DISPLAY_DURATION 1000

enum pointing_device_mode {
    MODE_MOUSE,
    MODE_SCROLLING,
    MODE_CUSTOM_KEYS, // New mode for WASD keys
    MODE_COUNT // Keeps track of the total number of modes
};

extern enum pointing_device_mode current_mode;


enum layers {
    _DEFAULT,
    _ONE,
    _TWO,
    _THREE
};

// OLED screensaver activity tracking
void register_oled_activity(void);
