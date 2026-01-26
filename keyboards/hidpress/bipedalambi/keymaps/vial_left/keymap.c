#include QMK_KEYBOARD_H
#include "bipedalambi.h"
#include "analog.h"
#include "dynamic_keymap.h"

// --- Left Side Layout Macro ---
// Based on KLE raw data - 29 keys
// Matrix positions: rows 0-3, cols 0-7
#define LAYOUT_left( \
    k03, \
    k02, k04, \
    k00, k01, k05, \
    k13, \
    k12, k14, \
    k10, k11, k15, k07, \
    k23, \
    k22, k24, \
    k20, k21, k25, k26, k27, k36, k37, \
    k33, \
    k32, k34, \
    k31, k35, k17 \
) { \
    { k00, k01, k02, k03, k04, k05, KC_NO, k07 }, \
    { k10, k11, k12, k13, k14, k15, KC_NO, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26,   k27 }, \
    { KC_NO, k31, k32, k33, k34, k35, k36, k37 } \
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
static enum pointing_device_mode layer_modes[4] = {MODE_MOUSE, MODE_MOUSE, MODE_MOUSE, MODE_MOUSE};
static uint8_t layer_actuation_indices[4] = {2, 2, 2, 2};
const uint16_t actuation_values[] = {352, 320, 256, 128, 64};
uint8_t current_actuation_index = 2;

// Scroll State
#define SCROLL_DIVISOR_H 24.0
#define SCROLL_DIVISOR_V 24.0
float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;
bool scroll_inverted = false;

// Joystick custom key state
bool customkeys[4];

// Layer cycle bounds
#define LAYER_CYCLE_START 0
#define LAYER_CYCLE_END 3

// --- EEPROM Persistence ---
void save_layer_config_to_eeprom(void) {
    uint32_t data = 0;
    for (int i = 0; i < 4; i++) {
        uint32_t layer_data = ((uint32_t)layer_modes[i] & 0x03) |
                              (((uint32_t)layer_actuation_indices[i] & 0x07) << 2);
        data |= layer_data << (i * 5);
    }
    eeconfig_update_user(data);
}

void load_layer_config_from_eeprom(void) {
    uint32_t data = eeconfig_read_user();
    for (int i = 0; i < 4; i++) {
        uint8_t layer_data = (data >> (i * 5)) & 0x1F;
        uint8_t mode = layer_data & 0x03;
        uint8_t act_idx = (layer_data >> 2) & 0x07;
        layer_modes[i] = (mode < MODE_COUNT) ? mode : MODE_MOUSE;
        layer_actuation_indices[i] = (act_idx <= 4) ? act_idx : 2;
    }
    current_mode = layer_modes[0];
    current_actuation_index = layer_actuation_indices[0];
    actuation = actuation_values[current_actuation_index];
}

void keyboard_post_init_user(void) {
    load_layer_config_from_eeprom();
}

// --- Keymap Definition ---
// 29-key layout for left side
// Order: k03, k02, k04, k00, k01, k05, k13, k12, k14, k10, k11, k15, k07, k23, k22, k24, k20, k21, k25, k26, k27, k36, k37, k33, k32, k34, k31, k35, k17
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_left(KC_E, KC_W, KC_R, KC_ESC, KC_Q, KC_T, KC_D, KC_S, KC_F, KC_TAB, KC_A, KC_G, KC_UP, KC_C, KC_X, KC_V, KC_LSFT, KC_Z, KC_B, KC_SPC, KC_LEFT, KC_BTN1, KC_RGHT, KC_LGUI, KC_LCTL, KC_LALT, KC_MINS, MO(1), KC_DOWN),
    [1] = LAYOUT_left(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [2] = LAYOUT_left(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
    [3] = LAYOUT_left(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
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
                    layer_actuation_indices[get_highest_layer(layer_state)] = current_actuation_index;
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
                    layer_actuation_indices[get_highest_layer(layer_state)] = current_actuation_index;
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
                layer_actuation_indices[get_highest_layer(layer_state)] = current_actuation_index;
                save_layer_config_to_eeprom();
                showing_actuation = true;
                actuation_display_timer = timer_read32();
                oled_clear();
            }
            return false;

        case SCROLL_DIR:
            if (record->event.pressed) {
                scroll_inverted = !scroll_inverted;
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

// --- Joystick Keycode Handler ---
// Custom keycodes (QK_KB_0+) need to go through process_record_user
// Standard keycodes can use register/unregister directly
static void handle_joystick_keycode(uint16_t keycode, bool pressed) {
    if (keycode >= QK_KB_0 && keycode <= QK_KB_31) {
        // Custom keycodes need to be processed through process_record
        keyrecord_t record = {
            .event = {
                .key = {.row = 0, .col = 7},
                .pressed = pressed,
                .time = timer_read()
            }
        };
        process_record_user(keycode, &record);
    } else {
        // Standard keycodes
        if (pressed) {
            register_code16(keycode);
        } else {
            unregister_code16(keycode);
        }
    }
}

// --- Matrix Scan User (Joystick Logic) ---
// Joystick custom keys are read from these matrix positions (configurable in Vial):
//   Up:    row 0, col 7
//   Down:  row 1, col 7
//   Left:  row 2, col 7
//   Right: row 3, col 7
void matrix_scan_user(void) {
    if (current_mode != MODE_CUSTOM_KEYS) return;

    // Read joystick position (512 is center of 10-bit ADC)
    int16_t joy_y = analogReadPin(GP28) - 512;
    int16_t joy_x = analogReadPin(GP29) - 512;

    // Up (Y < -actuation) - reads keycode from [0,7]
    if (!customkeys[0] && joy_y < -actuation) {
        customkeys[0] = true;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 0, 7);
        handle_joystick_keycode(keycode, true);
    } else if (customkeys[0] && joy_y > -actuation) {
        customkeys[0] = false;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 0, 7);
        handle_joystick_keycode(keycode, false);
    }

    // Down (Y > actuation) - reads keycode from [1,7]
    if (!customkeys[1] && joy_y > actuation) {
        customkeys[1] = true;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 1, 7);
        handle_joystick_keycode(keycode, true);
    } else if (customkeys[1] && joy_y < actuation) {
        customkeys[1] = false;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 1, 7);
        handle_joystick_keycode(keycode, false);
    }

    // Left (X < -actuation) - reads keycode from [2,7]
    if (!customkeys[2] && joy_x < -actuation) {
        customkeys[2] = true;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 2, 7);
        handle_joystick_keycode(keycode, true);
    } else if (customkeys[2] && joy_x > -actuation) {
        customkeys[2] = false;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 2, 7);
        handle_joystick_keycode(keycode, false);
    }

    // Right (X > actuation) - reads keycode from [3,7]
    if (!customkeys[3] && joy_x > actuation) {
        customkeys[3] = true;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 3, 7);
        handle_joystick_keycode(keycode, true);
    } else if (customkeys[3] && joy_x < actuation) {
        customkeys[3] = false;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 3, 7);
        handle_joystick_keycode(keycode, false);
    }
}

// --- Pointing Device Task (Mouse/Scroll Mode) ---
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (mouse_report.x != 0 || mouse_report.y != 0) register_oled_activity();

    if (current_mode == MODE_SCROLLING) {
        scroll_accumulated_h -= (float)mouse_report.x / SCROLL_DIVISOR_H;
        scroll_accumulated_v += (scroll_inverted ? -1 : 1) * (float)mouse_report.y / SCROLL_DIVISOR_V;

        mouse_report.h = (int8_t)scroll_accumulated_h;
        mouse_report.v = (int8_t)scroll_accumulated_v;

        scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
        scroll_accumulated_v -= (int8_t)scroll_accumulated_v;

        mouse_report.x = 0;
        mouse_report.y = 0;
    } else if (current_mode == MODE_CUSTOM_KEYS) {
        mouse_report.x = 0;
        mouse_report.y = 0;
    }
    return mouse_report;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t new_layer = get_highest_layer(state);
    current_mode = layer_modes[new_layer];
    current_actuation_index = layer_actuation_indices[new_layer];
    actuation = actuation_values[current_actuation_index];
    return state;
}

// Note: Encoder is on right PCB only. ACT_UP/ACT_DOWN are mapped to physical keys.
