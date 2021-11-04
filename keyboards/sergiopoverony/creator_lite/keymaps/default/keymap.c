/*
Copyright 2020 David Doan

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#define WIN_TAB LGUI(KC_TAB)
#define WIN_LOCK LGUI(KC_L)
#define KC_WRAP KC_F24

/* default layers */
enum layers {
  _HOME = 0,
  _RED = 1,
  _BLUE = 2,
  _GREEN = 3,
};


/* Encoder with all layouts

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) {
	if (clockwise) {
		tap_code16(KC_RIGHT);
	} else {
		tap_code16(KC_LEFT);
    }
  }
  return true;
}
*/

/* Encoder function with layers function */
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        switch (get_highest_layer(layer_state)) {
			
            case _HOME:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
				
            case _RED:
                if (clockwise) {
                    tap_code(KC_MS_WH_UP);
                } else {
                    tap_code(KC_MS_WH_DOWN);
                }
                break;		
				
            case _BLUE:
			    if (clockwise) {
                    tap_code(KC_PGUP);
                } else {
                    tap_code(KC_PGDN);
                }
                break;
				
            case _GREEN:
            default:
                if (clockwise) {
					tap_code16(KC_LEFT);
                } else {
					tap_code16(KC_RIGHT);
                }
                break;
        }
    }
    return true;
}


/* Layout */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_HOME] = LAYOUT(
     M(YOUR_MACRO_1), KC_2, KC_3, KC_4, TO(_RED)
   ),
  [_RED] = LAYOUT(
     KC_1, KC_2, KC_3, KC_4, TO(_BLUE)
  ),
  [_BLUE] = LAYOUT(
     KC_1, KC_2, KC_3, KC_4, TO(_GREEN)
  ),
  [_GREEN] = LAYOUT(
     KC_1, KC_2, KC_3, KC_4, TO(_HOME)
  )
};

/* Select led layout */
layer_state_t layer_state_set_user(layer_state_t state)
{
    turn_off_leds();	
    switch (get_highest_layer(state))
    {
		case _HOME:
	turn_on_led(RED_LED);
	turn_on_led(BLUE_LED);	
		break;

		case _RED:
		turn_on_led(RED_LED);
		break;

		case _BLUE:
		turn_on_led(BLUE_LED);
		break;

		case _GREEN:
		turn_on_led(GREEN_LED);
		break;
	}
    return state;
};
