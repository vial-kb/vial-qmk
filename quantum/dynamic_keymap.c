/* Copyright 2017 Jason Williams (Wilba)
 * Copyright 2024-2025 Nick Brassel (@tzarc)
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

#include "dynamic_keymap.h"
#include "keymap_introspection.h"
#include "action.h"
#include "send_string.h"
#include "keycodes.h"
#include "action_tapping.h"
#include "wait.h"
#include <string.h>

#include "qmk_settings.h"
#include "nvm_dynamic_keymap.h"

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#else
#    define NUM_ENCODERS 0
#endif

#ifdef VIAL_ENABLE
#include "vial.h"
#endif

#ifndef DYNAMIC_KEYMAP_MACRO_DELAY
#    define DYNAMIC_KEYMAP_MACRO_DELAY TAP_CODE_DELAY
#endif

uint8_t dynamic_keymap_get_layer_count(void) {
    return DYNAMIC_KEYMAP_LAYER_COUNT;
}

uint16_t dynamic_keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t column) {
    return nvm_dynamic_keymap_read_keycode(layer, row, column);
}

void dynamic_keymap_set_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode) {
    nvm_dynamic_keymap_update_keycode(layer, row, column, keycode);
}

#ifdef ENCODER_MAP_ENABLE
uint16_t dynamic_keymap_get_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise) {
    return nvm_dynamic_keymap_read_encoder(layer, encoder_id, clockwise);
}

void dynamic_keymap_set_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise, uint16_t keycode) {
    nvm_dynamic_keymap_update_encoder(layer, encoder_id, clockwise, keycode);
}
#endif // ENCODER_MAP_ENABLE

#ifdef QMK_SETTINGS
uint8_t dynamic_keymap_get_qmk_settings(uint16_t offset) {
    return nvm_dynamic_keymap_get_qmk_settings(offset);
}

void dynamic_keymap_set_qmk_settings(uint16_t offset, uint8_t value) {
    nvm_dynamic_keymap_set_qmk_settings(offset, value);
}
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
int dynamic_keymap_get_tap_dance(uint8_t index, vial_tap_dance_entry_t *entry) {
    return nvm_dynamic_keymap_get_tap_dance(index, entry);
}

int dynamic_keymap_set_tap_dance(uint8_t index, const vial_tap_dance_entry_t *entry) {
    return nvm_dynamic_keymap_set_tap_dance(index, entry);
}
#endif

#ifdef VIAL_COMBO_ENABLE
int dynamic_keymap_get_combo(uint8_t index, vial_combo_entry_t *entry) {
    return nvm_dynamic_keymap_get_combo(index, entry);
}

int dynamic_keymap_set_combo(uint8_t index, const vial_combo_entry_t *entry) {
    return nvm_dynamic_keymap_set_combo(index, entry);
}
#endif

#ifdef VIAL_KEY_OVERRIDE_ENABLE
int dynamic_keymap_get_key_override(uint8_t index, vial_key_override_entry_t *entry) {
    return nvm_dynamic_keymap_get_key_override(index, entry);
}

int dynamic_keymap_set_key_override(uint8_t index, const vial_key_override_entry_t *entry) {
    return nvm_dynamic_keymap_set_key_override(index, entry);
}
#endif

#ifdef VIAL_ALT_REPEAT_KEY_ENABLE
int dynamic_keymap_get_alt_repeat_key(uint8_t index, vial_alt_repeat_key_entry_t *entry) {
    return nvm_dynamic_keymap_get_alt_repeat_key(index, entry);
}

int dynamic_keymap_set_alt_repeat_key(uint8_t index, const vial_alt_repeat_key_entry_t *entry) {
    return nvm_dynamic_keymap_set_alt_repeat_key(index, entry);
}
#endif

void dynamic_keymap_reset(void) {
#ifdef VIAL_ENABLE
    /* temporarily unlock the keyboard so we can set hardcoded QK_BOOT keycode */
    int vial_unlocked_prev = vial_unlocked;
    vial_unlocked = 1;
