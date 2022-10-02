// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _RGB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        TO(_RGB),	KC_MSEL,	KC_MPRV,	KC_MNXT,	KC_MPLY
    ),
    [_RGB] = LAYOUT(
        TO(_BASE),	RGB_VAI,	RGB_TOG,	RGB_VAD, 	RGB_TOG
    )
};

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
			if(clockwise){
				tap_code(KC_VOLU);
			} else {
				tap_code(KC_VOLD);
			}		
        }
    } 
	return true;
};

#endif