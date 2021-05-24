/* Copyright 2021 FluxLab n kaz
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

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %u, row: %u, pressed: %b, time: %u, interrupt: %b, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
  return true;
}
*/
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum custom_layers {
    ALPHAS,
    NUM_SYM,
    NAV_eSYM,
    ADMIN,
};
#define EMOJI LGUI(KC_SCLN)
#define LOWER  MO(NUM_SYM)
#define RAISE  MO(NAV_eSYM)
#define POWPOW MO(ADMIN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty */
[ALPHAS] = LAYOUT(
   KC_ESC,		  KC_Q,    KC_W,    KC_E,  KC_R,   	KC_T,    	KC_Y,	KC_U,	 KC_I,	  KC_O,	   KC_P,	KC_DEL,
   KC_TAB,  	  KC_A,    KC_S,    KC_D,  KC_F,   	KC_G,    	KC_H,	KC_J,    KC_K,    KC_L,	   KC_QUOT, KC_BSPC,
   EMOJI, KC_Z,    KC_X,    KC_C,  KC_V,   	KC_B,		KC_N,	KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
   KC_LCTL,		  KC_LGUI, KC_LALT, LOWER, XXXXXXX,	KC_LSFT,	KC_SPC,	XXXXXXX, RAISE,	  KC_MINS, KC_SCLN, KC_EQL
),

/* Numbers and symbols */
[NUM_SYM] = LAYOUT(
  KC_NLCK, _______, KC_LPRN, KC_RPRN, KC_AMPR, KC_ASTR,		KC_P7, KC_P8,	KC_P9,	KC_PSLS, KC_PAST, KC_TRNS,
  KC_TRNS, _______, _______, KC_CIRC, KC_PERC, KC_DLR,		KC_P4, KC_P5,	KC_P6,	KC_PMNS, _______, KC_TRNS,
  POWPOW,  _______, _______, KC_HASH, KC_AT,   KC_EXLM,		KC_P1, KC_P2,	KC_P3,	KC_PPLS, _______, KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, XXXXXXX, KC_TRNS,		KC_P0, XXXXXXX,	POWPOW, KC_PDOT, KC_EQL,  KC_PENT
),

/* Nav and extended symbols */
[NAV_eSYM] = LAYOUT(
  KC_ESC,  _______, KC_UP,   _______, _______, _______,		_______, _______, _______, KC_LPRN,	KC_RPRN, KC_TRNS,
  KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,		_______, KC_PGUP, _______, KC_LBRC, KC_RBRC, KC_TRNS,
  KC_TRNS, _______, _______, _______, _______, _______,		KC_HOME, KC_PGDN, KC_END,  KC_BSLS, KC_GRV,  KC_TRNS,
  KC_TRNS, KC_TRNS, KC_TRNS, POWPOW,  XXXXXXX, KC_TRNS,		KC_SPC,	 XXXXXXX, KC_TRNS, _______, _______, POWPOW
),

/* F-Keys and superuser functions (usable single handed)*/
[ADMIN] = LAYOUT(
  RESET,   DEBUG,	KC_WAKE, XXXXXXX, XXXXXXX, XXXXXXX,		KC_F9,	 KC_F10,  KC_F11,  KC_F12,	XXXXXXX, RESET,
  KC_TRNS, XXXXXXX, KC_SLEP, XXXXXXX, XXXXXXX, XXXXXXX,		KC_F5,	 KC_F6,   KC_F7,   KC_F8,	XXXXXXX, RESET,
  KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,		KC_F1,	 KC_F2,   KC_F3,   KC_F4,	XXXXXXX, RESET,
  KC_TRNS, KC_TRNS,	KC_TRNS, KC_TRNS, XXXXXXX, KC_TRNS,		KC_TRNS, XXXXXXX, KC_TRNS, XXXXXXX, DEBUG,	 KC_TRNS
)


};
