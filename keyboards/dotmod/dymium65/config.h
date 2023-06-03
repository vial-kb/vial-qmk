<<<<<<<< HEAD:keyboards/keychron/q7/ansi/keymaps/vial/config.h
/* Copyright 2022 @ Keychron (https://www.keychron.com)
========
/* Copyright 2023 Finalkey
 * Copyright 2023 LiWenLiu <https://github.com/LiuLiuQMK>
>>>>>>>> qmk/master:keyboards/dotmod/dymium65/config.h
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

<<<<<<<< HEAD:keyboards/keychron/q7/ansi/keymaps/vial/config.h
#define VIAL_KEYBOARD_UID {0xF4, 0xB4, 0xCC, 0xD0, 0xA0, 0x27, 0xA9, 0xB3}

#define VIAL_UNLOCK_COMBO_ROWS {0, 2}
#define VIAL_UNLOCK_COMBO_COLS {0, 13}

/* Set dynamic keymap layer counts to 5 */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
========
/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// The number of LEDs connected
#define RGB_MATRIX_LED_COUNT 66
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0
#define RGB_MATRIX_LED_FLUSH_LIMIT 16
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
>>>>>>>> qmk/master:keyboards/dotmod/dymium65/config.h
