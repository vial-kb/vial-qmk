#include QMK_KEYBOARD_H
#include "bipedalambi.h"
#include "analog.h"
#include "dynamic_keymap.h"

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
    // Bits 0-7: Layer modes (2 bits per layer * 4 layers)
    for (int i = 0; i < 4; i++) {
        uint32_t mode = (uint32_t)layer_modes[i] & 0x03;
        data |= mode << (i * 2);
    }
    // Bits 8-10: Global actuation index (3 bits)
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
    debug_enable = true;
    debug_matrix = true;
    load_layer_config_from_eeprom();
    dprintf("SPLIT: master=%d left=%d\n", is_keyboard_master(), is_keyboard_left());
}

// --- Keymap Definition ---
// Unified 54-key layout: Left (29 keys) + Right (25 keys)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_bipedalambi(
        /* Left */
        KC_E,    KC_W,    KC_R,    KC_ESC,  KC_Q,    KC_T,
        KC_D,    KC_S,    KC_F,    KC_TAB,  KC_A,    KC_G,    KC_UP,
        KC_C,    KC_X,    KC_V,    KC_LSFT, KC_Z,    KC_B,    KC_SPC,  KC_LEFT, TMB_MODE, KC_RGHT,
        KC_LGUI, KC_LCTL, KC_LALT, KC_MINS, MO(1),   KC_DOWN,
        /* Right */
        KC_U,    KC_O,    KC_Y,    KC_I,    KC_P,    KC_BSPC,
        KC_J,    KC_K,    KC_H,    KC_L,    KC_SCLN, KC_QUOT,
        KC_COMM, KC_N,    KC_DOT,  KC_ENT,  KC_M,    KC_SLSH, KC_RSFT,
        TMB_MODE, KC_RGUI, KC_RALT, KC_RCTL, MO(1),  KC_EQL
    ),
    [1] = LAYOUT_bipedalambi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
    ),
    [2] = LAYOUT_bipedalambi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT_bipedalambi(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
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
#ifdef OLED_ENABLE
                    oled_clear();
#endif
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
#ifdef OLED_ENABLE
                    oled_clear();
#endif
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
#ifdef OLED_ENABLE
                oled_clear();
#endif
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
    // Actuation is global, so we don't change it when layer changes
    // current_actuation_index is already correct
    // actuation is already correct
    return state;
}

// --- Encoder Map ---
// Encoder is on right PCB only; left encoder arrays are empty so this is a no-op locally.
// Data must still be present for split sync.
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(CL_BWD, CL_FWD) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
