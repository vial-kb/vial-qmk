#include "bipedalambi.h"

// Global variables (used by keymap regardless of OLED)
enum pointing_device_mode current_mode = MODE_CUSTOM_KEYS;
int actuation = 256;
uint32_t actuation_display_timer = 0;
bool showing_actuation = false;

#ifdef OLED_ENABLE
#include "i2c_master.h"

// Send display off command before OLED driver initializes
void keyboard_pre_init_user(void) {
    i2c_init();
    uint8_t display_off_cmd[] = {0x00, 0xAE};
    i2c_transmit(0x3C << 1, display_off_cmd, 2, 100);
}

// Layer state arrays
static const char PROGMEM default_layer_on_scroll[] = {
    0x20, 0x21, 0x22, 0x23, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x31, 0x32, 0x93, 0x94,
    0x40, 0x41, 0x42, 0x43, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0x51, 0x52, 0xB3, 0xB4,
    0x60, 0x61, 0x62, 0x63, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0x71, 0x72, 0xD3, 0xD4, 0x00
};

static const char PROGMEM default_layer_on_keycodes[] = {
    0x95, 0x96, 0x97, 0x98, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x31, 0x32, 0x93, 0x94,
    0xB5, 0xB6, 0xB7, 0xB8, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0x51, 0x52, 0xB3, 0xB4,
    0xD5, 0xD6, 0xD7, 0xD8, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0x71, 0x72, 0xD3, 0xD4, 0x00
};

static const char PROGMEM one_layer_on_scroll[] = {
    0x20, 0x21, 0x22, 0x23, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x2E, 0x2F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0x40, 0x41, 0x42, 0x43, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0x4E, 0x4F, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0x60, 0x61, 0x62, 0x63, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0x6E, 0x6F, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
};

static const char PROGMEM one_layer_on_keycodes[] = {
    0x95, 0x96, 0x97, 0x98, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x2E, 0x2F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xB5, 0xB6, 0xB7, 0xB8, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0x4E, 0x4F, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xD5, 0xD6, 0xD7, 0xD8, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0x6E, 0x6F, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
};

static const char PROGMEM two_layer_on_scroll[] = {
    0x20, 0x21, 0x22, 0x23, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x2B, 0x2C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0x40, 0x41, 0x42, 0x43, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0x4B, 0x4C, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0x60, 0x61, 0x62, 0x63, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0x6B, 0x6C, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
};

static const char PROGMEM two_layer_on_keycodes[] = {
    0x95, 0x96, 0x97, 0x98, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x2B, 0x2C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xB5, 0xB6, 0xB7, 0xB8, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0x4B, 0x4C, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xD5, 0xD6, 0xD7, 0xD8, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0x6B, 0x6C, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
};

static const char PROGMEM three_layer_on_scroll[] = {
    0x20, 0x21, 0x22, 0x23, 0x84, 0x85, 0x86, 0x87, 0x28, 0x29, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0x40, 0x41, 0x42, 0x43, 0xA4, 0xA5, 0xA6, 0xA7, 0x48, 0x49, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0x60, 0x61, 0x62, 0x63, 0xC4, 0xC5, 0xC6, 0xC7, 0x68, 0x69, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
};

static const char PROGMEM three_layer_on_keycodes[] = {
    0x95, 0x96, 0x97, 0x98, 0x84, 0x85, 0x86, 0x87, 0x28, 0x29, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xB5, 0xB6, 0xB7, 0xB8, 0xA4, 0xA5, 0xA6, 0xA7, 0x48, 0x49, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xD5, 0xD6, 0xD7, 0xD8, 0xC4, 0xC5, 0xC6, 0xC7, 0x68, 0x69, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
};

// Actuation level arrays
static const char PROGMEM actuation_level_1[] = {
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3E, 0x3F, 0x1F, 0x9D, 0x1F, 0x84, 0x85, 0x86, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x5E, 0x5F, 0x1F, 0xBD, 0x1F, 0xA4, 0xA5, 0xA6, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x7E, 0x7F, 0x1F, 0xDD, 0x1F, 0xC4, 0xC5, 0xC6, 0x1F, 0x1F, 0x1F, 0x1F, 0x00
};

static const char PROGMEM actuation_level_2[] = {
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3C, 0x3D, 0x1F, 0x9D, 0x1F, 0x84, 0x85, 0x86, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x5C, 0x5D, 0x1F, 0xBD, 0x1F, 0xA4, 0xA5, 0xA6, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x7C, 0x7D, 0x1F, 0xDD, 0x1F, 0xC4, 0xC5, 0xC6, 0x1F, 0x1F, 0x1F, 0x1F, 0x00
};

