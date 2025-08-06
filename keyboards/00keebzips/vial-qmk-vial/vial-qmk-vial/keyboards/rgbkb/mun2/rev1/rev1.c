/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include "rev1.h"
#include "split_util.h"

#define NUMBER_OF_TOUCH_ENCODERS 2
#define TOUCH_ENCODER_OPTIONS TOUCH_SEGMENTS + 2

#define NUMBER_OF_ENCODERS 6
#define ENCODER_OPTIONS 2

typedef struct PACKED {
    uint8_t r;
    uint8_t c;
} encodermap_t;

// this maps encoders and then touch encoders to their respective electrical matrix entry
// mapping is row (y) then column (x) when looking at the electrical layout
const encodermap_t encoder_map[NUMBER_OF_ENCODERS][ENCODER_OPTIONS] = 
{
    { {  5, 0 }, {  5, 1 } }, // Encoder 0 matrix entries
    { {  5, 2 }, {  5, 3 } }, // Encoder 1 matrix entries
    { {  5, 4 }, {  5, 5 } }, // Encoder 2 matrix entries
    { { 12, 0 }, { 12, 1 } }, // Encoder 3 matrix entries
    { { 12, 2 }, { 12, 3 } }, // Encoder 4 matrix entries
    { { 12, 4 }, { 12, 5 } }  // Encoder 5 matrix entries
};

const encodermap_t touch_encoder_map[NUMBER_OF_TOUCH_ENCODERS][TOUCH_ENCODER_OPTIONS] = 
{
    { {  6, 0 }, {  6, 1 }, {  6, 2 }, {  6, 3 }, {  6, 4 }, }, // Touch Encoder 0 matrix entries
    { { 13, 0 }, { 13, 1 }, { 13, 2 }, { 13, 3 }, { 13, 4 }, }  // Touch Encoder 1 matrix entries
};

static void process_encoder_matrix(encodermap_t pos) {
    action_exec(MAKE_KEYEVENT(pos.r, pos.c, true));
#if TAP_CODE_DELAY > 0
    wait_ms(TAP_CODE_DELAY);
#endif
    action_exec(MAKE_KEYEVENT(pos.r, pos.c, false));
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise))
        return false;

    // Mapping clockwise (typically increase) to zero, and counter clockwise (decrease) to 1
    process_encoder_matrix(encoder_map[index][clockwise ? 0 : 1]);
    return false;
}

bool touch_encoder_update_kb(uint8_t index, bool clockwise) {
    if (!touch_encoder_update_user(index, clockwise))
        return false;

    // Mapping clockwise (typically increase) to zero, and counter clockwise (decrease) to 1
    process_encoder_matrix(touch_encoder_map[index][clockwise ? 0 : 1]);
    return false;
}

bool touch_encoder_tapped_kb(uint8_t index, uint8_t section) {
    if (!touch_encoder_tapped_user(index, section))
        return false;

    process_encoder_matrix(touch_encoder_map[index][section + 2]);
    return false;
}

