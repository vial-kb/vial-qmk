#ifdef RGB_MATRIX_ENABLE
// LED index
// 9    10    2    3
//         1
//         0
//   8 7   6   5 4

led_config_t g_led_config = {
    // Key Matrix to LED Index
    {
         {9,     10,    10,   11,    11, NO_LED,    0,  0,      1,     1,      2 },
         {9,     10,    10,   11,    11, NO_LED,    0,  0,      1,     1,      2 },
         {8,      8,     7,    7,     6,       6,   5,  5,      4,     4,      3 },
         {NO_LED, 7,     7,    6,     6,       6,    5,  4,      4,NO_LED, NO_LED}
    },
    // LED Index to Physical Positon
    {
        { 132, 16 }, // 3
        { 172, 16 }, // 2
        { 216, 16 },  // 1
        { 216, 32 },  // 12
        { 173, 44 }, // 11
        { 132, 44 }, // 10
        {  91, 44 }, // 9
        {  50, 44 },  // 8
        {   8, 32 },   // 7
        {   8, 16 },    // 6
        {  51, 16 },   // 5
        {  91, 16 }   // 4
    },
    //  LED Index to Flag
    //  https://docs.qmk.fm/#/feature_rgb_matrix?id=flags
    { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 }
};


#endif

