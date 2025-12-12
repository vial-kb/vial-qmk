/* Copyright 2020 Alexander Tulloh
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"
#include <math.h>
#include "picot_o44.h"
#include "wait.h"
#include "debug.h"
#include <stdio.h>
#include "pointing_device.h"
extern const pointing_device_driver_t pointing_device_driver;


// Invert vertical scroll direction
#ifndef COCOT_SCROLL_INV_DEFAULT
#    define COCOT_SCROLL_INV_DEFAULT true
#endif

#ifndef COCOT_CPI_OPTIONS
#    define COCOT_CPI_OPTIONS { 200, 400, 800, 1600, 3200 }
#    ifndef COCOT_CPI_DEFAULT
#       define COCOT_CPI_DEFAULT 3
#    endif
#endif
#ifndef COCOT_CPI_DEFAULT
#    define COCOT_CPI_DEFAULT 3
#endif

#ifndef COCOT_SCROLL_DIVIDERS
#    define COCOT_SCROLL_DIVIDERS { 1, 2, 3, 4, 5, 6 }
#    ifndef COCOT_SCROLL_DIV_DEFAULT
#       define COCOT_SCROLL_DIV_DEFAULT 4
#    endif
#endif
#ifndef COCOT_SCROLL_DIV_DEFAULT
#    define COCOT_SCROLL_DIV_DEFAULT 4
#endif


#ifndef COCOT_ROTATION_ANGLE
#    define COCOT_ROTATION_ANGLE { -90, -75, -60, -45, -30, -15, 0, 15, 30, 45, 60, 75, 90 }
#    ifndef COCOT_ROTATION_DEFAULT
#       define COCOT_ROTATION_DEFAULT 3
#    endif
#endif
#ifndef COCOT_ROTATION_DEFAULT
#    define COCOT_ROTATION_DEFAULT 3
#endif
#ifndef COCOT_AUTO_MOUSE_MODE
#    define COCOT_AUTO_MOUSE_MODE true
#endif





cocot_config_t cocot_config;
uint16_t cpi_array[] = COCOT_CPI_OPTIONS;
uint16_t scrl_div_array[] = COCOT_SCROLL_DIVIDERS;
uint16_t angle_array[] = COCOT_ROTATION_ANGLE;
#define CPI_OPTION_SIZE (sizeof(cpi_array) / sizeof(uint16_t))
#define SCRL_DIV_SIZE (sizeof(scrl_div_array) / sizeof(uint16_t))
#define ANGLE_SIZE (sizeof(angle_array) / sizeof(uint16_t))


void pointing_device_init_kb(void) {
    // set the CPI.
    pointing_device_set_cpi(cpi_array[cocot_config.cpi_idx]);
    cocot_config.raw = eeconfig_read_kb();
    eeconfig_update_kb(cocot_config.raw);
    //set_auto_mouse_layer(4);
    set_auto_mouse_enable(cocot_config.auto_mouse);
}



report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    static float x_accumulator = 0.0;
    static float y_accumulator = 0.0;
    static float prev_x = 0.0, prev_y = 0.0;

    float sensitivity = 0.5;           // Movement sensitivity
    float smoothing_factor = 0.7;     // Smoothing factor
    float sensitivity_multiplier = 1.5; // Base sensitivity multiplier

    // Apply rotation angle adjustment
    double rad = angle_array[cocot_config.rotation_angle] * (M_PI / 180) * -1;
    float rotated_x = -(mouse_report.x * cos(rad) - mouse_report.y * sin(rad)); // Reverse X-direction
    float rotated_y = mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    // Apply smoothing to the rotated values
    float smoothed_x = prev_x * smoothing_factor + rotated_x * (1.0 - smoothing_factor);
    float smoothed_y = prev_y * smoothing_factor + rotated_y * (1.0 - smoothing_factor);
    prev_x = smoothed_x;
    prev_y = smoothed_y;

    // Calculate the magnitude of movement
    float movement_magnitude = sqrt(smoothed_x * smoothed_x + smoothed_y * smoothed_y);

    // Dynamic multiplier: slower for small movements, faster for large
    float dynamic_multiplier = 1.0 + movement_magnitude / 10.0; // Adjust divisor for desired scaling
    dynamic_multiplier = fmin(fmax(dynamic_multiplier, 0.5), 3.0); // Clamp between 0.5 and 3.0

    // Apply dynamic multiplier to smoothed values
    smoothed_x *= sensitivity_multiplier * dynamic_multiplier;
    smoothed_y *= sensitivity_multiplier * dynamic_multiplier;

    // Scroll mode handling
    if (cocot_get_scroll_mode()) {
        static int h_acm = 0, v_acm = 0;

        // Determine scroll direction
        if (abs((int)smoothed_x) > abs((int)smoothed_y)) {
            smoothed_y = 0; // Horizontal scroll
        } else {
            smoothed_x = 0; // Vertical scroll
        }

        // Accumulate scroll values
        if (cocot_config.scrl_inv) {
            h_acm += smoothed_x;
            v_acm -= smoothed_y;
        } else {
            h_acm -= smoothed_x;
            v_acm += smoothed_y;
        }

        // Calculate scroll values with division factor
        int8_t h_scroll = h_acm >> scrl_div_array[cocot_config.scrl_div];
        int8_t v_scroll = v_acm >> scrl_div_array[cocot_config.scrl_div];

        // Apply scroll to mouse report
        if (h_scroll != 0) {
            mouse_report.h += h_scroll;
            h_acm -= h_scroll << scrl_div_array[cocot_config.scrl_div];
        }
        if (v_scroll != 0) {
            mouse_report.v += v_scroll;
            v_acm -= v_scroll << scrl_div_array[cocot_config.scrl_div];
        }

        // Reset X/Y movement in scroll mode
        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        // Movement smoothing and accumulation for normal mode
        x_accumulator += smoothed_x * sensitivity;
        y_accumulator += smoothed_y * sensitivity;

        if (fabs(x_accumulator) >= 1.0) {
            mouse_report.x = (int8_t)x_accumulator;
            x_accumulator -= mouse_report.x;
        } else {
            mouse_report.x = 0;
        }

        if (fabs(y_accumulator) >= 1.0) {
            mouse_report.y = (int8_t)y_accumulator;
            y_accumulator -= mouse_report.y;
        } else {
            mouse_report.y = 0;
        }
    }

    return pointing_device_task_user(mouse_report);
}



bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    // xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    
    if (!process_record_user(keycode, record)) return false;

    switch (keycode) {
        #ifndef MOUSEKEY_ENABLE
                // process KC_MS_BTN1~8 by myself
                // See process_action() in quantum/action.c for details.
                case KC_MS_BTN1 ... KC_MS_BTN8: {
                    extern void register_button(bool, enum mouse_buttons);
                    register_button(record->event.pressed, MOUSE_BTN_MASK(keycode - KC_MS_BTN1));
                    return false;
                }
        #endif
        //*
        case AM_TOG:
            if(record->event.pressed) { // key down
                //auto_mouse_layer_off(); // disable target layer if needed
                cocot_config.auto_mouse ^= 1;
                eeconfig_update_kb(cocot_config.raw);
                set_auto_mouse_enable(cocot_config.auto_mouse);
                //auto_mouse_tg_off = !get_auto_mouse_enable();
            } // do nothing on key up
            return false; // prevent further processing of keycode            
    //*/
    }
    
    if (keycode == CPI_SW && record->event.pressed) {
        cocot_config.cpi_idx = (cocot_config.cpi_idx + 1) % CPI_OPTION_SIZE;
        eeconfig_update_kb(cocot_config.raw);
        pointing_device_set_cpi(cpi_array[cocot_config.cpi_idx]);
    }

    if (keycode == SCRL_SW && record->event.pressed) {
        cocot_config.scrl_div = (cocot_config.scrl_div + 1) % SCRL_DIV_SIZE;
        eeconfig_update_kb(cocot_config.raw);
    }
    
    if (keycode == ROT_R15 && record->event.pressed) {
        cocot_config.rotation_angle = (cocot_config.rotation_angle + 1) % ANGLE_SIZE;
        eeconfig_update_kb(cocot_config.raw);
    }

    if (keycode == ROT_L15 && record->event.pressed) {
        cocot_config.rotation_angle = (ANGLE_SIZE + cocot_config.rotation_angle - 1) % ANGLE_SIZE;
        eeconfig_update_kb(cocot_config.raw);
    }

    if (keycode == SCRL_IN && record->event.pressed) {
        cocot_config.scrl_inv ^= 1;
        eeconfig_update_kb(cocot_config.raw);
    }

    if (keycode == SCRL_TO && record->event.pressed) {
        { cocot_config.scrl_mode ^= 1; }
    }

    if (keycode == SCRL_MO) {
        { cocot_config.scrl_mode ^= 1; }
    }

    return true;
}


