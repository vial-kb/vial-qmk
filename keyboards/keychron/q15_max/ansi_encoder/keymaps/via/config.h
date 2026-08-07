/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

/* VIA configuration */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

/* Increase VIA layout options */
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2

/* Keep USB connection active in wireless mode for VIA */
#define KEEP_USB_CONNECTION_IN_WIRELESS_MODE

/* Note: Color swap is handled at the driver level with SNLED27351_SWAP_RED_BLUE in main config.h */
/* RGB_MATRIX_COLOR_SWAP_RB was removed as it's not used in the codebase */

/* Ensure VIA works with wireless features */
#ifdef LK_WIRELESS_ENABLE
    #define VIA_CUSTOM_LIGHTING_ENABLE
    #define VIA_QMK_RGBLIGHT_ENABLE
#endif

/* Enable ALL RGB Matrix animations! */
#define ENABLE_RGB_MATRIX_ALPHAS_MODS          // Static dual hue, speed is hue for secondary hue
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN     // Static gradient top to bottom, speed controls how much gradient changes
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT  // Static gradient left to right, speed controls how much gradient changes
#define ENABLE_RGB_MATRIX_BREATHING            // Single hue brightness cycling animation
#define ENABLE_RGB_MATRIX_BAND_SAT             // Single hue band fading saturation scrolling left to right
#define ENABLE_RGB_MATRIX_BAND_VAL             // Single hue band fading brightness scrolling left to right
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT    // Single hue 3 blade spinning pinwheel fades saturation
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL    // Single hue 3 blade spinning pinwheel fades brightness
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT      // Single hue spinning spiral fades saturation
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL      // Single hue spinning spiral fades brightness
#define ENABLE_RGB_MATRIX_CYCLE_ALL            // Full keyboard solid hue cycling through full gradient
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT     // Full gradient scrolling left to right
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN        // Full gradient scrolling top to bottom
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN         // Full gradient scrolling out to in
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL    // Full dual gradients scrolling out to in
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON // Full gradient chevron scrolling left to right
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL       // Full gradient spinning pinwheel around center of keyboard
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL         // Full gradient spinning spiral around center of keyboard
#define ENABLE_RGB_MATRIX_DUAL_BEACON          // Full gradient spinning around center of keyboard
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON       // Full tighter gradient spinning around center of keyboard
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS    // Full dual gradients spinning two halfs of keyboard
#define ENABLE_RGB_MATRIX_FLOWER_BLOOMING      // Full multiple gradients blooming from the center
#define ENABLE_RGB_MATRIX_RAINDROPS            // Randomly lights LEDs winking in and out
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS  // Randomly lights LEDs with random hues
#define ENABLE_RGB_MATRIX_HUE_BREATHING        // Hue shifts up a slight amount then shifts back
#define ENABLE_RGB_MATRIX_HUE_PENDULUM         // Hue shifts up a slight amount in a wave to the right, then back to the left
#define ENABLE_RGB_MATRIX_HUE_WAVE             // Hue shifts up a slight amount and then back down in a wave to the right
#define ENABLE_RGB_MATRIX_PIXEL_FLOW            // Pulsing RGB flow along LED wiring with random hues
#define ENABLE_RGB_MATRIX_PIXEL_RAIN           // Randomly light keys with random hues
#define ENABLE_RGB_MATRIX_STARLIGHT            // LEDs turn on and off at random at varying brightness
#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_HUE   // LEDs turn on and off at random at varying brightness and two hues
#define ENABLE_RGB_MATRIX_STARLIGHT_DUAL_SAT   // LEDs turn on and off at random at varying brightness and saturation
// Removed PIXEL_FRACTAL and RIVERFLOW - incompatible with this branch

#ifdef RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP       // How hot is your WPM!
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN         // That famous computer simulation
#endif

#ifdef RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE   // Pulses keys hit to hue & value then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE          // Static single hue, pulses keys hit to shifted hue then fades to current hue
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE     // Hue & value pulse near a single key hit then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE // Hue & value pulse near multiple key hits then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS    // Hue & value pulse the same column and row of a single key hit then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS // Hue & value pulse the same column and row of multiple key hits then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS    // Hue & value pulse away on the same column and row of a single key hit then fades value out
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS // Hue & value pulse away on the same column and row of multiple key hits then fades value out
#define ENABLE_RGB_MATRIX_SPLASH                  // Full gradient & value pulse away from a single key hit then fades value out
#define ENABLE_RGB_MATRIX_MULTISPLASH             // Full gradient & value pulse away from multiple key hits then fades value out
#define ENABLE_RGB_MATRIX_SOLID_SPLASH            // Hue & value pulse away from a single key hit then fades value out
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH       // Hue & value pulse away from multiple key hits then fades value out
#endif