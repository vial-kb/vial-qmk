/*
 * WARNING: be careful changing this code, it is very timing dependent
 */

#include "quantum.h"
#include "serial.h"
#include "wait.h"

#include "uart_tx.pio.h"
#include "uart_rx.pio.h"
#include "pio_manager.h"

#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/gpio.h"
#include "hardware/sync.h"
#include "hardware/irq.h"
#include <stdio.h>

#ifndef SELECT_SOFT_SERIAL_SPEED
#    define SELECT_SOFT_SERIAL_SPEED 1
// TODO: correct speeds...
#endif

// Serial pulse period in microseconds. At the moment, going lower than 12
// causes communication failure
#if SELECT_SOFT_SERIAL_SPEED == 0
#    define SERIAL_DELAY 16
#    define SERIAL_BAUD 921600
#elif SELECT_SOFT_SERIAL_SPEED == 1
#    define SERIAL_DELAY 16
#    define SERIAL_BAUD 230400
#elif SELECT_SOFT_SERIAL_SPEED == 2
#    define SERIAL_DELAY 24
#    define SERIAL_BAUD 115200
#elif SELECT_SOFT_SERIAL_SPEED == 3
#    define SERIAL_DELAY 32
#    define SERIAL_BAUD 57600
#elif SELECT_SOFT_SERIAL_SPEED == 4
#    define SERIAL_DELAY 48
#    define SERIAL_BAUD 9600
#elif SELECT_SOFT_SERIAL_SPEED == 5
#    define SERIAL_DELAY 64
#    define SERIAL_BAUD 4800
#else
#    error invalid SELECT_SOFT_SERIAL_SPEED value
#endif

inline static void serial_delay(void) { wait_us(SERIAL_DELAY); }
inline static void serial_delay_half(void) { wait_us(SERIAL_DELAY / 2); }
inline static void serial_delay_blip(void) { wait_us(1); }
inline static void serial_output(void) {
    setPinOutput(SOFT_SERIAL_PIN);

    gpio_set_slew_rate(SOFT_SERIAL_PIN, GPIO_SLEW_RATE_FAST);
    gpio_set_drive_strength(SOFT_SERIAL_PIN, GPIO_DRIVE_STRENGTH_12MA);
}
inline static void serial_input(void) { setPinInputHigh(SOFT_SERIAL_PIN); }
inline static bool serial_read_pin(void) { return readPin(SOFT_SERIAL_PIN); }
inline static void serial_low(void) { writePinLow(SOFT_SERIAL_PIN); }
inline static void serial_high(void) { writePinHigh(SOFT_SERIAL_PIN); }

void interrupt_handler(uint gpio, uint32_t events);

static PIO  pio = pio0;
static uint sm_tx, sm_rx;

inline static void soft_serial_disable_rx(void) {
    pio_sm_set_enabled(pio, sm_rx, false);
    pio_sm_restart(pio, sm_rx);
}

inline static void soft_serial_enable_rx(void) {
    setPinInputHigh(SOFT_SERIAL_PIN);
    // pio_gpio_init is not needed
    pio_sm_clear_fifos(pio, sm_rx);
    pio_sm_set_enabled(pio, sm_rx, true);
}

inline static void soft_serial_disable_tx(void) {
    pio_sm_set_enabled(pio, sm_tx, false);
    pio_sm_restart(pio, sm_tx);
}

static void soft_serial_enable_tx(void) {
    writePinHigh(SOFT_SERIAL_PIN);
    setPinOutput(SOFT_SERIAL_PIN);
    gpio_set_slew_rate(SOFT_SERIAL_PIN, GPIO_SLEW_RATE_FAST);
    gpio_set_drive_strength(SOFT_SERIAL_PIN, GPIO_DRIVE_STRENGTH_12MA);
    pio_sm_clear_fifos(pio, sm_tx);
    pio_gpio_init(pio, SOFT_SERIAL_PIN);
    pio_sm_set_enabled(pio, sm_tx, true);
}

inline static int soft_serial_pio_init(void) {
    sm_rx = pio_manager_get_empty_sm(pio);

    if (sm_rx < 0) return -1;

    int32_t offset = pio_manager_add_program(pio, sm_rx, &uart_rx_mini_program);

    if (offset < 0) return -1;

    uart_rx_mini_program_init(pio, sm_rx, offset, SOFT_SERIAL_PIN, SERIAL_BAUD);
    soft_serial_disable_rx();

    sm_tx = pio_manager_get_empty_sm(pio);

    if (sm_tx < 0) return -1;

    offset = pio_manager_add_program(pio, sm_tx, &uart_tx_program);

    if (offset < 0) return -1;

    writePinHigh(SOFT_SERIAL_PIN);
    uart_tx_program_init(pio, sm_tx, offset, SOFT_SERIAL_PIN, SERIAL_BAUD);
    soft_serial_disable_tx();

    return 0;
}

