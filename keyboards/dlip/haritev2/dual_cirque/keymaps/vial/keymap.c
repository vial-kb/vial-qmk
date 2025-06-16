// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_5x6(
              KC_U,              KC_U,              KC_U,              KC_U,                    KC_U,              KC_U,              KC_U,              KC_U,
        KC_L, KC_C, KC_R,  KC_L, KC_C, KC_R,  KC_L, KC_C, KC_R,  KC_L, KC_C, KC_R,        KC_L, KC_C, KC_R,  KC_L, KC_C, KC_R,  KC_L, KC_C, KC_R,  KC_L, KC_C, KC_R,
              KC_D,              KC_D,              KC_D,              KC_D,                    KC_D,              KC_D,              KC_D,              KC_D,

                                                                       KC_U,                    KC_U,
                                                                 KC_L, KC_C, KC_R,        KC_L, KC_C, KC_R,
                                                                       KC_D,                    KC_D,

                                                                       KC_U,                    KC_U,
                                                                 KC_L, KC_C, KC_R,        KC_L, KC_C, KC_R,
                                                                       KC_D,                    KC_D
    )
};

// Modify these values to adjust the scrolling speed
#define SCROLL_DIVISOR_H 12.0
#define SCROLL_DIVISOR_V 12.0

// Variables to store accumulated scroll values
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

// Function to handle mouse reports and perform drag scrolling
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    // Calculate and accumulate scroll values based on mouse movement and divisors
    scroll_accumulated_h += (float)left_report.x / SCROLL_DIVISOR_H;
    scroll_accumulated_v += (float)-left_report.y / SCROLL_DIVISOR_V;

    // Assign integer parts of accumulated scroll values to the mouse report
    left_report.h = (int8_t)scroll_accumulated_h;
    left_report.v = (int8_t)scroll_accumulated_v;

    // Update accumulated scroll values by subtracting the integer parts
    scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
    scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

    // Clear the X and Y values of the mouse report
    left_report.x = 0;
    left_report.y = 0;
    return pointing_device_combine_reports(left_report, right_report);
}
