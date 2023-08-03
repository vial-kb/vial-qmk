/* Copyright 2019 Leo Batyuk
 * Copyright 2020 Drashna Jaelre <@drashna>
 * Copyright 2023 @ben_roe (keycapsss.com)
 * Copyright 2023 @Ex3c4Def
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

enum layers {
    _QWERTY,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define RAISE MO(_RAISE)
#define LOWER MO(_LOWER)
#define QWERTY MO(_QWERTY)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,--------------------------------------------.                                   ,----------------------------------------------.
 * |         |   1  |   2  |   3  |   4  |   5  |                                   |   6  |   7  |   8  |   9  |   0  |  `        |
 * |---------+------+------+------+------+------|                                   |------+------+------+------+------+-----------|
 * |   Tab   |   Q  |   W  |   E  |   R  |   T  |                                   |   Y  |   U  |   I  |   O  |   P  |  -        |
 * |---------+------+------+------+------+------|                                   |------+------+------+------+------+-----------|
 * |  LShift |   A  |   S  |   D  |   F  |   G  |---------------.   ,---------------|   H  |   J  |   K  |   L  |   ;  |  '        |
 * |---------+------+------+------+------+------|  [   | RALT   |   |  DEL  |   ]   |------+------+------+------+------+-----------|
 * |  LCTRL  |   Z  |   X  |   C  |   V  |   B  |------|--------|   |-------|-------|   N  |   M  |   ,  |  .  |   /  |RShift/Enter|
 * `--------------------------------------------|               /    \              |----------------------------------------------'
 *                         | LCTRL| LGUI |LALT  |LOWER | Space /      \Enter| RAISE |BackSP| RGUI | RALT |
 *                         `----------------------------------'        '---------------------------------'
 */
 [_QWERTY] = LAYOUT(
    KC_ESC,  KC_1,  KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
    KC_TAB,  KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,                                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    KC_LSFT, KC_A,  KC_S,    KC_D,    KC_F,    KC_G,                                         KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LCTL, KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC, KC_RALT,  KC_DEL, KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
                             KC_LCTL, KC_LGUI, KC_LALT,   LOWER, KC_SPC,   KC_ENT,   RAISE, KC_BSPC, KC_RGUI, KC_RALT
),
/* LOWER
* QWERTY
 * ,--------------------------------------------.                                   ,----------------------------------------------.
 * |         |  F1  |  F2  |  F3  | F4 |  F5  |                                   |  F6  |  F7  |  F8  |  F9  | F10  |  F11      |
 * |---------+------+------+------+------+------|                                   |------+------+------+------+------+-----------|
 * |         |   1  |   2  |   3  |   4  |   5  |                                   |   6  |   7  |   8  |   9  |   0  |  F12      |
 * |---------+------+------+------+------+------|                                   |------+------+------+------+------+-----------|
 * |    `    |   !  |   @  |   #  |   $  |   %  |---------------.   ,---------------|   ^  |   &  |   *  |   (  |   )  |  ~        |
 * |---------+------+------+------+------+------|      |        |   |       |       |------+------+------+------+------+-----------|
 * |         |      |      |      |      |      |------|--------|   |-------|-------|      |   _  |   +  |   {  |   }  |  \        |
 * `--------------------------------------------|               /    \              |----------------------------------------------'
 *                         | LCTRL| LGUI |LALT  |LOWER | Space /      \Enter| RAISE |BackSP| RGUI | RALT |
 *                         `----------------------------------'        '---------------------------------'
 */
