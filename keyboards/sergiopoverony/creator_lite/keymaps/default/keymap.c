#include QMK_KEYBOARD_H

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

/* Layout */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_HOME] = LAYOUT(
     KC_1, KC_2, KC_3, KC_4, TO(_RED)
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
