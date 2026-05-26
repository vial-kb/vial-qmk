/*
Copyright 2023 YANG <drk@live.com>

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

#include "hal.h"
#include "ch.h"
#include "led.h"
#include "rgblight.h"

#include "stdint.h"
#include "quantum.h"

#ifndef LOGIC_INDICATOR_NUM
#define LOGIC_INDICATOR_NUM PHY_INDICATOR_NUM
#endif

extern rgblight_config_t rgblight_config;
extern bool is_sc_leds_mcu;

static LED_TYPE RGBLIGHT_COLOR_OFF = { .r = 0, .g = 0, .b = 0 };
uint8_t indicator_state = 0;
uint8_t indicator_color_config[3];
LED_TYPE indicator_color[3];

#ifdef WELCOME_LIGHT
uint8_t welcome_light_on = 10;
#else
uint8_t welcome_light_on = 0;
#endif

LED_TYPE rgbled[PHY_INDICATOR_NUM+RGBLED_NUM];

void single_color_indicator_set(uint8_t index, bool on)
{
    if (index == 0) {
        if (on) palSetPad(GPIOB, 14);
        else palClearPad(GPIOB, 14);
    } else if (index == 1) {
        if (on) palSetPad(GPIOA, 8);
        else palClearPad(GPIOA, 8);
    }
}

void set_rgb_user(uint8_t r, uint8_t g,  uint8_t b)
{
    for (uint8_t i=0; i<(PHY_INDICATOR_NUM+RGBLED_NUM); i++) {
        rgbled[i].r = r;
        rgbled[i].g = g;
        rgbled[i].b = b;
    }
    ws2812_setleds(rgbled, PHY_INDICATOR_NUM+RGBLED_NUM);
}

void rgblight_user_init(void)
{
#ifdef CONFIG_BOOT_TEST_RGB
    set_rgb_user(32, 0, 0);
    wait_ms(300);
    set_rgb_user(0, 32, 0);
    wait_ms(300);
    set_rgb_user(0, 0, 32);
    wait_ms(300);
#endif
    set_rgb_user(0, 0, 0);
}

void rgblight_call_driver(LED_TYPE *start_led, uint8_t num_leds) {
    // keep indicator color
    for (uint8_t i=0; i<PHY_INDICATOR_NUM; i++) {
        if (indicator_state & (1<<i)) {
            rgbled[i] = indicator_color[i];
            single_color_indicator_set(i, true);
        } else {
            rgbled[i] = RGBLIGHT_COLOR_OFF;
            single_color_indicator_set(i, false);
        }
    }


    if (is_sc_leds_mcu) {
        ws2812_setleds(start_led, RGBLED_NUM);
        return;
    }

    memcpy(&rgbled[PHY_INDICATOR_NUM], start_led, RGBLED_NUM*3);
#ifdef RGB_EXTRA_PROCESS_ENABLE
    rgb_extra_process(rgbled);
#endif

    if (!welcome_light_on) ws2812_setleds(rgbled, PHY_INDICATOR_NUM+RGBLED_NUM);
}

void led_set_user(uint8_t usb_led)
{
    indicator_state = 0;
#ifdef INDICATOR_FUNCT
    static uint8_t indicator_funct[LOGIC_INDICATOR_NUM] = INDICATOR_FUNCT;
    for (uint8_t i=0; i<LOGIC_INDICATOR_NUM; i++) {
        if (usb_led & indicator_funct[i]) {
            indicator_state |= (1<<i);
        }
    }
    // 固定颜色模式下，更新一次。否则在关闭led时，指示灯颜色未更新。
    if (rgblight_config.mode == 1) rgblight_mode_noeeprom(rgblight_config.mode);
    rgblight_set(); //set rgb even when rgblight.enable=0
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint8_t mod_keys_registered;
    uint8_t pressed_mods = get_mods();
    switch (keycode) {
        case 0x5c00: // via/vial reset to bootloader
            if (record->event.pressed) {
                clear_keyboard();
                volatile uint32_t *uf2bl_backup_reg = (uint32_t*)0x20004000;
            	*uf2bl_backup_reg = 0x9d5bfc2bUL;
            	NVIC_SystemReset();
            }
            return false;
        // 0x5f8f for Alt+Esc=f4 and RShift+Esc=~
        case 0x5F8F:
            if (record->event.pressed) {
                if ((pressed_mods & MOD_BIT(KC_RSHIFT)) && (~pressed_mods & MOD_BIT(KC_LCTRL))) {
                    mod_keys_registered = KC_GRV;
                } else if (pressed_mods & MOD_BIT(KC_LALT)) {
                    mod_keys_registered = KC_F4;
                } else {
                    mod_keys_registered = KC_ESC;
                }
                register_code(mod_keys_registered);
                send_keyboard_report();
            } else {
                unregister_code(mod_keys_registered);
                send_keyboard_report();
            }
            return false;
        default:
            return true; // Process all other keycodes normally
    }
}

void enter_bootloader(void) {
    clear_keyboard();
    volatile uint32_t *uf2bl_backup_reg = (uint32_t*)0x20004000;
    *uf2bl_backup_reg = 0x9d5bfc2bUL;
    NVIC_SystemReset();
}
/* LShift+RShift+LCtrl+B to Bootloader */
#include "command.h"