// Initialize master
void soft_serial_initiator_init(void) {
    soft_serial_pio_init();

    serial_output();
    serial_high();
}

// Initialize slave
void soft_serial_target_init(void) {
    soft_serial_pio_init();

    setPinInputHigh(SOFT_SERIAL_PIN);
    gpio_set_irq_enabled_with_callback(SOFT_SERIAL_PIN, GPIO_IRQ_EDGE_FALL,
                                       true, interrupt_handler);
    irq_set_priority(IO_IRQ_BANK0, PICO_HIGHEST_IRQ_PRIORITY);
}

// Used by the master to synchronize timing with the slave.
static int __attribute__((noinline)) sync_recv(void) {
    serial_input();

    volatile uint64_t timeout = time_us_64() + 10000;
    while (!serial_read_pin() && time_us_64() < timeout) {
        // tight_loop_contents();
    }
    if (time_us_64() >= timeout) {
        // dprintf("serial::NO_RESPONSE0\n");
        return -1;
    }

    timeout = time_us_64() + 10000;
    while (serial_read_pin() && time_us_64() < timeout) {
        // tight_loop_contents();
    }

    if (time_us_64() >= timeout) {
        // dprintf("serial::NO_RESPONSE1\n");
        return -1;
    }

    timeout = time_us_64() + 10000;
    while (!serial_read_pin() && time_us_64() < timeout) {
        // tight_loop_contents();
    }

    if (time_us_64() >= timeout) {
        // dprintf("serial::NO_RESPONSE2\n");
        return -2;
    }

    return 0;
}

// Used by the slave to send a synchronization signal to the master.
static void __attribute__((noinline)) sync_send(void) {
    serial_output();

    serial_low();
    serial_delay();

    serial_high();
    while (!serial_read_pin()) {
        continue;
    }
}

// Reads a byte from the serial line
static uint16_t __attribute__((noinline)) serial_read_byte(void) {
    uint64_t timeout = time_us_64() + 10000;
    while (pio_sm_is_rx_fifo_empty(pio, sm_rx) && (time_us_64() < timeout)) {
        tight_loop_contents();
    }

    if (time_us_64() >= timeout) {
        // dprintf("serial: pio_rx timeout\n");
        return 0xffff;
    } else {
        return uart_rx_program_getc(pio, sm_rx);
    }
}

// Sends a byte with MSB ordering
static void __attribute__((noinline)) serial_write_byte(uint8_t data) {
    uart_tx_program_putc(pio, sm_tx, data);
}

static void serial_wait_send_complete(void) {
    while (pio_sm_get_tx_fifo_level(pio, sm_tx) != 0) {
        continue;
    }
    wait_us(1000000 * 12 / (SERIAL_BAUD));
}

// interrupt handle to be used by the slave device
void interrupt_handler(uint gpio, uint32_t events) {
    if (gpio != SOFT_SERIAL_PIN || events != GPIO_IRQ_EDGE_FALL) {
        return;
    }

    uint32_t interrupt_status = save_and_disable_interrupts();

    gpio_set_irq_enabled_with_callback(SOFT_SERIAL_PIN, GPIO_IRQ_EDGE_FALL,
                                       false, interrupt_handler);

    while (!serial_read_pin()) {
        continue;
    }
    serial_delay_blip();

    sync_send();

    uint8_t checksum_computed = 0;
    int     sstd_index        = 0;
    int     receive_res       = 0;
    uint8_t checksum_received = 0xff;

    split_transaction_desc_t *trans;

    serial_input();
    while (!serial_read_pin()) {
        continue;
    }

    // activate receive
    soft_serial_enable_rx();

    do {
        sstd_index = serial_read_byte();
        if (sstd_index > NUM_TOTAL_TRANSACTIONS) {
            printf("invalid sstd_index:%d\n", sstd_index);
            receive_res = -1;
            break;
        }

        soft_serial_disable_rx();

        serial_delay();
        sync_send();

        soft_serial_enable_rx();

        trans = &split_transaction_table[sstd_index];
        for (int i = 0; i < trans->initiator2target_buffer_size; ++i) {
            split_trans_initiator2target_buffer(trans)[i] = serial_read_byte();
            checksum_computed += split_trans_initiator2target_buffer(trans)[i];
        }
        checksum_computed ^= 7;
        checksum_received = serial_read_byte();
    } while (0);

    soft_serial_disable_rx();

    if (receive_res < 0) {
        // receive timeout error
        serial_input();
        gpio_set_irq_enabled_with_callback(SOFT_SERIAL_PIN, GPIO_IRQ_EDGE_FALL,
                                           true, interrupt_handler);
        restore_interrupts(interrupt_status);

        return;
    }

    serial_delay();
    sync_send();

    soft_serial_enable_tx();

    // wait for the sync to finish sending
    serial_delay();

    // Allow any slave processing to occur
    if (trans->slave_callback) {
        trans->slave_callback(trans->initiator2target_buffer_size,
                              split_trans_initiator2target_buffer(trans),
                              trans->target2initiator_buffer_size,
                              split_trans_target2initiator_buffer(trans));
    }

    uint8_t checksum = 0;
    for (int i = 0; i < trans->target2initiator_buffer_size; ++i) {
        uint8_t b = split_trans_target2initiator_buffer(trans)[i];
        serial_write_byte(b);
        checksum += b;
    }
    serial_write_byte(checksum ^ 7);
    serial_wait_send_complete();


    *trans->status = (checksum_computed == checksum_received)
                         ? TRANSACTION_ACCEPTED
                         : TRANSACTION_DATA_ERROR;


    // end transaction
    serial_input();

    //
    gpio_set_irq_enabled_with_callback(SOFT_SERIAL_PIN, GPIO_IRQ_EDGE_FALL,
                                       true, interrupt_handler);

    restore_interrupts(interrupt_status);
}