[_LOWER] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                                      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
    KC_GRV,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                    KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
    _______, _______, _______, _______, _______, _______, _______, QWERTY, _______, _______, XXXXXXX, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_BSLS,
                               _______, _______, _______, _______,_______, _______, _______, _______, _______, _______
),
/* RAISE
 * ,--------------------------------------------.                                   ,----------------------------------------------.
 * |         |      |      |      |      |      |                                   |      |      |      |      |      |           |
 * |---------+------+------+------+------+------|                                   |------+------+------+------+------+-----------|
 * |   `     |   1  |   2  |   3  |   4  |   5  |                                   |   6  |   7  |   8  |   9  |   0  |           |
 * |---------+------+------+------+------+------|                                   |------+------+------+------+------+-----------|
 * |  F1     |  F2  |  F3  | F4 |  F5  |  F6  |---------------.   ,---------------| Left | Down |  Up  |Right |   ;  |           |
 * |---------+------+------+------+------+------|  [   |   [    |   |   [   |   [   |------+------+------+------+------+-----------|
 * |  F7     |  F8  |  F9  | F10  | F11  | F12  |------|--------|   |-------|-------|   +  |   -  |   =  |  [  |   ]   |   \       |
 * `--------------------------------------------|               /    \              |----------------------------------------------'
 *                         | LCTRL| LGUI |LALT  |LOWER | Space /      \Enter| RAISE |BackSP| RGUI | RALT |
 *                         `----------------------------------'        '---------------------------------'
 */
 [_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______, _______,                                        _______, _______, _______, _______, _______, _______,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
    KC_F1,  KC_F2,    KC_F3,   KC_F4,   KC_F5,   KC_F6,                                          XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, XXXXXXX,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,   _______, _______,  _______, _______,  KC_PLUS, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
                               _______, _______, _______,  _______, _______,  _______, _______,  _______, _______, _______
),
/* ADJUST (Press LOWER and RAISE together)
 * ,--------------------------------------------.                                   ,----------------------------------------------.
 * | QK_BOOT |      |      |      |     |       |                                   |      |      |      |      |      |           |
 * |---------+------+------+------+------+------|                                   |------+------+------+------+------+-----------|
 * | RGB ON  | HUE+ | SAT+ | VAL+ |      |      |                                   | PREV | PLAY | NEXT |      |      |           |
 * |---------+------+------+------+------+------|                                   |------+------+------+------+------+-----------|
 * | MODE    | HUE- | SAT- | VAL- |      |      |---------------.   ,---------------| VOL+ | MUTE | VOL- |      |      |           |
 * |---------+------+------+------+------+------|      |        |   |       |       |------+------+------+------+------+-----------|
 * |         |      |      |      |      |      |------|--------|   |-------|-------|      |      |      |      |       |           |
 * `--------------------------------------------|               /    \              |----------------------------------------------'
 *                         | LCTRL| LGUI |LALT  |LOWER | Space /      \Enter| RAISE |BackSP| RGUI | RALT |
 *                         `----------------------------------'        '---------------------------------'
 */
[_ADJUST] = LAYOUT(
    QK_BOOT,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                                     KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                                     KC_VOLU, KC_MUTE, KC_VOLD, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
)
};

