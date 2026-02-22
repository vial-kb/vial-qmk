#include QMK_KEYBOARD_H
#include "bipedalambi.h"
#include "analog.h"
#include "dynamic_keymap.h"
#include "transactions.h"

// --- Joystick Split Transport ---
// Joystick ADC is on left half (GP28/GP29). When right is master, slave handler
// reads ADC and master polls via RPC to get values for keycode processing.
typedef struct {
    int16_t joy_x;
    int16_t joy_y;
} joystick_sync_t;

void joystick_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    joystick_sync_t *joy = (joystick_sync_t *)out_data;
    joy->joy_y = analogReadPin(GP28) - 512;
    joy->joy_x = -(analogReadPin(GP29) - 512);
}

// --- State Sync (master → slave for OLED display) ---
typedef struct {
    uint8_t mode;
} state_sync_t;

void state_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    const state_sync_t *state = (const state_sync_t *)in_data;
    current_mode = state->mode;
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
    ENC_MOD,
    KC_JOYSTICK_BUTTON
};

// --- Per-Layer State ---
static uint8_t layer_modes[4] = {MODE_CUSTOM_KEYS, MODE_CUSTOM_KEYS, MODE_CUSTOM_KEYS, MODE_CUSTOM_KEYS};
// static uint8_t layer_actuation_indices[4] = {2, 2, 2, 2}; // Removed for global actuation
const uint16_t actuation_values[] = {352, 320, 256, 128, 64};
uint8_t current_actuation_index = 2;

// Joystick custom key state
bool customkeys[4];

// Encoder modifier state
bool enc_mod_held = false;

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
        layer_modes[i] = (mode < MODE_COUNT) ? mode : MODE_CUSTOM_KEYS;
    }
    // Bits 8-10: Global actuation index
    uint8_t act_idx = (data >> 8) & 0x07;
    current_actuation_index = (act_idx <= 4) ? act_idx : 2;

    current_mode = layer_modes[0];
    actuation = actuation_values[current_actuation_index];
}

void eeconfig_init_user(void) {
    // Default: all layers MODE_CUSTOM_KEYS (0), actuation_index = 2 (middle)
    // Encoding: bits 0-7 = layer modes (2 bits each), bits 8-10 = actuation index
    // (0 << 0) | (0 << 2) | (0 << 4) | (0 << 6) | (2 << 8) = 0x200
    eeconfig_update_user(0x200);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_JOYSTICK, joystick_sync_slave_handler);
    transaction_register_rpc(USER_SYNC_STATE, state_sync_slave_handler);
    debug_enable = true;
    debug_matrix = true;
    load_layer_config_from_eeprom();
    dprintf("SPLIT: master=%d left=%d\n", is_keyboard_master(), is_keyboard_left());
}

void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
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
        ENC_MOD,  KC_RGUI, KC_RALT, KC_RCTL, MO(1),  KC_EQL
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

        case TMB_MODE:
            if (record->event.pressed) {
                current_mode = (current_mode + 1) % MODE_COUNT;
                layer_modes[get_highest_layer(layer_state)] = current_mode;
                save_layer_config_to_eeprom();
            }
            return false;

        case CL_FWD:
            if (record->event.pressed) {
                if (enc_mod_held) {
                    // Shift to actuation up
                    if (current_actuation_index < 4) {
                        current_actuation_index++;
                        actuation = actuation_values[current_actuation_index];
                        save_layer_config_to_eeprom();
                        showing_actuation = true;
                        actuation_display_timer = timer_read32();
#ifdef OLED_ENABLE
                        oled_clear();
#endif
                    }
                } else {
                    uint8_t current_layer = get_highest_layer(layer_state);
                    if (current_layer >= LAYER_CYCLE_START && current_layer <= LAYER_CYCLE_END) {
                        uint8_t next_layer = current_layer + 1;
                        if (next_layer > LAYER_CYCLE_END) {
                            next_layer = LAYER_CYCLE_START;
                        }
                        layer_move(next_layer);
                    }
                }
            }
            return false;

        case CL_BWD:
            if (record->event.pressed) {
                if (enc_mod_held) {
                    // Shift to actuation down
                    if (current_actuation_index > 0) {
                        current_actuation_index--;
                        actuation = actuation_values[current_actuation_index];
                        save_layer_config_to_eeprom();
                        showing_actuation = true;
                        actuation_display_timer = timer_read32();
#ifdef OLED_ENABLE
                        oled_clear();
#endif
                    }
                } else {
                    uint8_t current_layer = get_highest_layer(layer_state);
                    if (current_layer >= LAYER_CYCLE_START && current_layer <= LAYER_CYCLE_END) {
                        int8_t prev_layer = current_layer - 1;
                        if (prev_layer < LAYER_CYCLE_START) {
                            prev_layer = LAYER_CYCLE_END;
                        }
                        layer_move(prev_layer);
                    }
                }
            }
            return false;

        case ENC_MOD:
            enc_mod_held = record->event.pressed;
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

