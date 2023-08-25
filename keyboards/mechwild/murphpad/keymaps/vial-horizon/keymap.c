/*  Copyright 2021 Kyle McCreery
    Copyright 2023 CRMSN_

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

/*               0,   ,11
    ,----,----,    ---     __________
    |    |    |  (' e `)  ||  murph  |
    '===='===='    ---     ¯¯¯¯¯¯¯¯¯¯
    ,----,----,----,----,----,  ,----,
    |    |    |    |    |    |  |    |
    ;====;====;====;====;====;  ;----;
    |    |    |    |    |    |  |    |
    ;====;====;====;====;====;  ;----;
    |    |    |    |    |    |  |    |
    ;====;====;====;====;====;  ;----;
    |    |    |    |    |    |  |    |
    '----'----'----'----'----'  '----'
*/

// defines names for use in layer keycodes and the keymap

enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3,
    _FN4,
    _FN5,
    _FN6,
    _FN7,
    _RGB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* base */
    [_BASE] = LAYOUT(
        _______, _______, _______,

        _______,  _______,  _______,  _______,  QK_BOOT,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,

                  _______,  _______,  _______
    ),
    [_FN1] = LAYOUT(
        _______, _______, _______,

        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,

                  _______,  _______,  _______
    ),
	[_FN2] = LAYOUT(
        _______, _______, _______,

        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,

                  _______,  _______,  _______
    ),
	[_FN3] = LAYOUT(
        _______, _______, _______,

        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,

                  _______,  _______,  _______
   ),
	[_FN4] = LAYOUT(
        _______, _______, _______,

        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,

                  _______,  _______,  _______
   ),
    [_FN5] = LAYOUT(
        _______, _______, _______,

        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,

                  _______,  _______,  _______
   ),
    [_FN6] = LAYOUT(
        _______, _______, _______,

        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,

                  _______,  _______,  _______
   ),
   	[_FN7] = LAYOUT(
        _______, _______, _______,

        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,

                  _______,  _______,  _______
   ),
	[_RGB] = LAYOUT(
        _______, _______, _______,

        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,
        _______,  _______,  _______,  _______,  _______,     _______,

                  _______,  _______,  _______
   )
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(_______, _______), ENCODER_CCW_CW(_______, _______) },
    [_FN1] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
    [_FN2] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
    [_FN3] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
    [_FN4] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
    [_FN5] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
    [_FN6] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
    [_FN7] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
    [_RGB] = { ENCODER_CCW_CW(_______, _______),  ENCODER_CCW_CW(_______, _______) },
};
#endif

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;       // flippant grip
}

    static void render_logo(void) {
    static const char PROGMEM raw_logo[] = { // cave owl logo
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x80, 0x80, 0x00,
        0x00, 0x40, 0x40, 0x00, 0x04, 0x44,
        0x44, 0x20, 0xE2, 0xE6, 0x32, 0x39,
        0x1B, 0x0E, 0x02, 0x07, 0x06, 0x03,
        0x03, 0x03, 0x03, 0x02, 0x07, 0x03,
        0x03, 0x06, 0x06, 0x06, 0x0C, 0x08,
        0x08, 0x60, 0xC8, 0xC0, 0x08, 0x00,
        0x00, 0x00, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
        0x01, 0x01, 0x01, 0x00, 0x01, 0x01,
        0x01, 0x00, 0x01, 0x01, 0x01, 0x00,
        0x01, 0x01, 0x01, 0x00, 0x01, 0x01,
        0x00, 0x01, 0x01, 0x00, 0x01, 0x01,
        0x00, 0x00, 0x01, 0x00, 0x00, 0x01,
        0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x10, 0x00, 0x10, 0x00,
        0x00, 0x00, 0x10, 0x10, 0x20, 0x10,
        0x50, 0xF6, 0xFF, 0x0F, 0x83, 0xC0,
        0x60, 0x38, 0x18, 0x0E, 0x87, 0xCE,
        0xBC, 0x18, 0x1C, 0x06, 0x03, 0x0D,
        0x08, 0x18, 0xF8, 0xDC, 0x8E, 0x07,
        0x0E, 0x38, 0x38, 0x60, 0xE0, 0xC3,
        0x8F, 0x6E, 0xF0, 0x20, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
        0x04, 0x08, 0x00, 0x00, 0x10, 0x24,
        0x18, 0x11, 0x23, 0x37, 0x6E, 0xF3,
        0xC1, 0x00, 0x00, 0x00, 0x00, 0x01,
        0x13, 0x07, 0x1E, 0x08, 0x60, 0xC0,
        0x80, 0xC0, 0xE0, 0x70, 0x0C, 0x1D,
        0x03, 0x02, 0x06, 0x08, 0x00, 0x40,
        0x81, 0xC1, 0x73, 0x37, 0x2F, 0x18,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x04, 0x00, 0x08, 0x08, 0x0A,
        0x00, 0x14, 0x1B, 0x0F, 0x2E, 0x1C,
        0x18, 0x34, 0x10, 0x7C, 0x22, 0xF0,
        0xC0, 0xC0, 0xC1, 0xC3, 0xC0, 0xC0,
        0xC0, 0x60, 0x60, 0x70, 0x30, 0x1B,
        0x1E, 0x0C, 0x02, 0x00, 0x00, 0x00,
        0x00, 0x00,
};

    oled_write_raw_P(raw_logo, sizeof(raw_logo)); // render cave owl logo
}

bool oled_task_user(void) {
    render_logo();

    oled_set_cursor(0, 2);

    // host kb led status
    led_t led_state = host_keyboard_led_state();

    oled_write_P(led_state.num_lock ? PSTR("# ") : PSTR("N "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("$ ") : PSTR("S "), false);
    oled_write_P(led_state.caps_lock ? PSTR("Z\r") : PSTR("z\r"), false);

    oled_set_cursor(0, 0);

    oled_write_P(PSTR("1984 > "), false);    // layer status

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("crmsn_"), false);
            break;
        case 1:
            oled_write_P(PSTR("I_"), false);
            break;
        case 2:
            oled_write_P(PSTR("II_"), false);
            break;
        case 3:
            oled_write_P(PSTR("III_"), false);
            break;
        case 4:
            oled_write_P(PSTR("IV_"), false);
            break;
        case 5:
            oled_write_P(PSTR("V_"), false);
            break;
        case 6:
            oled_write_P(PSTR("VI_"), false);
            break;
        case 7:
            oled_write_P(PSTR("VII_"), false);
            break;
        case 8:
            oled_write_P(PSTR("RGB_"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Z?"), false);
    }

    return false;
}
#endif