#ifdef POINTING_DEVICE_ENABLE
	void pointing_device_init_user(void) {
		#if defined(POINTING_DEVICE_DRIVER_pimoroni_trackball)
			// pimoroni_trackball_set_cpi(128*125); // default should be 128*125
			pimoroni_trackball_set_rgbw(0, 40, 0, 0);
		#endif
		#if defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_i2c) || defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_spi)
			cirque_pinnacle_set_scale(64); //default: 1024
			cirque_pinnacle_configure_circular_scroll(6, 2, 1137, 18, 0); //(uint8_t outer_ring_pct 33, uint8_t trigger_px 16, uint16_t trigger_ang 9102/50deg, uint8_t wheel_clicks 18, bool left_handed)
		#endif
	}

	#ifdef POINTING_TEST_SETTINGS	
		static bool set_scrolling = false; //used for alternative scrolling behaviour of pointing device
		
		report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
			
			#ifdef PIMORONI_TEST_SETTINGS	
			// testing different scaling of pointing device mouse input
			uint8_t scale1 = 1; // used for scaling the scrolling behaviour
			uint8_t scale2 = 3; //default PIMORONI_TRACKBALL_SCALE was 5, set to 1 in config.h to get slower scrolling and setting it now here
			uint8_t min_limit = 1;
			int8_t sign_x = 1;
			int8_t sign_y = 1;
			#endif
			
			#ifdef CIRQUE_TEST_SETTINGS	
			// testing different scaling of pointing device mouse input
			uint8_t scale1 = 1; // used for scaling the  mod layer scrolling behaviour
			uint8_t scale2 = 1; // used to scale the circular scrolling
			uint8_t scale3 = 4; // used to scale the standard mouse input 
			// uint8_t min_limit = 1;
			// int8_t sign_x = 1;
			// int8_t sign_y = 1;
			#endif
			
			if (set_scrolling) {								//used for alternative scrolling behaviour of pointing device
			#ifdef PIMORONI_TEST_SETTINGS
				mouse_report.h = mouse_report.x * scale1;
				mouse_report.v = -mouse_report.y * scale1;
			#endif
			#ifdef CIRQUE_TEST_SETTINGS
				mouse_report.h = mouse_report.x * scale1;
				mouse_report.v = -mouse_report.y * scale1;
			#endif
				mouse_report.x = 0;
				mouse_report.y = 0;
			}			
		
			#ifdef PIMORONI_TEST_SETTINGS
			else {												// testing different scaling of pointing device mouse input	
				if (mouse_report.x < 0) 
				{ sign_x = -1; }
				else
				{ sign_x =  1; }
				if (mouse_report.y  < 0) 
				{ sign_y = -1; }
				else
				{ sign_y =  1; }
		
				if (min_limit > (mouse_report.x * sign_x) )
				{ mouse_report.x = 0; }
				else
				{ mouse_report.x = sign_x * mouse_report.x * mouse_report.x * scale2; }

				if (min_limit > (mouse_report.y * sign_y) )
				{ mouse_report.y = 0; }
				else
				{ mouse_report.y = sign_y * mouse_report.y * mouse_report.y * scale2; }	
			}
			#endif
			#ifdef CIRQUE_TEST_SETTINGS
			else {				
				// if (mouse_report.x < 0) 
				// { sign_x = -1; }
				// else
				// { sign_x =  1; }
				// if (mouse_report.y  < 0) 
				// { sign_y = -1; }
				// else
				// { sign_y =  1; }
			
				mouse_report.h = mouse_report.h * scale2;
				mouse_report.v = mouse_report.v * scale2;
				// mouse_report.x = sign_x * mouse_report.x * mouse_report.x * scale3;
				// mouse_report.y = sign_y * mouse_report.y * mouse_report.y * scale3;
				mouse_report.x = mouse_report.x  * mouse_report.x * mouse_report.x * scale3;
				mouse_report.y = mouse_report.y  * mouse_report.y * mouse_report.y * scale3;
			}
			#endif
			
			return mouse_report;
		}
			
			
		layer_state_t layer_state_set_user(layer_state_t state) {
			state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
			
			switch (get_highest_layer(state)) {
				case _QWERTY:
					set_scrolling = false;
				#ifdef PIMORONI_TEST_SETTINGS	
					pimoroni_trackball_set_rgbw(0, 40, 0, 0);
				#endif
					break;
				case _LOWER:
					set_scrolling = true;
				#ifdef PIMORONI_TEST_SETTINGS	
					pimoroni_trackball_set_rgbw(40, 0, 0, 0);
				#endif
					break;
				case _RAISE:
					set_scrolling = true;
				#ifdef PIMORONI_TEST_SETTINGS	
					pimoroni_trackball_set_rgbw(0, 0, 40, 0);
				#endif
					break;
				case _ADJUST:
					set_scrolling = false;
				#ifdef PIMORONI_TEST_SETTINGS	
					pimoroni_trackball_set_rgbw(40, 40, 40, 0);
				#endif
					break;
			}		
			return state;
	}
	#endif //  POINTING_TEST_SETTINGS
#else
layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _RAISE, _LOWER, _ADJUST);
    return state;
}
#endif // POINTING_DEVICE_ENABLE

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
		if (is_keyboard_master()) {
			#ifdef OLED_DISPLAY_128X64
				return OLED_ROTATION_180;
			#else
				return OLED_ROTATION_270;
			#endif
		} else {
			#ifdef OLED_DISPLAY_128X64
				return OLED_ROTATION_180;
			#else
				return OLED_ROTATION_270;
			#endif
		}
	}

#ifndef OLED_DISPLAY_128X64
void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}
#endif

