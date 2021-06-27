#include "iusb.h"
#include "raw_hid.h"

#ifdef MIDI_ENABLE
#    include "qmk_midi.h"
#endif
#include "usb_descriptors.h"

#include "device/usbd.h"
#include "hid_device.h"
#include "class/midi/midi_device.h"

/* declarations */
uint8_t keyboard_leds(void) {
    // TODO
    return 0;
}

void send_keyboard(report_keyboard_t *report) {
    while (!tud_hid_n_ready(ITF_NUM_HID_KEYBOARD)) {
        tud_task();
        if (!tud_ready()) {
            return;
        }
    }
    tud_hid_n_report(ITF_NUM_HID_KEYBOARD, 0, report, sizeof(*report));
    tud_task();
}

void send_mouse(report_mouse_t *report) {
    while (!tud_hid_n_ready(ITF_NUM_HID_MOUSE)) {
        tud_task();
        if (!tud_ready()) {
            return;
        }
    }
    // Require only 5 bytes. Do not usb report->id
    tud_hid_n_report(ITF_NUM_HID_MOUSE, 0, &report->buttons, 5);
    tud_task();
}

void send_system(uint16_t data) {
    while (!tud_hid_n_ready(ITF_NUM_HID_EXTRA)) {
        tud_task();
        if (!tud_ready()) {
            return;
        }
    }
    tud_hid_n_report(ITF_NUM_HID_EXTRA, REPORT_ID_SYSTEM, &data, 2);
    tud_task();
}

void send_consumer(uint16_t data) {
    while (!tud_hid_n_ready(ITF_NUM_HID_EXTRA)) {
        tud_task();
        if (!tud_ready()) {
            return;
        }
    }
    tud_hid_n_report(ITF_NUM_HID_EXTRA, REPORT_ID_CONSUMER, &data, 2);
    tud_task();
}

void raw_hid_send(uint8_t* data, uint8_t length) {
    while (!tud_hid_n_ready(ITF_NUM_HID_RAW)) {
        tud_task();
        if (!tud_ready()) {
            return;
        }
    }
    tud_hid_n_report(ITF_NUM_HID_RAW, 0, data, length);
    tud_task();
}

#ifdef MIDI_ENABLE
void send_midi_packet(MIDI_EventPacket_t *event) {
    tud_midi_packet_write((uint8_t *)event);
    tud_task();
}

bool recv_midi_packet(MIDI_EventPacket_t *const event) {
    if (tud_midi_available()) {
        tud_midi_packet_read((uint8_t *)event);

        return true;
    } else {
        return false;
    }
}

#endif // MIDI_ENABLE
