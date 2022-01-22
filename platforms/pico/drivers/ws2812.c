// Copyright 2022 sekigon-gonnoc
// SPDX-License-Identifier: GPL-2.0-or-later

#include <stdio.h>

#include "ws2812.h"
#include "ws2812.pio.h"

#include "atomic_util.h"
#include "pio_manager.h"
#include "boards/pico_boards.h"

#include "pico/stdlib.h"
#include "hardware/dma.h"

static PIO pio    = pio0;
static int sm     = 0;
static int dma_ch = 1;

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

    dma_channel_config conf = dma_channel_get_default_config(dma_ch);

    channel_config_set_read_increment(&conf, true);
    channel_config_set_write_increment(&conf, false);
    channel_config_set_transfer_data_size(&conf, DMA_SIZE_32);
    channel_config_set_dreq(&conf, pio_get_dreq(pio, sm, true));

    dma_channel_set_config(dma_ch, &conf, false);
    dma_channel_set_write_addr(dma_ch, &pio->txf[sm], false);
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

    uint32_t leddata[RGBLED_NUM];
    for (int i = 0; i < number_of_leds; i++) {
        leddata[i] = (((uint32_t)ledarray[i].g) << 24) |
                     (((uint32_t)ledarray[i].r) << 16) |
                     ((uint32_t)ledarray[i].b << 8);
    }

    dma_channel_transfer_from_buffer_now(dma_ch, leddata, number_of_leds);
    dma_channel_wait_for_finish_blocking(dma_ch);
}