#ifdef OLED_DISPLAY_128X64
void render_mod_status_gui_alt_ctrl_shift(uint8_t modifiers) {		
	static const char PROGMEM gui_off_1[] = {0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x85, 0x86, 0};
	static const char PROGMEM gui_off_2[] = {0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xa5, 0xa6, 0};
	static const char PROGMEM gui_on_1[] =  {0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x8d, 0x8e, 0};
	static const char PROGMEM gui_on_2[] =  {0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xad, 0xae, 0};

	static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0xD1, 0};
	static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0xD1, 0};
	static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0xD1, 0};
	static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0xD1, 0};
	
	static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
	static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
	static const char PROGMEM ctrl_on_1[]  = {0x91, 0x92, 0};
	static const char PROGMEM ctrl_on_2[]  = {0xb1, 0xb2, 0};

	static const char PROGMEM shift_off_1[] = {0x8b, 0x8c,0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0};
	static const char PROGMEM shift_off_2[] = {0xab, 0xac,0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0};
	static const char PROGMEM shift_on_1[]  = {0xcd, 0xce,0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0};
	static const char PROGMEM shift_on_2[]  = {0xcf, 0xd0,0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0};

	//fillers between the modifier icons bleed into the icon frames
	static const char PROGMEM off_off_1[] = {0xc5, 0};
	static const char PROGMEM off_off_2[] = {0xc6, 0};
	static const char PROGMEM on_off_1[]  = {0xc7, 0};
	static const char PROGMEM on_off_2[]  = {0xc8, 0};
	static const char PROGMEM off_on_1[]  = {0xc9, 0};
	static const char PROGMEM off_on_2[]  = {0xca, 0};
	static const char PROGMEM on_on_1[]   = {0xcb, 0};
	static const char PROGMEM on_on_2[]   = {0xcc, 0};
	
	// line 1, gui & alt
	// ------------------------------------
	if(modifiers & MOD_MASK_GUI) {
		oled_write_P(gui_on_1, false);
	} else {
		oled_write_P(gui_off_1, false);
	}

	if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
		oled_write_P(on_on_1, false);
	} else if(modifiers & MOD_MASK_GUI) {
		oled_write_P(on_off_1, false);
	} else if(modifiers & MOD_MASK_ALT) {
		oled_write_P(off_on_1, false);
	} else {
		oled_write_P(off_off_1, false);
	}

	if(modifiers & MOD_MASK_ALT) {
		oled_write_P(alt_on_1, false);
	} else {
		oled_write_P(alt_off_1, false);
	}
	// ------------------------------------
	
	// line 1, ctrl & shift
	// ------------------------------------
	if(modifiers & MOD_MASK_CTRL) {
		oled_write_P(ctrl_on_1, false);
	} else {
		oled_write_P(ctrl_off_1, false);
	}

	if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
		oled_write_P(on_on_1, false);
	} else if(modifiers & MOD_MASK_CTRL) {
		oled_write_P(on_off_1, false);
	} else if(modifiers & MOD_MASK_SHIFT) {
		oled_write_P(off_on_1, false);
	} else {
		oled_write_P(off_off_1, false);
	}

	if(modifiers & MOD_MASK_SHIFT) {
		oled_write_P(shift_on_1, false);
	} else {
		oled_write_P(shift_off_1, false);
	}
	// ------------------------------------
	
	
	// line 2, gui & alt
	// ------------------------------------
	if(modifiers & MOD_MASK_GUI) {
		oled_write_P(gui_on_2, false);
	} else {
		oled_write_P(gui_off_2, false);
	}

	if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
		oled_write_P(on_on_2, false);
	} else if(modifiers & MOD_MASK_GUI) {
		oled_write_P(on_off_2, false);
	} else if(modifiers & MOD_MASK_ALT) {
		oled_write_P(off_on_2, false);
	} else {
		oled_write_P(off_off_2, false);
	}

	if(modifiers & MOD_MASK_ALT) {
		oled_write_P(alt_on_2, false);
	} else {
		oled_write_P(alt_off_2, false);
	}
	// ------------------------------------
		
	// line 2, ctrl & shift
	// ------------------------------------
	if(modifiers & MOD_MASK_CTRL) {
		oled_write_P(ctrl_on_2, false);
	} else {
		oled_write_P(ctrl_off_2, false);
	}
	
	if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
		oled_write_P(on_on_2, false);
	} else if(modifiers & MOD_MASK_CTRL) {
		oled_write_P(on_off_2, false);
	} else if(modifiers & MOD_MASK_SHIFT) {
		oled_write_P(off_on_2, false);
	} else {
		oled_write_P(off_off_2, false);
	}

	if(modifiers & MOD_MASK_SHIFT) {
		oled_write_P(shift_on_2, false);
	} else {
		oled_write_P(shift_off_2, false);
	}
	// ------------------------------------
}
#endif	