#endif

    // Erase the keymaps, if necessary.
    nvm_dynamic_keymap_erase();

    // Reset the keymaps in EEPROM to what is in flash.
    for (int layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            for (int column = 0; column < MATRIX_COLS; column++) {
                dynamic_keymap_set_keycode(layer, row, column, keycode_at_keymap_location_raw(layer, row, column));
            }
        }
#ifdef ENCODER_MAP_ENABLE
        for (int encoder = 0; encoder < NUM_ENCODERS; encoder++) {
            dynamic_keymap_set_encoder(layer, encoder, true, keycode_at_encodermap_location_raw(layer, encoder, true));
            dynamic_keymap_set_encoder(layer, encoder, false, keycode_at_encodermap_location_raw(layer, encoder, false));
        }
#endif // ENCODER_MAP_ENABLE
    }

#ifdef QMK_SETTINGS
    qmk_settings_reset();
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
    {
        vial_tap_dance_entry_t td = { KC_NO, KC_NO, KC_NO, KC_NO, TAPPING_TERM };
        for (size_t i = 0; i < VIAL_TAP_DANCE_ENTRIES; ++i) {
            dynamic_keymap_set_tap_dance(i, &td);
        }
    }
#endif

#ifdef VIAL_COMBO_ENABLE
    {
        vial_combo_entry_t combo = { 0 };
        for (size_t i = 0; i < VIAL_COMBO_ENTRIES; ++i)
            dynamic_keymap_set_combo(i, &combo);
    }
#endif

#ifdef VIAL_KEY_OVERRIDE_ENABLE
    {
        vial_key_override_entry_t ko = { 0 };
        ko.layers = ~0;
        ko.options = vial_ko_option_activation_negative_mod_up | vial_ko_option_activation_required_mod_down | vial_ko_option_activation_trigger_down;
        for (size_t i = 0; i < VIAL_KEY_OVERRIDE_ENTRIES; ++i)
            dynamic_keymap_set_key_override(i, &ko);
    }
#endif

#ifdef VIAL_ALT_REPEAT_KEY_ENABLE
    {
        vial_alt_repeat_key_entry_t arep = { 0 };
        for (size_t i = 0; i < VIAL_ALT_REPEAT_KEY_ENTRIES; ++i)
            dynamic_keymap_set_alt_repeat_key(i, &arep);
    }
#endif

#ifdef VIAL_ENABLE
    /* re-lock the keyboard */
    vial_unlocked = vial_unlocked_prev;
#endif
}

void dynamic_keymap_get_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    nvm_dynamic_keymap_read_buffer(offset, size, data);
}

void dynamic_keymap_set_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    nvm_dynamic_keymap_update_buffer(offset, size, data);
}

uint16_t keycode_at_keymap_location(uint8_t layer_num, uint8_t row, uint8_t column) {
    if (layer_num < DYNAMIC_KEYMAP_LAYER_COUNT && row < MATRIX_ROWS && column < MATRIX_COLS) {
        return dynamic_keymap_get_keycode(layer_num, row, column);
    }
    return KC_NO;
}

#ifdef ENCODER_MAP_ENABLE
uint16_t keycode_at_encodermap_location(uint8_t layer_num, uint8_t encoder_idx, bool clockwise) {
    if (layer_num < DYNAMIC_KEYMAP_LAYER_COUNT && encoder_idx < NUM_ENCODERS) {
        return dynamic_keymap_get_encoder(layer_num, encoder_idx, clockwise);
    }
    return KC_NO;
}
#endif // ENCODER_MAP_ENABLE

uint8_t dynamic_keymap_macro_get_count(void) {
    return DYNAMIC_KEYMAP_MACRO_COUNT;
}

uint16_t dynamic_keymap_macro_get_buffer_size(void) {
    return (uint16_t)nvm_dynamic_keymap_macro_size();
}

void dynamic_keymap_macro_get_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    nvm_dynamic_keymap_macro_read_buffer(offset, size, data);
}

void dynamic_keymap_macro_set_buffer(uint16_t offset, uint16_t size, uint8_t *data) {
    nvm_dynamic_keymap_macro_update_buffer(offset, size, data);
}