static const char PROGMEM actuation_level_3[] = {
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x3A, 0x3B, 0x1F, 0x9D, 0x1F, 0x84, 0x85, 0x86, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x5A, 0x5B, 0x1F, 0xBD, 0x1F, 0xA4, 0xA5, 0xA6, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x7A, 0x7B, 0x1F, 0xDD, 0x1F, 0xC4, 0xC5, 0xC6, 0x1F, 0x1F, 0x1F, 0x1F, 0x00
};

static const char PROGMEM actuation_level_4[] = {
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x38, 0x39, 0x1F, 0x9D, 0x1F, 0x84, 0x85, 0x86, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x58, 0x59, 0x1F, 0xBD, 0x1F, 0xA4, 0xA5, 0xA6, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x78, 0x79, 0x1F, 0xDD, 0x1F, 0xC4, 0xC5, 0xC6, 0x1F, 0x1F, 0x1F, 0x1F, 0x00
};

static const char PROGMEM actuation_level_5[] = {
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x36, 0x37, 0x1F, 0x9D, 0x1F, 0x84, 0x85, 0x86, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x56, 0x57, 0x1F, 0xBD, 0x1F, 0xA4, 0xA5, 0xA6, 0x1F, 0x1F, 0x1F, 0x1F,
    0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x76, 0x77, 0x1F, 0xDD, 0x1F, 0xC4, 0xC5, 0xC6, 0x1F, 0x1F, 0x1F, 0x1F, 0x00
};

void render_layer_state(void) {
    uint8_t layer = get_highest_layer(layer_state);

    switch(layer) {
        case 0:
            switch(current_mode) {
                case MODE_SCROLLING:    oled_write_P(default_layer_on_scroll, false); break;
                case MODE_CUSTOM_KEYS:
                default:                oled_write_P(default_layer_on_keycodes, false); break;
            }
            break;
        case 1:
            switch(current_mode) {
                case MODE_SCROLLING:    oled_write_P(one_layer_on_scroll, false); break;
                case MODE_CUSTOM_KEYS:
                default:                oled_write_P(one_layer_on_keycodes, false); break;
            }
            break;
        case 2:
            switch(current_mode) {
                case MODE_SCROLLING:    oled_write_P(two_layer_on_scroll, false); break;
                case MODE_CUSTOM_KEYS:
                default:                oled_write_P(two_layer_on_keycodes, false); break;
            }
            break;
        case 3:
            switch(current_mode) {
                case MODE_SCROLLING:    oled_write_P(three_layer_on_scroll, false); break;
                case MODE_CUSTOM_KEYS:
                default:                oled_write_P(three_layer_on_keycodes, false); break;
            }
            break;
        default:
            oled_write_P(PSTR("LAYER: UNKNOWN\n"), false);
            break;
    }
}

void render_actuation_state(void) {
    switch(actuation) {
        case 64:  oled_write_P(actuation_level_5, false); break;
        case 128: oled_write_P(actuation_level_4, false); break;
        case 256: oled_write_P(actuation_level_3, false); break;
        case 320: oled_write_P(actuation_level_2, false); break;
        case 352: oled_write_P(actuation_level_1, false); break;
        default:  oled_write_P(actuation_level_3, false); break;
    }
}

// --- SCREENSAVER LOGIC ---

#define SCREEN_CENTER_X 64
#define SCREEN_CENTER_Y 16
#define FRAME_DELAY 40
#define NUM_PARTICLES 50
#define SCREENSAVER_TIMEOUT 60000
#define SCREEN_OFF_TIMEOUT 300000
#define SPLASH_DURATION 2000

typedef struct {
    int16_t x; int16_t y;
    int16_t dx; int16_t dy;
    int16_t prev_x; int16_t prev_y;
    int16_t prev2_x; int16_t prev2_y;
} warp_particle_t;

static warp_particle_t warp_particles[NUM_PARTICLES];
static uint32_t animation_timer = 0;
static bool warp_initialized = false;
static uint32_t last_activity_time = 0;
static bool screensaver_active = false;
static uint32_t screensaver_start_time = 0;
static bool screen_is_off = false;
static uint16_t rng_state = 12345;
static bool splash_shown = false;
static bool splash_initialized = false;

static uint16_t simple_rand(void) {
    rng_state ^= rng_state << 7;
    rng_state ^= rng_state >> 9;
    rng_state ^= rng_state << 8;
    return rng_state;
}

