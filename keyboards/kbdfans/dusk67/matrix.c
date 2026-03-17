// Copyright 2026 Sarah Helmbrecht (@skhelmbrecht)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "matrix.h"
#include "gpio.h"
#include "timer.h"
#include <string.h>

#define SR_CLK_PIN  B12
#define SR_DATA_PIN B13

#define SR_TOTAL_POSITIONS 112
#define SR_GROUPS          14
#define SR_BITS_PER_GROUP  8

#define PRESS_THRESHOLD   0xC0
#define RELEASE_THRESHOLD 0x04

#define HOLDOFF_SCANS 15

static uint8_t integrator[SR_TOTAL_POSITIONS];
static uint8_t holdoff[SR_TOTAL_POSITIONS];
static uint8_t debounced[SR_GROUPS];
static uint16_t last_scan_time;

static inline void sr_clk_pulse(void) {
    gpio_write_pin_high(SR_CLK_PIN);
    gpio_write_pin_low(SR_CLK_PIN);
}

static inline void sr_data_out(void) {
    gpio_set_pin_output(SR_DATA_PIN);
}

static inline void sr_data_in(void) {
    gpio_set_pin_input_high(SR_DATA_PIN);
}

static inline bool sr_read(void) {
    return !gpio_read_pin(SR_DATA_PIN);
}

static void sr_load(void) {
    sr_data_out();
    gpio_write_pin_high(SR_DATA_PIN);

    for (uint8_t i = 0; i < SR_TOTAL_POSITIONS; i++) {
        sr_clk_pulse();
    }

    gpio_write_pin_low(SR_DATA_PIN);
    sr_clk_pulse();

    sr_data_in();
}

static void sr_advance(void) {
    sr_data_out();
    gpio_write_pin_high(SR_DATA_PIN);
    sr_clk_pulse();
    sr_data_in();
}

void matrix_init_custom(void) {
    gpio_set_pin_output(SR_CLK_PIN);
    gpio_write_pin_low(SR_CLK_PIN);
    sr_data_in();

    memset(integrator, 0, sizeof(integrator));
    memset(holdoff, 0, sizeof(holdoff));
    memset(debounced, 0, sizeof(debounced));
    last_scan_time = timer_read();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    uint16_t now = timer_read();
    if (now == last_scan_time) {
        return false;
    }
    last_scan_time = now;

    bool changed = false;

    sr_load();

    for (uint8_t group = 0; group < SR_GROUPS; group++) {
        for (uint8_t bit = 0; bit < SR_BITS_PER_GROUP; bit++) {
            uint8_t idx  = group * SR_BITS_PER_GROUP + bit;
            uint8_t mask = 1 << bit;

            uint8_t sample = sr_read() ? 0x80 : 0x00;
            integrator[idx] = sample | (integrator[idx] >> 1);
            sr_advance();
            if (holdoff[idx] != 0 && !(debounced[group] & mask)) {
                holdoff[idx]--;
            } else if (integrator[idx] >= PRESS_THRESHOLD) {
                debounced[group] |= mask;
                holdoff[idx] = HOLDOFF_SCANS;
            } else if (integrator[idx] < RELEASE_THRESHOLD) {
                debounced[group] &= ~mask;
            }
        }
    }

    for (uint8_t row = 0; row < SR_GROUPS; row++) {
        matrix_row_t new_row = debounced[row];
        if (current_matrix[row] != new_row) {
            current_matrix[row] = new_row;
            changed = true;
        }
    }

    return changed;
}
