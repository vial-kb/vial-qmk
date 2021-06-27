
#include <string.h>
#include <stdio.h>

// qmk
#include "eeprom.h"
#include "eeconfig.h"
#include "timer.h"
#include "debug.h"
#include "print.h"

#include "pico_eeprom.h"

// pico
#include "pico/stdlib.h"
#include "hardware/flash.h"
#include "hardware/sync.h"

#ifndef DYNAMIC_KEYMAP_EEPROM_ADDR
#    ifdef VIA_EEPROM_CUSTOM_CONFIG_ADDR
#        define DYNAMIC_KEYMAP_EEPROM_ADDR \
            (VIA_EEPROM_CUSTOM_CONFIG_ADDR + VIA_EEPROM_CUSTOM_CONFIG_SIZE)
#    else
#        define DYNAMIC_KEYMAP_EEPROM_ADDR (EECONFIG_SIZE + 1)
#    endif
#endif

#ifndef EEPEMU_EECONFIG_SIZE
#    define EEPEMU_EECONFIG_SIZE 1024
#endif
_Static_assert(EEPEMU_EECONFIG_SIZE > EECONFIG_SIZE,
               "EEPEMU_EECONFIG Region is too small");

#ifndef EEPEMU_KEYMAP_SIZE
#    define EEPEMU_KEYMAP_SIZE 4096
#endif
_Static_assert(EEPEMU_KEYMAP_SIZE > DYNAMIC_KEYMAP_EEPROM_MAX_ADDR,
               "EEPEMU_KEYMAP Region is too small");

#define ALIGNED_REGION(size, align) ((size + align - 1) / align * align)

#ifndef EEPEMU_KEYMAP_START_OFFSET
#    define EEPEMU_KEYMAP_START_OFFSET \
        (PICO_FLASH_SIZE_BYTES -       \
         ALIGNED_REGION(EEPEMU_KEYMAP_SIZE, FLASH_SECTOR_SIZE))
#endif

#ifndef EEPEMU_EECONFIG_START_OFFSET
#    define EEPEMU_EECONFIG_START_OFFSET \
        (EEPEMU_KEYMAP_START_OFFSET -    \
         ALIGNED_REGION(EEPEMU_EECONFIG_SIZE, FLASH_SECTOR_SIZE))
#endif

#ifndef EEPEMU_LAZY_WRITEBACK_TIMEOUT
#    define EEPEMU_LAZY_WRITEBACK_TIMEOUT \
        30000  // write back to ROM if 30s elapsed.
#endif

_Static_assert(EEPEMU_EECONFIG_START_OFFSET % FLASH_SECTOR_SIZE == 0,
               "Offset should be aligned to FLASH_SCTOR_SIZE");
_Static_assert(EEPEMU_KEYMAP_START_OFFSET % FLASH_SECTOR_SIZE == 0,
               "Offset should be aligned to FLASH_SCTOR_SIZE");

static uint8_t eepemu_eeconfig[EEPEMU_EECONFIG_SIZE];      // 1kB
static uint8_t eepemu_dynamic_keymap[EEPEMU_KEYMAP_SIZE];  // 4kB
static int32_t eeconfig_last_edit;
static int32_t dynamic_keymap_last_edit;

// Load ROM data to RAM
void pico_eepemu_init(void) {
    memcpy(eepemu_eeconfig, (void *)XIP_BASE + EEPEMU_EECONFIG_START_OFFSET,
           sizeof(eepemu_eeconfig));
    memcpy(eepemu_dynamic_keymap, (void *)XIP_BASE + EEPEMU_KEYMAP_START_OFFSET,
           sizeof(eepemu_dynamic_keymap));

    eeconfig_last_edit       = -1;
    dynamic_keymap_last_edit = -1;
}

void pico_eepemu_lazy_write_back(void) {
    if (eeconfig_last_edit >= 0) {
        if (timer_elapsed(eeconfig_last_edit) >=
            EEPEMU_LAZY_WRITEBACK_TIMEOUT) {
            printf("eeconfig is written to ROM\n");
            pico_eepemu_flash_eeconfig();
        }
    }

    if (dynamic_keymap_last_edit >= 0) {
        if (timer_elapsed(dynamic_keymap_last_edit) >=
            EEPEMU_LAZY_WRITEBACK_TIMEOUT) {
            printf("Dynamic keymap is written to ROM\n");
            pico_eepemu_flash_dynamic_keymap();
        }
    }
}

