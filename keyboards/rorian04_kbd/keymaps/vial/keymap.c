// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q, KC_W, KC_E, KC_R, QK_BOOT,
        KC_ENT,  KC_A, KC_S, KC_D, KC_F, KC_G,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,
                             KC_LALT, KC_SPC, KC_TAB
    ),
	[1] = LAYOUT_split_3x6_3(
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
                                    _______, _______,    _______
    ),
	[2] = LAYOUT_split_3x6_3(
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
                                    _______, _______,    _______
    ),
	[3] = LAYOUT_split_3x6_3(
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
                                    _______, _______,    _______
    ),
	[4] = LAYOUT_split_3x6_3(
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
                                    _______, _______,    _______
    ),
	[5] = LAYOUT_split_3x6_3(
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
                                    _______, _______,    _______
    ),
	[6] = LAYOUT_split_3x6_3(
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
                                    _______, _______,    _______
    ),
	[7] = LAYOUT_split_3x6_3(
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
        _______,  _______, _______, _______, _______,    _______,
                                    _______, _______,    _______
    )
};

#define value 40
// Change LED color based on layer
const rgblight_segment_t PROGMEM layer0_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 85, 255, value}       // color if layer 0
);

const rgblight_segment_t PROGMEM layer1_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 125, 255, value}       // color if layer 1
);

const rgblight_segment_t PROGMEM layer2_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 170, 255, value}       // color if layer 2
);

const rgblight_segment_t PROGMEM layer3_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 200, 255, value}       // color if layer 3
);

const rgblight_segment_t PROGMEM layer4_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 45, 255, value}       // color if layer 4
);

const rgblight_segment_t PROGMEM layer5_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 85, 0, value}       // color if layer 5
);

const rgblight_segment_t PROGMEM layer6_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, 0, 255, value}       // color if layer 6
);

const rgblight_segment_t PROGMEM layer7_rgb[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_OFF}       // color if layer 6
);


// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer0_rgb,	// Bottom layer
	layer1_rgb,    // Overrides above layers
    layer2_rgb,    // Overrides above layers
	layer3_rgb,    // Overrides above layers
	layer4_rgb,    // Overrides above layers
	layer5_rgb,    // Overrides above layers
	layer6_rgb,    // Overrides above layers
	layer7_rgb    // Overrides above layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;
}


//bellow code block checks and changes state of LED
layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, 0));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
	rgblight_set_layer_state(3, layer_state_cmp(state, 3));
	rgblight_set_layer_state(4, layer_state_cmp(state, 4));
	rgblight_set_layer_state(5, layer_state_cmp(state, 5));
	rgblight_set_layer_state(6, layer_state_cmp(state, 6));
	rgblight_set_layer_state(7, layer_state_cmp(state, 7));
    return state;
}