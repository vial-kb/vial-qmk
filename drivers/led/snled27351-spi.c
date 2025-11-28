/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * SPI variant ported from Keychron wireless branch by Tymon3310
 * Adapted for Vial QMK by d3lilah
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

#include "snled27351-spi.h"
#include "spi_master.h"

#define SNLED27351_PWM_REGISTER_COUNT 192
#define SNLED27351_LED_CONTROL_REGISTER_COUNT 24

#ifndef SNLED27351_PHASE_CHANNEL
#    define SNLED27351_PHASE_CHANNEL SNLED27351_SCAN_PHASE_12_CHANNEL
#endif

#ifndef SNLED27351_CURRENT_TUNE
#    define SNLED27351_CURRENT_TUNE \
        { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
#endif

#define SNLED27351_WRITE (0 << 7)
#define SNLED27351_READ (1 << 7)
#define SNLED27351_PATTERN (2 << 4)

#ifdef DRIVER_CS_PINS
pin_t cs_pins[] = DRIVER_CS_PINS;
#else
error "no DRIVER_CS_PINS defined"
#endif

// These buffers match the snled27351 PWM registers.
// The control buffers match the PG0 LED On/Off registers.
// Storing them like this is optimal for I2C transfers to the registers.
// We could optimize this and take out the unused registers from these
// buffers and the transfers in snled27351_write_pwm_buffer() but it's
// probably not worth the extra complexity.
typedef struct snled27351_driver_t {
    uint8_t pwm_buffer[SNLED27351_PWM_REGISTER_COUNT];
    bool    pwm_buffer_dirty;
    uint8_t led_control_buffer[SNLED27351_LED_CONTROL_REGISTER_COUNT];
    bool    led_control_buffer_dirty;
} PACKED snled27351_driver_t;

snled27351_driver_t driver_buffers[SNLED27351_DRIVER_COUNT] = {{
    .pwm_buffer               = {0},
    .pwm_buffer_dirty         = false,
    .led_control_buffer       = {0},
    .led_control_buffer_dirty = false,
}};

bool snled27351_write(uint8_t index, uint8_t page, uint8_t reg, uint8_t *data, uint8_t len) {
    static uint8_t spi_transfer_buffer[2] = {0};

    if (index > ARRAY_SIZE(((pin_t[])DRIVER_CS_PINS)) - 1) return false;

    if (!spi_start(cs_pins[index], false, 0, SNLED27351_SPI_DIVISOR)) {
        spi_stop();
        return false;
    }

    spi_transfer_buffer[0] = SNLED27351_WRITE | SNLED27351_PATTERN | (page & 0x0F);
    spi_transfer_buffer[1] = reg;

    if (spi_transmit(spi_transfer_buffer, 2) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }

    if (spi_transmit(data, len) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }

    spi_stop();
    return true;
}

bool snled27351_write_register(uint8_t index, uint8_t page, uint8_t reg, uint8_t data) {
    return snled27351_write(index, page, reg, &data, 1);
}

void snled27351_write_pwm_buffer(uint8_t index) {
    snled27351_write(index, SNLED27351_COMMAND_PWM, 0, driver_buffers[index].pwm_buffer, SNLED27351_PWM_REGISTER_COUNT);
}

void snled27351_init_drivers(void) {
#if defined(SNLED27351_SDB_PIN)
    gpio_set_pin_output_push_pull(SNLED27351_SDB_PIN);
    gpio_write_pin_high(SNLED27351_SDB_PIN);
#endif

    spi_init();

    for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++) {
        snled27351_init(i);
    }

    for (int index = 0; index < SNLED27351_LED_COUNT; index++) {
        snled27351_set_led_control_register(index, true, true, true);
    }

    for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++)
        snled27351_update_led_control_registers(i);
}

void snled27351_init(uint8_t index) {
    gpio_set_pin_output_push_pull(cs_pins[index]);
    gpio_write_pin_high(cs_pins[index]);
    // Setting LED driver to shutdown mode
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_SOFTWARE_SHUTDOWN, SNLED27351_SOFTWARE_SHUTDOWN_SSD_SHUTDOWN);
    // Setting internal channel pulldown/pullup
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_PULLDOWNUP, SNLED27351_PULLDOWNUP_ALL_ENABLED);
    // Select number of scan phase
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_SCAN_PHASE, SNLED27351_PHASE_CHANNEL);
    // Setting PWM Delay Phase
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_SLEW_RATE_CONTROL_MODE_1, SNLED27351_SLEW_RATE_CONTROL_MODE_1_PDP_ENABLE);
    // Setting Driving/Sinking Channel Slew Rate
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_SLEW_RATE_CONTROL_MODE_2, SNLED27351_SLEW_RATE_CONTROL_MODE_2_SSL_ENABLE);
    // Setting Iref
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_SOFTWARE_SLEEP, 0);

    // Set LED CONTROL PAGE (Page 0)
    uint8_t on_off_reg[SNLED27351_LED_CONTROL_ON_OFF_LENGTH] = {0};
    snled27351_write(index, SNLED27351_COMMAND_LED_CONTROL, 0, on_off_reg, SNLED27351_LED_CONTROL_ON_OFF_LENGTH);

    // Set PWM PAGE (Page 1)
    uint8_t pwm_reg[SNLED27351_LED_PWM_LENGTH];
    memset(pwm_reg, 0, SNLED27351_LED_PWM_LENGTH);
    snled27351_write(index, SNLED27351_COMMAND_PWM, 0, pwm_reg, SNLED27351_LED_PWM_LENGTH);

    // Set CURRENT PAGE (Page 4)
    uint8_t current_tune_reg[SNLED27351_LED_CURRENT_TUNE_LENGTH] = SNLED27351_CURRENT_TUNE;
    snled27351_write(index, SNLED27351_COMMAND_CURRENT_TUNE, 0, current_tune_reg, SNLED27351_LED_CURRENT_TUNE_LENGTH);

    //    // Enable LEDs ON/OFF
    //    memset(on_off_reg, 0xFF, SNLED27351_LED_CONTROL_ON_OFF_LENGTH);
    //    snled27351_write(index, SNLED27351_COMMAND_LED_CONTROL, 0, on_off_reg, SNLED27351_LED_CONTROL_ON_OFF_LENGTH);

    // Setting LED driver to normal mode
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_SOFTWARE_SHUTDOWN, SNLED27351_SOFTWARE_SHUTDOWN_SSD_NORMAL);
}

