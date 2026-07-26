/*
Copyright 2022 YANG <drk@live.com>

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

/* rough code */

#include "ch.h"
#include "hal.h"

/*
 * scan matrix
 */
#include "eeconfig.h"
#include "action.h"
#include "debug.h"
#include "timer.h"
#include "util.h"
#include "matrix.h"
#include "debounce_pk.h"
#include "wait.h"
#include "switch_board.h"
#include "rgblight.h"

#ifndef MAX_ROWS
#define MAX_ROWS MATRIX_ROWS
#endif
#define PREVENT_KEYIO_GND
#define SHOW_BOUNCE_DN
#define SHOW_BOUNCE_UP

extern debug_config_t debug_config;

bool bootmagic_checked = 0;
static matrix_row_t matrix[MATRIX_ROWS] = {0};
static uint8_t matrix_debouncing[MATRIX_ROWS][MATRIX_COLS] = {0};
uint8_t now_debounce_dn_mask = DEBOUNCE_DN_MASK;
uint8_t now_debounce_up_mask = DEBOUNCE_UP_MASK;

static void select_key(uint8_t mode);
static uint8_t get_key(void);
static void init_cols(void);
__attribute__ ((weak))
void matrix_scan_user(void) {}

__attribute__ ((weak))
void matrix_scan_kb(void)
{
    matrix_scan_user();
    hook_keyboard_loop();
}

bool is_ver5020 = 0;
bool is_sc_leds_mcu = 0;
bool has_extra_pull_up = 0;

void matrix_init(void)
{
    debug_config.enable = 1;
    debug_config.matrix = 0;

    user_config_init();

    //check ver595 or ver5020. PB9
    palSetPadMode(GPIOB, 9, PAL_MODE_INPUT_PULLUP);
    palSetPad(GPIOB, 9);
    //check if single color led indicators. PB8
    palSetPadMode(GPIOB, 8, PAL_MODE_INPUT_PULLUP);
    palSetPad(GPIOB, 8);
    wait_ms(10);
    if (palReadPad(GPIOB, 9) == 0) is_ver5020 = 1;
    if (palReadPad(GPIOB, 8) == 0) is_sc_leds_mcu = 1;

    // caps_led, PB14
    palSetPadMode(GPIOB, 14, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOB, 14);
    // scroll_led, PA8
    palSetPadMode(GPIOA, 8, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOA, 8);

    init_cols();

    // check extra pull up
    palSetPad(GPIOB, 13);
    palSetPadMode(GPIOB, 13, PAL_MODE_INPUT_PULLDOWN);
    wait_ms(5);
    if (palReadPad(GPIOB, 13)) {
        has_extra_pull_up = 1;
    }
    rgblight_user_init();
}

#ifdef PREVENT_KEYIO_GND
static bool process_key_press = 0;
bool should_process_keypress(void) {
    return process_key_press;
}
#endif

uint8_t matrix_scan(void)
{
#ifdef PREVENT_KEYIO_GND
    uint8_t matrix_keys_idle = 0;
#endif

    matrix_scan_kb(); // use this to run hook_keyboard_loop()
#if 0
    //scan matrix every 1ms
    static uint16_t matrix_scan_timestamp = 0;
    uint16_t time_check = timer_read();
    if (matrix_scan_timestamp == time_check) return 1;
    matrix_scan_timestamp = time_check;
#endif

    select_key(0);
    for (uint8_t row=0; row<MAX_ROWS; row++) {
        for (uint8_t col=0; col<MATRIX_COLS; col++) {
            uint8_t *debounce = &matrix_debouncing[row][col];

            uint8_t key = get_key();
            *debounce = (*debounce >> 1) | key;
            //select next key
            select_key(1);
            if (1) {
                matrix_row_t *p_row = &matrix[row];
                matrix_row_t col_mask = ((matrix_row_t)1 << col);

                    if        (*debounce > now_debounce_dn_mask) {  //debounce KEY DOWN 
                        *p_row |=  col_mask;
                    } else if (*debounce < now_debounce_up_mask) { //debounce KEY UP
                        *p_row &= ~col_mask;
                      #ifdef PREVENT_KEYIO_GND
                        matrix_keys_idle++;
                      #endif
                }

                bool bouncing = 0;
              #ifdef SHOW_BOUNCE_DN
                bouncing = (*debounce >= 0b10001000 && *debounce <= 0b10111111);
              #endif
              #ifdef SHOW_BOUNCE_UP
                uint8_t db_up = ~(*debounce);
                bouncing |= (db_up >= 0b10001000 && db_up <= 0b10111111);
              #endif
                if (bouncing) {
                    xprintf("\nKey(%d,%d) bounce %08b!", row, col, *debounce);
                    //raw_hid_send_bouncing_key(row, col);
                }
            }
        }
    }

#ifdef PREVENT_KEYIO_GND
    // to avoid all the keys being down in some cases like KEY is connected to GND.
    process_key_press = (matrix_keys_idle > 0);
#endif


    return 1;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{

}

uint8_t matrix_key_count(void)
{
    return 0;
}

static void init_cols(void)
{
    // 595 | 5020 pin
    palSetGroupMode(GPIOB, (1<<13 | 1<<12), 0 , PAL_MODE_OUTPUT_PUSHPULL);
    // disable all keys
    select_key_ready();
    KEY_SDI_OFF();
    for (uint8_t i = 0; i < MAX_ROWS * MATRIX_COLS; i++) {
        CLOCK_PULSE();
    }
}

 
static uint8_t get_key(void)
{
    // B13(595) and B14(5020)
    return palReadPad(GPIOB, 13)? 0 : 0x80;
}

static void select_key(uint8_t mode)
{
    select_key_ready();
    if (mode == 0) {
        KEY_SDI_OFF();
        for (uint8_t i = 0; i < MAX_ROWS * MATRIX_COLS; i++) {
            CLOCK_PULSE();
        }
        KEY_SDI_ON();
        CLOCK_PULSE();
    } else {
        KEY_SDI_OFF();
        CLOCK_PULSE();
    }
    //KEYS_LATCH();
    get_key_ready();
}

#include "eeprom.h"
#include "via.h"

void bootmagic_lite(void)
{
    for (uint8_t i=0; i < (DEBOUNCE_DN * 2); i++) {
        matrix_scan();
        wait_ms(2);
    }

    //check result
    uint8_t keys_down_pos[3] = {0xff, 0xff, 0xff};
    uint8_t i = 0;
    for (uint8_t row=0; row<MAX_ROWS; row++) {
        for (uint8_t col=0; col<MATRIX_COLS; col++) {
            if (matrix_get_row(row) & (1<<col)) {
                keys_down_pos[i] = row * MATRIX_COLS + col;
                if (i < 2) i++;
            }
        }
    }

    if (keys_down_pos[0] == 0) { 
        if (keys_down_pos[1] == 0xff) {
            // only esc down
            enter_bootloader();
        } else if (keys_down_pos[2] == 0xff) {
            //two keys down. if the other key is KC_E, clear eeprom.
            if (eeprom_read_byte(VIA_EEPROM_CONFIG_END+1 + keys_down_pos[1]*2) == KC_E) {
                eeconfig_init_via();
            }
        }
    }
    bootmagic_checked = 1;
}

void early_hardware_init_pre(void)
{
    // Override hard-wired USB pullup to disconnect and reconnect
    palSetPadMode(GPIOA, 12, PAL_MODE_OUTPUT_PUSHPULL);
    palClearPad(GPIOA, 12);
    for (uint32_t i = 0; i < 800000; i++) {
        __asm__("nop");
    }
}
