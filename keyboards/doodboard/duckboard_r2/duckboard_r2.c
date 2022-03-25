/* Copyright 2020-2021 doodboard
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

#include "duckboard_r2.h"

#ifdef RGB_MATRIX_ENABLE

#define XX NO_LED

led_config_t g_led_config = { 
    {
        // Key Matrix to LED Index
        { XX, 7,  XX, 6,  XX },
        { 0,  XX, XX, XX, 5  },
        { XX, XX, XX, XX, XX },
        { 1,  XX, XX, XX, 4  },
        { XX, 2,  XX, 3,  XX } 
    }, {
        // LED Index to Physical Position
        { 0, 16 }, { 0, 48 }, { 56, 64 }, { 168, 64 }, { 224, 48 }, {  224, 16 }, { 168, 0 }, { 56, 0 }
    }, {
        // LED Index to Flag
        2, 2, 2, 2, 2, 2, 2, 2
    } 
};
#endif
