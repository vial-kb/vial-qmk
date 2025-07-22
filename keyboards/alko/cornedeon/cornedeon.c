#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    // WS2812 LED strings are addressed from 0 (1st) to RGB_MATRIX_LED_COUNT-1 (last)
    { 0,  1,  2,  3,   4,  5 },
    { 6,  7,  8,  9,  10, 11 },  
    { 12, 13, 14, 15, 16, 17 },
    { 18, 19, 20, 21, 22, 23 }
}, {
    // LED Index to Physical Position
    // **NB**: Reversed order
    {224,64 }, {204,64 }, {184,64 }, {144,64 }, {124,64 }, {104,64 },
    {224,44 }, {204,44 }, {184,44 }, {144,44 }, {124,44 }, {104,44 },
    {224,24 }, {204,24 }, {184,24 }, {144,24 }, {124,24 }, {104,24 },
    {224,0  }, {204,0  }, {184,0  }, {144,0  }, {124,0  }, {104,0 }
}, {
    // LED Index to Flag
    // **NB**: Reversed order
    4, 4, 4, 4, 4, 4,
    1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1,    
    1, 1, 1, 1, 1, 1
} };

#endif  // RGB_MATRIX_ENABLE
