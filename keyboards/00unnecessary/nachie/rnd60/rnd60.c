/*
Copyright 2024 nachie

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

#include "quantum.h"

led_config_t g_led_config = { {
    { NO_LED, 0, NO_LED, 1, NO_LED, 2, NO_LED, NO_LED, 3, NO_LED, 4, NO_LED, 5, NO_LED, NO_LED },
    { 6, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 7 },
    { 8, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, 9 },
    { NO_LED, NO_LED, 10, NO_LED, 11, 12, NO_LED, NO_LED, 13, 14, NO_LED, 15, NO_LED, NO_LED, NO_LED }
}, {
    { 16,0 }, { 49,0 }, { 81,0 }, { 130,0 }, { 163,0 }, { 195,0 },
    { 4,16 }, { 224,16 },
    { 6,32 },
    { 224,48 },
    { 16,64 }, { 51,64 }, { 79,64 }, { 120,64 }, { 153,64 }, { 204,64 }
}, {
    1, 1, 1, 1, 1, 1,
    1, 1,
    1,
    1,
    1, 1, 1, 1, 1, 1
} };