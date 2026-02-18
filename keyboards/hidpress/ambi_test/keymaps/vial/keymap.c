#include QMK_KEYBOARD_H
#include "ambi_test.h"
#include "analog.h"
#include "dynamic_keymap.h"

// --- Custom Keycodes ---
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
        uint32_t mode = (uint32_t)layer_modes[i] & 0x03;
        data |= mode << (i * 2);
    }
    data |= ((uint32_t)current_actuation_index & 0x07) << 8;
    eeconfig_update_user(data);
}

void load_layer_config_from_eeprom(void) {
    uint32_t data = eeconfig_read_user();
    for (int i = 0; i < 4; i++) {
        uint8_t mode = (data >> (i * 2)) & 0x03;
        layer_modes[i] = (mode < MODE_COUNT) ? mode : MODE_MOUSE;
    }
    uint8_t act_idx = (data >> 8) & 0x07;
    current_actuation_index = (act_idx <= 4) ? act_idx : 2;

    current_mode = layer_modes[0];
    actuation = actuation_values[current_actuation_index];
}

void eeconfig_init_user(void) {
    eeconfig_update_user(0x200);
}

void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
    load_layer_config_from_eeprom();
    dprintf("AMBI-TEST: master=%d left=%d\n", is_keyboard_master(), is_keyboard_left());
}

// --- Keymap Definition ---
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
        KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_SPC,
        KC_LCTL, KC_LGUI, KC_LALT, TMB_MODE, MO(1),
        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_ENT,
        MO(1),   KC_RALT, KC_RGUI, KC_RCTL, KC_EQL
    ),
    [1] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
        KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
        KC_TRNS, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_LBRC, KC_RBRC,
        KC_F6,   KC_F12,  KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [3] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
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
static void handle_joystick_keycode(uint16_t keycode, bool pressed) {
    if (keycode >= QK_KB_0 && keycode <= QK_KB_31) {
        keyrecord_t record = {
            .event = {
                .key = {.row = 0, .col = 7},
                .pressed = pressed,
                .time = timer_read()
            }
        };
        process_record_user(keycode, &record);
    } else {
        if (pressed) {
            register_code16(keycode);
        } else {
            unregister_code16(keycode);
        }
    }
}

// --- Matrix Scan User (Joystick Custom Keys Logic) ---
void matrix_scan_user(void) {
    if (current_mode != MODE_CUSTOM_KEYS) return;

    int16_t joy_y = analogReadPin(GP28) - 512;
    int16_t joy_x = analogReadPin(GP29) - 512;

    // Up (Y < -actuation)
    if (!customkeys[0] && joy_y < -actuation) {
        customkeys[0] = true;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 0, 7);
        handle_joystick_keycode(keycode, true);
    } else if (customkeys[0] && joy_y > -actuation) {
        customkeys[0] = false;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 0, 7);
        handle_joystick_keycode(keycode, false);
    }

    // Down (Y > actuation)
    if (!customkeys[1] && joy_y > actuation) {
        customkeys[1] = true;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 1, 7);
        handle_joystick_keycode(keycode, true);
    } else if (customkeys[1] && joy_y < actuation) {
        customkeys[1] = false;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 1, 7);
        handle_joystick_keycode(keycode, false);
    }

    // Left (X < -actuation)
    if (!customkeys[2] && joy_x < -actuation) {
        customkeys[2] = true;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 2, 7);
        handle_joystick_keycode(keycode, true);
    } else if (customkeys[2] && joy_x > -actuation) {
        customkeys[2] = false;
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 2, 7);
        handle_joystick_keycode(keycode, false);
    }

    // Right (X > actuation)
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
