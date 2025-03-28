/* Copyright 2020 Ilya Zhuravlev
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <inttypes.h>
#include <stdbool.h>

#include "eeprom.h"
#include "action.h"

#define VIAL_PROTOCOL_VERSION ((uint32_t)0x00000006)
#define VIAL_RAW_EPSIZE 32

void vial_init(void);
void vial_handle_cmd(uint8_t *data, uint8_t length);
bool process_record_vial(uint16_t keycode, keyrecord_t *record);

extern int vial_unlocked;
extern int vial_unlock_in_progress;
extern uint16_t g_vial_magic_keycode_override;

enum {
    vial_get_keyboard_id = 0x00,
    vial_get_size = 0x01,
    vial_get_def = 0x02,
    vial_get_encoder = 0x03,
    vial_set_encoder = 0x04,
    vial_get_unlock_status = 0x05,
    vial_unlock_start = 0x06,
    vial_unlock_poll = 0x07,
    vial_lock = 0x08,
    vial_qmk_settings_query = 0x09,
    vial_qmk_settings_get = 0x0A,
    vial_qmk_settings_set = 0x0B,
    vial_qmk_settings_reset = 0x0C,
    vial_dynamic_entry_op = 0x0D,  /* operate on tapdance, combos, etc */
};

enum {
    dynamic_vial_get_number_of_entries = 0x00,
    dynamic_vial_tap_dance_get = 0x01,
    dynamic_vial_tap_dance_set = 0x02,
    dynamic_vial_combo_get = 0x03,
    dynamic_vial_combo_set = 0x04,
    dynamic_vial_key_override_get = 0x05,
    dynamic_vial_key_override_set = 0x06,
};

#define VIAL_MACRO_EXT_TAP 5
#define VIAL_MACRO_EXT_DOWN 6
#define VIAL_MACRO_EXT_UP 7

void vial_keycode_down(uint16_t keycode);
void vial_keycode_up(uint16_t keycode);
void vial_keycode_tap(uint16_t keycode);

/* Fake position in keyboard matrix, can't use 255 as that is immediately rejected by IS_NOEVENT
   used to send arbitrary keycodes thru process_record_quantum_helper */
#define VIAL_MATRIX_MAGIC 240


#ifdef TAP_DANCE_ENABLE
#define VIAL_TAP_DANCE_ENABLE

#ifndef VIAL_TAP_DANCE_ENTRIES
    #if TOTAL_EEPROM_BYTE_COUNT > 4000
        #define VIAL_TAP_DANCE_ENTRIES 32
    #elif TOTAL_EEPROM_BYTE_COUNT > 2000
        #define VIAL_TAP_DANCE_ENTRIES 16
    #elif TOTAL_EEPROM_BYTE_COUNT > 1000
        #define VIAL_TAP_DANCE_ENTRIES 8
    #else
        #define VIAL_TAP_DANCE_ENTRIES 4
    #endif
#endif

typedef struct {
    uint16_t on_tap;
    uint16_t on_hold;
    uint16_t on_double_tap;
    uint16_t on_tap_hold;
    uint16_t custom_tapping_term;
} vial_tap_dance_entry_t;
_Static_assert(sizeof(vial_tap_dance_entry_t) == 10, "Unexpected size of the vial_tap_dance_entry_t structure");

#else
#undef VIAL_TAP_DANCE_ENTRIES
#define VIAL_TAP_DANCE_ENTRIES 0
#endif


#ifdef COMBO_ENABLE
#define VIAL_COMBO_ENABLE

#ifndef VIAL_COMBO_ENTRIES
    #if TOTAL_EEPROM_BYTE_COUNT > 4000
        #define VIAL_COMBO_ENTRIES 32
    #elif TOTAL_EEPROM_BYTE_COUNT > 2000
        #define VIAL_COMBO_ENTRIES 16
    #elif TOTAL_EEPROM_BYTE_COUNT > 1000
        #define VIAL_COMBO_ENTRIES 8
    #else
        #define VIAL_COMBO_ENTRIES 4
    #endif
#endif

typedef struct {
    uint16_t input[4];
    uint16_t output;
} vial_combo_entry_t;
_Static_assert(sizeof(vial_combo_entry_t) == 10, "Unexpected size of the vial_combo_entry_t structure");

/* also to catch wrong include order in e.g. process_combo.h */
#ifdef COMBO_COUNT
#error COMBO_COUNT redefined - define VIAL_COMBO_ENTRIES instead
#endif

#define COMBO_COUNT VIAL_COMBO_ENTRIES

#else
#undef VIAL_COMBO_ENTRIES
#define VIAL_COMBO_ENTRIES 0
#endif


#ifdef KEY_OVERRIDE_ENABLE
#define VIAL_KEY_OVERRIDE_ENABLE

#include "process_key_override.h"

#ifndef VIAL_KEY_OVERRIDE_ENTRIES
    #if TOTAL_EEPROM_BYTE_COUNT > 4000
        #define VIAL_KEY_OVERRIDE_ENTRIES 32
    #elif TOTAL_EEPROM_BYTE_COUNT > 2000
        #define VIAL_KEY_OVERRIDE_ENTRIES 16
    #elif TOTAL_EEPROM_BYTE_COUNT > 1000
        #define VIAL_KEY_OVERRIDE_ENTRIES 8
    #else
        #define VIAL_KEY_OVERRIDE_ENTRIES 4
    #endif
#endif

/* the key override structure as it is stored in eeprom and transferred to vial-gui;
   it is deserialized into key_override_t by vial_get_key_override */
typedef struct {
    uint16_t trigger;
    uint16_t replacement;
    uint16_t layers;
    uint8_t trigger_mods;
    uint8_t negative_mod_mask;
    uint8_t suppressed_mods;
    uint8_t options;
} vial_key_override_entry_t;
_Static_assert(sizeof(vial_key_override_entry_t) == 10, "Unexpected size of the vial_key_override_entry_t structure");

enum {
    vial_ko_option_activation_trigger_down = (1 << 0),
    vial_ko_option_activation_required_mod_down = (1 << 1),
    vial_ko_option_activation_negative_mod_up = (1 << 2),
    vial_ko_option_one_mod = (1 << 3),
    vial_ko_option_no_reregister_trigger = (1 << 4),
    vial_ko_option_no_unregister_on_other_key_down = (1 << 5),
    vial_ko_enabled = (1 << 7),
};

#else
#undef VIAL_KEY_OVERRIDE_ENTRIES
#define VIAL_KEY_OVERRIDE_ENTRIES 0
#endif
