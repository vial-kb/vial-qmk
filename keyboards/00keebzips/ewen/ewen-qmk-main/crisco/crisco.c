#include "crisco.h"

void matrix_scan_kb(void) {
#ifdef DEBUG_MATRIX
    for (uint8_t c = 0; c < MATRIX_COLS; c++)
                for (uint8_t r = 0; r < MATRIX_ROWS; r++)
                  if (matrix_is_on(r, c)) xprintf("r:%d c:%d \n", r, c);
#endif

  matrix_scan_user();
}
