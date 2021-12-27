/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */


#include "flash_pico.h"

#include "pico/bootrom.h"
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "hardware/structs/ssi.h"
#include "hardware/structs/ioqspi.h"

#define BOOT2_SIZE_WORDS 64
#define FLASHCMD_PAGE_PROGRAM 0x02
#define FLASHCMD_READ_STATUS 0x05
#define FLASHCMD_WRITE_ENABLE 0x06

static ssi_hw_t *const ssi = (ssi_hw_t *)XIP_SSI_BASE;

// Sanity check
#undef static_assert
#define static_assert(cond, x) extern int static_assert[(cond) ? 1 : -1]
check_hw_layout(ssi_hw_t, ssienr, SSI_SSIENR_OFFSET);
check_hw_layout(ssi_hw_t, spi_ctrlr0, SSI_SPI_CTRLR0_OFFSET);

static uint32_t boot2_copyout[BOOT2_SIZE_WORDS];
static bool     boot2_copyout_valid = false;

static void __no_inline_not_in_flash_func(flash_init_boot2_copyout)(void) {
    if (boot2_copyout_valid) return;
    for (int i = 0; i < BOOT2_SIZE_WORDS; ++i)
        boot2_copyout[i] = ((uint32_t *)XIP_BASE)[i];
    __compiler_memory_barrier();
    boot2_copyout_valid = true;
}

static void __no_inline_not_in_flash_func(flash_enable_xip_via_boot2)(void) {
    ((void (*)(void))boot2_copyout + 1)();
}

// Bitbanging the chip select using IO overrides, in case RAM-resident IRQs
// are still running, and the FIFO bottoms out. (the bootrom does the same)
static void __no_inline_not_in_flash_func(flash_cs_force)(bool high) {
    uint32_t field_val = high ? IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_VALUE_HIGH
                              : IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_VALUE_LOW;
    hw_write_masked(&ioqspi_hw->io[1].ctrl,
                    field_val << IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_LSB,
                    IO_QSPI_GPIO_QSPI_SS_CTRL_OUTOVER_BITS);
}

// Also allow any unbounded loops to check whether the above abort condition
// was asserted, and terminate early
static int __no_inline_not_in_flash_func(flash_was_aborted)(void) {
    return *(io_rw_32 *)(IO_QSPI_BASE + IO_QSPI_GPIO_QSPI_SD1_CTRL_OFFSET) &
           IO_QSPI_GPIO_QSPI_SD1_CTRL_INOVER_BITS;
}

// Put bytes from one buffer, and get bytes into another buffer.
// These can be the same buffer.
// If tx is NULL then send zeroes.
// If rx is NULL then all read data will be dropped.
//
// If rx_skip is nonzero, this many bytes will first be consumed from the FIFO,
// before reading a further count bytes into *rx.
// E.g. if you have written a command+address just before calling this function.
static void __no_inline_not_in_flash_func(flash_put_get)(const uint8_t *tx,
                                                         uint8_t *      rx,
                                                         size_t         count,
                                                         size_t rx_skip) {
    // Make sure there is never more data in flight than the depth of the RX
    // FIFO. Otherwise, when we are interrupted for long periods, hardware
    // will overflow the RX FIFO.
    const uint max_in_flight = 16 - 2;  // account for data internal to SSI
    size_t     tx_count      = count;
    size_t     rx_count      = count;
    while (tx_count || rx_skip || rx_count) {
        // NB order of reads, for pessimism rather than optimism
        uint32_t tx_level = ssi_hw->txflr;
        uint32_t rx_level = ssi_hw->rxflr;
        bool     did_something =
            false;  // Expect this to be folded into control flow, not register
        if (tx_count && tx_level + rx_level < max_in_flight) {
            ssi->dr0 = (uint32_t)(tx ? *tx++ : 0);
            --tx_count;
            did_something = true;
        }
        if (rx_level) {
            uint8_t rxbyte = ssi->dr0;
            did_something  = true;
            if (rx_skip) {
                --rx_skip;
            } else {
                if (rx) *rx++ = rxbyte;
                --rx_count;
            }
        }
        // APB load costs 4 cycles, so only do it on idle loops (our budget is
        // 48 cyc/byte)
        if (!did_something && __builtin_expect(flash_was_aborted(), 0)) break;
    }
    flash_cs_force(1);
}

