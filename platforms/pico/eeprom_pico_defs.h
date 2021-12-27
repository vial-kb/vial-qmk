
#pragma once

#include "hardware/flash.h"
#include "hardware/structs/ssi.h"

#define FEE_PAGE_SIZE FLASH_SECTOR_SIZE
#define FEE_PAGE_COUNT 2
#define FEE_MCU_FLASH_SIZE (PICO_FLASH_SIZE_BYTES / 1024)
#define FEE_PAGE_BASE_ADDRESS \
    (PICO_FLASH_SIZE_BYTES - FEE_PAGE_SIZE * FEE_PAGE_COUNT)