void snled27351_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    snled27351_led_t led;
    if (index >= 0 && index < SNLED27351_LED_COUNT) {
        memcpy_P(&led, (&g_snled27351_leds[index]), sizeof(led));

        if (driver_buffers[led.driver].pwm_buffer[led.r] == red && driver_buffers[led.driver].pwm_buffer[led.g] == green && driver_buffers[led.driver].pwm_buffer[led.b] == blue) {
            return;
        }

        driver_buffers[led.driver].pwm_buffer[led.r] = red;
        driver_buffers[led.driver].pwm_buffer[led.g] = green;
        driver_buffers[led.driver].pwm_buffer[led.b] = blue;
        driver_buffers[led.driver].pwm_buffer_dirty  = true;
    }
}

void snled27351_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < SNLED27351_LED_COUNT; i++) {
        snled27351_set_color(i, red, green, blue);
    }
}

void snled27351_set_led_control_register(uint8_t index, bool red, bool green, bool blue) {
    snled27351_led_t led;
    memcpy_P(&led, (&g_snled27351_leds[index]), sizeof(led));

    uint8_t control_register_r = led.r / 8;
    uint8_t control_register_g = led.g / 8;
    uint8_t control_register_b = led.b / 8;
    uint8_t bit_r              = led.r % 8;
    uint8_t bit_g              = led.g % 8;
    uint8_t bit_b              = led.b % 8;

    if (red) {
        driver_buffers[led.driver].led_control_buffer[control_register_r] |= (1 << bit_r);
    } else {
        driver_buffers[led.driver].led_control_buffer[control_register_r] &= ~(1 << bit_r);
    }
    if (green) {
        driver_buffers[led.driver].led_control_buffer[control_register_g] |= (1 << bit_g);
    } else {
        driver_buffers[led.driver].led_control_buffer[control_register_g] &= ~(1 << bit_g);
    }
    if (blue) {
        driver_buffers[led.driver].led_control_buffer[control_register_b] |= (1 << bit_b);
    } else {
        driver_buffers[led.driver].led_control_buffer[control_register_b] &= ~(1 << bit_b);
    }

    driver_buffers[led.driver].led_control_buffer_dirty = true;
}

float snled27351_get_load_ratio(void) {
    uint32_t totalBuf = 0;
     for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++)
        for (uint8_t j = 0; j < SNLED27351_PWM_REGISTER_COUNT; j++)
            totalBuf += driver_buffers[i].pwm_buffer[j];

    return (float)totalBuf/(0xFF * 3 * SNLED27351_LED_COUNT);
}

void snled27351_update_pwm_buffers(uint8_t index) {
    if (driver_buffers[index].pwm_buffer_dirty) {
        snled27351_write_pwm_buffer(index);
        driver_buffers[index].pwm_buffer_dirty = false;
    }
}

void snled27351_update_led_control_registers(uint8_t index) {
    if (driver_buffers[index].led_control_buffer_dirty) {
        snled27351_write(index, SNLED27351_COMMAND_LED_CONTROL, 0, driver_buffers[index].led_control_buffer, SNLED27351_LED_CONTROL_REGISTER_COUNT);
        driver_buffers[index].led_control_buffer_dirty = false;
    }
}

void snled27351_flush(void) {
    for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++) {
        snled27351_update_pwm_buffers(i);
    }
}

void snled27351_shutdown(void) {
#if defined(SNLED27351_SDB_PIN)
    gpio_write_pin_low(SNLED27351_SDB_PIN);
#else
    for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++)
        snled27351_sw_shutdown(i);
#endif
}

void snled27351_exit_shutdown(void) {
#if defined(SNLED27351_SDB_PIN)
    gpio_write_pin_high(SNLED27351_SDB_PIN);
#else
    for (uint8_t i = 0; i < SNLED27351_DRIVER_COUNT; i++)
        snled27351_sw_return_normal(i);
#endif
}

void snled27351_sw_return_normal(uint8_t index) {
    // Setting LED driver to normal mode
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_SOFTWARE_SHUTDOWN, SNLED27351_SOFTWARE_SHUTDOWN_SSD_NORMAL);
}

void snled27351_sw_shutdown(uint8_t index) {
    // Setting LED driver to shutdown mode
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_SOFTWARE_SHUTDOWN, SNLED27351_SOFTWARE_SHUTDOWN_SSD_SHUTDOWN);
    // Write SW Sleep Register
    snled27351_write_register(index, SNLED27351_COMMAND_FUNCTION, SNLED27351_FUNCTION_REG_SOFTWARE_SLEEP, SNLED27351_SOFTWARE_SLEEP_ENABLE);
}
