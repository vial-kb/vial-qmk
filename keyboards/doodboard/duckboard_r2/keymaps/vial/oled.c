/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H
#include "animation_frames.h"

#ifdef OLED_ENABLE
#define IDLE_FRAME_DURATION 200 // Idle animation iteration rate in ms

oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

uint32_t anim_timer         = 0;
uint8_t  current_idle_frame = 0;

// Decompress and write a precompressed bitmap frame to the OLED.
// Documentation and python compression script available at:
// https://github.com/nullbitsco/squeez-o
#ifdef USE_OLED_BITMAP_COMPRESSION
static void oled_write_compressed_P(const char* input_block_map, const char* input_block_list) {
    uint16_t block_index = 0;
    for (uint16_t i=0; i<NUM_OLED_BYTES; i++) {
        uint8_t bit = i%8;
        uint8_t map_index = i/8;
        uint8_t _block_map = (uint8_t)pgm_read_byte_near(input_block_map + map_index);
        uint8_t nonzero_byte = (_block_map & (1 << bit));
        if (nonzero_byte) {
            const char data = (const char)pgm_read_byte_near(input_block_list + block_index++);
            oled_write_raw_byte(data, i);
        } else {
            const char data = (const char)0x00;
            oled_write_raw_byte(data, i);
        }
    }
}
#endif

static void render_anim(void) {
    void animation_phase(void) {
        current_idle_frame = (current_idle_frame + 1) % NUM_IDLE_FRAMES;
        uint8_t idx = abs((NUM_IDLE_FRAMES - 1) - current_idle_frame);
        #ifdef USE_OLED_BITMAP_COMPRESSION
        oled_write_compressed_P(idle_block_map[idx], idle_frames[idx]);
        #else
        oled_write_raw_P(idle_frames[idx], NUM_OLED_BYTES);
        #endif
    }

    if (timer_elapsed32(anim_timer) > IDLE_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase();
    }
}

bool oled_task_user(void) {
    render_anim();
    oled_set_cursor(0,6);
    oled_write_P(PSTR("DUCK\nBOARD\n"), false);
    oled_write_P(PSTR("-----\n"), false);
    // Host Keyboard Layer Status
    oled_write_P(PSTR("MODE\n\n"), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("BASE\n"), false);
            break;
        case 1:
            oled_write_P(PSTR("FUNC\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("FUNC2\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("FUNC3\n"), false);
            break;
        case 4:
            oled_write_P(PSTR("FUNC4\n"), false);
            break;
        default:
            oled_write_P(PSTR("QUACK\n"), false);
            break;
    }
    return false;
}

void suspend_power_down_user(void) {
    oled_off();
}
#endif
