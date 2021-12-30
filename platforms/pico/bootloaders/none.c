#include "bootloader.h"

#include "pico/stdlib.h"
#include "pico/bootrom.h"

#define FLASH_SIZE (FLASHEND + 1L)

#if !defined(BOOTLOADER_SIZE)
uint16_t bootloader_start;
#endif

__attribute__((weak)) void bootloader_jump(void) {
    reset_usb_boot(0, 0);
}
