// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "compiler_support.h"
#include "keycodes.h"
#include "eeprom.h"
#include "dynamic_keymap.h"
#include "nvm_dynamic_keymap.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "nvm_eeprom_via_internal.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#else
#    define NUM_ENCODERS 0
#endif

#ifdef VIA_ENABLE
#    include "via.h"
#    define DYNAMIC_KEYMAP_EEPROM_START (VIA_EEPROM_CONFIG_END)
#else
#    define DYNAMIC_KEYMAP_EEPROM_START (EECONFIG_SIZE)
#endif

#ifndef DYNAMIC_KEYMAP_EEPROM_MAX_ADDR
#    define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (TOTAL_EEPROM_BYTE_COUNT - 1)
#endif

STATIC_ASSERT(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR <= (TOTAL_EEPROM_BYTE_COUNT - 1), "DYNAMIC_KEYMAP_EEPROM_MAX_ADDR is configured to use more space than what is available for the selected EEPROM driver");

// Due to usage of uint16_t check for max 65535
STATIC_ASSERT(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR <= 65535, "DYNAMIC_KEYMAP_EEPROM_MAX_ADDR must be less than 65536");

// If DYNAMIC_KEYMAP_EEPROM_ADDR not explicitly defined in config.h,
#ifndef DYNAMIC_KEYMAP_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_EEPROM_ADDR DYNAMIC_KEYMAP_EEPROM_START
#endif

// Encoders are located right after the dynamic keymap
#define VIAL_ENCODERS_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))
#define DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR VIAL_ENCODERS_EEPROM_ADDR

#define VIAL_ENCODERS_SIZE (NUM_ENCODERS * DYNAMIC_KEYMAP_LAYER_COUNT * 2 * 2)

// QMK settings area is just past encoders
#define VIAL_QMK_SETTINGS_EEPROM_ADDR (VIAL_ENCODERS_EEPROM_ADDR + VIAL_ENCODERS_SIZE)

#ifdef QMK_SETTINGS
#include "qmk_settings.h"
#define VIAL_QMK_SETTINGS_SIZE (sizeof(qmk_settings_t))
#else
#define VIAL_QMK_SETTINGS_SIZE 0
#endif

// Tap-dance
#define VIAL_TAP_DANCE_EEPROM_ADDR (VIAL_QMK_SETTINGS_EEPROM_ADDR + VIAL_QMK_SETTINGS_SIZE)

#ifdef VIAL_TAP_DANCE_ENABLE
#define VIAL_TAP_DANCE_SIZE (sizeof(vial_tap_dance_entry_t) * VIAL_TAP_DANCE_ENTRIES)
#else
#define VIAL_TAP_DANCE_SIZE 0
#endif

// Combos
#define VIAL_COMBO_EEPROM_ADDR (VIAL_TAP_DANCE_EEPROM_ADDR + VIAL_TAP_DANCE_SIZE)

#ifdef VIAL_COMBO_ENABLE
#define VIAL_COMBO_SIZE (sizeof(vial_combo_entry_t) * VIAL_COMBO_ENTRIES)
#else
#define VIAL_COMBO_SIZE 0
#endif

// Key overrides
#define VIAL_KEY_OVERRIDE_EEPROM_ADDR (VIAL_COMBO_EEPROM_ADDR + VIAL_COMBO_SIZE)

#ifdef VIAL_KEY_OVERRIDE_ENABLE
#define VIAL_KEY_OVERRIDE_SIZE (sizeof(vial_key_override_entry_t) * VIAL_KEY_OVERRIDE_ENTRIES)
#else
#define VIAL_KEY_OVERRIDE_SIZE 0
#endif

// Alt Repeat Key
#define VIAL_ALT_REPEAT_KEY_EEPROM_ADDR (VIAL_KEY_OVERRIDE_EEPROM_ADDR + VIAL_KEY_OVERRIDE_SIZE)

#ifdef VIAL_ALT_REPEAT_KEY_ENABLE
#define VIAL_ALT_REPEAT_KEY_SIZE (sizeof(vial_alt_repeat_key_entry_t) * VIAL_ALT_REPEAT_KEY_ENTRIES)
#else
#define VIAL_ALT_REPEAT_KEY_SIZE 0
#endif

