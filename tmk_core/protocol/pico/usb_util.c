
#include "usb_util.h"

#include "tusb.h"

bool usb_connected_state(void) {
    tud_task();
    return tud_connected();
}
void usb_disconnect(void) {
#warning "No implementation" //TODO implement
}
