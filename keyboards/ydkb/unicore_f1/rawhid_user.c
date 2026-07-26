/*
Copyright 2025 YANG

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

#include "hal.h"
#include "ch.h"
#include "quantum.h"
#include "via.h"


void rprint(char *msg) {
    return;
    //0xfdee
    uint8_t eeee_buf[32] = {0};
    uint8_t msg_len = strlen(msg);
    if (msg_len > 30) msg_len = 30;
    memcpy(&eeee_buf[2], msg, msg_len);
    eeee_buf[0] = 0xFD;
    eeee_buf[1] = 0xEE;
    raw_hid_send(eeee_buf, 32);
}

void raw_hid_receive_kb(uint8_t *data, uint8_t length) {
    return;
}

//after set layout command
void via_set_layout_options_after(void)
{
    //layout 选项里有用来存储配置的。
    user_config_init();
}