bool command_extra(uint8_t code)
{
    uint8_t pressed_mods = get_mods();
    clear_keyboard();
    switch (code) {
        case KC_B:
            ;
            wait_us(500*1000);
            if (pressed_mods & MOD_BIT(KC_LCTRL)) {
                enter_bootloader();
            }
            //soft reset
            NVIC_SystemReset();
            //*(uint32_t *)(0xE000ED0CUL) = 0x05FA0000UL | (*(uint32_t *)(0xE000ED0CUL) & 0x0700) | 0x04;
            break;
        default:
            return false;   // yield to default command
    }
    return true;
}

void restart_usb_driver(USBDriver *usbp) {
    NVIC_SystemReset();
}

void user_config_init(void)
{
    static const uint8_t indicator_hue_preset[8] = {254, 0, 42, 85, 127, 170, 212, 255};
    #ifdef INDICATOR_VAL
    static uint8_t val = INDICATOR_VAL;
    #else 
    static uint8_t val = 255;
    #endif

    uint16_t layout_value = via_get_layout_options();
    for (uint8_t i=0; i<3; i++) {
        indicator_color_config[i] = (layout_value & 0b111);
        uint8_t hue = indicator_hue_preset[ indicator_color_config[i] ];
        layout_value >>= 3;
        if (hue == 254) indicator_color[i] = (LED_TYPE){val/2, val/2, val/2}; //white color, val/2
        else if (hue == 255) indicator_color[i] = (LED_TYPE){0, 0, 0}; //disable this indicator
        else            indicator_color[i] = hsv_to_rgb((HSV){hue, 255, val});
        xprintf("\n indicator %d R: %d, G: %d, B:%d", i, indicator_color[i].r, indicator_color[i].g, indicator_color[i].b);
    }
    led_wakeup(); //立即更新指示灯颜色
    rprint("Layout set change\n");
}

//rgblight welcome
extern rgblight_config_t rgblight_config;
extern bool is_rgblight_initialized;
extern LED_TYPE led[];
void hook_keyboard_loop(void)
{
#ifndef WELCOME_LIGHT
    return;
#endif
    //only for taco75
    //ready
    static LED_TYPE *led = &rgbled[PHY_INDICATOR_NUM];
    if (welcome_light_on == 10 && is_rgblight_initialized) {
        welcome_light_on = 4;
        rgblight_config.enable = 0;
        rgblight_config.mode = 0;
    }

    // show
    static uint16_t rgb_update_timer = 0;
    if (welcome_light_on && rgb_update_timer != timer_read() && timer_elapsed(rgb_update_timer) > 30) {
        rgb_update_timer = timer_read();

        static uint8_t welcome_step = 0;
        LED_TYPE welcome_led_color;
        sethsv(rgblight_config.hue, rgblight_config.sat, rgblight_config.val, &welcome_led_color);
        if (welcome_light_on == 2 || welcome_light_on == 4) {
            memset(led, 0, RGBLED_NUM*3);
        } else if (welcome_light_on == 1 || welcome_light_on == 3) {
            for (uint8_t i=0;i<RGBLED_NUM;i++) {
                led[i] = welcome_led_color;
            }
            welcome_led_color = RGBLIGHT_COLOR_OFF;
        }
        for (uint8_t i=0; i<welcome_step; i++) {
            led[6-i] = led[7+i] = welcome_led_color;
        }
        // force rgb update even rgblight off
        ws2812_setleds(rgbled, PHY_INDICATOR_NUM+RGBLED_NUM);
        if (welcome_step < 7) {
            static uint8_t led_step = 0;
            if (++led_step < 3) return;
            led_step = 0;
            welcome_step++;
        } else {
            welcome_step = 0;
            welcome_light_on--;
            //restore config
            if (welcome_light_on == 0) {
                rgblight_reload_from_eeprom();
            }
        }
    }
}

// Snap Tap / SOCD
static const uint8_t SOCD_KEY[2][2] = {
    { KC_W, KC_S },
    { KC_A, KC_D }
};

bool socd_key_state[2][2] = { {0,0},{0,0}};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= USER00 && keycode <= USER03) {
        uint8_t key = keycode - USER00;
        uint8_t k_group = key&1;
        uint8_t k_num = key>>1;
        uint8_t k_op_num = k_num?0:1;
        if (record->event.pressed) {
            socd_key_state[k_group][k_num] = 1;
            if (socd_key_state[k_group][k_op_num]) {
                unregister_code(SOCD_KEY[k_group][k_op_num]);
            }
            register_code(SOCD_KEY[k_group][k_num]);
        } else {
            socd_key_state[k_group][k_num] = 0;
            unregister_code(SOCD_KEY[k_group][k_num]);
            if (socd_key_state[k_group][k_op_num]) {
                register_code(SOCD_KEY[k_group][k_op_num]);
            }
        }
    }
}