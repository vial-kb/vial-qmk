// Copyright 2022 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "config_common.h"

#define SERIAL_USART_FULL_DUPLEX    // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0     // USART TX pin
#define SERIAL_USART_RX_PIN GP1     // USART RX pin
#define SERIAL_USART_PIN_SWAP       // Swap TX and RX pins if keyboard is master halve.
#define SELECT_SOFT_SERIAL_SPEED 0  // Sped: 460800 baud :)
#define USB_VBUS_PIN GP19           // for rp2040 | When USB_VBUS_PIN is not defined, SPLIT_USB_DETECT is used.
#define SPLIT_LED_STATE_ENABLE      // sync host leds (caps lock, ...)
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSPORT_MIRROR

// #define POINTING_DEVICE_TASK_THROTTLE_MS 4

#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE

#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_EFFECT_BREATHING + 2
#define RGBLIGHT_DEFAULT_HUE 152
#define RGBLIGHT_DEFAULT_SAT 232
#define RGBLIGHT_DEFAULT_VAR 255
#define RGBLIGHT_DEFAULT_SPD 2

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

