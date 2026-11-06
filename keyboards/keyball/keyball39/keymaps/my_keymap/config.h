/*
This is the c configuration file for the keymap

Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

// Vial keyboard identity (random, generated for this board).
#define VIAL_KEYBOARD_UID {0x1A, 0x48, 0x65, 0x77, 0xDF, 0xD4, 0xDC, 0xB9}

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_EFFECT_BREATHING
#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#    define RGBLIGHT_EFFECT_SNAKE
#    define RGBLIGHT_EFFECT_KNIGHT
#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
#    define RGBLIGHT_EFFECT_RGB_TEST
#    define RGBLIGHT_EFFECT_ALTERNATING
#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#define TAP_CODE_DELAY 5

#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 1
#define AUTO_MOUSE_TIME 650
#define DYNAMIC_KEYMAP_LAYER_COUNT 7
#define AUTO_MOUSE_LAYER_KEEP_TIME 30000
#define TAPPING_TERM 200
#undef MOUSE_EXTENDED_REPORT
#undef WHEEL_EXTENDED_REPORT
// Tried POINTING_DEVICE_HIRES_SCROLL_ENABLE (HID Resolution Multiplier) here
// to report scroll as fractional sub-detent units, hoping it would help
// macOS/Obsidian recognize continuous scroll input. Result: scrolling became
// wildly oversensitive and the Obsidian issue was unchanged — macOS most
// likely doesn't honor the Resolution Multiplier feature report (it's a
// Windows-era HID mechanism), so it just read our inflated raw values
// directly as whole clicks instead of fractional ones. Reverted.
// Add our own layer-sync RPC transaction alongside holykeebs' HK_SYNC_STATE
#undef SPLIT_TRANSACTION_IDS_USER
#define SPLIT_TRANSACTION_IDS_USER HK_SYNC_STATE, MY_LAYER_SYNC
#define KEYBALL_SCROLL_DIV_DEFAULT 4
// EXPERIMENT (aml-stock-test branch): AML activation and cursor scaling are back to
// the stock QMK approach to compare against the old anti-vibration setup, which paired
// this low CPI with a software multiplier (MOVE_SCALE 11/7, about 943 effective CPI).
// The multiplier is gone, so cursor speed now comes from CPI alone; this default is
// deliberately unchanged and the CPI saved in EEPROM is tuned with the CPI keys.
// Axis-snap in keyball_on_apply_motion_to_mouse_move still suppresses cross-axis drift.
// CPI is auto-saved to EEPROM in housekeeping_task_user whenever it changes.
// After flashing, press KBC_RST (or use VIA) to reset saved CPI to this new default.
#define KEYBALL_CPI_DEFAULT 600

// Historical note: bytes 4092-4095 of EEPROM used to hold a bespoke
// (value + 0xBEEF magic) tapping-term save, kept out of dynamic-keymap macro
// storage by capping the boundary below. Tapping term now lives in
// QS.tapping_term (quantum/qmk_settings.c) instead — see keymap.c — so those
// bytes are unused, but the cap is left in place since loosening it changes
// the EEPROM layout QMK/Vial already computed and isn't worth the risk of an
// unintended full reset of the saved keymap/macros/tap-dances.
// RP2040 wear-leveling EEPROM here is 4096 bytes (TOTAL_EEPROM_BYTE_COUNT), not the
// 1024-byte AVR-style size this was originally tuned for — Vial's tap dance/combo/
// key override tables (32 entries each by default on >4000-byte EEPROM, defined in
// quantum/vial.h) are inserted between the dynamic keymap and the macro storage
// region, so the boundary must leave room for all of that, not just the keymap.
#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 4091

// Disable split watchdog to prevent the secondary MCU from resetting during USB suspend.
//
// Root cause of the "CPI feels low after idle" bug:
//   1. Host suspends USB (display sleep) → master stops sending split sync packets.
//   2. Holykeebs sets SPLIT_WATCHDOG_TIMEOUT to 3000ms, so secondary resets after 3s.
//   3. Secondary reboots and reads CPI from its own EEPROM (flash).
//      On RP2040, each MCU has independent flash; VIA only writes to master's flash,
//      so secondary always restores to KEYBALL_CPI_DEFAULT (1200) after reset.
//   4. Master's split CPI sync only sends on change (last_cpi != shared_cpi).
//      Since the master's CPI hasn't changed, it never resyncs to the secondary.
//   5. User sees abnormally low CPI until USB is reconnected (which resets last_cpi).
//
// Fix: prevent secondary reset by disabling the watchdog.
// RP2040 is stable enough that a secondary hang requiring watchdog recovery is
// effectively never seen in practice.
#undef SPLIT_WATCHDOG_ENABLE

#define COMBO_TERM 100
// Always match combos against layer 0 keycodes.
// Without this, combos don't fire on layer 1 (auto mouse) because D/F/J/K
// map to different keys on that layer.
#define COMBO_ONLY_FROM_LAYER 0
#define USB_POLLING_INTERVAL_MS 1
#define SPLIT_USB_DETECT