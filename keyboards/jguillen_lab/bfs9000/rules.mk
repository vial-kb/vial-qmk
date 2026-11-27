# SPDX-License-Identifier: GPL-2.0-or-later
#
# BFS9000 — Keyboard-level build rules
# Copyright (C) 2026 jguillen-lab
#
# This file is part of the BFS9000 / Marquichuelo keyboard firmware.
# It is distributed under the terms of the GNU General Public License
# version 2 or later.

# ─────────────────────────────────────────────────────────────────────────────
# SPLIT SERIAL TRANSPORT
# ─────────────────────────────────────────────────────────────────────────────
#
# The two halves communicate over the RP2040 vendor serial driver.
# Pin assignment and split-side detection live in config.h.

SERIAL_DRIVER = vendor

# ─────────────────────────────────────────────────────────────────────────────
# OLED SUPPORT
# ─────────────────────────────────────────────────────────────────────────────
#
# Select the SSD1306 OLED driver and I²C transport. The physical I²C pins and
# display behaviour are configured in config.h.

OLED_DRIVER = ssd1306
OLED_TRANSPORT = i2c
