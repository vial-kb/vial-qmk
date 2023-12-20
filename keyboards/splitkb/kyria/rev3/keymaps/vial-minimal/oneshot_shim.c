/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Copyright 2023 splitkb.com <support@splitkb.com> */

#include QMK_KEYBOARD_H

// The atmega32u4 builds have NO_ACTION_ONESHOT defined due to space issues,
// but helix.c uses `get_oneshot_mods()`.
// This provides a no-op shim.

uint8_t get_oneshot_mods(void) {
    return 0;
}
