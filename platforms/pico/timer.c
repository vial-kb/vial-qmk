/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "timer.h"
#include "pico/stdlib.h"

/** \brief timer initialization
 *
 * FIXME: needs doc
 */
void timer_init(void) {
}

/** \brief timer read
 *
 * FIXME: needs doc
 */
inline uint16_t timer_read(void) {

    return (to_ms_since_boot(get_absolute_time()) & 0xFFFF);
}

/** \brief timer read32
 *
 * FIXME: needs doc
 */
inline uint32_t timer_read32(void) {
    return (to_ms_since_boot(get_absolute_time()) & 0xFFFFFFFF);
}

/** \brief timer elapsed
 *
 * FIXME: needs doc
 */
inline uint16_t timer_elapsed(uint16_t last) {
    uint32_t t;

    t = timer_read32();

    return TIMER_DIFF_16((t & 0xFFFF), last);
}

/** \brief timer elapsed32
 *
 * FIXME: needs doc
 */
inline uint32_t timer_elapsed32(uint32_t last) {
    uint32_t t;

    t = timer_read32();

    return TIMER_DIFF_32(t, last);
}