static void init_warp_particle(warp_particle_t *p) {
    int16_t edge_rand = simple_rand() % 100;
    if (edge_rand < 40) { p->x = (simple_rand() % 128) * 16; p->y = 0; }
    else if (edge_rand < 80) { p->x = (simple_rand() % 128) * 16; p->y = 31 * 16; }
    else if (edge_rand < 90) { p->x = 0; p->y = (simple_rand() % 32) * 16; }
    else { p->x = 127 * 16; p->y = (simple_rand() % 32) * 16; }

    int16_t target_x = SCREEN_CENTER_X * 16;
    int16_t target_y = SCREEN_CENTER_Y * 16;
    int16_t diff_x = target_x - p->x;
    int16_t diff_y = target_y - p->y;
    int16_t abs_dx = diff_x < 0 ? -diff_x : diff_x;
    int16_t abs_dy = diff_y < 0 ? -diff_y : diff_y;
    int16_t dist = abs_dx > abs_dy ? abs_dx + (abs_dy >> 1) : abs_dy + (abs_dx >> 1);
    int16_t speed = 32 + (simple_rand() % 32);

    if (dist > 16) {
        p->dx = (diff_x * speed) / dist;
        p->dy = (diff_y * speed) / dist;
    } else {
        p->dx = 16; p->dy = 8;
    }
    p->prev_x = p->x; p->prev_y = p->y;
    p->prev2_x = p->x; p->prev2_y = p->y;
}

static void init_warp(void) {
    rng_state = timer_read() | 1;
    for (int i = 0; i < NUM_PARTICLES; i++) init_warp_particle(&warp_particles[i]);
}

static void update_warp(bool respawn) {
    int16_t target_x = SCREEN_CENTER_X * 16;
    int16_t target_y = SCREEN_CENTER_Y * 16;
    for (int i = 0; i < NUM_PARTICLES; i++) {
        warp_particle_t *p = &warp_particles[i];
        p->prev2_x = p->prev_x; p->prev2_y = p->prev_y;
        p->prev_x = p->x; p->prev_y = p->y;
        p->x += p->dx; p->y += p->dy;

        int16_t diff_x = target_x - p->x;
        int16_t diff_y = target_y - p->y;
        int16_t abs_dx = diff_x < 0 ? -diff_x : diff_x;
        int16_t abs_dy = diff_y < 0 ? -diff_y : diff_y;

        if (abs_dx < 32 && abs_dy < 32) {
            if (respawn) init_warp_particle(p);
            else { p->x = target_x; p->y = target_y; p->dx = 0; p->dy = 0; }
        }
    }
}

static void render_warp(uint8_t count) {
    oled_clear();
    int16_t target_x = SCREEN_CENTER_X * 16;
    int16_t target_y = SCREEN_CENTER_Y * 16;
    for (int i = 0; i < count && i < NUM_PARTICLES; i++) {
        warp_particle_t *p = &warp_particles[i];
        if (p->dx == 0 && p->dy == 0 && p->x == target_x && p->y == target_y) continue;

        int16_t px = p->x / 16; int16_t py = p->y / 16;
        if (px >= 0 && px < 128 && py >= 0 && py < 32) oled_write_pixel(px, py, true);

        px = p->prev_x / 16; py = p->prev_y / 16;
        if (px >= 0 && px < 128 && py >= 0 && py < 32) oled_write_pixel(px, py, true);

        px = p->prev2_x / 16; py = p->prev2_y / 16;
        if (px >= 0 && px < 128 && py >= 0 && py < 32) oled_write_pixel(px, py, true);

        int16_t dist_x = p->x - target_x;
        int16_t dist_y = p->y - target_y;
        int16_t adx = dist_x < 0 ? -dist_x : dist_x;
        int16_t ady = dist_y < 0 ? -dist_y : dist_y;

        if (adx < 80 && ady < 80) {
            px = p->x / 16;
            py = p->y / 16;
            if (px > 0 && px < 127) {
                oled_write_pixel(px - 1, py, true);
                oled_write_pixel(px + 1, py, true);
            }
            if (py > 0 && py < 31) {
                oled_write_pixel(px, py - 1, true);
                oled_write_pixel(px, py + 1, true);
            }
        }
    }
}

// Startup animation state
static uint32_t oled_startup_timer = 0;
static bool oled_startup_complete = false;
static uint8_t startup_phase = 0;
static uint8_t noise_frame = 0;
#define NOISE_DURATION 1000
#define NOISE_FRAME_MS 50
#define DISSOLVE_MS 2500