void pico_eepemu_flash_eeconfig(void) {
    int32_t status = save_and_disable_interrupts();

    flash_range_erase(EEPEMU_EECONFIG_START_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(EEPEMU_EECONFIG_START_OFFSET, eepemu_eeconfig,
                        sizeof(eepemu_eeconfig));
    eeconfig_last_edit = -1;

    restore_interrupts(status);
}

void pico_eepemu_flash_dynamic_keymap(void) {
    int32_t status = save_and_disable_interrupts();

    flash_range_erase(EEPEMU_KEYMAP_START_OFFSET, FLASH_SECTOR_SIZE);
    flash_range_program(EEPEMU_KEYMAP_START_OFFSET, eepemu_dynamic_keymap,
                        sizeof(eepemu_dynamic_keymap));
    dynamic_keymap_last_edit = -1;

    restore_interrupts(status);
}

static inline bool is_eeconfig_addr(const void *eeaddr) {
    if ((uint32_t)eeaddr < DYNAMIC_KEYMAP_EEPROM_ADDR) {
        return true;
    } else {
        return false;
    }
}

static void *convert_address(const void *addr) {
    // TODO Assert address
    if (is_eeconfig_addr(addr)) {
        return (void *)(eepemu_eeconfig + (uint32_t)addr);
    } else {
        return (void *)(eepemu_dynamic_keymap + (uint32_t)addr -
                        DYNAMIC_KEYMAP_EEPROM_ADDR);
    }
}

uint8_t eeprom_read_byte(const uint8_t *__p) {
    uint8_t *addr = convert_address(__p);
    if (addr == NULL) {
        return 0xff;
    }

    return *addr;
}

uint16_t eeprom_read_word(const uint16_t *__p) {
    uint16_t *addr = convert_address(__p);
    if (addr == NULL) {
        return 0xffff;
    }

    if ((uint32_t)addr % 2 == 0) {
        return *addr;
    } else {
        uint16_t ret;
        memcpy(&ret, addr, sizeof(ret));
        return ret;
    }
}

uint32_t eeprom_read_dword(const uint32_t *__p) {
    uint32_t *addr = convert_address(__p);
    if (addr == NULL) {
        return 0xffffffff;
    }

    if ((uint32_t)addr % 4 == 0) {
        return *addr;
    } else {
        uint32_t ret;
        memcpy(&ret, addr, sizeof(ret));
        return ret;
    }
}

void eeprom_read_block(void *__dst, const void *__src, size_t __n) {
    uint32_t *addr = convert_address(__src);
    if (addr == NULL) {
        return;
    }

    memcpy(__dst, addr, __n);
}

static void update_last_edit_time(const void *eeaddr) {
    if (is_eeconfig_addr(eeaddr)) {
        eeconfig_last_edit = timer_read();
    } else {
        dynamic_keymap_last_edit = timer_read();
    }
}

void eeprom_write_byte(uint8_t *__p, uint8_t __value) {
    uint8_t *addr = convert_address(__p);
    if (addr == NULL) {
        return;
    }

    *addr = __value;

    update_last_edit_time(__p);
}

void eeprom_write_word(uint16_t *__p, uint16_t __value) {
    uint16_t *addr = convert_address(__p);
    if (addr == NULL) {
        return;
    }

    if ((uint32_t)addr % 2 == 0) {
        *addr = __value;
    } else {
        memcpy(addr, &__value, sizeof(__value));
    }

    update_last_edit_time(__p);
}
void eeprom_write_dword(uint32_t *__p, uint32_t __value) {
    uint32_t *addr = convert_address(__p);
    if (addr == NULL) {
        return;
    }

    if ((uint32_t)addr % 4 == 0) {
        *addr = __value;
    } else {
        memcpy(addr, &__value, sizeof(__value));
    }

    update_last_edit_time(__p);
}

void eeprom_write_block(const void *__src, void *__dst, size_t __n) {
    uint32_t *addr = convert_address(__dst);
    if (addr == NULL) {
        return;
    }

    memcpy(addr, __src, __n);

    update_last_edit_time(__dst);
}

void eeprom_update_byte(uint8_t *__p, uint8_t __value) {
    if (eeprom_read_byte(__p) != __value) {
        eeprom_write_byte(__p, __value);
    }
}

void eeprom_update_word(uint16_t *__p, uint16_t __value) {
    if (eeprom_read_word(__p) != __value) {
        eeprom_write_word(__p, __value);
    }
}

void eeprom_update_dword(uint32_t *__p, uint32_t __value) {
    if (eeprom_read_dword(__p) != __value) {
        eeprom_write_dword(__p, __value);
    }
}

void eeprom_update_block(const void *__src, void *__dst, size_t __n) {
    uint32_t *addr = convert_address(__dst);
    if (addr == NULL) {
        return;
    }

    if (memcmp(__src, addr, __n) != 0) {
        eeprom_write_block(__src, __dst, __n);
    }
}