// --- Joystick Processing ---
// Processes joystick ADC values into keycodes. Called from matrix_scan_user
// (left-as-master) or housekeeping_task_user (right-as-master via split transport).
// Joystick custom keys are read from these matrix positions (configurable in Vial):
//   Up:    row 0, col 7
//   Down:  row 1, col 7
//   Left:  row 2, col 7
//   Right: row 3, col 7
static void process_joystick(int16_t joy_x, int16_t joy_y) {
    if (current_mode == MODE_CUSTOM_KEYS) {
        // Custom keys mode: fire directional keycodes from dynamic keymap

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
    } else if (current_mode == MODE_SCROLLING) {
        // Scroll mode: send mouse wheel keycodes based on ADC deflection
        // Uses same actuation threshold as custom keys for consistent feel
        static bool scroll_active[4] = {false, false, false, false};

        // Scroll Down (Y < -actuation, joystick pushed up → content scrolls up)
        if (!scroll_active[0] && joy_y < -actuation) {
            scroll_active[0] = true;
            tap_code(KC_MS_WH_DOWN);
        } else if (scroll_active[0] && joy_y > -actuation) {
            scroll_active[0] = false;
        }

        // Scroll Up (Y > actuation, joystick pushed down → content scrolls down)
        if (!scroll_active[1] && joy_y > actuation) {
            scroll_active[1] = true;
            tap_code(KC_MS_WH_UP);
        } else if (scroll_active[1] && joy_y < actuation) {
            scroll_active[1] = false;
        }

        // Scroll Right (X < -actuation, joystick pushed left → content scrolls left)
        if (!scroll_active[2] && joy_x < -actuation) {
            scroll_active[2] = true;
            tap_code(KC_MS_WH_RIGHT);
        } else if (scroll_active[2] && joy_x > -actuation) {
            scroll_active[2] = false;
        }

        // Scroll Left (X > actuation, joystick pushed right → content scrolls right)
        if (!scroll_active[3] && joy_x > actuation) {
            scroll_active[3] = true;
            tap_code(KC_MS_WH_LEFT);
        } else if (scroll_active[3] && joy_x < actuation) {
            scroll_active[3] = false;
        }
    }
}

// --- Matrix Scan User ---
void matrix_scan_user(void) {
    // Joystick: only read ADC + process on left-as-master (direct hardware access)
    // When right is master, housekeeping_task_user polls via split transport instead
    if (is_keyboard_left() && is_keyboard_master()) {
        int16_t joy_y = analogReadPin(GP28) - 512;
        int16_t joy_x = -(analogReadPin(GP29) - 512);
        process_joystick(joy_x, joy_y);
    }
}

// --- Housekeeping Task (Split Transport Polling) ---
void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        // Sync state (current_mode) to slave for OLED display
        static uint32_t last_state_sync = 0;
        if (timer_elapsed32(last_state_sync) > 100) {  // 10Hz — OLED doesn't need faster
            state_sync_t state = {.mode = current_mode};
            transaction_rpc_send(USER_SYNC_STATE, sizeof(state), &state);
            last_state_sync = timer_read32();
        }

        // When right is master, poll joystick ADC from left (slave) via split transport
        if (!is_keyboard_left()) {
            static uint32_t last_joy_sync = 0;
            if (timer_elapsed32(last_joy_sync) > 10) {  // 100Hz polling
                joystick_sync_t joy = {0, 0};
                if (transaction_rpc_recv(USER_SYNC_JOYSTICK, sizeof(joy), &joy)) {
                    process_joystick(joy.joy_x, joy.joy_y);
                }
                last_joy_sync = timer_read32();
            }
        }
    }
}

// --- Pointing Device Task (TPS43 pass-through) ---
// The TPS43 azoteq_iqs5xx driver handles gestures internally:
//   - x/y for single-finger cursor movement
//   - h/v for two-finger scroll
//   - buttons for taps, swipes, press-and-hold
//
// Phantom right-click filter (right-side master only):
// The TPS43 fires false two_finger_tap (~3s after idle) due to EMI when
// the right side is USB master. A 2s activity gate filters these.
// Double two-finger-tap within 500ms overrides the gate.
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    static uint32_t last_touch_time = 0;
    static uint32_t suppressed_btn2_time = 0;
    static bool     awaiting_double_tap = false;

    // Any movement, scroll, or tap (BUTTON1) counts as real touch activity
    if (mouse_report.x != 0 || mouse_report.y != 0 ||
        mouse_report.h != 0 || mouse_report.v != 0 ||
        (mouse_report.buttons & MOUSE_BTN1)) {
        last_touch_time = timer_read32();
    }

    if (mouse_report.x != 0 || mouse_report.y != 0) register_oled_activity();

    // Only filter when right side is USB master (phantom doesn't occur with left master)
    if (!is_keyboard_left() && is_keyboard_master()) {
        bool idle = timer_elapsed32(last_touch_time) > 2000;

        if (idle && (mouse_report.buttons & MOUSE_BTN2)) {
            if (awaiting_double_tap && timer_elapsed32(suppressed_btn2_time) < 500) {
                // Double tap override — let it through and reset state
                awaiting_double_tap = false;
            } else {
                // First suppressed tap — start double-tap window
                suppressed_btn2_time = timer_read32();
                awaiting_double_tap = true;
                mouse_report.buttons &= ~MOUSE_BTN2;
            }
        }

        // Expire double-tap window
        if (awaiting_double_tap && timer_elapsed32(suppressed_btn2_time) > 500) {
            awaiting_double_tap = false;
        }
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
// Rotation is remappable in Vial. When ENC_MOD is held, CL_FWD/CL_BWD
// are intercepted in process_record_user to do ACT_UP/ACT_DOWN instead.
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(CL_BWD, CL_FWD) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
