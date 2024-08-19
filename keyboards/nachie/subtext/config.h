/*
Copyright 2024 nachie

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef OLED_ENABLE
/* Oled config */
#define OLED_DISPLAY_ADDRESS 0x3C
#define I2C1_SCL_PIN B6
#define I2C1_SDA_PIN B7
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1

#define OLED_TIMEOUT 60000       // Turns off the OLED screen after x ms of keyboard inactivity. Helps reduce OLED Burn-in. Set to 0 to disable.
#define OLED_BRIGHTNESS 50       // The default brightness level of the OLED, from 0 to 255.
#define OLED_UPDATE_INTERVAL 16  // limits in milliseconds how frequently the OLED updates. Calculation 1000/fps (increases keyboard responsiveness)

#endif

/* I2c Timings at 48mhz - Fast mode 400KHz */
// #define I2C1_TIMINGR_PRESC 2U
// #define I2C1_TIMINGR_SCLDEL 1U
// #define I2C1_TIMINGR_SDADEL 0U
// #define I2C1_TIMINGR_SCLH 9U
// #define I2C1_TIMINGR_SCLL 26U

/* I2c Timings at 48mhz - Fast mode plus 1MHz */
#define I2C1_TIMINGR_PRESC 0x00U
#define I2C1_TIMINGR_SCLDEL 0x03U
#define I2C1_TIMINGR_SDADEL 0x01U
#define I2C1_TIMINGR_SCLH 0x03U
#define I2C1_TIMINGR_SCLL 0x09U
