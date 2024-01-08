#pragma once

#include QMK_KEYBOARD_H
#include <string.h>

#include "report.h"
#include "print.h"

/* check settings and set defaults */
#ifndef TRACKPOINT_TAP_ENABLE
#    error "TRACKPOINT_TAP_ENABLE not defined! check config settings"
#endif

#ifndef TRACKPOINT_TAPPING_TERM
#        include "action.h"
#        include "action_tapping.h"
#        define TRACKPOINT_TAPPING_TERM GET_TAPPING_TERM(KC_BTN1, &(keyrecord_t){})
#endif
#ifndef TRACKPOINT_TOUCH_DEBOUNCE
#        define TRACKPOINT_TOUCH_DEBOUNCE (TRACKPOINT_TAPPING_TERM * 8)
#endif
#ifndef TRACKPOINT_MAX_TAP_OFFSET
#    define TRACKPOINT_MAX_TAP_OFFSET 5
#endif
#ifndef TRACKPOINT_MIN_DELTA
#    define TRACKPOINT_MIN_DELTA 100
#endif

/* track_point structure */
typedef struct {
    struct {
        //// tap
        bool     is_enabled;
        uint8_t  max_offset;
    } config;
    struct {
        uint16_t active;
    } timer;
    struct {
        /* track_point是否被触发 */
        bool   touch_down;
        uint16_t touch_status_diff_times;
        bool td;
        uint16_t ldt;
        uint16_t total_delta;
    } status;
} trackpoint_tap_context_t;

typedef enum {
    TRACKPOINT_BUTTON1,
    TRACKPOINT_BUTTON2,
    TRACKPOINT_BUTTON3,
} trackpoint_buttons_t;


/* ----------Set up and control------------------------------------------------------------------------------ */
void    set_trackpoint_tap_enable(bool enable);                       // enable/disable auto mouse feature

/* ----------For custom pointing device activation----------------------------------------------------------- */
/**
 * 判断是否按下
*/
bool    trackpoint_touch_down(report_mouse_t mouse_report); // handles pointing device trigger conditions for target layer activation (overwritable)

/* ----------Core functions (only used in custom pointing devices or key processing)------------------------- */
void    trackpoint_tap(report_mouse_t *mouse_report); // add to pointing_device_task_*