// Dynamic macro
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (VIAL_ALT_REPEAT_KEY_EEPROM_ADDR + VIAL_ALT_REPEAT_KEY_SIZE)
#endif

// Sanity check that dynamic keymaps fit in available EEPROM
// If there's not 100 bytes available for macros, then something is wrong.
// The keyboard should override DYNAMIC_KEYMAP_LAYER_COUNT to reduce it,
// or DYNAMIC_KEYMAP_EEPROM_MAX_ADDR to increase it, *only if* the microcontroller has
// more than the default.
STATIC_ASSERT((int64_t)(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR) - (int64_t)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR) >= 100, "Dynamic keymaps are configured to use more EEPROM than is available.");

#ifndef TOTAL_EEPROM_BYTE_COUNT
#    error Unknown total EEPROM size. Cannot derive maximum for dynamic keymaps.
#endif
// Dynamic macros are stored after the keymaps and use what is available
// up to and including DYNAMIC_KEYMAP_EEPROM_MAX_ADDR.
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 1)
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void nvm_dynamic_keymap_erase(void) {
    // No-op, nvm_eeconfig_erase() will have already erased EEPROM if necessary.
}

void nvm_dynamic_keymap_macro_erase(void) {
    // No-op, nvm_eeconfig_erase() will have already erased EEPROM if necessary.
}

static inline void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column) {
    return ((void *)DYNAMIC_KEYMAP_EEPROM_ADDR) + (layer * MATRIX_ROWS * MATRIX_COLS * 2) + (row * MATRIX_COLS * 2) + (column * 2);
}

uint16_t nvm_dynamic_keymap_read_keycode(uint8_t layer, uint8_t row, uint8_t column) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || row >= MATRIX_ROWS || column >= MATRIX_COLS) return KC_NO;
    void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
    // Big endian, so we can read/write EEPROM directly from host if we want
    uint16_t keycode = eeprom_read_byte(address) << 8;
    keycode |= eeprom_read_byte(address + 1);
    return keycode;
}

void nvm_dynamic_keymap_update_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || row >= MATRIX_ROWS || column >= MATRIX_COLS) return;
    void *address = dynamic_keymap_key_to_eeprom_address(layer, row, column);
    // Big endian, so we can read/write EEPROM directly from host if we want
    eeprom_update_byte(address, (uint8_t)(keycode >> 8));
    eeprom_update_byte(address + 1, (uint8_t)(keycode & 0xFF));
}

#ifdef ENCODER_MAP_ENABLE
static void *dynamic_keymap_encoder_to_eeprom_address(uint8_t layer, uint8_t encoder_id) {
    return ((void *)DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR) + (layer * NUM_ENCODERS * 2 * 2) + (encoder_id * 2 * 2);
}

uint16_t nvm_dynamic_keymap_read_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || encoder_id >= NUM_ENCODERS) return KC_NO;
    void *address = dynamic_keymap_encoder_to_eeprom_address(layer, encoder_id);
    // Big endian, so we can read/write EEPROM directly from host if we want
    uint16_t keycode = ((uint16_t)eeprom_read_byte(address + (clockwise ? 0 : 2))) << 8;
    keycode |= eeprom_read_byte(address + (clockwise ? 0 : 2) + 1);
    return keycode;
}

void nvm_dynamic_keymap_update_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise, uint16_t keycode) {
    if (layer >= DYNAMIC_KEYMAP_LAYER_COUNT || encoder_id >= NUM_ENCODERS) return;
    void *address = dynamic_keymap_encoder_to_eeprom_address(layer, encoder_id);
    // Big endian, so we can read/write EEPROM directly from host if we want
    eeprom_update_byte(address + (clockwise ? 0 : 2), (uint8_t)(keycode >> 8));
    eeprom_update_byte(address + (clockwise ? 0 : 2) + 1, (uint8_t)(keycode & 0xFF));
}
#endif // ENCODER_MAP_ENABLE

