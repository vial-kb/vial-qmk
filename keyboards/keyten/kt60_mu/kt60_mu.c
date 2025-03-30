// Copyright 2025 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#define LEFT_LED_PIN A14
#define RIGHT_LED_PIN B11

typedef union {
    uint16_t raw;
    struct {
        uint16_t right_led: 3;
        uint16_t left_led: 3;
    };
} layout_options_t;

static layout_options_t layout_options;

static layer_state_t current_layer_state = 0;

void via_set_layout_options_kb(uint32_t value) {
    layout_options.raw = value;
    led_update_kb(host_keyboard_led_state());
}

enum led_mode_t {
    LED_MODE_OFF,
    LED_MODE_ON,
    LED_MODE_CAPS_LOCK,
    LED_MODE_NUM_LOCK,
    LED_MODE_SCROLL_LOCK,
    LED_MODE_LAYER_1,
    LED_MODE_LAYER_2,
    LED_MODE_LAYER_3,
};

void set_led_state(uint32_t pin, uint8_t mode, led_t led_state) {
    switch (mode) {
        case LED_MODE_OFF:
            gpio_write_pin_low(pin);
            break;
        case LED_MODE_ON:
            gpio_write_pin_high(pin);
            break;
        case LED_MODE_CAPS_LOCK:
            gpio_write_pin(pin, led_state.caps_lock);
            break;
        case LED_MODE_NUM_LOCK:
            gpio_write_pin(pin, led_state.num_lock);
            break;
        case LED_MODE_SCROLL_LOCK:
            gpio_write_pin(pin, led_state.scroll_lock);
            break;
        case LED_MODE_LAYER_1:
            gpio_write_pin(pin, (current_layer_state & (1 << 1)) != 0);
            break;
        case LED_MODE_LAYER_2:
            gpio_write_pin(pin, (current_layer_state & (1 << 2)) != 0);
            break;
        case LED_MODE_LAYER_3:
            gpio_write_pin(pin, (current_layer_state & (1 << 3)) != 0);
            break;
        default:
            gpio_write_pin_low(pin);
            break;
    }
}

void led_update_ports(led_t led_state) {
    gpio_set_pin_output(LEFT_LED_PIN);
    gpio_set_pin_output(RIGHT_LED_PIN);
  
    set_led_state(LEFT_LED_PIN, layout_options.left_led, led_state);
    set_led_state(RIGHT_LED_PIN, layout_options.right_led, led_state);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    current_layer_state = state;
    return current_layer_state;
}
