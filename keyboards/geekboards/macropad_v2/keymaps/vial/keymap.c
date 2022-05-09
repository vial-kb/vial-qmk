/* Copyright 2020 Geekboards ltd. (geekboards.ru / geekboards.de)
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
#include <string.h>

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

enum custom_keycodes {
  ALT_TAB = USER00,
};

const uint16_t keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_2x4(
        KC_1, KC_2, KC_3, KC_4,
        KC_5, KC_6, KC_7, KC_8
    ),

    [1] = LAYOUT_ortho_2x4(
        KC_A, KC_B, KC_C, KC_D,
        KC_E, KC_F, KC_G, KC_H
    )
};

//------------ SUPER ALTTAB ---------------
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {               
        case ALT_TAB:
            if (record->event.pressed) {
                if (!is_alt_tab_active) {
                    is_alt_tab_active = true;
                    register_code(KC_LALT);
                }
                alt_tab_timer = timer_read();
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) {     
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}

void keyboard_post_init_user(void) {
    // set default macro after reset (alt-tab)
    uint8_t get[16] = {0};
    uint8_t zero[16] = {0};
    dynamic_keymap_macro_get_buffer(0,16,get);
    if(memcmp(get, zero, 16) == 0)
    {
        uint8_t set[] = {2, 0xe2, 2, 0xe1, 3, 0xe1, 3, 0xe2, 0};
        dynamic_keymap_macro_set_buffer(0, 9, set);
    }
}
