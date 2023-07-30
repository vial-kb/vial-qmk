/* Copyright 2019-2020 DMQ Design
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                KC_PGUP, KC_PSCR, KC_HOME, KC_MUTE,
                KC_PGDN, KC_UP, KC_END, G(KC_L),
                KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS,
                KC_DEL, KC_ENT, TO(1)
                ),
    [1] = LAYOUT(/* FKeys */
                KC_F13, KC_F14, KC_F15, KC_TRNS,
                KC_F16, KC_F17, KC_F18, KC_TRNS,
                KC_F19, KC_F20, KC_F21, KC_TRNS,
                KC_F22, KC_F23, TO(2)
                ), 
    [2] = LAYOUT(/* Numpad */
                KC_7, KC_8, KC_9, KC_TRNS,
                KC_4, KC_5, KC_6, KC_TRNS,
                KC_1, KC_2, KC_3, KC_TRNS,
                KC_0, RGB_TOG, TO(3)
                ),
    [3] = LAYOUT(/* RGB */
                RGB_M_P, RGB_M_B, RGB_M_R, RGB_TOG,
                RGB_M_SW, RGB_M_SN, RGB_M_K, KC_TRNS,
                RGB_M_X, RGB_M_G, RGB_M_T, KC_TRNS,
                RGB_RMOD, RGB_MOD, TO(0)
                ),                          
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_BRIU, KC_BRID),  ENCODER_CCW_CW(KC_WH_D, KC_WH_U)  },
    //                  Encoder 1                                     Encoder 2
    [1] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    //                  Encoder 1                                     Encoder 2
    [2] =   { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS)  },
    //                  Encoder 1                                     Encoder 2
    [3] =   { ENCODER_CCW_CW(RGB_VAD, RGB_VAI), ENCODER_CCW_CW(RGB_SAD, RGB_SAI),  ENCODER_CCW_CW(RGB_HUD, RGB_HUI)  },
    //                  Encoder 1                                     Encoder 2
};
#endif

#ifdef OLED_ENABLE
static const char *ANIMATION_NAMES[] = {
	"unknown",
	"static",
	"breathing I",
	"breathing II",
	"breathing III",
	"breathing IV",
	"rainbow mood I",
	"rainbow mood II",
	"rainbow mood III",
	"rainbow swirl I",
	"rainbow swirl II",
	"rainbow swirl III",
	"rainbow swirl IV",
	"rainbow swirl V",
	"rainbow swirl VI",
	"snake I",
	"snake II",
	"snake III",
	"snake IV",
	"snake V",
	"snake VI",
	"knight I",
	"knight II",
	"knight III",
	"christmas",
	"static gradient I",
	"static gradient II",
	"static gradient III",
	"static gradient IV",
	"static gradient V",
	"static gradient VI",
	"static gradient VII",
	"static gradient VIII",
	"static gradient IX",
	"static gradient X",
	"rgb test",
	"alternating",
	"twinkle I",
	"twinkle II",
	"twinkle III",
	"twinkle IV",
	"twinkle V",
	"twinkle VI"
};

void rgblight_get_mode_name(uint8_t mode, size_t bufsize, char *buf) {
    snprintf(buf, bufsize, "%-25s", ANIMATION_NAMES[mode]);
}
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees
}

bool oled_task_user(void) {
  // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("Function keys\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Numpad\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("RGB\n"), false);
            break;      
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
    oled_write_P(PSTR("                 uwu\n"), false);
    static char rgb_mode_name[30];
    rgblight_get_mode_name(rgblight_get_mode(), sizeof(rgb_mode_name), rgb_mode_name);

    oled_write_P(PSTR("RGB Mode: \n"), false);
    oled_write_ln(rgb_mode_name, false);
   
    return false;
}

#endif

