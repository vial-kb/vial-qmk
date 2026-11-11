 /* Copyright 2021 OpenAnnePro community
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

// Obins stock firmware has something similar to this already enabled, but disabled by default in QMK
#define PERMISSIVE_HOLD

#define VIAL_KEYBOARD_UID {0x62, 0x1D, 0xA7, 0x0A, 0x38, 0xAF, 0xDD, 0x60}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 12 }

/* The wear_leveling/spi_flash EEPROM fits at most 5 layers: at 6 the
 * "Dynamic keymaps are configured to use more EEPROM than is available"
 * static assert in nvm_dynamic_keymap.c fires. Kept at 3 to match the
 * plain `vial` keymap; raising it costs no flash, only EEPROM. */
#define DYNAMIC_KEYMAP_LAYER_COUNT 3

#include "animations.h"
