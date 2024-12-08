#include QMK_KEYBOARD_H

#ifdef RGBLIGHT_ENABLE
    const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED});
    const rgblight_segment_t PROGMEM osm_shift_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_YELLOW});

    const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(capslock_layer, osm_shift_layer);
    void keyboard_post_init_user(void) { rgblight_layers = rgb_layers; }

    /* light up led in red when caps lock in on */
    bool led_update_user(led_t led_state) {
        rgblight_set_layer_state(0, led_state.caps_lock);
        return true;
    }

    /* light up led in yellow when sticky shift is activated */
    void oneshot_mods_changed_user(uint8_t mods) {
      if (mods & MOD_MASK_SHIFT) { rgblight_set_layer_state(1, true); }
      if (!mods) { rgblight_set_layer_state(1, false); }
    }
#endif

/* default empty layout */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x5_2(
                 KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                 KC_TRNS, KC_TRNS, KC_TRNS,                           KC_TRNS, KC_TRNS, KC_TRNS,
                                      KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS
    )
};
