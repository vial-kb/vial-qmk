
#pragma once

#include "hardware/pio.h"

int32_t pio_manager_get_empty_sm(PIO pio);
int32_t pio_manager_add_program(PIO pio, uint32_t sm,
                                pio_program_t const* program);
