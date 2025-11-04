// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

//#define SERIAL_USART_FULL_DUPLEX
//#define SERIAL_USART_RX_PIN GP2
//#define SERIAL_USART_TX_PIN GP1
//#define USE_SERIAL
//#define SOFT_SERIAL_PIN GP1
//#define USB_VBUS_PIN GP2

/* RP2040- and hardware-specific config */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64
