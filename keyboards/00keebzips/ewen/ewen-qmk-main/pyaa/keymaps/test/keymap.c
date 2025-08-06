/* Copyright 2021 konomu
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
#include "sten.h"
// #include "keymap_steno.h"
// #define IGNORE_MOD_TAP_INTERRUPT

// Steno Layers
#define EXTN	( PWR )

// Keys and chords that, once they appear, are added to every subsequent partial chord
// until the whole thing is sent.

// QMK Layers
#define STEN   0

uint32_t processQwerty(bool lookup) {
	// EXTN layer
	// Left hand
	P( EXTN | LSU,			SEND(KC_LALT));
	P( EXTN | LFT,			SEND(KC_LGUI));
	P( EXTN | LP,			SEND(KC_LSFT));
	P( EXTN | LH,			SEND(KC_LCTL));
	P( EXTN | MNO,			SEND(KC_VOLU));

	P( EXTN | LSD,			SEND(KC_LCTL); SEND(KC_Z));
	P( EXTN | LK,			SEND(KC_LCTL); SEND(KC_X));
	P( EXTN | LW,			SEND(KC_LCTL); SEND(KC_C));
	P( EXTN | LR,			SEND(KC_LCTL); SEND(KC_V));
	P( EXTN | NNO,			SEND(KC_VOLD));

	// Right hand
	P( EXTN | ST3,			SEND(KC_PGUP));
	P( EXTN | RF,			SEND(KC_HOME));
	P( EXTN | RP,			SEND(KC_UP));
	P( EXTN | RL,			SEND(KC_END));
	P( EXTN | RT,			SEND(KC_DEL));
	P( EXTN | RD,			SEND(KC_ESC));

	P( EXTN | ST4,			SEND(KC_PGDN));
	P( EXTN | RR,			SEND(KC_LEFT));
	P( EXTN | RB,			SEND(KC_DOWN));
	P( EXTN | RG,			SEND(KC_RGHT));
	P( EXTN | RS,			SEND(KC_DEL));
	P( EXTN | RZ,			SEND(KC_TAB));
	
	//Thumbs
	P( EXTN | LNO,			SEND(KC_LALT); SEND(KC_TAB));
	P( EXTN | LA,			SEND(KC_MUTE));
	P( EXTN | LO,			SEND(KC_BSPC));
	
	P( EXTN | RE,			SEND(KC_SPC));
	P( EXTN | RU,			SEND(KC_ENT));
	P( EXTN | RNO,			SEND(KC_SLEP));
	
	
	//COLE layer
	//Left hand
	P( LSU,					SEND(KC_Q));
	P( LFT,					SEND(KC_W));
	P( LP,					SEND(KC_F));
	P( LH,					SEND(KC_P));
	P( MNO,					SEND(KC_B));

	P( LSU | LSD,			SEND(KC_A));
	P( LFT | LK,			SEND(KC_R));
	P( LP  | LW,			SEND(KC_S));
	P( LH  | LR,			SEND(KC_T));
	P( MNO | NNO,			SEND(KC_G));

	P( LSD,					SEND(KC_Z));
	P( LK,					SEND(KC_X));
	P( LW,					SEND(KC_C));
	P( LR,					SEND(KC_D));
	P( NNO,					SEND(KC_V));

	// Right hand
	P( ST3,					SEND(KC_J));
	P( RF,					SEND(KC_L));
	P( RP,					SEND(KC_U));
	P( RL,					SEND(KC_Y));
	P( RT,					SEND(KC_QUOT));
	P( RD,					SEND(KC_MINS));

	P( ST3 | ST4,			SEND(KC_M));
	P( RF  | RR,			SEND(KC_N));
	P( RP  | RB,			SEND(KC_E));
	P( RG  | RL,			SEND(KC_I));
	P( RT  | RS,			SEND(KC_O));
	P( RZ  | RD,			SEND(KC_SCLN));

	P( ST4,					SEND(KC_K));
	P( RR,					SEND(KC_H));
	P( RB,					SEND(KC_COMM));
	P( RG,					SEND(KC_DOT));
	P( RS,					SEND(KC_SLSH));
	P( RZ,					SEND(KC_DEL));
	
	//Thumbs
	P( LNO,					SEND(KC_TAB));
	P( LA,					SEND(KC_LCTL));
	P( LO,					SEND(KC_BSPC));
	P( RE,					SEND(KC_SPC));
	P( RU,					SEND(KC_ENT));
	P( RNO,					SEND(KC_DEL));
	P( LNO | LA,			SEND(KC_LALT));
	P( LA | LO,				SEND(KC_LCTL); SEND(KC_LSFT));
	P( RE | RU,				SEND(KC_LALT));
	P( RU | RNO,			SEND(KC_LGUI));
	P( LA | RE | RU,		SEND(KC_LALT); SEND(KC_LSFT));
	P( LA | RU | RNO,		SEND(KC_LGUI); SEND(KC_LSFT));
	P( LNO | LA | RU | RNO,	SEND(KC_LCTL); SEND(KC_LSFT); SEND(KC_LALT); SEND(KC_LGUI));
	
	//Shifted characters left
	P( LO | LSU,				SEND(KC_LSFT); SEND(KC_Q));
	P( LO | LFT,				SEND(KC_LSFT); SEND(KC_W));
	P( LO | LP,					SEND(KC_LSFT); SEND(KC_F));
	P( LO | LH,					SEND(KC_LSFT); SEND(KC_P));
	P( LO | MNO,				SEND(KC_LSFT); SEND(KC_B));

	P( LO | LSU | LSD,			SEND(KC_LSFT); SEND(KC_A));
	P( LO | LFT | LK,			SEND(KC_LSFT); SEND(KC_R));
	P( LO | LP  | LW,			SEND(KC_LSFT); SEND(KC_S));
	P( LO | LH  | LR,			SEND(KC_LSFT); SEND(KC_T));
	P( LO | MNO | NNO,			SEND(KC_LSFT); SEND(KC_G));

	P( LO | LSD,				SEND(KC_LSFT); SEND(KC_Z));
	P( LO | LK,					SEND(KC_LSFT); SEND(KC_X));
	P( LO | LW,					SEND(KC_LSFT); SEND(KC_C));
	P( LO | LR,					SEND(KC_LSFT); SEND(KC_D));
	P( LO | NNO,				SEND(KC_LSFT); SEND(KC_V));

	// Shifted characters right
	P( LO | ST3,				SEND(KC_LSFT); SEND(KC_J));
	P( LO | RF,					SEND(KC_LSFT); SEND(KC_L));
	P( LO | RP,					SEND(KC_LSFT); SEND(KC_U));
	P( LO | RL,					SEND(KC_LSFT); SEND(KC_Y));
	P( LO | RT,					SEND(KC_LSFT); SEND(KC_QUOT));
	P( LO | RD,					SEND(KC_LSFT); SEND(KC_MINS));

	P( LO | ST3 | ST4,			SEND(KC_LSFT); SEND(KC_M));
	P( LO | RF  | RR,			SEND(KC_LSFT); SEND(KC_N));
	P( LO | RP  | RB,			SEND(KC_LSFT); SEND(KC_E));
	P( LO | RG  | RL,			SEND(KC_LSFT); SEND(KC_I));
	P( LO | RT  | RS,			SEND(KC_LSFT); SEND(KC_O));
	P( LO | RZ  | RD,			SEND(KC_LSFT); SEND(KC_SCLN));

	P( LO | ST4,				SEND(KC_LSFT); SEND(KC_K));
	P( LO | RR,					SEND(KC_LSFT); SEND(KC_H));
	P( LO | RB,					SEND(KC_LSFT); SEND(KC_COMM));
	P( LO | RG,					SEND(KC_LSFT); SEND(KC_DOT));
	P( LO | RS,					SEND(KC_LSFT); SEND(KC_SLSH));
	P( LO | RZ,					SEND(KC_LSFT); SEND(KC_DEL));
	

	// SYM, Left
	P( LNO | FN,	 SEND(KC_LSFT); SEND(KC_GRV));
    P( LNO | LSU,    SEND(KC_LSFT); SEND(KC_1));
    P( LNO | LFT,    SEND(KC_LSFT); SEND(KC_2));
    P( LNO | LP,     SEND(KC_LSFT); SEND(KC_3));
    P( LNO | LH,     SEND(KC_LSFT); SEND(KC_4));
    P( LNO | MNO,    SEND(KC_LSFT); SEND(KC_5));
    P( LNO | ST3,    SEND(KC_LSFT); SEND(KC_6));
    P( LNO | RF,     SEND(KC_LSFT); SEND(KC_7));
    P( LNO | RP,     SEND(KC_LSFT); SEND(KC_8));
    P( LNO | RL,     SEND(KC_LSFT); SEND(KC_EQL));
    P( LNO | RT,     SEND(KC_LSFT); SEND(KC_SCLN));
    P( LNO | RD,     SEND(KC_LSFT); SEND(KC_BSLS));
	
	P( LNO | PWR,	 SEND(KC_GRV));
	P( LNO | LSD,    SEND(KC_MINS));
    P( LNO | LK,     SEND(KC_LSFT); SEND(KC_MINS));
    P( LNO | LW,     SEND(KC_LSFT); SEND(KC_9));
    P( LNO | LR,     SEND(KC_LSFT); SEND(KC_LBRC));
    P( LNO | NNO,    SEND(KC_LBRC));
    P( LNO | ST4,    SEND(KC_RBRC));
    P( LNO | RR,     SEND(KC_LSFT); SEND(KC_RBRC));
    P( LNO | RB,     SEND(KC_LSFT); SEND(KC_0));
    P( LNO | RG,     SEND(KC_EQL));
    P( LNO | RS,     SEND(KC_SCLN));
	P( LNO | RZ,	 SEND(KC_BSLS));

    // NUM, Right
	P( RNO | FN,	 SEND(KC_F1));
    P( RNO | LSU,    SEND(KC_F2));
    P( RNO | LFT,    SEND(KC_F3));
    P( RNO | LP,     SEND(KC_F4));
    P( RNO | LH,     SEND(KC_F5));
    P( RNO | MNO,    SEND(KC_F6));
    P( RNO | ST3,    SEND(KC_F7));
    P( RNO | RF,     SEND(KC_F8));
    P( RNO | RP,     SEND(KC_F9));
    P( RNO | RL,     SEND(KC_F10));
    P( RNO | RT,     SEND(KC_F11));
    P( RNO | RD,     SEND(KC_F12));
	
	P( RNO | LSD,    SEND(KC_1));
    P( RNO | LK,     SEND(KC_2));
    P( RNO | LW,     SEND(KC_3));
    P( RNO | LR,     SEND(KC_4));
    P( RNO | NNO,    SEND(KC_5));
    P( RNO | ST4,    SEND(KC_6));
    P( RNO | RR,     SEND(KC_7));
    P( RNO | RB,     SEND(KC_8));
    P( RNO | RG,     SEND(KC_9));
    P( RNO | RS,     SEND(KC_0));
	
   PC( FN,			 SEND(KC_ESC));
	
	return 0;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [STEN] = LAYOUT( \
   KC_E, KC_C, KC_4, KC_2, KC_0, KC_Q, KC_T, KC_B, KC_9, KC_7, KC_N, KC_L,
   KC_P, KC_1, KC_3, KC_5, KC_D, KC_G, KC_J, KC_M, KC_6, KC_8, KC_A, KC_S,
	             KC_O, KC_H, KC_F, KC_K, KC_I, KC_R
    )
};