// Convenience wrapper for above
// (And it's hard for the debug host to get the tight timing between
// cmd DR0 write and the remaining data)
static void __no_inline_not_in_flash_func(_flash_do_cmd)(uint8_t        cmd,
                                                         const uint8_t *tx,
                                                         uint8_t *      rx,
                                                         size_t         count) {
    flash_cs_force(0);
    ssi->dr0 = cmd;
    flash_put_get(tx, rx, count, 1);
}

// Timing of this one is critical, so do not expose the symbol to debugger etc
static void __no_inline_not_in_flash_func(flash_put_cmd_addr)(uint8_t  cmd,
                                                              uint32_t addr) {
    flash_cs_force(0);
    addr |= cmd << 24;
    for (int i = 0; i < 4; ++i) {
        ssi->dr0 = addr >> 24;
        addr <<= 8;
    }
}

// Poll the flash status register until the busy bit (LSB) clears
static void __no_inline_not_in_flash_func(flash_wait_ready)(void) {
    uint8_t stat;
    do {
        _flash_do_cmd(FLASHCMD_READ_STATUS, NULL, &stat, 1);
    } while (stat & 0x1 && !flash_was_aborted());
}

// Set the WEL bit (needed before any program/erase operation)
static void __no_inline_not_in_flash_func(flash_enable_write)(void) {
    _flash_do_cmd(FLASHCMD_WRITE_ENABLE, NULL, NULL, 0);
}

static void __no_inline_not_in_flash_func(pico_program_half_word)(
    uint32_t flash_offs, uint16_t data) {
    rom_connect_internal_flash_fn connect_internal_flash =
        (rom_connect_internal_flash_fn)rom_func_lookup_inline(
            ROM_FUNC_CONNECT_INTERNAL_FLASH);
    rom_flash_exit_xip_fn flash_exit_xip =
        (rom_flash_exit_xip_fn)rom_func_lookup_inline(ROM_FUNC_FLASH_EXIT_XIP);
    rom_flash_range_program_fn flash_range_program =
        (rom_flash_range_program_fn)rom_func_lookup_inline(
            ROM_FUNC_FLASH_RANGE_PROGRAM);
    rom_flash_flush_cache_fn flash_flush_cache =
        (rom_flash_flush_cache_fn)rom_func_lookup_inline(
            ROM_FUNC_FLASH_FLUSH_CACHE);
    assert(connect_internal_flash && flash_exit_xip && flash_range_program &&
           flash_flush_cache);
    flash_init_boot2_copyout();

    __compiler_memory_barrier();

    connect_internal_flash();
    flash_exit_xip();

    flash_enable_write();
    flash_put_cmd_addr(FLASHCMD_PAGE_PROGRAM, flash_offs);
    flash_put_get((uint8_t *)&data, NULL, 2, 4);
    flash_wait_ready();

    flash_flush_cache();  // Note this is needed to remove CSn IO force as well
                          // as cache flushing
    flash_enable_xip_via_boot2();
}

FLASH_Status FLASH_WaitForLastOperation(uint32_t Timeout) {
    return FLASH_COMPLETE;
}

FLASH_Status FLASH_ErasePage(uint32_t Page_Address) {
    flash_range_erase(Page_Address, FLASH_SECTOR_SIZE);
    return FLASH_COMPLETE;
}

FLASH_Status FLASH_ProgramHalfWord(uint32_t Address, uint16_t Data) {
    pico_program_half_word(Address, Data);
    return FLASH_COMPLETE;
}

__attribute__((weak)) void pico_before_flash_operation(void) {}
__attribute__((weak)) void pico_after_flash_operation(void) {}

static int intr_stat;

void FLASH_Lock(void) {
    restore_interrupts(intr_stat);
    pico_after_flash_operation();
}
void FLASH_Unlock(void) {
    intr_stat = save_and_disable_interrupts();
    pico_before_flash_operation();
}
