#pragma once

/* Unlock combo: hold Esc + Enter */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 2 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 13 }

#define VIAL_KEYBOARD_UID {0xC8, 0x22, 0xE8, 0x9B, 0x3E, 0x99, 0x79, 0x9E}

/* Trim heavier RGB effects to leave flash headroom */
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