/////////
//  start transaction by initiator
//
// int  soft_serial_transaction(int sstd_index)
//
// Returns:
//    TRANSACTION_END
//    TRANSACTION_NO_RESPONSE
//    TRANSACTION_DATA_ERROR
// this code is very time dependent, so we need to disable interrupts
int soft_serial_transaction(int sstd_index) {
    if (sstd_index > NUM_TOTAL_TRANSACTIONS) return TRANSACTION_TYPE_ERROR;
    split_transaction_desc_t *trans = &split_transaction_table[sstd_index];
    if (!trans->status) return TRANSACTION_TYPE_ERROR;  // not registered

    // TODO: remove extra delay between transactions
    serial_delay();

    // this code is very time dependent, so we need to disable interrupts
    uint32_t interrupt_status = save_and_disable_interrupts();

    // signal to the slave that we want to start a transaction
    serial_output();
    serial_low();
    serial_delay_blip();
    serial_high();

    // wait for the slaves response
    if (sync_recv() != 0) {
        // dprintf("NACK 1\n");
        restore_interrupts(interrupt_status);
        return TRANSACTION_NO_RESPONSE;
    }

    // if the slave is present syncronize with it
    soft_serial_enable_tx();

    uint8_t checksum = 0;
    // send data to the slave
    serial_write_byte(sstd_index);  // first chunk is transaction id
    serial_wait_send_complete();

    soft_serial_disable_tx();

    if (sync_recv() != 0) {
        // dprintf("NACK 1.5\n");
        restore_interrupts(interrupt_status);
        return TRANSACTION_NO_RESPONSE;
    }

    soft_serial_enable_tx();
    serial_delay();

    for (int i = 0; i < trans->initiator2target_buffer_size; ++i) {
        serial_write_byte(split_trans_initiator2target_buffer(trans)[i]);
        checksum += split_trans_initiator2target_buffer(trans)[i];
    }
    serial_write_byte(checksum ^ 7);

    serial_wait_send_complete();

    soft_serial_disable_tx();

    if (sync_recv() != 0) {
        // dprintf("NACK 2\n");
        restore_interrupts(interrupt_status);
        return TRANSACTION_NO_RESPONSE;
    }

    soft_serial_enable_rx();

    // receive data from the slave
    uint8_t checksum_computed = 0;
    uint8_t receive_bytes = trans->target2initiator_buffer_size;
    for (int i = 0; i < receive_bytes; ++i) {
        split_trans_target2initiator_buffer(trans)[i] = serial_read_byte();
        checksum_computed += split_trans_target2initiator_buffer(trans)[i];
    }
    checksum_computed ^= 7;
    uint8_t checksum_received = serial_read_byte();

    soft_serial_disable_rx();

    if ((checksum_computed) != (checksum_received)) {
        dprintf("serial::FAIL[%u,%u,%u]\n", checksum_computed,
                checksum_received, sstd_index);
        serial_output();
        serial_high();

        restore_interrupts(interrupt_status);
        return TRANSACTION_DATA_ERROR;
    }

    // always, release the line when not in use
    serial_high();
    serial_output();

    restore_interrupts(interrupt_status);
    return TRANSACTION_END;
}
