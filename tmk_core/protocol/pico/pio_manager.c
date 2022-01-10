/* Copyright 2021 sekigon-gonnoc
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
