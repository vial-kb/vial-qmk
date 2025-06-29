// Copyright 2022 aki27 (@aki27kbd)
// SPDX-License-Identifier: GPL-2.0-or-later

/* Trackball */

#ifdef POINTING_DEVICE_ENABLE
 
#    undef RP_pSPI_USE_SPI0
#    define RP_SPI_USE_SPI0 TRUE
#    undef RP_SPI_USE_SPI1
#    define RP_SPI_USE_SPI1 FALSE
#    define SPI_DRIVER SPID0

#    define SPI_SCK_PIN GP18
#    define SPI_MISO_PIN GP16
#    define SPI_MOSI_PIN GP19

#endif

#ifndef PMW33XX_CS_PIN
#    define PMW33XX_CS_PIN GP17
#endif

#define POINTING_DEVICE_ROTATION_180
