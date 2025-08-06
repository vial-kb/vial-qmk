/*
 * `qmk chibios-confmigrate -i firmware/nachie/syndrome/chconf.h -r ../keymaps_qmk/platforms/chibios/boards/GENERIC_PROMICRO_RP2040/configs/chconf.h`
 */


#pragma once

#include_next <chconf.h>

#undef CH_CFG_ST_TIMEDELTA
#define CH_CFG_ST_TIMEDELTA                 100