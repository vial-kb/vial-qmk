/* Copyright 2021 beanaccle
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

#include "v1.h"

/*
 * Board-specific initialization code.
 */
void board_init(void) {
   //JTAG-DP Disabled and SW-DP Enabled
   AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE;
   //Set backup register DR10 to enter bootloader on reset
//    BKP->DR10 = RTC_BOOTLOADER_FLAG;
}
