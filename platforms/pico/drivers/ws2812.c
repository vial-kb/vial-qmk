
#include <stdio.h>

#include "ws2812.h"
#include "ws2812.pio.h"

#include "pio_manager.h"
#include "boards/pico_boards.h"

#include "pico/stdlib.h"

static PIO pio = pio0;
static int sm  = 0;

static int ws2812_init(void) {
    sm = pio_manager_get_empty_sm(pio);

    if (sm < 0) {
        return -1;
    }

    int32_t offset = pio_manager_add_program(pio, sm, &ws2812_program);

    if (offset < 0) {
        return -1;
    }

    ws2812_program_init(pio, sm, offset, RGB_DI_PIN, 800000, false);

    return 0;
}

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds) {
    static bool s_init = false;
    if (!s_init) {
        if (ws2812_init() == 0) {
            s_init = true;
        } else {
            return;
        }
    }

    printf("led %d %d %d\n", ledarray[0].r, ledarray[0].g, ledarray[0].b);

    for (int i = 0; i < number_of_leds; i++) {
        pio_sm_put_blocking(pio, sm,
                            (((uint32_t)ledarray[i].r) << 16) |
                                (((uint32_t)ledarray[i].g) << 24) |
                                ((uint32_t)ledarray[i].b << 8));
    }
}
