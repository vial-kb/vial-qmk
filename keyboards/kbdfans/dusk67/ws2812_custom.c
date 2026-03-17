// Copyright 2026 Sarah Helmbrecht (@skhelmbrecht)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "ws2812.h"

#include "gpio.h"
#include "wait.h"
#include <hal.h>

/* Use the board-specific timing that was validated on hardware. */
#define T0H_NOPS "nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n"
#define T0L_NOPS "nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n nop\n"
#define T1H_NOPS T0L_NOPS
#define T1L_NOPS T0H_NOPS

static void ws2812_send_byte(uint8_t byte) {
    for (int8_t bit = 7; bit >= 0; bit--) {
        if (byte & (1 << bit)) {
            gpio_write_pin_high(WS2812_DI_PIN);
            __asm__ volatile(T1H_NOPS);
            gpio_write_pin_low(WS2812_DI_PIN);
            __asm__ volatile(T1L_NOPS);
        } else {
            gpio_write_pin_high(WS2812_DI_PIN);
            __asm__ volatile(T0H_NOPS);
            gpio_write_pin_low(WS2812_DI_PIN);
            __asm__ volatile(T0L_NOPS);
        }
    }
}

ws2812_led_t ws2812_leds[WS2812_LED_COUNT];

void ws2812_init(void) {
    gpio_set_pin_output(WS2812_DI_PIN);
    gpio_write_pin_low(WS2812_DI_PIN);
    wait_us(300);
}

void ws2812_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    ws2812_leds[index].r = red;
    ws2812_leds[index].g = green;
    ws2812_leds[index].b = blue;
#if defined(WS2812_RGBW)
    ws2812_rgb_to_rgbw(&ws2812_leds[index]);
#endif
}

void ws2812_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < WS2812_LED_COUNT; i++) {
        ws2812_set_color(i, red, green, blue);
    }
}

void ws2812_flush(void) {
    chSysLock();

    for (int i = 0; i < WS2812_LED_COUNT; i++) {
#if (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_GRB)
        ws2812_send_byte(ws2812_leds[i].g);
        ws2812_send_byte(ws2812_leds[i].r);
        ws2812_send_byte(ws2812_leds[i].b);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_RGB)
        ws2812_send_byte(ws2812_leds[i].r);
        ws2812_send_byte(ws2812_leds[i].g);
        ws2812_send_byte(ws2812_leds[i].b);
#elif (WS2812_BYTE_ORDER == WS2812_BYTE_ORDER_BGR)
        ws2812_send_byte(ws2812_leds[i].b);
        ws2812_send_byte(ws2812_leds[i].g);
        ws2812_send_byte(ws2812_leds[i].r);
#endif
#ifdef WS2812_RGBW
        ws2812_send_byte(ws2812_leds[i].w);
#endif
    }

    chSysUnlock();
    wait_us(300);
}
