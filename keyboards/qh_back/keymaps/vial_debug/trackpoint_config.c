/* Copyright 2022 durken (https://github.com/durken1/)
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
#if (defined(TRACKPOINT_TAP_ENABLE)) || (defined(TRACKPOINT_AUTO_MOUSE_ENABLE))

#include QMK_KEYBOARD_H
#include "report.h"
#include "print.h"

#ifdef TRACKPOINT_TAP_ENABLE 
#   include "trackpoint_tap.c"
#endif
#ifdef TRACKPOINT_AUTO_MOUSE_ENABLE 
#   include "trackpoint_auto_mouse.c"
#endif
void ps2_mouse_init_user(void) {
    #ifdef TRACKPOINT_TAP_ENABLE 
        set_trackpoint_tap_enable(true);
    #endif
    #ifdef TRACKPOINT_AUTO_MOUSE_ENABLE 
        set_trackpoint_auto_mouse_enable(true);
    #endif
}

void ps2_mouse_moved_user(report_mouse_t *mouse_report) {
    // uprintf("ps2_mouse_moved_user>>>x:%d, y:%d, v:%d, h:%d", mouse_report->x, mouse_report->y, mouse_report->v, mouse_report->h);
    #ifdef TRACKPOINT_TAP_ENABLE 
        trackpoint_tap(mouse_report);
    #endif
    #ifdef TRACKPOINT_AUTO_MOUSE_ENABLE 
        trackpoint_auto_mouse(*mouse_report);
    #endif
}

#endif // TRACKPOINT_TAP_ENABLE || TRACKPOINT_AUTO_MOUSE_ENABLE
