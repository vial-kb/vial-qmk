// Copyright 2025 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "rgb_matrix.h"
#include "riley.h"

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    led_t led_state = host_keyboard_led_state();

    if (led_state.caps_lock) {
        RGB rgb = hsv_to_rgb((HSV){0, 255, 255}); // Red
        rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);
    }

    if (led_state.scroll_lock) {
        RGB rgb = hsv_to_rgb((HSV){170, 255, 255}); // Blue
        rgb_matrix_set_color(1, rgb.r, rgb.g, rgb.b);
    }

    if (led_state.num_lock) {
        RGB rgb = hsv_to_rgb((HSV){85, 255, 255}); // Green
        rgb_matrix_set_color(2, rgb.r, rgb.g, rgb.b);
    }

    return true;
}

void keyboard_post_init_kb(void) {
    rgb_matrix_enable_noeeprom(); 
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(0, 0, 0);

    keyboard_post_init_user();
}