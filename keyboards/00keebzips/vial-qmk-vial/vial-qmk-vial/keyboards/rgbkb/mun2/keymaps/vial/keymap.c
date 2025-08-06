/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum sol_layers {
  _QWERTY,
  _COLEMAK,
  _FN,
  _ADJUST
};

enum zygo_keycodes {
  // Disables touch processing
  TCH_TOG = SAFE_RANGE,
  MENU_BTN,
  MENU_UP,
  MENU_DN,
  RGB_RST
};

#define FN       MO(_FN)
#define ADJUST   MO(_ADJUST)
#define COLEMAK  DF(_COLEMAK)
#define QWERTY   DF(_QWERTY)
#define FN_CAPS  LT(_FN, KC_CAPS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
   QK_GESC,      KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_MINS,      KC_EQL,     KC_6,     KC_7,     KC_8,     KC_9,    KC_0,     KC_BSPC,
    KC_TAB,      KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_LBRC,     KC_RBRC,     KC_Y,     KC_U,     KC_I,     KC_O,    KC_P,     KC_BSLS,
    FN_CAPS,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_LPRN,     KC_RPRN,     KC_H,     KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_QUOT,
    KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_LCBR,     KC_RCBR,     KC_N,     KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,  KC_ENT,
    KC_LCTL,  KC_LGUI,  KC_LALT,  RGB_TOG,   ADJUST,   KC_SPC,      KC_SPC,      KC_SPC,     KC_SPC,   KC_LEFT,  KC_DOWN,  KC_UP,   KC_RIGHT, KC_RCTL,

    KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,
    KC_VOLU,  KC_VOLD,  KC_MNXT,  KC_MPLY,  KC_MPRV,                      KC_VOLU,  KC_VOLD,  KC_MNXT,  KC_MPLY,  KC_MPRV
  ), 

  [_COLEMAK] = LAYOUT(
    QK_GESC,     KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_F1,     KC_F5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,  KC_BSPC,
     KC_TAB,     KC_Q,     KC_W,     KC_F,     KC_P,     KC_B,     KC_F2,     KC_F6,     KC_J,     KC_L,     KC_U,     KC_Y,  KC_SCLN,  KC_BSLS,
    FN_CAPS,     KC_A,     KC_R,     KC_S,     KC_T,     KC_G,     KC_F3,     KC_F7,     KC_K,     KC_N,     KC_E,     KC_I,     KC_O,  KC_QUOT,
    KC_LSFT,     KC_Z,     KC_X,     KC_C,     KC_D,     KC_V,     KC_F4,     KC_F8,     KC_M,     KC_H,  KC_COMM,   KC_DOT,  KC_SLSH,   KC_ENT,
    KC_LCTL,  KC_LGUI,  KC_LALT,  RGB_TOG,   ADJUST,   KC_SPC,     KC_SPC,     KC_SPC,   KC_SPC,   KC_LEFT,  KC_DOWN,  KC_UP,   KC_RIGHT, KC_RCTL, 

    KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,  KC_VOLD,  KC_VOLU,
    KC_VOLU,  KC_VOLD,  KC_MNXT,  KC_MPLY,  KC_MPRV,                      KC_VOLU,  KC_VOLD,  KC_MNXT,  KC_MPLY,  KC_MPRV
  ),

  [_FN] = LAYOUT(
    _______,  KC_F1,    KC_F2,   KC_F3,    KC_F4,    KC_F5,     KC_F11,   KC_F12,  KC_F6,     KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    _______,  KC_PGDN,  KC_UP,   KC_PGUP,   _______,  _______,  _______,  _______,  _______,  KC_PGDN,  KC_UP,    KC_PGUP,  KC_PSCR,  KC_HOME,
    _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,  _______,  _______,  _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_INS,   KC_END,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  RGB_MOD,  _______,  _______,  _______,  _______,  _______,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,

    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______
  ),

  [_ADJUST] =  LAYOUT(
    _______,  KC_F1,    KC_F2,   KC_F3,    KC_F4,    KC_F5,     KC_F11,   KC_F12,  KC_F6,     KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,
    _______,  RGB_SAD,  RGB_VAI,  RGB_SAI,  QK_BOOT,  _______,  _______,  _______,  _______,  KC_P7,   KC_P8,   KC_P9,   _______, _______,
    _______,  RGB_HUD,  RGB_VAD,  RGB_HUI,  RGB_RST,  _______,  _______,  _______,  _______,  KC_P4,   KC_P5,   KC_P6,   _______, _______,
    _______,  RGB_SPD, _______,   RGB_SPI,  _______,  _______,  _______,  _______,  _______,  KC_P1,   KC_P2,   KC_P3,   _______, _______,
    _______,  _______,  _______,  RGB_MOD,  _______,  _______,  _______,  _______,  _______,  KC_P0,   KC_PDOT, KC_NUM,  QWERTY,  COLEMAK,

    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode)
    {
        case MENU_BTN:
            if (record->event.pressed) {
                rgb_menu_selection();
            }
            return false;
        case MENU_UP:
            if (record->event.pressed) {
                rgb_menu_action(true);
            }
            return false;
        case MENU_DN:
            if (record->event.pressed) {
                rgb_menu_action(false);
            }
            return false;
        case RGB_RST:
            if (record->event.pressed) {
                eeconfig_update_rgb_matrix_default();
            }
            return false;
        case TCH_TOG:
            if (record->event.pressed) {
                touch_encoder_toggle();
            }
            return false;  // Skip all further processing of this key
        default:
            return true;
    }
}

void render_layer_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("QWRTY"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("Colemk"), false);
            break;
        case _FN:
            oled_write_ln_P(PSTR("FN   "), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Adjst"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}