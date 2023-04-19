/* Copyright 2021 kbdfans
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
#include "d45.h"

#if defined(RGB_MATRIX_ENABLE)
led_config_t g_led_config = { {
  {   0,   1,      2,   3,   4,       5,   6,      7,   8,      9,  10,  11,    12,      13,      14,  15   },
  {   55,  29,     28,  27,  26,      25,  24,     23,  22,     21, 20,  19,    18,      NO_LED,  17,  16   },
  {   54,  30,     31,  32,  33,      34,  35,     36,  37,     38, 39,  40,    NO_LED,  41,      42,  43   },
  {   53,  NO_LED, 52,  51,  NO_LED,  50,  NO_LED, 49,  NO_LED, 48, 47,  NO_LED,NO_LED,  46,      45,  44   }
}, {
    {   0,   0 }, {  14.93,   0 }, {  14.93*2,   0 }, {  14.93*3,   0 }, {  14.93*4,   0 }, {  14.93*5,   0 }, {  14.93*6,   0 }, { 14.93*7,   0 }, { 14.93*8,   0 }, { 14.93*9,   0 }, { 14.93*10,   0 }, { 14.93*11,   0 }, { 14.93*12,   0 }, { 14.93*13,   0 },{  14.93*14,   0 }, {  14.93*15,   0 },     
    {  14.93*15,   21.33 }, {   14.93*14,   21.33 }, {  14.93*12,   21.33 }, {  14.93*11,   21.33 },{  14.93*10,   21.33 },  {  14.93*9,   21.33 }, {  14.93*8,   21.33 }, {  14.93*7,   21.33 },{  14.93*6,   21.33 },  {  14.93*5,   21.33 }, {  14.93*4,   21.33 }, {  14.93*3,   21.33 }, {  14.93*2,   21.33 }, {  14.93,   21.33 }, 
{  14.93,   42.66 }, {  14.93*2,   42.66 },{  14.93*3,   42.66 },  {  14.93*4,   42.66 }, {  14.93*5,   42.66 }, {  14.93*6,   42.66 },{  14.93*7,   42.66 },  {  14.93*8,   42.66 }, {  14.93*9,   42.66 }, {  14.93*10,   42.66 }, {  14.93*11,   42.66 }, {  14.93*13,   42.66 }, {  14.93*14,   42.66 }, {  14.93*15,   42.66 },   
    {   14.93*15,   64 }, {  14.93*14,   64 },{  14.93*13,   64 }, {  14.93*10,   64 }, {  14.93*9,   64 }, {  14.93*7,   64 }, {  14.93*5,   64 },  {  14.93*3,   64 }, {  14.93*2,   64 }, {  0,   64 },  {  0,   42.66}, {  0,   21.33 }, 
   {0,10},{32,10},{32*2,10},{32*3,10},{32*4,10},{32*5,10},{32*6,10},{32*7,10},
   {0,50},{32,50},{32*2,50},{32*3,50},{32*4,50},{32*5,50},{32*6,50},{32*7,50}
    
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4,
    4,    4, 4,    4,    4,    4, 4,       4, 4, 4, 
    2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2
} };
#endif