#ifdef RGB_MATRIX_ENABLE
// clang-format off
led_config_t g_led_config = { {
    {  NO_LED, NO_LED,   1,   2,   3,   4,   5,   6},
    {  0, 13,  12,  11,  10,   9,   8,   7},
    {  NO_LED, 14,  15,  16,  17,  18,  19,  20},
    {  28, 27,  26,  25,  24,  23,  22,  21},
    {  NO_LED, NO_LED,  29,  30,  31,  32,  33,  34},
    
    {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },

    {  NO_LED, NO_LED,  36,  37,  38,  39,  40,  41},
    {  35, 48,  47,  46,  45,  44,  43,  42},
    {  NO_LED, 49,  50,  51,  52,  53,  54,  55},
    {  63, 62,  61,  60,  59,  58,  57,  56},
    {  NO_LED, NO_LED,  64,  65,  66,  67,  68,  69},
    
    {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
    {  NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED }
}, { 
    {  11,  16},{  34,  16},{  49,  16},{  64,  16},{  79,  16},{  94,  16},{ 109,  16},
    { 109,  31},{  94,  31},{  79,  31},{  64,  31},{  49,  31},{  34,  31},{  11,  31},
    {  11,  46},{  34,  46},{  49,  46},{  64,  46},{  79,  46},{  94,  46},{ 109,  46},
    { 109,  61},{  94,  61},{  79,  61},{  64,  61},{  49,  61},{  34,  61},{  11,  61},
    {  11,  76},{  34,  76},{  49,  76},{  64,  76},{  79,  72},{  94,  72},{ 109,  72},

    //{  97,   5},{  91,   5},{  86,   5},{  80,   5},{  75,   5},{  69,   5},{  63,   5},
    //{  58,   5},{  52,   5},{  46,   5},{  41,   5},{  35,   5},{  30,   5},{  24,   5},{ 18,   5},

    { 219,  16},{ 199,  16},{ 184,  16},{ 169,  16},{ 154,  16},{ 139,  16},{ 124,  16},
    { 124,  31},{ 139,  31},{ 154,  31},{ 169,  31},{ 184,  31},{ 199,  31},{ 219,  31},
    { 219,  46},{ 199,  46},{ 184,  46},{ 169,  46},{ 154,  46},{ 139,  46},{ 124,  46},
    { 124,  61},{ 139,  61},{ 154,  61},{ 169,  61},{ 184,  61},{ 199,  61},{ 219,  61},
    { 219,  76},{ 199,  76},{ 184,  76},{ 169,  76},{ 154,  72},{ 139,  72},{ 124,  72}

    //{ 159,   5},{ 164,   5},{ 170,   5},{ 176,   5},{ 181,   5},{ 187,   5},{ 192,   5},
    //{ 198,   5},{ 204,   5},{ 209,   5},{ 215,   5},{ 221,   5},{ 226,   5},{ 232,   5},{ 238,   5}
    
}, {
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1,
    //2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1
    //2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2

} };
// clang-format on

void rgb_matrix_increase_flags(void)
{
    switch (rgb_matrix_get_flags()) {
        case LED_FLAG_ALL: {
            rgb_matrix_set_flags(LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_KEYLIGHT | LED_FLAG_MODIFIER: {
            rgb_matrix_set_flags(LED_FLAG_UNDERGLOW);
            rgb_matrix_set_color_all(0, 0, 0);
            }
            break;
        case LED_FLAG_UNDERGLOW: {
            rgb_matrix_set_flags(LED_FLAG_NONE);
            rgb_matrix_disable_noeeprom();
            }
            break;
        default: {
            rgb_matrix_set_flags(LED_FLAG_ALL);
            rgb_matrix_enable_noeeprom();
            }
            break;
    }
}
#endif


__attribute__((weak)) 
void render_layer_status(void) {
    // Keymap specific, expected to be overridden
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer"), false);
    oled_write_ln_P(PSTR("Undef"), false);
}

__attribute__((weak))
void render_leds_status(void)
{
    // Host Keyboard LED Status
    static const char PROGMEM led_icon[] = {
        0x0F,0x3A,0
    };
    oled_write_P(led_icon, false);
    led_t led_state = host_keyboard_led_state();
    oled_write_P(   led_state.num_lock ? PSTR("N") : PSTR(" "), false);
    oled_write_P(  led_state.caps_lock ? PSTR("C") : PSTR(" "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("S") : PSTR(" "), false);
}

__attribute__((weak))
void render_touch_status(void)
{
    // Host Touch LED Status
    static const char PROGMEM touch_icon[] = {
        0x12,0x3A,0
    };
    oled_write_P(touch_icon, false);
    oled_write_P(         touch_encoder_is_on() ? PSTR("T") : PSTR(" "), false);
    oled_write_P(touch_encoder_is_calibrating() ? PSTR("C") : PSTR(" "), false);
    oled_write_P(PSTR(" "), false);
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    // Sol 3 uses OLED_ROTATION_270 for default rotation on both halves
    return oled_init_user(OLED_ROTATION_270);
}

bool oled_task_kb(void) {
    if (!oled_task_user())
        return false;
    
    if (is_keyboard_left()) {
        render_icon();
        oled_write_P(PSTR("     "), false);
        render_layer_status();
        oled_write_P(PSTR("     "), false);
        render_leds_status();
        oled_write_P(PSTR("     "), false);
        render_touch_status();
    }
    else {
        render_icon();
        oled_write_P(PSTR("     "), false);
        render_rgb_menu();
    }
    return false;
}

//bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
//    if (!process_record_user(keycode, record))
//        return false;
//
//    switch(keycode) {
//#ifdef RGB_MATRIX_ENABLE
//        case RGB_TOG:
//            if (record->event.pressed) {
//                rgb_matrix_increase_flags();
//            }
//            return false;
//#endif
//    }
//    return true;
//};
