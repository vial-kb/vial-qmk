/* SPDX-License-Identifier: GPL-2.0-or-later
 *
 * BFS9000 — Keyboard-level firmware configuration
 * Copyright (C) 2026 jguillen-lab
 *
 * This file is part of the BFS9000 / Marquichuelo keyboard firmware.
 * It is distributed under the terms of the GNU General Public License
 * version 2 or later.
 */

#pragma once

/* ─────────────────────────────────────────────────────────────────────────────
 * SPLIT SERIAL TRANSPORT
 * ─────────────────────────────────────────────────────────────────────────────
 *
 * The BFS9000 is a split keyboard. These defines configure the serial link
 * used by QMK to exchange matrix state, LED state and user transactions between
 * the two halves.
 *
 * SERIAL_USART_FULL_DUPLEX
 *   Enables independent TX and RX wires instead of half-duplex communication.
 *
 * SERIAL_USART_TX_PIN / SERIAL_USART_RX_PIN
 *   RP2040 GPIO pins used by the serial transport.
 *
 * SERIAL_USART_PIN_SWAP
 *   Swaps the UART pin mapping when the selected peripheral/pin pair requires
 *   it. Keep this aligned with the PCB wiring.
 */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP16
#define SERIAL_USART_RX_PIN GP17
#define SERIAL_USART_PIN_SWAP

/* ─────────────────────────────────────────────────────────────────────────────
 * SPLIT SIDE DETECTION
 * ─────────────────────────────────────────────────────────────────────────────
 *
 * SPLIT_HAND_PIN tells QMK which GPIO is used to decide whether this half is
 * the left or right side. The electrical pull direction is defined by the PCB
 * wiring and the corresponding QMK split-hand configuration.
 */
#define SPLIT_HAND_PIN GP18

/* ─────────────────────────────────────────────────────────────────────────────
 * OLED I²C BUS
 * ─────────────────────────────────────────────────────────────────────────────
 *
 * The OLED display is connected to I²C1 on the RP2040.
 * These pins must match the PCB routing.
 */
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

/* ─────────────────────────────────────────────────────────────────────────────
 * OLED DISPLAY DEFAULTS
 * ─────────────────────────────────────────────────────────────────────────────
 *
 * Only compiled when OLED_ENABLE=yes is active in the keymap rules.
 *
 * OLED_DISPLAY_128X64
 *   Selects a 128×64 panel layout.
 *
 * OLED_TIMEOUT 0
 *   Keeps the display permanently on.
 *
 * OLED_UPDATE_INTERVAL 50
 *   Refreshes the OLED roughly every 50 ms. This is responsive enough for
 *   status updates without needlessly refreshing every matrix scan.
 */
#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_TIMEOUT 0
#    define OLED_UPDATE_INTERVAL 50
#endif