void nvm_dynamic_keymap_read_buffer(uint32_t offset, uint32_t size, uint8_t *data) {
    uint32_t dynamic_keymap_eeprom_size = DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2;
    void *   source                     = (void *)(uintptr_t)(DYNAMIC_KEYMAP_EEPROM_ADDR + offset);
    uint8_t *target                     = data;
    for (uint32_t i = 0; i < size; i++) {
        if (offset + i < dynamic_keymap_eeprom_size) {
            *target = eeprom_read_byte(source);
        } else {
            *target = 0x00;
        }
        source++;
        target++;
    }
}

void nvm_dynamic_keymap_update_buffer(uint32_t offset, uint32_t size, uint8_t *data) {
    uint16_t dynamic_keymap_eeprom_size = DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2;
    void *   target                     = (void *)((uintptr_t)(DYNAMIC_KEYMAP_EEPROM_ADDR + offset));
    uint8_t *source                     = data;

#ifdef VIAL_ENABLE
    /* ensure the writes are bounded */
    if (offset >= dynamic_keymap_eeprom_size || dynamic_keymap_eeprom_size - offset < size)
        return;

#ifndef VIAL_INSECURE
    /* Check whether it is trying to send a QK_BOOT keycode; only allow setting these if unlocked */
    if (!vial_unlocked) {
        /* how much of the input array we'll have to check in the loop */
        uint16_t chk_offset = 0;
        uint16_t chk_sz = size;

        /* initial byte misaligned -- this means the first keycode will be a combination of existing and new data */
        if (offset % 2 != 0) {
            uint16_t kc = (eeprom_read_byte((uint8_t*)target - 1) << 8) | data[0];
            if (kc == QK_BOOT)
                data[0] = 0xFF;

            /* no longer have to check the first byte */
            chk_offset += 1;
        }

        /* final byte misaligned -- this means the last keycode will be a combination of new and existing data */
        if ((offset + size) % 2 != 0) {
            uint16_t kc = (data[size - 1] << 8) | eeprom_read_byte((uint8_t*)target + size);
            if (kc == QK_BOOT)
                data[size - 1] = 0xFF;

            /* no longer have to check the last byte */
            chk_sz -= 1;
        }

        /* check the entire array, replace any instances of QK_BOOT with invalid keycode 0xFFFF */
        for (uint16_t i = chk_offset; i < chk_sz; i += 2) {
            uint16_t kc = (data[i] << 8) | data[i + 1];
            if (kc == QK_BOOT) {
                data[i] = 0xFF;
                data[i + 1] = 0xFF;
            }
        }
    }
#endif
#endif

    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < dynamic_keymap_eeprom_size) {
            eeprom_update_byte(target, *source);
        }
        source++;
        target++;
    }
}

uint32_t nvm_dynamic_keymap_macro_size(void) {
    return DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE;
}

void nvm_dynamic_keymap_macro_read_buffer(uint32_t offset, uint32_t size, uint8_t *data) {
    void *   source = (void *)(uintptr_t)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + offset);
    uint8_t *target = data;
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE) {
            *target = eeprom_read_byte(source);
        } else {
            *target = 0x00;
        }
        source++;
        target++;
    }
}

void nvm_dynamic_keymap_macro_update_buffer(uint32_t offset, uint32_t size, uint8_t *data) {
    void *   target = (void *)(uintptr_t)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + offset);
    uint8_t *source = data;
    for (uint16_t i = 0; i < size; i++) {
        if (offset + i < DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE) {
            eeprom_update_byte(target, *source);
        }
        source++;
        target++;
    }
}

void nvm_dynamic_keymap_macro_reset(void) {
    void *  start     = (void *)(uintptr_t)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR);
    void *  end       = (void *)(uintptr_t)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE);
    long    remaining = end - start;
    uint8_t dummy[16] = {0};
    for (int i = 0; i < DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE; i += sizeof(dummy)) {
        int this_loop = remaining < sizeof(dummy) ? remaining : sizeof(dummy);
        eeprom_update_block(dummy, start, this_loop);
        start += this_loop;
        remaining -= this_loop;
    }
}

#ifdef QMK_SETTINGS
uint8_t nvm_dynamic_keymap_get_qmk_settings(uint16_t offset) {
    if (offset >= VIAL_QMK_SETTINGS_SIZE)
        return 0;

    void *address = (void*)(VIAL_QMK_SETTINGS_EEPROM_ADDR + offset);
    return eeprom_read_byte(address);
}

