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

#include "v4.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,  1,  2,  3,  4,   5 },
    {  6,  7,  8,  9,  10,   11 },
    {  12,  13,  14,  15,  16,   17 },
    { NO_LED, NO_LED, NO_LED,  18,  19,   20 },
    {  27,  28,  29,  30,  31,  32 },
    {  33,  34,  35,  36,  37,  38 },
    {  39,  40,  41,  42,  43,  44 },
    { 45, 46, 47,  NO_LED,  NO_LED,  NO_LED }
}, {
    // left LED_FLAG_KEYLIGHT
    {   0,   7 }, {  16,   7 }, {  33,   3 }, {  50,   0 }, {  68,   2 }, {  85,   4 },
    {   0,  24 }, {  16,  24 }, {  33,  20 }, {  50,  13 }, {  68,  19 }, {  85,  21 },
    {   0,  41 }, {  16,  42 }, {  33,  37 }, {  50,  35 }, {  68,  37 }, {  85,  39 },
                                              {  60,  55 }, {  80,  58 }, {  95,  63 },
    // left LED_FLAG_UNDERGLOW
    {  85,  52 }, {  50,  48 }, {  16,  38 }, {  16,  20 }, {  50,  13 }, {  85,  16 }, 

    // right LED_FLAG_KEYLIGHT
    { 139,   4 }, { 156,   2 }, { 174,   0 }, { 191,   3 }, { 208,   7 }, { 224,   7 },
    { 139,  21 }, { 156,  19 }, { 174,  13 }, { 191,  20 }, { 208,  24 }, { 224,  24 },
    { 139,  39 }, { 156,  37 }, { 174,  35 }, { 191,  37 }, { 208,  42 }, { 224,  41 },
    { 129,  63 }, { 144,  58 }, { 164,  55 },
    // right LED_FLAG_UNDERGLOW
    { 139,  52 }, { 174,  48 }, { 208,  38 }, { 208,  20 }, { 174,  13 }, { 139,  16 }
}, {
    // left LED_FLAG_KEYLIGHT
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
                      0x01, 0x01, 0x01,
    // left LED_FLAG_UNDERGLOW
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    // right LED_FLAG_KEYLIGHT
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x01, 0x01, 0x01,
    // right LED_FLAG_UNDERGLOW
    0x01, 0x01, 0x01, 0x01, 0x01, 0x01
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