void render_logo(void) {
	#ifndef OLED_DISPLAY_128X64
		static const char PROGMEM kimiko_logo[] = {
			0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
			0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0};
		oled_write_P(kimiko_logo, false);
		// oled_write_P(PSTR("Kimiko"), false);
	#endif
	#ifdef OLED_DISPLAY_128X64
		//  1     2     3     4     5     6     7     8     9     10    11    12    13    14    15    16    17    18    19    20    21    22
		static const char PROGMEM kimiko_logo[] = {
			0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x72, 0x65, 0x76, 0x32,
			0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0};
		oled_write_P(kimiko_logo, false);
		oled_write_P(PSTR("\n"), false);
	#endif

	}

void render_layer_state(void) {
	#ifndef OLED_DISPLAY_128X64
		static const char PROGMEM default_layer[] = {
			0x20, 0x94, 0x95, 0x96, 0x20,
			0x20, 0xb4, 0xb5, 0xb6, 0x20,
			0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
		static const char PROGMEM raise_layer[] = {
			0x20, 0x97, 0x98, 0x99, 0x20,
			0x20, 0xb7, 0xb8, 0xb9, 0x20,
			0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
		static const char PROGMEM lower_layer[] = {
			0x20, 0x9a, 0x9b, 0x9c, 0x20,
			0x20, 0xba, 0xbb, 0xbc, 0x20,
			0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
		static const char PROGMEM adjust_layer[] = {
			0x20, 0x9d, 0x9e, 0x9f, 0x20,
			0x20, 0xbd, 0xbe, 0xbf, 0x20,
			0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
	#endif
	#ifdef OLED_DISPLAY_128X64
		static const char PROGMEM default_layer[] = {
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0x94, 0x95, 0x96, 0x20, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1,
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0xb4, 0xb5, 0xb6, 0x20, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1,
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
		static const char PROGMEM raise_layer[] = {
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0x97, 0x98, 0x99, 0x20, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1,
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0xb7, 0xb8, 0xb9, 0x20, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1,
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
		static const char PROGMEM lower_layer[] = {
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0x9a, 0x9b, 0x9c, 0x20, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1,
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0xba, 0xbb, 0xbc, 0x20, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1,  0xD1, 0xD1, 0xD1,
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
		static const char PROGMEM adjust_layer[] = {
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0x9d, 0x9e, 0x9f, 0x20, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1,
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0xbd, 0xbe, 0xbf, 0x20, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1,
			0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0xD1, 0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
	#endif
		if(layer_state_is(_ADJUST)) {
			oled_write_P(adjust_layer, false);
		} else if(layer_state_is(_LOWER)) {
			oled_write_P(lower_layer, false);
		} else if(layer_state_is(_RAISE)) {
			oled_write_P(raise_layer, false);
		} else {
			oled_write_P(default_layer, false);
		}
		#ifdef OLED_DISPLAY_128X64
			oled_write_P(PSTR("\n"), false);
		#endif
	}

void render_status_main(void) {
	#ifndef OLED_DISPLAY_128X64
		render_space();
		render_space();
		render_logo();
		render_space();
		render_layer_state();
		render_space();
		render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
		render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
	#endif

	#ifdef OLED_DISPLAY_128X64
		render_logo();
		render_layer_state();
		oled_write_P(PSTR("\n"), false);
		render_mod_status_gui_alt_ctrl_shift(get_mods()|get_oneshot_mods());
	#endif
	}

void render_status_secondary(void) {
	#ifndef OLED_DISPLAY_128X64
		render_space();
		render_space();
		render_logo();
		render_space();
	#endif
	#ifdef OLED_DISPLAY_128X64
		oled_write_P(PSTR("\n"), false);
		oled_write_P(PSTR("\n"), false);
		render_logo();
		oled_write_P(PSTR("\n"), false);
	#endif
	}

bool oled_task_user(void) {
	#ifndef OLED_KYRIA_STYLE
		if (is_keyboard_master()) {
			render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
			// render_status_secondary();
		} 
		else {
			// render_status_secondary();
			render_status_main(); 
		}
		return false;
	#endif
		
	#ifdef OLED_KYRIA_STYLE
		if (is_keyboard_master()) {
			// QMK Logo and version information
			// clang-format off
			// static const char PROGMEM qmk_logo[] = {
				// 0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
				// 0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
				// 0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};
			// clang-format on
			// oled_write_P(qmk_logo, false);
			// oled_write_P(PSTR("Kimiko "), false);
			// oled_write_P(PSTR("rev2\n\n"), false);
			
			render_logo();
			oled_write_P(PSTR("\n"), false);

			// Host Keyboard Layer Status
			oled_write_P(PSTR("Layer: "), false);
			// switch (get_highest_layer(layer_state | default_layer_state)) {
			if(layer_state_is(_QWERTY)) {
				oled_write_P(PSTR("QWERTY\n"), false);
			} 
			else if(layer_state_is(_LOWER)) {
				oled_write_P(PSTR("LOWER\n"), false);
			} 
			else if(layer_state_is(_RAISE)) {
				oled_write_P(PSTR("RAISE\n"), false);
			} 
			else if(layer_state_is(_ADJUST)) {
				oled_write_P(PSTR("ADJUST\n"), false);
			} 
			else {
				oled_write_P(PSTR("Undefined\n"), false);
			}

			// Host Keyboard LED Status
			led_t led_usb_state = host_keyboard_led_state();
			oled_write_P(led_usb_state.num_lock ?    PSTR("NUMLCK ") : PSTR("       "), false);
			oled_write_P(led_usb_state.caps_lock ?   PSTR("CAPLCK ") : PSTR("       "), false);
			oled_write_P(led_usb_state.scroll_lock ? PSTR("SCRLCK ") : PSTR("       "), false);
		} 
		// else {
			// //clang-format off
			// static const char PROGMEM kyria_logo[] = {
				// 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,192,224,240,112,120, 56, 60, 28, 30, 14, 14, 14,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7,  7, 14, 14, 14, 30, 28, 60, 56,120,112,240,224,192,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				// 0,  0,  0,  0,  0,  0,  0,192,224,240,124, 62, 31, 15,  7,  3,  1,128,192,224,240,120, 56, 60, 28, 30, 14, 14,  7,  7,135,231,127, 31,255,255, 31,127,231,135,  7,  7, 14, 14, 30, 28, 60, 56,120,240,224,192,128,  1,  3,  7, 15, 31, 62,124,240,224,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				// 0,  0,  0,  0,240,252,255, 31,  7,  1,  0,  0,192,240,252,254,255,247,243,177,176, 48, 48, 48, 48, 48, 48, 48,120,254,135,  1,  0,  0,255,255,  0,  0,  1,135,254,120, 48, 48, 48, 48, 48, 48, 48,176,177,243,247,255,254,252,240,192,  0,  0,  1,  7, 31,255,252,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				// 0,  0,  0,255,255,255,  0,  0,  0,  0,  0,254,255,255,  1,  1,  7, 30,120,225,129,131,131,134,134,140,140,152,152,177,183,254,248,224,255,255,224,248,254,183,177,152,152,140,140,134,134,131,131,129,225,120, 30,  7,  1,  1,255,255,254,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0,255,255,  0,  0,192,192, 48, 48,  0,  0,240,240,  0,  0,  0,  0,  0,  0,240,240,  0,  0,240,240,192,192, 48, 48, 48, 48,192,192,  0,  0, 48, 48,243,243,  0,  0,  0,  0,  0,  0, 48, 48, 48, 48, 48, 48,192,192,  0,  0,  0,  0,  0,
				// 0,  0,  0,255,255,255,  0,  0,  0,  0,  0,127,255,255,128,128,224,120, 30,135,129,193,193, 97, 97, 49, 49, 25, 25,141,237,127, 31,  7,255,255,  7, 31,127,237,141, 25, 25, 49, 49, 97, 97,193,193,129,135, 30,120,224,128,128,255,255,127,  0,  0,  0,  0,  0,255,255,255,  0,  0,  0,  0, 63, 63,  3,  3, 12, 12, 48, 48,  0,  0,  0,  0, 51, 51, 51, 51, 51, 51, 15, 15,  0,  0, 63, 63,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 48, 48, 63, 63, 48, 48,  0,  0, 12, 12, 51, 51, 51, 51, 51, 51, 63, 63,  0,  0,  0,  0,  0,
				// 0,  0,  0,  0, 15, 63,255,248,224,128,  0,  0,  3, 15, 63,127,255,239,207,141, 13, 12, 12, 12, 12, 12, 12, 12, 30,127,225,128,  0,  0,255,255,  0,  0,128,225,127, 30, 12, 12, 12, 12, 12, 12, 12, 13,141,207,239,255,127, 63, 15,  3,  0,  0,128,224,248,255, 63, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				// 0,  0,  0,  0,  0,  0,  0,  3,  7, 15, 62,124,248,240,224,192,128,  1,  3,  7, 15, 30, 28, 60, 56,120,112,112,224,224,225,231,254,248,255,255,248,254,231,225,224,224,112,112,120, 56, 60, 28, 30, 15,  7,  3,  1,128,192,224,240,248,124, 62, 15,  7,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
				// 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  7, 15, 14, 30, 28, 60, 56,120,112,112,112,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,224,112,112,112,120, 56, 60, 28, 30, 14, 15,  7,  3,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0
			// };
			// //clang-format on
			// oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
		// }
		return false;
	#endif
	}

#endif  //OLED_ENABLE

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_QWERTY] = { ENCODER_CCW_CW(KC_UP, KC_DOWN),		ENCODER_CCW_CW(KC_RGHT, KC_LEFT) },
    [_LOWER] =  { ENCODER_CCW_CW(KC_TAB, RGB_HUI),		ENCODER_CCW_CW(KC_VOLU, KC_VOLD) },
    [_RAISE] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI),		ENCODER_CCW_CW(RGB_SPD, RGB_SPI) },
    [_ADJUST] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD),	ENCODER_CCW_CW(RGB_HUI, RGB_HUD) },
};
#endif // ENCODER_MAP_ENABLE


#ifndef VIAL_ENABLE
	enum combos {
	  FG_M_BT1,
	  VB_M_BT2,
	  RT_M_BT3,
	  
	  HJ_M_BT4,
	  NM_M_BT5,
	  YU_M_BT6,
	  COMBO_LENGTH
	};
	const uint16_t PROGMEM fg_combo[] = {KC_F, KC_G, COMBO_END};
	const uint16_t PROGMEM vb_combo[] = {KC_V, KC_B, COMBO_END};
	const uint16_t PROGMEM rt_combo[] = {KC_R, KC_T, COMBO_END};

	const uint16_t PROGMEM hj_combo[] = {KC_H, KC_J, COMBO_END};
	const uint16_t PROGMEM nm_combo[] = {KC_N, KC_M, COMBO_END};
	const uint16_t PROGMEM yu_combo[] = {KC_Y, KC_U, COMBO_END};

	uint16_t COMBO_LEN = COMBO_LENGTH;  // remove the COMBO_COUNT define and use this instead!
	combo_t key_combos[] = {
		[FG_M_BT1] = COMBO(fg_combo, KC_MS_BTN1),
		[VB_M_BT2] = COMBO(vb_combo, KC_MS_BTN2),
		[RT_M_BT3] = COMBO(rt_combo, KC_MS_BTN3),
		
		[HJ_M_BT4] = COMBO(hj_combo, KC_MS_BTN4),
		[NM_M_BT5] = COMBO(nm_combo, KC_MS_BTN5),
		[YU_M_BT6] = COMBO(yu_combo, KC_MS_BTN6),
	};
#endif

// void keyboard_post_init_user(void) {
  // //Customise these values to desired behaviour
  // debug_enable=true;
  // debug_matrix=true;
  // debug_keyboard=true;
  // //debug_mouse=true;
// }