layer_state_t layer_state_set_kb(layer_state_t state) {
    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        case 1 ... 2:
            //rgblight_sethsv_range(HSV_YELLOW, 0, 9);
            //cocot_set_scroll_mode(true);
            //state = remove_auto_mouse_layer(state, false);
            //set_auto_mouse_enable(false);
            break;
        case 3 ... 7:
            //rgblight_sethsv_range(HSV_CYAN, 0, 9);
            //cocot_set_scroll_mode(false);
            //set_auto_mouse_enable(true);
            break;
        default:
            //rgblight_sethsv_range(HSV_RED, 0, 9);
            cocot_set_scroll_mode(false);
            
            if (cocot_config.auto_mouse) {
                set_auto_mouse_enable(true);
            } else {
                //state = remove_auto_mouse_layer(state, false);
                set_auto_mouse_enable(false);
            }
            break;
        }
    //rgblight_set_effect_range( 9, 36);
  return state;
};



void eeconfig_init_kb(void) {
    cocot_config.cpi_idx = COCOT_CPI_DEFAULT;
    cocot_config.scrl_div = COCOT_SCROLL_DIV_DEFAULT;
    cocot_config.rotation_angle = COCOT_ROTATION_DEFAULT;
    cocot_config.scrl_inv = COCOT_SCROLL_INV_DEFAULT;
    cocot_config.scrl_mode = false;
    cocot_config.auto_mouse = COCOT_AUTO_MOUSE_MODE;
    eeconfig_update_kb(cocot_config.raw);
    eeconfig_init_user();
}


void matrix_init_kb(void) {
    // is safe to just read CPI setting since matrix init
    // comes before pointing device init.
    cocot_config.raw = eeconfig_read_kb();
    if (cocot_config.cpi_idx > CPI_OPTION_SIZE) // || cocot_config.scrl_div > SCRL_DIV_SIZE || cocot_config.rotation_angle > ANGLE_SIZE)
    {
        eeconfig_init_kb();
    }
    matrix_init_user();
}


bool cocot_get_scroll_mode(void) {
    return cocot_config.scrl_mode;
}

void cocot_set_scroll_mode(bool mode) {
    cocot_config.scrl_mode = mode;
}

