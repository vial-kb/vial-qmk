#include "remote.h"
#include <string.h>
#include "quantum.h"
#include "raw_hid.h"

void remote_handle_cmd(uint8_t *data, uint8_t length) {
    switch (data[1]) {
        case 0x01:{
            // move to layer
            data[1] = 0xfd;
            layer_move(data[2]);
            break;
        }
        case 0x02:{
            // turn on layer
            data[1] = 0xfd;
            layer_on(data[2]);
            break;
        }
        case 0x03:{
            // turn off layer
            data[1] = 0xfd;
            layer_off(data[2]);
            break;
        }
    }
    raw_hid_send(data, length);
}