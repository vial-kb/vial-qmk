/* Copyright 2026 OpenAnnePro community
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

/* Anne Pro 2 flash budget.
 *
 * The IAP bootloader refuses to write past 0x10000: it stops answering write
 * commands at that address and the flashing tool hangs waiting for a reply.
 * With the bootloader occupying 0x0000-0x3FFF, the usable window is
 * 0x4000-0x10000, i.e. 48 KiB. This is a bootloader limit, not a chip limit:
 * the C18's HT32F52352 has 128 KiB of flash, but the upper 64 KiB cannot be
 * reached over IAP. Raising the linker script to match the datasheet makes
 * the firmware link and then hang halfway through flashing -- do not.
 *
 * keyboards/annepro2/info.json enables 43 rgb_matrix effects, which costs
 * roughly 250 bytes each. With all of them on, Vial + RGB matrix comes to
 * 51528 bytes and does not fit. Disabling 33 of them brings it to 43216,
 * leaving ~5.9 KiB of headroom -- enough to put about twenty back if needed.
 *
 * This is why the plain `vial` keymap sets RGB_MATRIX_ENABLE = no.
 */

#pragma once

/* Disabled effects. */
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#undef ENABLE_RGB_MATRIX_MULTISPLASH
#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

/* Kept: BREATHING, CYCLE_ALL, CYCLE_LEFT_RIGHT, RAINBOW_MOVING_CHEVRON,
 *       JELLYBEAN_RAINDROPS, TYPING_HEATMAP, SOLID_REACTIVE_SIMPLE,
 *       SOLID_REACTIVE, SPLASH, SOLID_SPLASH
 * plus the always-available SOLID_COLOR. */