static uint8_t dynamic_keymap_read_byte(uint32_t offset) {
    uint8_t d;
    nvm_dynamic_keymap_macro_read_buffer(offset, 1, &d);
    return d;
}

void dynamic_keymap_macro_reset(void) {
    // Erase the macros, if necessary.
    nvm_dynamic_keymap_macro_erase();
    nvm_dynamic_keymap_macro_reset();
}

static uint16_t decode_keycode(uint16_t kc) {
    /* map 0xFF01 => 0x0100; 0xFF02 => 0x0200, etc */
    if (kc > 0xFF00)
        return (kc & 0xFF) << 8;
    return kc;
}

void dynamic_keymap_macro_send(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return;
    }

    // Check the last byte of the buffer.
    // If it's not zero, then we are in the middle
    // of buffer writing, possibly an aborted buffer
    // write. So do nothing.
    if (dynamic_keymap_read_byte(nvm_dynamic_keymap_macro_size() - 1) != 0) {
        return;
    }

    // Skip N null characters
    // offset will then point to the Nth macro
    uint32_t offset = 0;
    uint32_t end    = nvm_dynamic_keymap_macro_size();
    while (id > 0) {
        // If we are past the end of the buffer, then there is
        // no Nth macro in the buffer.
        if (offset == end) {
            return;
        }
        if (dynamic_keymap_read_byte(offset) == 0) {
            --id;
        }
        ++offset;
    }

    // Send the macro string one or three chars at a time
    // by making temporary 1 or 3 char strings
    char data[4] = {0, 0, 0, 0};
    // We already checked there was a null at the end of
    // the buffer, so this cannot go past the end
    while (1) {
        memset(data, 0, sizeof(data));
        data[0] = dynamic_keymap_read_byte(offset++);
        // Stop at the null terminator of this macro string
        if (data[0] == 0) {
            break;
        }
        if (data[0] == SS_QMK_PREFIX) {
            // If the char is magic, process it as indicated by the next character
            // (tap, down, up, delay)
            data[1] = dynamic_keymap_read_byte(offset++);
            if (data[1] == 0)
                break;
            if (data[1] == SS_TAP_CODE || data[1] == SS_DOWN_CODE || data[1] == SS_UP_CODE) {
                // For tap, down, up, just stuff it into the array and send_string it
                data[2] = dynamic_keymap_read_byte(offset++);
                if (data[2] != 0)
                    send_string(data);
            } else if (data[1] == VIAL_MACRO_EXT_TAP || data[1] == VIAL_MACRO_EXT_DOWN || data[1] == VIAL_MACRO_EXT_UP) {
                data[2] = dynamic_keymap_read_byte(offset++);
                if (data[2] != 0) {
                    data[3] = dynamic_keymap_read_byte(offset++);
                    if (data[3] != 0) {
                        uint16_t kc;
                        memcpy(&kc, &data[2], sizeof(kc));
                        kc = decode_keycode(kc);
                        switch (data[1]) {
                        case VIAL_MACRO_EXT_TAP:
                            vial_keycode_tap(kc);
                            break;
                        case VIAL_MACRO_EXT_DOWN:
                            vial_keycode_down(kc);
                            break;
                        case VIAL_MACRO_EXT_UP:
                            vial_keycode_up(kc);
                            break;
                        }
                    }
                }
            } else if (data[1] == SS_DELAY_CODE) {
                // For delay, decode the delay and wait_ms for that amount
                uint8_t d0 = dynamic_keymap_read_byte(offset++);
                uint8_t d1 = dynamic_keymap_read_byte(offset++);
                if (d0 == 0 || d1 == 0)
                    break;
                // we cannot use 0 for these, need to subtract 1 and use 255 instead of 256 for delay calculation
                int ms = (d0 - 1) + (d1 - 1) * 255;
                while (ms--) wait_ms(1);
            }
        } else {
            // If the char wasn't magic, just send it
            send_string_with_delay(data, DYNAMIC_KEYMAP_MACRO_DELAY);
        }
    }
}
