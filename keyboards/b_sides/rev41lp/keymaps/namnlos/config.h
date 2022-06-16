/* Copyright 2022 Jan Lindblom (@janlindblom)
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
#pragma once

#undef BACKLIGHT_LIMIT_VAL
#define BACKLIGHT_LIMIT_VAL 230
#undef BACKLIGHT_LEVELS
#define BACKLIGHT_LEVELS 23
#define BACKLIGHT_DEFAULT_LEVEL 11
#ifndef BACKLIGHT_BREATHING
#define BACKLIGHT_BREATHING
#endif

#define IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
#ifndef TAPPING_TERM_PER_KEY
#define TAPPING_TERM_PER_KEY
#endif

#define DYNAMIC_KEYMAP_LAYER_COUNT 4

#define VIAL_KEYBOARD_UID {0xDE, 0x6E, 0x0C, 0xA6, 0x14, 0xC7, 0x7E, 0x9A}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

