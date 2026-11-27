// ============================================================================
// keymaps/default/keymap.c — Basic standalone keymap
// ============================================================================
//
// SPDX-License-Identifier: GPL-2.0-or-later
//
// This keymap is intentionally small and dependency-free.  The fully featured
// Vial keymap lives in `keymaps/vial`; this default keymap is meant to be a
// clean fallback that can compile without Vial, RGB Matrix, OLED or Tap Dance.
//
// Keep this file conservative:
//   • no Vial-only features
//   • no Tap Dance keycodes
//   • no OLED/helper code
//   • only standard QMK keycodes and momentary layers
//
// The keymap is written as a raw matrix table instead of using `LAYOUT(...)` so
// it is easy to compare with `g_led_config` and with the generated Vial matrix.
// ============================================================================

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN,
    _NAV,
    _ADJ,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // ── Base layer ──────────────────────────────────────────────────────────
    // Rows 0–5 are the left half, rows 6–11 are the right half.
    [_BASE] = {
        { KC_PSCR, KC_SCRL, KC_PAUS, KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_NO    }, // row 0
        { KC_NO,   KC_INS,  KC_HOME, KC_PGUP, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO    }, // row 1
        { KC_NO,   KC_DEL,  KC_END,  KC_PGDN, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_NO    }, // row 2
        { KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_NO    }, // row 3
        { KC_NO,   KC_NO,   KC_NO,   KC_LSFT, KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE  }, // row 4
        { KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_LGUI, KC_LALT, MO(_NAV),KC_DEL,  KC_ENTER }, // row 5

        { KC_PMNS, KC_PAST, KC_PSLS, KC_NUM,  KC_F12,  KC_F11,  KC_F10,  KC_F9,   KC_F8,   KC_F7,   KC_NO    }, // row 6
        { KC_PPLS, KC_P9,   KC_P8,   KC_P7,   KC_MINUS, KC_0,    KC_9,    KC_8,    KC_7,    KC_6,    KC_NO    }, // row 7
        { KC_NO,   KC_P6,   KC_P5,   KC_P4,   KC_LBRC, KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,    KC_NO    }, // row 8
        { KC_PENT, KC_P3,   KC_P2,   KC_P1,   KC_QUOT, KC_SCLN, KC_L,    KC_K,    KC_J,    KC_H,    KC_NO    }, // row 9
        { KC_NO,   KC_PDOT, KC_UP,   KC_P0,   KC_RCTL, KC_SLSH, KC_DOT,  KC_COMM, KC_M,    KC_N,    KC_NO    }, // row 10
        { KC_NO,   KC_RIGHT, KC_DOWN, KC_LEFT, KC_NO,   KC_NO,   KC_RGUI, KC_RALT, MO(_FN), KC_BSPC, KC_SPACE   }, // row 11
    },

    // ── Function layer ──────────────────────────────────────────────────────
    // Minimal maintenance layer: bootloader access on both halves.
    [_FN] = {
        { QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 0
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 1
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 2
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 3
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 4
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 5
        { QK_BOOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 6
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 7
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 8
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 9
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 10
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 11
    },

    // ── Navigation layer ────────────────────────────────────────────────────
    // Kept deliberately small; the physical arrow cluster is already available
    // on the base layer, so this layer mostly remains transparent.
    [_NAV] = {
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 0
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 1
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 2
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 3
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 4
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 5
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 6
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 7
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 8
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 9
        { KC_NO,   KC_RIGHT, KC_DOWN, KC_LEFT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 10
        { KC_TRNS, KC_RIGHT, KC_DOWN, KC_LEFT, KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 11
    },

    // ── Adjust layer placeholder ────────────────────────────────────────────
    // Reserved for future non-Vial maintenance shortcuts.
    [_ADJ] = {
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 0
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 1
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 2
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 3
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 4
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 5
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 6
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 7
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 8
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO   }, // row 9
        { KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 10
        { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   KC_NO,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS }, // row 11
    },
};
