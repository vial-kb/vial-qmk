/* Copyright 2024 @ Keychron (https://www.keychron.com)
 * Modified for Vial wired-only build
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

#pragma once

/* Disable I2C to avoid peripheral errors */
#undef HAL_USE_I2C
#define HAL_USE_I2C FALSE

/* SPI needed for RGB Matrix LED driver */
#define HAL_USE_SPI TRUE

/* Encoder support */
#ifdef ENCODER_ENABLE
#    define PAL_USE_CALLBACKS TRUE
#endif

#include_next <halconf.h>
