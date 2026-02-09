/* Copyright 2026 Javier Domingo
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

#ifdef RGB_MATRIX_ENABLE

#include "rule_lighting.h"
#include "keymap_introspection.h"
#include "dynamic_keymap.h"
#include <string.h>

#ifdef SPLIT_KEYBOARD
#    include "keyboard.h"
#    include "transactions.h"
#    include "timer.h"
#    include "split_util.h"
#endif

/* Forward declarations for EEPROM access */
extern void nvm_dynamic_keymap_load_rgb_indicators(rule_lighting_entry_t *entries);
extern void nvm_dynamic_keymap_save_rgb_indicators(const rule_lighting_entry_t *entries);

/**
 * Rules array defined by user in keymap.c
 * Weak default provides empty array if not defined
 */
__attribute__((weak)) const rule_lighting_entry_t rules[RULE_LIGHTING_ENTRIES] = {0};

#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)
/* Slave-side RAM copy of rules synced from master
 * Sync is needed with DYNAMIC_KEYMAP because:
 * - EEPROM is per-chip (independent on each half)
 * - Keymaps can diverge between halves via VIA/HID writes
 * For static keymaps, both halves read rules directly from flash (no sync needed)
 */
static rule_lighting_entry_t slave_rules[RULE_LIGHTING_ENTRIES];

/* Reset rule lighting to defaults from flash and save to EEPROM */
void rule_lighting_reset(void) {
    for (uint8_t i = 0; i < RULE_LIGHTING_ENTRIES; i++) {
        slave_rules[i] = rules[i];
    }
    nvm_dynamic_keymap_save_rgb_indicators(slave_rules);
}

/* Master-side sync state */
static bool master_sync_complete = false;
#    endif

/**
 * Get rules array (master uses flash, slave uses RAM copy only for dynamic keymaps)
 */
const rule_lighting_entry_t *rule_lighting_get_rules(void) {
    return slave_rules;
}

/**
 * Save all rule lighting data to EEPROM
 */
void rule_lighting_save(void) {
    nvm_dynamic_keymap_save_rgb_indicators(slave_rules);
}

static uint16_t synced_keymap[DYNAMIC_KEYMAP_LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS];

/**
 * Get keycode for a key position (supports split keyboard)
 * Resolves KC_TRNS by walking down layers to find actual keycode
 */
uint16_t get_synced_keycode(uint8_t layer, uint8_t row, uint8_t col) {
    /* Use keymap introspection to get keycode from RAM/EEPROM/flash */
    if (layer >= keymap_layer_count() || row >= MATRIX_ROWS || col >= MATRIX_COLS) {
        return KC_NO;
    }

    bool use_synced = !is_keyboard_master();
    for (int8_t l = layer; l >= 0; l--) {

#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)
        uint16_t kc = use_synced ? synced_keymap[l][row][col]
                                 : dynamic_keymap_get_keycode(l, row, col);
#    else
        uint16_t kc = keycode_at_keymap_location_raw(l, row, col);
#    endif
        if (kc != KC_TRNS) {
            return kc;
        }
    }
    return KC_NO;
}

#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)

/**
 * Slave handler for rule sync RPC
 * Receives rules from master and sends ACK back
 */
static void rule_lighting_slave_handler(uint8_t m2s_size, const void *m2s_buffer, uint8_t s2m_size, void *s2m_buffer) {
    uint8_t *ack = (uint8_t *)s2m_buffer;

    if (m2s_size == sizeof(slave_rules) && s2m_size >= 1) {
        memcpy(slave_rules, m2s_buffer, sizeof(slave_rules));
        *ack = 1; /* Send ACK */
    } else if (s2m_size >= 1) {
        *ack = 0; /* Invalid size */
    }
}

/**
 * Slave callback for keymap sync
 */
static void keymap_slave_handler(uint8_t m2s_size, const void *m2s_buffer, uint8_t s2m_size, void *s2m_buffer) {
    uint8_t *ack = (uint8_t *)s2m_buffer;

    if (m2s_size == sizeof(keymap_layer_sync_t) && s2m_size >= 1) {
        const keymap_layer_sync_t *data = (const keymap_layer_sync_t *)m2s_buffer;

        if (data->layer >= DYNAMIC_KEYMAP_LAYER_COUNT) {
            *ack = 0;
            return;
        }

        memcpy(synced_keymap[data->layer], data->keycodes, sizeof(data->keycodes));
        *ack = 1; /* Send ACK */
    } else if (s2m_size >= 1) {
        *ack = 0; /* Invalid size */
    }
}

/**
 * Reset keymap sync - called when dynamic keymap is modified
 */
void dynamic_keymap_reset_sync(void) {
    master_sync_complete = false;
}

/**
 * Master sync - sync rules to slave on connection
 * Handles late slave connection by detecting disconnection and resetting sync state
 */
static void rule_lighting_master_sync(void) {
    /* If not connected and sync was complete, reset sync state */
    if (!is_transport_connected()) {
        if (master_sync_complete) {
            master_sync_complete = false;
        }
        return;
    }

    /* If sync complete, nothing to do */
    if (master_sync_complete) {
        return;
    }

    /* Rate limit to once per 500ms */
    static uint32_t last_attempt = 0;
    if (timer_elapsed32(last_attempt) <= 500) {
        return;
    }
    last_attempt = timer_read32();

    /* Sync all keymap layers */
    for (uint8_t layer = 0; layer < DYNAMIC_KEYMAP_LAYER_COUNT; layer++) {
        keymap_layer_sync_t layer_data;
        layer_data.layer = layer;
        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                layer_data.keycodes[row][col] = dynamic_keymap_get_keycode(layer, row, col);
            }
        }

        uint8_t ack = 0;
        if (!transaction_rpc_exec(SPLIT_KEYMAP_SYNC_ID, sizeof(keymap_layer_sync_t), &layer_data, sizeof(ack), &ack) || ack != 1) {
            return;
        }
    }

    /* Send rules */
    uint8_t ack = 0;
    if (!transaction_rpc_exec(SPLIT_RULE_LIGHTING_SYNC_ID, sizeof(slave_rules), slave_rules, sizeof(ack), &ack)) {
        return;
    }
    if (ack == 1) {
        master_sync_complete = true;
    }
}

/**
 * Register split transactions - must be called AFTER split_post_init()
 */
void rule_lighting_post_init(void) {
    transaction_register_rpc(SPLIT_RULE_LIGHTING_SYNC_ID, rule_lighting_slave_handler);
    transaction_register_rpc(SPLIT_KEYMAP_SYNC_ID, keymap_slave_handler);
}

#    endif /* SPLIT_KEYBOARD && DYNAMIC_KEYMAP_ENABLE */

/**
 * Housekeeping task for rule lighting
 * Handles split sync on master when dynamic keymaps are enabled
 */
void rule_lighting_task(void) {
#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)
    if (is_keyboard_master()) {
        rule_lighting_master_sync();
    }
#    endif
}

void rule_lighting_init(void) {
#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)
    /* Clear slave rules on init */
    if (!is_keyboard_master()) {
        memset(slave_rules, 0, sizeof(slave_rules));
        return;
    }
#    endif
    nvm_dynamic_keymap_load_rgb_indicators(slave_rules);
}

#endif /* RGB_MATRIX_ENABLE */