static uint16_t noise_seed = 31337;
static uint8_t fast_rand(void) {
    noise_seed ^= noise_seed << 7;
    noise_seed ^= noise_seed >> 9;
    noise_seed ^= noise_seed << 8;
    return (uint8_t)(noise_seed & 0xFF);
}

static void fill_noise(void) {
    uint8_t width = oled_max_chars() * OLED_FONT_WIDTH;
    uint8_t height = oled_max_lines() * OLED_FONT_HEIGHT;
    oled_clear();
    for (uint8_t y = 0; y < height; y++) {
        for (uint8_t x = 0; x < width; x++) {
            if ((fast_rand() % 10) == 0) {
                oled_write_pixel(x, y, true);
            }
        }
    }
}

static void render_dissolve(uint8_t noise_level) {
    uint8_t width = oled_max_chars() * OLED_FONT_WIDTH;
    uint8_t height = oled_max_lines() * OLED_FONT_HEIGHT;
    oled_clear();
    render_layer_state();
    for (uint8_t y = 0; y < height; y++) {
        for (uint8_t x = 0; x < width; x++) {
            if ((fast_rand() % 100) < noise_level) {
                oled_write_pixel(x, y, (fast_rand() % 10) == 0);
            }
        }
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    oled_startup_timer = timer_read32();
    oled_startup_complete = false;
    startup_phase = 0;
    noise_frame = 0;
    noise_seed = timer_read() | 1;
    return rotation;
}

void register_oled_activity(void) {
    last_activity_time = timer_read32();
    if (screen_is_off) {
        screen_is_off = false;
        oled_on();
    }
    if (screensaver_active) {
        screensaver_active = false;
        warp_initialized = false;
        oled_clear();
    }
}

bool oled_task_user(void) {
    if (!oled_startup_complete) {
        uint32_t elapsed = timer_elapsed32(oled_startup_timer);

        switch (startup_phase) {
            case 0:
                if (elapsed < NOISE_DURATION) {
                    if (elapsed >= (noise_frame + 1) * NOISE_FRAME_MS) {
                        fill_noise();
                        noise_frame++;
                    }
                } else {
                    startup_phase = 1;
                    oled_startup_timer = timer_read32();
                }
                break;
            case 1:
                if (elapsed < DISSOLVE_MS) {
                    uint32_t progress = (elapsed * 100) / DISSOLVE_MS;
                    uint32_t eased = (progress * progress) / 100;
                    uint8_t noise_level = 100 - eased;
                    if ((fast_rand() % 8) == 0) {
                        noise_level = noise_level / 3;
                    }
                    render_dissolve(noise_level);
                } else {
                    startup_phase = 2;
                }
                break;
            case 2:
                oled_startup_complete = true;
                splash_shown = true;
                splash_initialized = true;
                last_activity_time = timer_read32();
                oled_clear();
                render_layer_state();
                break;
        }
        return false;
    }

    // Use QMK's synced activity timer to wake OLED on either half
    // (process_record_user only runs on master, so slave OLED needs this)
    if ((screensaver_active || screen_is_off) && last_input_activity_elapsed() < 1000) {
        register_oled_activity();
    }

    if (!screensaver_active && timer_elapsed32(last_activity_time) > SCREENSAVER_TIMEOUT) {
        screensaver_active = true;
        screensaver_start_time = timer_read32();
    }

    if (screensaver_active) {
        if (!screen_is_off && timer_elapsed32(screensaver_start_time) > SCREEN_OFF_TIMEOUT) {
            screen_is_off = true;
            oled_clear();
            oled_off();
        }
        if (screen_is_off) return false;

        if (timer_elapsed32(animation_timer) > FRAME_DELAY) {
            if (!warp_initialized) { init_warp(); warp_initialized = true; }
            update_warp(true);
            render_warp(NUM_PARTICLES);
            animation_timer = timer_read32();
        }
        return false;
    }

    static bool was_showing_actuation = false;

    if (showing_actuation) {
        if (!was_showing_actuation) {
            oled_clear();
            was_showing_actuation = true;
        }
        if (timer_elapsed32(actuation_display_timer) > ACTUATION_DISPLAY_DURATION) {
            showing_actuation = false;
            was_showing_actuation = false;
            oled_clear();
            render_layer_state();
        } else {
            render_actuation_state();
        }
    } else {
        if (was_showing_actuation) {
            oled_clear();
            was_showing_actuation = false;
        }
        render_layer_state();
    }

    return false;
}

#else
// No OLED - provide stub
void register_oled_activity(void) {}
#endif
