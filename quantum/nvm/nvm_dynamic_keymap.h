// Copyright 2024 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include <stdint.h>
#include <stdbool.h>

void nvm_dynamic_keymap_erase(void);
void nvm_dynamic_keymap_macro_erase(void);

uint16_t nvm_dynamic_keymap_read_keycode(uint8_t layer, uint8_t row, uint8_t column);
void     nvm_dynamic_keymap_update_keycode(uint8_t layer, uint8_t row, uint8_t column, uint16_t keycode);

#ifdef ENCODER_MAP_ENABLE
uint16_t nvm_dynamic_keymap_read_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise);
void     nvm_dynamic_keymap_update_encoder(uint8_t layer, uint8_t encoder_id, bool clockwise, uint16_t keycode);
#endif // ENCODER_MAP_ENABLE

void nvm_dynamic_keymap_read_buffer(uint32_t offset, uint32_t size, uint8_t *data);
void nvm_dynamic_keymap_update_buffer(uint32_t offset, uint32_t size, uint8_t *data);

uint32_t nvm_dynamic_keymap_macro_size(void);

void nvm_dynamic_keymap_macro_read_buffer(uint32_t offset, uint32_t size, uint8_t *data);
void nvm_dynamic_keymap_macro_update_buffer(uint32_t offset, uint32_t size, uint8_t *data);

void nvm_dynamic_keymap_macro_reset(void);

#ifdef QMK_SETTINGS
uint8_t nvm_dynamic_keymap_get_qmk_settings(uint16_t offset);
void nvm_dynamic_keymap_set_qmk_settings(uint16_t offset, uint8_t value);
#endif

#ifdef VIAL_TAP_DANCE_ENABLE
int nvm_dynamic_keymap_get_tap_dance(uint8_t index, vial_tap_dance_entry_t *entry);
int nvm_dynamic_keymap_set_tap_dance(uint8_t index, const vial_tap_dance_entry_t *entry);
#endif

#ifdef VIAL_COMBO_ENABLE
int nvm_dynamic_keymap_get_combo(uint8_t index, vial_combo_entry_t *entry);
int nvm_dynamic_keymap_set_combo(uint8_t index, const vial_combo_entry_t *entry);
#endif

#ifdef VIAL_KEY_OVERRIDE_ENABLE
int nvm_dynamic_keymap_get_key_override(uint8_t index, vial_key_override_entry_t *entry);
int nvm_dynamic_keymap_set_key_override(uint8_t index, const vial_key_override_entry_t *entry);
#endif

#ifdef VIAL_ALT_REPEAT_KEY_ENABLE
int nvm_dynamic_keymap_get_alt_repeat_key(uint8_t index, vial_alt_repeat_key_entry_t *entry);
int nvm_dynamic_keymap_set_alt_repeat_key(uint8_t index, const vial_alt_repeat_key_entry_t *entry);
#endif
