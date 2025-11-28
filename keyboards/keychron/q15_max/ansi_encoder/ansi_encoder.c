/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
 *
 * This program is free software : you can redistribute it and /or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see < http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

// clang-format off

#ifdef RGB_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[RGB_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  R location
 *   |  |           G location
 *   |  |           |           B location
 *   |  |           |           | */
    {0, CB7_CA1,    CB9_CA1,    CB8_CA1},
    {0, CB7_CA2,    CB9_CA2,    CB8_CA2},
    {0, CB1_CA2,    CB3_CA2,    CB2_CA2},
    {0, CB1_CA1,    CB3_CA1,    CB2_CA1},
    {0, CB1_CA4,    CB3_CA4,    CB2_CA4},
    {0, CB10_CA10,  CB12_CA10,  CB11_CA10},
    {0, CB10_CA11,  CB12_CA11,  CB11_CA11},
    {0, CB10_CA8,   CB12_CA8,   CB11_CA8},
    {0, CB10_CA2,   CB12_CA2,   CB11_CA2},
    {0, CB10_CA1,   CB12_CA1,   CB11_CA1},
    {0, CB4_CA1,    CB6_CA1,    CB5_CA1},
    {0, CB4_CA2,    CB6_CA2,    CB5_CA2},

    {0, CB4_CA16,   CB6_CA16,   CB5_CA16},
    {0, CB4_CA15,   CB6_CA15,   CB5_CA15},
    {0, CB4_CA14,   CB6_CA14,   CB5_CA14},
    {0, CB4_CA13,   CB6_CA13,   CB5_CA13},
    {0, CB4_CA12,   CB6_CA12,   CB5_CA12},
    {0, CB4_CA11,   CB6_CA11,   CB5_CA11},
    {0, CB4_CA10,   CB6_CA10,   CB5_CA10},
    {0, CB4_CA9,    CB6_CA9,    CB5_CA9},
    {0, CB4_CA8,    CB6_CA8,    CB5_CA8},
    {0, CB4_CA7,    CB6_CA7,    CB5_CA7},
    {0, CB4_CA6,    CB6_CA6,    CB5_CA6},
    {0, CB4_CA5,    CB6_CA5,    CB5_CA5},
    {0, CB4_CA4,    CB6_CA4,    CB5_CA4},
    {0, CB4_CA3,    CB6_CA3,    CB5_CA3},

    {0, CB1_CA16,   CB3_CA16,   CB2_CA16},
    {0, CB1_CA15,   CB3_CA15,   CB2_CA15},
    {0, CB1_CA14,   CB3_CA14,   CB2_CA14},
    {0, CB1_CA13,   CB3_CA13,   CB2_CA13},
    {0, CB1_CA12,   CB3_CA12,   CB2_CA12},
    {0, CB1_CA11,   CB3_CA11,   CB2_CA11},
    {0, CB1_CA10,   CB3_CA10,   CB2_CA10},
    {0, CB1_CA9,    CB3_CA9,    CB2_CA9},
    {0, CB1_CA8,    CB3_CA8,    CB2_CA8},
    {0, CB1_CA7,    CB3_CA7,    CB2_CA7},
    {0, CB1_CA6,    CB3_CA6,    CB2_CA6},
    {0, CB1_CA5,    CB3_CA5,    CB2_CA5},
    {0, CB1_CA3,    CB3_CA3,    CB2_CA3},

    {0, CB7_CA16,   CB9_CA16,   CB8_CA16},
    {0, CB7_CA15,   CB9_CA15,   CB8_CA15},
    {0, CB7_CA14,   CB9_CA14,   CB8_CA14},
    {0, CB7_CA13,   CB9_CA13,   CB8_CA13},
    {0, CB7_CA12,   CB9_CA12,   CB8_CA12},
    {0, CB7_CA11,   CB9_CA11,   CB8_CA11},
    {0, CB7_CA10,   CB9_CA10,   CB8_CA10},
    {0, CB7_CA9,    CB9_CA9,    CB8_CA9},
    {0, CB7_CA8,    CB9_CA8,    CB8_CA8},
    {0, CB7_CA7,    CB9_CA7,    CB8_CA7},
    {0, CB7_CA6,    CB9_CA6,    CB8_CA6},
    {0, CB7_CA5,    CB9_CA5,    CB8_CA5},
    {0, CB7_CA4,    CB9_CA4,    CB8_CA4},
    {0, CB7_CA3,    CB9_CA3,    CB8_CA3},

    {0, CB10_CA16,  CB12_CA16,  CB11_CA16},
    {0, CB10_CA15,  CB12_CA15,  CB11_CA15},
    {0, CB10_CA14,  CB12_CA14,  CB11_CA14},
    {0, CB10_CA13,  CB12_CA13,  CB11_CA13},
    {0, CB10_CA12,  CB12_CA12,  CB11_CA12},
    {0, CB10_CA9,   CB12_CA9,   CB11_CA9},
    {0, CB10_CA7,   CB12_CA7,   CB11_CA7},
    {0, CB10_CA6,   CB12_CA6,   CB11_CA6},
    {0, CB10_CA5,   CB12_CA5,   CB11_CA5},
    {0, CB10_CA4,   CB12_CA4,   CB11_CA4},
    {0, CB10_CA3,   CB12_CA3,   CB11_CA3},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { __,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, __ },
        { 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 },
        { 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, __ },
        { 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52 },
        { 53, 54, 55, 56, 57, __, __, 58, __, 59, 60, 61, 62, 63 },
    },
    {
        //  LED Index to Physical Position
               {17,0}, {34,0}, {51,0}, {68,0}, {84,0}, {102,0}, {119,0}, {136,0}, {153,0}, {170,0}, {187,0}, {204,0},
        {0,16},{17,16},{34,16},{51,16},{68,16},{84,16},{102,16},{119,16},{136,16},{153,16},{170,16},{187,16},{204,16},{220,16},
        {0,32},{17,32},{34,32},{51,32},{68,32},{84,32},{102,32},{119,32},{136,32},{153,32},{170,32},{187,32},         {212,32},
        {0,48},{17,48},{34,48},{51,48},{68,48},{84,48},{102,48},{119,48},{136,48},{153,48},{170,48},{187,48},{204,48},{220,48},
        {0,64},{17,64},{34,64},{51,64},{76,64},                 {121,64},         {153,64},{170,64},{187,64},{204,64},{220,64},
    },
    {
        // RGB LED Index to Flag
           1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1,       1,    1, 1, 1, 1,
    }
};
#endif
