#include QMK_KEYBOARD_H
#include "bipedalambi.h"

// --- Right Side Layout Macro ---
// Based on KLE raw data - 25 keys + encoder
// Matrix positions: rows 0-3, cols 0-6 (col 7 unused)
#define LAYOUT_right( \
    k03, \
    k04, k02, \
    k05, k01, k00, \
    k13, \
    k14, k12, \
    k15, k11, k10, \
    k23, \
    k24, k22, \
    k26, k25, k21, k20, \
    k36, k33, \
    k34, k32, \
    k35, k31 \
) { \
    { k00, k01, k02, k03, k04, k05, KC_NO, KC_NO }, \
    { k10, k11, k12, k13, k14, k15, KC_NO, KC_NO }, \
    { k20, k21, k22, k23, k24, k25, k26,   KC_NO }, \
    { KC_NO, k31, k32, k33, k34, k35, k36, KC_NO } \
}

// --- Custom Keycodes ---
// MUST use QK_KB_0 for Vial to recognize custom keycodes
// Order must match customKeycodes array in vial.json
enum custom_keycodes {
    TMB_MODE = QK_KB_0,
    CL_FWD,
    CL_BWD,
    SCROLL_DIR,
    ACT_UP,
    ACT_DOWN,
    ACT_RESET,
    KC_JOYSTICK_BUTTON
};

// --- Per-Layer State ---
static uint8_t layer_modes[4] = {MODE_MOUSE, MODE_MOUSE, MODE_MOUSE, MODE_MOUSE};
// static uint8_t layer_actuation_indices[4] = {2, 2, 2, 2}; // Removed for global actuation
const uint16_t actuation_values[] = {352, 320, 256, 128, 64};
uint8_t current_actuation_index = 2;

// Layer cycle bounds
#define LAYER_CYCLE_START 0
#define LAYER_CYCLE_END 3

// --- EEPROM Persistence ---
void save_layer_config_to_eeprom(void) {
    uint32_t data = 0;
    // Bits 0-7: Layer modes
    for (int i = 0; i < 4; i++) {
        uint32_t mode = (uint32_t)layer_modes[i] & 0x03;
        data |= mode << (i * 2);
    }
    // Bits 8-10: Global actuation index
    data |= ((uint32_t)current_actuation_index & 0x07) << 8;

    eeconfig_update_user(data);
}

void load_layer_config_from_eeprom(void) {
    uint32_t data = eeconfig_read_user();
    // Bits 0-7: Layer modes
    for (int i = 0; i < 4; i++) {
        uint8_t mode = (data >> (i * 2)) & 0x03;
        layer_modes[i] = (mode < MODE_COUNT) ? mode : MODE_MOUSE;
    }
    // Bits 8-10: Global actuation index
    uint8_t act_idx = (data >> 8) & 0x07;
    current_actuation_index = (act_idx <= 4) ? act_idx : 2;

    current_mode = layer_modes[0];
    actuation = actuation_values[current_actuation_index];
}

void eeconfig_init_user(void) {
    // Default: all layers MODE_MOUSE (0), actuation_index = 2 (middle)
    // Encoding: bits 0-7 = layer modes (2 bits each), bits 8-10 = actuation index
    // (0 << 0) | (0 << 2) | (0 << 4) | (0 << 6) | (2 << 8) = 0x200
    eeconfig_update_user(0x200);
}

void keyboard_post_init_user(void) {
    load_layer_config_from_eeprom();
}

// --- Keymap Definition ---
// 25-key layout for right side
// Order: k03, k04, k02, k05, k01, k00, k13, k14, k12, k15, k11, k10, k23, k24, k22, k26, k25, k21, k20, k36, k33, k34, k32, k35, k31
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_right(KC_U, KC_O, KC_Y, KC_I, KC_P, KC_BSPC, KC_J, KC_K, KC_H, KC_L, KC_SCLN, KC_QUOT, KC_COMM, KC_N, KC_DOT, KC_ENT, KC_M, KC_SLSH, KC_RSFT, TMB_MODE, KC_RGUI, KC_RALT, KC_RCTL, MO(1), KC_EQL),
    [1] = LAYOUT_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR, KC_TRNS),
    [2] = LAYOUT_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [3] = LAYOUT_right(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

// --- Process Record User ---
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    register_oled_activity();

    switch (keycode) {
        case ACT_DOWN:
            if (record->event.pressed) {
                if (current_actuation_index > 0) {
                    current_actuation_index--;
                    actuation = actuation_values[current_actuation_index];
                    // Global actuation, no per-layer index to update
                    save_layer_config_to_eeprom();
                    showing_actuation = true;
                    actuation_display_timer = timer_read32();
                    oled_clear();
                }
            }
            return false;

        case ACT_UP:
            if (record->event.pressed) {
                if (current_actuation_index < 4) {
                    current_actuation_index++;
                    actuation = actuation_values[current_actuation_index];
                    // Global actuation, no per-layer index to update
                    save_layer_config_to_eeprom();
                    showing_actuation = true;
                    actuation_display_timer = timer_read32();
                    oled_clear();
                }
            }
            return false;

        case ACT_RESET:
            if (record->event.pressed) {
                current_actuation_index = 2;
                actuation = actuation_values[current_actuation_index];
                // Global actuation, no per-layer index to update
                save_layer_config_to_eeprom();
                showing_actuation = true;
                actuation_display_timer = timer_read32();
                oled_clear();
            }
            return false;

        case TMB_MODE:
            if (record->event.pressed) {
                current_mode = (current_mode + 1) % MODE_COUNT;
                layer_modes[get_highest_layer(layer_state)] = current_mode;
                save_layer_config_to_eeprom();
            }
            return false;

        case CL_FWD:
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                if (current_layer >= LAYER_CYCLE_START && current_layer <= LAYER_CYCLE_END) {
                    uint8_t next_layer = current_layer + 1;
                    if (next_layer > LAYER_CYCLE_END) {
                        next_layer = LAYER_CYCLE_START;
                    }
                    layer_move(next_layer);
                }
            }
            return false;

        case CL_BWD:
            if (record->event.pressed) {
                uint8_t current_layer = get_highest_layer(layer_state);
                if (current_layer >= LAYER_CYCLE_START && current_layer <= LAYER_CYCLE_END) {
                    int8_t prev_layer = current_layer - 1;
                    if (prev_layer < LAYER_CYCLE_START) {
                        prev_layer = LAYER_CYCLE_END;
                    }
                    layer_move(prev_layer);
                }
            }
            return false;
    }
    return true;
}

// --- Layer State Callback ---
layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t new_layer = get_highest_layer(state);
    current_mode = layer_modes[new_layer];
    // Actuation is global
    return state;
}

// --- Encoder Map ---
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(CL_BWD, CL_FWD) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
