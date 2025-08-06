#ifdef RGB_MATRIX_ENABLE
// LED index
// 7, 6, 5, 4, 3, 2, 1, 0

led_config_t g_led_config = {
    // Key Matrix to LED Index
    {
         {   0  ,    0  ,    1  ,   2   ,   3   ,   4   ,    5   ,   6   ,   7   ,    7   ,   7     },
         {   0  ,    0  ,    1  ,   2   ,   3   ,   4   ,    5   ,   6   ,   7   ,    7   ,   7     },
         {   0  ,    0  ,    1  ,   2   ,   3   ,   4   ,    5   ,   6   ,   7   ,    7             },
         {   0  ,    0  ,    1  ,           3   ,   4   ,            6   ,   7   ,    7             }
    },
    // LED Index to Physical Positon
    {
        { 0  , 8  },
        { 32, 16 },
        { 64, 24 },
        { 96, 32 },
        { 128 , 40 },
        { 160 , 48 },
        { 192 , 56 },
        { 224 , 64 }
    },
    //  LED Index to Flag
    { 1, 1, 1, 1, 1, 1, 1, 1 }
};

#define RGB_MATRIX_TYPING_HEATMAP_SPREAD 80
#define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 32


#endif