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

#include "pico/stdlib.h"
#include "pico/bootrom.h"

#define FLASH_SIZE (FLASHEND + 1L)

#if !defined(BOOTLOADER_SIZE)
uint16_t bootloader_start;
#endif

__attribute__((weak)) void bootloader_jump(void) {
    reset_usb_boot(0, 0);
}
