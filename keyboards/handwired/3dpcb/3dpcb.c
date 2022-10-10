#include "3dpcb.h"

static uint16_t led_timer;
bool            led_layer_state = false;

// Blink at layer 1, 2 or 3
void matrix_scan_kb(void) {
    uint8_t layer   = biton32(layer_state);
    uint8_t usb_led = host_keyboard_leds();

    if (timer_elapsed(led_timer) > LAYER_BLINK_TIME) {
        switch (layer) {
            case 1:
                if (!led_layer_state) {
                    led_set(0);
                } else {
                    led_set(2);
                }

                led_layer_state = !led_layer_state;
                break;
            case 2:
                if (!led_layer_state) {
                    led_set(0);
                } else {
                    led_set(1);
                }

                led_layer_state = !led_layer_state;
                break;
            case 3:
                if (!led_layer_state) {
                    led_set(0);
                } else {
                    led_set(3);
                }

                led_layer_state = !led_layer_state;
                break;
            default:
                led_set(usb_led);
                led_layer_state = false;
        }

        led_timer = timer_read();
    }

    matrix_scan_user();
};