void nvm_dynamic_keymap_set_qmk_settings(uint16_t offset, uint8_t value) {
    if (offset >= VIAL_QMK_SETTINGS_SIZE)
        return;

    void *address = (void*)(VIAL_QMK_SETTINGS_EEPROM_ADDR + offset);
    eeprom_update_byte(address, value);
}
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
int nvm_dynamic_keymap_get_tap_dance(uint8_t index, vial_tap_dance_entry_t *entry) {
    if (index >= VIAL_TAP_DANCE_ENTRIES)
        return -1;

    void *address = (void*)(VIAL_TAP_DANCE_EEPROM_ADDR + index * sizeof(vial_tap_dance_entry_t));
    eeprom_read_block(entry, address, sizeof(vial_tap_dance_entry_t));

    return 0;
}

int nvm_dynamic_keymap_set_tap_dance(uint8_t index, const vial_tap_dance_entry_t *entry) {
    if (index >= VIAL_TAP_DANCE_ENTRIES)
        return -1;

    void *address = (void*)(VIAL_TAP_DANCE_EEPROM_ADDR + index * sizeof(vial_tap_dance_entry_t));
    eeprom_write_block(entry, address, sizeof(vial_tap_dance_entry_t));

    return 0;
}
#endif

#ifdef VIAL_COMBO_ENABLE
int nvm_dynamic_keymap_get_combo(uint8_t index, vial_combo_entry_t *entry) {
    if (index >= VIAL_COMBO_ENTRIES)
        return -1;

    void *address = (void*)(VIAL_COMBO_EEPROM_ADDR + index * sizeof(vial_combo_entry_t));
    eeprom_read_block(entry, address, sizeof(vial_combo_entry_t));

    return 0;
}

int nvm_dynamic_keymap_set_combo(uint8_t index, const vial_combo_entry_t *entry) {
    if (index >= VIAL_COMBO_ENTRIES)
        return -1;

    void *address = (void*)(VIAL_COMBO_EEPROM_ADDR + index * sizeof(vial_combo_entry_t));
    eeprom_write_block(entry, address, sizeof(vial_combo_entry_t));

    return 0;
}
#endif

#ifdef VIAL_KEY_OVERRIDE_ENABLE
int nvm_dynamic_keymap_get_key_override(uint8_t index, vial_key_override_entry_t *entry) {
    if (index >= VIAL_KEY_OVERRIDE_ENTRIES)
        return -1;

    void *address = (void*)(VIAL_KEY_OVERRIDE_EEPROM_ADDR + index * sizeof(vial_key_override_entry_t));
    eeprom_read_block(entry, address, sizeof(vial_key_override_entry_t));

    return 0;
}

int nvm_dynamic_keymap_set_key_override(uint8_t index, const vial_key_override_entry_t *entry) {
    if (index >= VIAL_KEY_OVERRIDE_ENTRIES)
        return -1;

    void *address = (void*)(VIAL_KEY_OVERRIDE_EEPROM_ADDR + index * sizeof(vial_key_override_entry_t));
    eeprom_write_block(entry, address, sizeof(vial_key_override_entry_t));

    return 0;
}
#endif

#ifdef VIAL_ALT_REPEAT_KEY_ENABLE
int nvm_dynamic_keymap_get_alt_repeat_key(uint8_t index, vial_alt_repeat_key_entry_t *entry) {
    if (index >= VIAL_ALT_REPEAT_KEY_ENTRIES)
        return -1;

    void *address = (void*)(VIAL_ALT_REPEAT_KEY_EEPROM_ADDR + index * sizeof(vial_alt_repeat_key_entry_t));
    eeprom_read_block(entry, address, sizeof(vial_alt_repeat_key_entry_t));

    return 0;
}

int nvm_dynamic_keymap_set_alt_repeat_key(uint8_t index, const vial_alt_repeat_key_entry_t *entry) {
    if (index >= VIAL_ALT_REPEAT_KEY_ENTRIES)
        return -1;

    void *address = (void*)(VIAL_ALT_REPEAT_KEY_EEPROM_ADDR + index * sizeof(vial_alt_repeat_key_entry_t));
    eeprom_write_block(entry, address, sizeof(vial_alt_repeat_key_entry_t));

    return 0;
}
#endif
