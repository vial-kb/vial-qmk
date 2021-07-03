/* Copyright 2021 sekigon-gonnoc
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

#include "iusb.h"
#include "raw_hid.h"

#ifdef MIDI_ENABLE
#    include "qmk_midi.h"
#endif
#include "usb_descriptors.h"

#include "device/usbd.h"
#include "hid_device.h"
#include "class/midi/midi_device.h"
#include "device/dcd.h"

uint8_t keyboard_leds(void) {
    return get_keyboard_led_status();
}

void send_keyboard(report_keyboard_t *report) {
    if (tud_suspended()) {
        tud_remote_wakeup();
        busy_wait_ms(15);
        dcd_event_bus_signal(0, DCD_EVENT_RESUME, true);
        return;
    }

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
    if (tud_suspended()) {
        tud_remote_wakeup();
        busy_wait_ms(15);
        dcd_event_bus_signal(0, DCD_EVENT_RESUME, true);
        return;
    }

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

void raw_hid_send(uint8_t *data, uint8_t length) {
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
