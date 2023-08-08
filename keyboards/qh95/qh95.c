/* Copyright 2021 beanaccle
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

#include "qh95.h"

#ifdef RGB_MATRIX_ENABLE
// 14
// 18
// 18
// 16
// 17
// 12
// x = 224 / (NUMBER_OF_COLS - 1) * COL_POSITION
// y =  64 / (NUMBER_OF_ROWS - 1) * ROW_POSITION
led_config_t g_led_config = { {
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, NO_LED, NO_LED, NO_LED, NO_LED },
    { 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31 },
    { 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49 },
    { 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, NO_LED, 62, 63, 64, 65, NO_LED },
    { 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, NO_LED, 78, 79, 80, 81, 82 },
    { 83, 84, 85, NO_LED, NO_LED, NO_LED, 86, NO_LED, NO_LED, 87, 88, 89, 90, 91, 92, 93, 94, NO_LED },
}, {
    {6.0, 0}, {21.0, 0}, {33.0, 0}, {45.0, 0}, {57.0, 0}, {72.0, 0}, {84.0, 0}, {96.0, 0}, {108.0, 0}, {123.0, 0}, {135.0, 0}, {147.0, 0}, {159.0, 0}, {174.0, 0},
    {6.0, 0}, {18.0, 0}, {30.0, 0}, {42.0, 0}, {54.0, 0}, {66.0, 0}, {78.0, 0}, {90.0, 0}, {102.0, 0}, {114.0, 0}, {126.0, 0}, {138.0, 0}, {150.0, 0}, {168.0, 0}, {186.0, 0}, {198.0, 0}, {210.0, 0}, {222.0, 0},
    {9.0, 0}, {24.0, 0}, {36.0, 0}, {48.0, 0}, {60.0, 0}, {72.0, 0}, {84.0, 0}, {96.0, 0}, {108.0, 0}, {120.0, 0}, {132.0, 0}, {144.0, 0}, {156.0, 0}, {171.0, 0}, {186.0, 0}, {198.0, 0}, {210.0, 0}, {222.0, 0},
    {10.5, 0}, {27.0, 0}, {39.0, 0}, {51.0, 0}, {63.0, 0}, {75.0, 0}, {87.0, 0}, {99.0, 0}, {111.0, 0}, {123.0, 0}, {135.0, 0}, {147.0, 0}, {166.5, 0}, {186.0, 0}, {198.0, 0}, {210.0, 0},
    {13.5, 0}, {33.0, 0}, {45.0, 0}, {57.0, 0}, {69.0, 0}, {81.0, 0}, {93.0, 0}, {105.0, 0}, {117.0, 0}, {129.0, 0}, {141.0, 0}, {157.5, 0}, {174.0, 0}, {186.0, 0}, {198.0, 0}, {210.0, 0}, {222.0, 0},
    {7.5, 0}, {22.5, 0}, {37.5, 0}, {82.5, 0}, {120.0, 0}, {132.0, 0}, {144.0, 0}, {156.0, 0}, {168.0, 0}, {180.0, 0}, {192.0, 0}, {204.0, 0}
}, {
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01
} };

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}

#endif
