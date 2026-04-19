// Copyright 2026 Sarah Helmbrecht (@skhelmbrecht)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include <hal.h>
#include <string.h>

#define UNICORE_MAGIC_BOOT 0x9D5BCB2AUL
#define UNICORE_MAGIC_REG  (*(volatile uint32_t *)0x20004000)

void bootloader_jump(void) {
    UNICORE_MAGIC_REG = UNICORE_MAGIC_BOOT;
    NVIC_SystemReset();
}

void mcu_reset(void) {
    NVIC_SystemReset();
}

#ifdef RGB_MATRIX_ENABLE
static rgb_config_t current_rgb_matrix_config(void) {
    rgb_config_t config = {0};
    config.enable       = rgb_matrix_is_enabled() ? 1 : 0;
    config.mode         = rgb_matrix_get_mode();
    config.hsv          = rgb_matrix_get_hsv();
    config.speed        = rgb_matrix_get_speed();
    config.flags        = rgb_matrix_get_flags();
    return config;
}

led_config_t g_led_config = {{
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
    {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}
}, {
    {0, 0}
}, {
    LED_FLAG_INDICATOR
}};

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (!host_keyboard_led_state().caps_lock) {
        rgb_matrix_set_color(0, 0, 0, 0);
    } else {
        hsv_t hsv = rgb_matrix_get_hsv();
        rgb_t rgb = hsv_to_rgb(hsv);
        rgb_matrix_set_color(0, rgb.r, rgb.g, rgb.b);
    }

    return true;
}

void housekeeping_task_kb(void) {
    static rgb_config_t last_seen_config  = {0};
    static rgb_config_t last_saved_config = {0};
    static uint32_t     change_timer      = 0;
    static bool         initialized       = false;

    rgb_config_t config = current_rgb_matrix_config();

    if (!initialized) {
        last_seen_config  = config;
        last_saved_config = config;
        change_timer      = timer_read32();
        initialized       = true;
    } else if (memcmp(&config, &last_seen_config, sizeof(config)) != 0) {
        last_seen_config = config;
        change_timer     = timer_read32();
    } else if (memcmp(&config, &last_saved_config, sizeof(config)) != 0 && timer_elapsed32(change_timer) > 1000) {
        eeconfig_update_rgb_matrix(&config);
        last_saved_config = config;
    }

    housekeeping_task_user();
}
#endif
