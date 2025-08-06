/*
Copyright 2021 Kyle McCreery
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

#pragma once

#if TAPPING_TERM == 0
    #undef TAPPING_TERM
#endif

#define WEAR_LEVELING_LOGICAL_SIZE 4096
#define WEAR_LEVELING_BACKING_SIZE WEAR_LEVELING_LOGICAL_SIZE * 2

#define DYNAMIC_KEYMAP_MACRO_COUNT 32

/* VIAL Specific definitions */
#define VIAL_KEYBOARD_UID {0xFD, 0xD4, 0x17, 0x1D, 0x64, 0x5F, 0x30, 0x75}
#define VIAL_UNLOCK_COMBO_ROWS { 1, 5 }
#define VIAL_UNLOCK_COMBO_COLS { 5, 0 }
