
#include "pio_manager.h"
#include "hardware/pio.h"

int32_t pio_manager_get_empty_sm(PIO pio) {
    check_pio_param(pio);
    for (uint32_t sm = 0; sm < NUM_PIO_STATE_MACHINES; sm++) {
        if (!pio_sm_is_claimed(pio, sm)) return sm;
    }

    return -1;
}

int32_t pio_manager_add_program(PIO pio, uint32_t sm,
                                pio_program_t const* program) {
    check_pio_param(pio);
    check_sm_param(sm);

    if (pio_sm_is_claimed(pio, sm)) {
        return -1;
    }

    if (!pio_can_add_program(pio, program)) {
        return -2;
    }

    pio_sm_claim(pio, sm);

    uint32_t offset = pio_add_program(pio, program);

    return offset;
}
