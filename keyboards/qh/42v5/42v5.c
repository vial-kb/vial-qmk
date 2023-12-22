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

#include "42v5.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  18,  17,  16,  15,  14,   13 },
    {  19,  8,  9,  10,  11,   12 },
    {  20,  7,  6,  5,  4,   3 },
    { NO_LED, NO_LED, NO_LED,  0,  1,   2 },
    {  34,  35,  36,  37,  38,  39 },
    {  33,  32,  31,  30,  29,  40 },
    {  24,  25,  26,  27,  28,  41 },
    { 23, 22, 21,  NO_LED,  NO_LED,  NO_LED }
}, {
    // left LED_FLAG_KEYLIGHT
    {  60,  55 }, {  80,  58 }, {  95,  63 },
    {  85,  39 }, {  68,  37 }, {  50,  35 }, {  33,  37 }, {  16,  42 },             
    {  16,  24 }, {  33,  20 }, {  50,  13 }, {  68,  19 }, {  85,  21 },
    {  85,   4 }, {  68,   2 }, {  50,   0 }, {  33,   3 }, {  16,   7 },  
    {   0,   7 }, {   0,  24 }, {   0,  41 },
    
    
    // right LED_FLAG_KEYLIGHT
    { 164,  55 }, { 144,  58 }, { 129,  63 }, 
    { 139,  39 }, { 156,  37 }, { 174,  35 }, { 191,  37 }, { 208,  42 },      
    { 208,  24 }, { 191,  20 }, { 174,  13 }, { 156,  19 }, { 139,  21 }, 
    { 139,   4 }, { 156,   2 }, { 174,   0 }, { 191,   3 }, { 208,   7 },       
    { 224,   7 }, { 224,  24 }, { 224,  41 }
    
    
}, {
    // left LED_FLAG_KEYLIGHT
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    // right LED_FLAG_KEYLIGHT
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
    LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
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
