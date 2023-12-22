/*
Copyright 2021 beanaccle

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

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B4, B5, B7, A6 }
#define MATRIX_COL_PINS { B14, B15, A8, B0, A5, A7 }
#define MATRIX_ROW_PINS_RIGHT { B12, B13, B14, B5 }
#define MATRIX_COL_PINS_RIGHT { B4, B7, B3, B15, A8, A9 }

#define EE_HANDS
// qmk flash -kb qh/42v5 -km vial -bl dfu-util-split-left
// qmk flash -kb qh/42v5 -km vial -bl dfu-util-split-right
// qmk flash -kb qh40/v4 -km vial -bl uf2-split-left
// qmk flash -kb qh40/v4 -km vial -bl uf2-split-right

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
// #define SPLIT_HAND_PIN B1
// #define SPLIT_HAND_MATRIX_GRID B11,B7

// #define SPLIT_USB_DETECT
// #define MASTER_LEFT
// #define MASTER_RIGHT

// #define EE_HANDS
#define SOFT_SERIAL_PIN B6
// #define SERIAL_USART_TX_PIN B6
// #define SERIAL_USART_SPEED 921600
#define USART1_REMAP               // Remap USART TX and RX pins on STM32F103 MCUs, see table below.
// #define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7

#define COMBO_ONLY_FROM_LAYER 0
#define LAYER_STATE_16BIT

#define WS2812_DI_PIN B13
#define WS2812_PWM_COMPLEMENTARY_OUTPUT
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA1_STREAM5
#define WS2812_DMA_CHANNEL 1
// #define WS2812_PWM_TARGET_PERIOD 800000




// #define RGB_DI_PIN A1
// #define WS2812_PWM_DRIVER PWMD2
// #define WS2812_PWM_CHANNEL 2
// #define WS2812_PWM_PAL_MODE 1
// #define WS2812_EXTERNAL_PULLUP
// #define WS2812_DMA_STREAM STM32_DMA1_STREAM1
// #define WS2812_DMA_CHANNEL 3
// #define WS2812_PWM_TARGET_PERIOD 800000

#ifdef RGB_MATRIX_ENABLE
#   define ENABLE_RGB_MATRIX_ALPHAS_MODS
#   define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#   define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_BREATHING
#   define ENABLE_RGB_MATRIX_BAND_SAT
#   define ENABLE_RGB_MATRIX_BAND_VAL
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#   define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#   define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#   define ENABLE_RGB_MATRIX_CYCLE_ALL
#   define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#   define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#   define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#   define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#   define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#   define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#   define ENABLE_RGB_MATRIX_DUAL_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#   define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#   define ENABLE_RGB_MATRIX_RAINDROPS
#   define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#   define ENABLE_RGB_MATRIX_HUE_BREATHING
#   define ENABLE_RGB_MATRIX_HUE_PENDULUM
#   define ENABLE_RGB_MATRIX_HUE_WAVE
#   define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#   define ENABLE_RGB_MATRIX_PIXEL_FLOW
#   define ENABLE_RGB_MATRIX_PIXEL_RAIN
// Framebuffer Defines	
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects
#   define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#   define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// Reactive Defines	
#   define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE	
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE	
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE	
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE	
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS	
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS	
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS	
#   define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS	
#   define ENABLE_RGB_MATRIX_SPLASH	
#   define ENABLE_RGB_MATRIX_MULTISPLASH	
#   define ENABLE_RGB_MATRIX_SOLID_SPLASH	
#   define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH	
#endif

#ifdef PS2_DRIVER_INTERRUPT
// #define PS2_MOUSE_INVERT_BUTTONS
/* Use remote mode instead of the default stream mode (see link) */
// #define PS2_MOUSE_USE_REMOTE_MODE

/* Enable the scrollwheel or scroll gesture on your mouse or touchpad */
// #define PS2_MOUSE_ENABLE_SCROLLING

/* Some mice will need a scroll mask to be configured. The default is 0xFF. */
// #define PS2_MOUSE_SCROLL_MASK 0x0F

/* Applies a transformation to the movement before sending to the host (see link) */
// #define PS2_MOUSE_USE_2_1_SCALING
// #define PS2_MOUSE_X_MULTIPLIER 3
// #define PS2_MOUSE_Y_MULTIPLIER 3
// #define PS2_MOUSE_V_MULTIPLIER 1
#define PS2_MOUSE_BTN_LEFT      0
#define PS2_MOUSE_BTN_RIGHT     1
#define PS2_MOUSE_BTN_MIDDLE    2
// left
// #define PS2_CLOCK_PIN A15
// #define PS2_DATA_PIN  B3
// right
#define PS2_CLOCK_PIN B0
#define PS2_DATA_PIN  B1
#endif
