
#include "quantum.h"
#include "i2c_master.h"
#undef i2c_init
#include <string.h>

#include "pico/binary_info.h"
#include "hardware/i2c.h"

static uint8_t i2c_address;

static i2c_status_t pico_status_to_qmk(int res) {
    if (res == PICO_ERROR_GENERIC) {
        return I2C_STATUS_ERROR;
    } else if (res == PICO_ERROR_TIMEOUT) {
        return I2C_STATUS_TIMEOUT;
    } else {
        return I2C_STATUS_SUCCESS;
    }
}

void i2c_init_pico(void) {
    static bool is_initialised = false;
    if (!is_initialised) {
        is_initialised = true;

        i2c_init(I2C_DRIVER, 50 * 1000);
        gpio_set_function(I2C1_SCL, GPIO_FUNC_I2C);
        gpio_set_function(I2C1_SDA, GPIO_FUNC_I2C);
        gpio_pull_up(I2C1_SCL);
        gpio_pull_up(I2C1_SDA);
        // Make the I2C pins available to picotool
        bi_decl(bi_2pins_with_func(I2C1_SDA, I2C1_SCL, GPIO_FUNC_I2C));
    }
}

i2c_status_t i2c_start(uint8_t address) {
    i2c_address = address;
    return I2C_STATUS_SUCCESS;
}

i2c_status_t i2c_transmit(uint8_t address, const uint8_t* data, uint16_t length,
                          uint16_t timeout) {
    i2c_address = address;

    int res = i2c_write_timeout_us(I2C_DRIVER, i2c_address >> 1, data, length,
                                   true, timeout * 1000);

    return pico_status_to_qmk(res);
}

i2c_status_t i2c_receive(uint8_t address, uint8_t* data, uint16_t length,
                         uint16_t timeout) {
    i2c_address = address;

    int res = i2c_read_timeout_us(I2C_DRIVER, i2c_address >> 1, data, length,
                                  true, timeout * 1000);

    return pico_status_to_qmk(res);
}

i2c_status_t i2c_writeReg(uint8_t devaddr, uint8_t regaddr, const uint8_t* data,
                          uint16_t length, uint16_t timeout) {
    i2c_address = devaddr;

    uint8_t complete_packet[length + 1];
    for (uint8_t i = 0; i < length; i++) {
        complete_packet[i + 1] = data[i];
    }
    complete_packet[0] = regaddr;

    int res =
        i2c_write_timeout_us(I2C_DRIVER, (i2c_address >> 1), complete_packet,
                             length + 1, true, timeout * 1000);

    return pico_status_to_qmk(res);
}

i2c_status_t i2c_readReg(uint8_t devaddr, uint8_t regaddr, uint8_t* data,
                         uint16_t length, uint16_t timeout) {
    i2c_address = devaddr;
    i2c_write_timeout_us(I2C_DRIVER, (i2c_address >> 1), &regaddr, 1, true,
                         timeout * 1000);

    int res = i2c_read_timeout_us(I2C_DRIVER, i2c_address >> 1, data, length,
                                  true, timeout * 1000);

    return pico_status_to_qmk(res);
}

void i2c_stop(void) {
    // Abort
    I2C_DRIVER->hw->enable |= (1 << 1);
    I2C_DRIVER->restart_on_next = false;
    while (I2C_DRIVER->hw->enable & (1 << 1)) {
        continue;
    }
    // clear abort bit
    I2C_DRIVER->hw->clr_tx_abrt;
}
