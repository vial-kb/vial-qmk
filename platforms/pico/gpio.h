/* Copyright 2021 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#pragma once

#include "pico/stdlib.h"
#include "pin_defs.h"

typedef uint8_t pin_t;

#define setPinInput(pin) (gpio_disable_pulls(pin), gpio_set_dir(pin, GPIO_IN))
#define setPinInputHigh(pin) (gpio_set_dir(pin, GPIO_IN), gpio_pull_up(pin))
#define setPinInputLow(pin) (gpio_init(pin), gpio_set_dir(pin, GPIO_IN), gpio_pull_down(pin))
#define setPinOutput(pin) (gpio_set_dir(pin, GPIO_OUT))

#define writePinHigh(pin) (gpio_put(pin, 1))
#define writePinLow(pin) (gpio_put(pin, 0))
#define writePin(pin, level) ((level) ? writePinHigh(pin) : writePinLow(pin))

#define readPin(pin) (gpio_get(pin))

#define togglePin(pin) (gpio_out(pin, !gpio_get(pin)))
