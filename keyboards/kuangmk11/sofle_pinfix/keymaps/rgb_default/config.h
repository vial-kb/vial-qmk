 /* Copyright 2021 Dane Evans
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


//#define USE_MATRIX_I2C

/* Select hand configuration */

///https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/

// Vial Support
#define VIAL_KEYBOARD_UID { 0x05, 0xCD, 0x9F, 0x8A, 0xF4, 0xDF, 0xDE, 0xB2 }

// The four corners
#define VIAL_UNLOCK_COMBO_ROWS { 0, 5, 3, 8 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0, 0, 0 }



#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#define CUSTOM_FONT

#define CUSTOM_LAYER_READ //if you remove this it causes issues - needs better guarding


#define QUICK_TAP_TERM 0
#ifdef TAPPING_TERM
    #undef TAPPING_TERM
    #define TAPPING_TERM 200
#endif
#define ENCODER_DIRECTION_FLIP


#define RGBLIGHT_SLEEP
//
#define RGBLIGHT_LAYERS

/* ws2812 RGB LED */
#define WS2812_DI_PIN GP3


#ifdef RGB_MATRIX_ENABLE
#define RGBLED_NUM 35    // Number of LEDs
#define RGBLED_NUM 35    // Number of LEDs
#define RGB_MATRIX_LED_COUNT RGBLED_NUM
#endif

#ifdef RGBLIGHT_ENABLE
    #undef RGBLED_NUM

	#define RGBLIGHT_EFFECT_BREATHING
	#define RGBLIGHT_EFFECT_RAINBOW_MOOD
	#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	#define RGBLIGHT_EFFECT_SNAKE
	#define RGBLIGHT_EFFECT_KNIGHT
	#define RGBLIGHT_EFFECT_CHRISTMAS
	#define RGBLIGHT_EFFECT_STATIC_GRADIENT
	#define RGBLIGHT_EFFECT_RGB_TEST
	#define RGBLIGHT_EFFECT_ALTERNATING
	#define RGBLIGHT_EFFECT_TWINKLE

    #define RGBLED_NUM 70
	//#define RGBLED_SPLIT
	#define RGBLED_SPLIT { 35, 35 } // haven't figured out how to use this yet

	//#define RGBLED_NUM 30
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

#ifdef RGB_MATRIX_ENABLE
#   define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#   define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #   define RGB_MATRIX_LED_PROCESS_LIMIT (RGB_MATRIX_LED_COUNT + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
// #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.

#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_GRADIENT_LEFT_RIGHT

#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

/* Disable the animations you don't want/need.  You will need to disable a good number of these    *
 * because they take up a lot of space.  Disable until you can successfully compile your firmware. */
 //#   undef ENABLE_RGB_MATRIX_ALPHAS_MODS
 // #   undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
 // #   undef ENABLE_RGB_MATRIX_BREATHING
 // #   undef ENABLE_RGB_MATRIX_CYCLE_ALL
 // #   undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
 // #   undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
 // #   undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
 // #   undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
 // #   undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
 // #   undef ENABLE_RGB_MATRIX_DUAL_BEACON
 // #   undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
 // #   undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
 // #   undef ENABLE_RGB_MATRIX_RAINDROPS
 // #   undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
 // #   undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
 // #   undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
 // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
 // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
 // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
 // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
 // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
 // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
 // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
 // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
 // #   undef ENABLE_RGB_MATRIX_SPLASH
 // #   undef ENABLE_RGB_MATRIX_MULTISPLASH
 // #   undef ENABLE_RGB_MATRIX_SOLID_SPLASH
 // #   undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif

#define MIDI_ADVANCED

//#define USE_I2C
#ifdef OLED_ENABLE
    //#define OLED_DISPLAY_128X32
    #define I2C1_SCL_PIN        GP13
    #define I2C1_SDA_PIN        GP12
    #define OLED_BRIGHTNESS 128
    //#define OLED_FONT_H "keyboards/mlego/m65/lib/glcdfont.c"
#endif

/* ChibiOS SPI definitions */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP13
#define SPI_MOSI_PIN GP27
#define SPI_MISO_PIN GP28

/* Audio */
#define AUDIO_PIN GP0
#define AUDIO_PWM_DRIVER PWMD0
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#define AUDIO_INIT_DELAY
#define AUDIO_CLICKY
#define DAC_SAMPLE_MAX 65535U

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PREONIC_SOUND)
#endif


#define DYNAMIC_KEYMAP_LAYER_COUNT 9
