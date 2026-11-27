# SPDX-License-Identifier: GPL-2.0-or-later
#
# BFS9000 — Vial keymap build rules
# Copyright (C) 2026 jguillen-lab
#
# This file is part of the BFS9000 / Marquichuelo keyboard firmware.
# It is distributed under the terms of the GNU General Public License
# version 2 or later.

# ─────────────────────────────────────────────────────────────────────────────
# VIA / VIAL
# ─────────────────────────────────────────────────────────────────────────────
#
# VIA_ENABLE enables the base VIA protocol layer.
# VIAL_ENABLE enables Vial on top of VIA, including the Vial desktop protocol,
# security unlock combo and the RAW HID interface used by Vial-compatible tools.

VIA_ENABLE = yes
VIAL_ENABLE = yes

# ─────────────────────────────────────────────────────────────────────────────
# RGB MATRIX / VIALRGB
# ─────────────────────────────────────────────────────────────────────────────
#
# RGB_MATRIX_ENABLE compiles QMK's per-LED RGB engine.
# RGB_MATRIX_DRIVER selects the LED transport implementation.
# WS2812_DRIVER=vendor uses the RP2040 vendor driver for WS2812/SK6812 LEDs.
# VIALRGB_ENABLE exposes RGB Matrix controls to Vial over the Vial RAW HID path.

RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812
WS2812_DRIVER = vendor
VIALRGB_ENABLE = yes

# ─────────────────────────────────────────────────────────────────────────────
# USER-FACING QMK FEATURES
# ─────────────────────────────────────────────────────────────────────────────
#
# OLED_ENABLE compiles the OLED status/display code.
# COMBO_ENABLE enables multi-key combo actions.
# TAP_DANCE_ENABLE enables tap/hold/multi-tap key behaviours.

OLED_ENABLE = yes
COMBO_ENABLE = yes
TAP_DANCE_ENABLE = yes

# ─────────────────────────────────────────────────────────────────────────────
# POINTING DEVICE / TPS65
# ─────────────────────────────────────────────────────────────────────────────
#
# Enables QMK's pointing-device subsystem and selects the Azoteq IQS5xx driver,
# used here for the TPS65-style trackpad hardware.
#
# Split-side behaviour and right-half placement are configured in config.h.

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = azoteq_iqs5xx

# ─────────────────────────────────────────────────────────────────────────────
# HELP KEY LANGUAGE
# ─────────────────────────────────────────────────────────────────────────────
#
# Language of the HELP_KEY texts on the slave OLED: en (default) or es.
# Choose it at build time without editing this file:
#   qmk compile -kb jguillen_lab/bfs9000 -km vial -e BFS_HELP_LANG=es

BFS_HELP_LANG ?= en
ifeq ($(strip $(BFS_HELP_LANG)), es)
    OPT_DEFS += -DBFS_HELP_LANG_ES
endif
