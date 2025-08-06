/*Copyright 2021 perce
 *
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 2 of the License, or
 *(at your option) any later version.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with this program.  If not, see<http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define RANDOM_STRING_DELAY 100

enum custom_keycodes {
    RANDOM_STRING_MACRO = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { [0] = LAYOUT(RANDOM_STRING_MACRO)
};

const char sentence_01[] PROGMEM = "My name is Juno!!!! \n";
const char sentence_02[] PROGMEM = "RooOOOoOoooo \n";
const char sentence_03[] PROGMEM = "rUuuUUuUUUuuuuuuuu \n";
const char sentence_04[] PROGMEM = "Sometimes my poops are soft :(\n";
const char sentence_05[] PROGMEM = "rooo? \n";
const char sentence_06[] PROGMEM = "BORK BORK \n";
const char sentence_07[] PROGMEM = "*lick* \n";
const char sentence_08[] PROGMEM = "rrrrrrrrrrrrrrrRRrrrr \n";
const char sentence_09[] PROGMEM = "AWOOOOOOOOOOOOO \n";
const char sentence_10[] PROGMEM = "*pant pant* \n";

PGM_P const sentences[] PROGMEM = {
    sentence_01,
    sentence_02,
    sentence_03,
    sentence_04,
    sentence_05,
    sentence_06,
    sentence_07,
    sentence_08,
    sentence_09,
    sentence_10
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        int sentences_size = sizeof(sentences) / sizeof(sentences[0]);
        int i = rand() % sentences_size;

        switch (keycode) {
            case RANDOM_STRING_MACRO:
                send_string_with_delay_P((PGM_P)pgm_read_word(&(sentences[i])), RANDOM_STRING_DELAY);
                tap_code(KC_ENT);

                return false;
        }
    }

    return true;
}