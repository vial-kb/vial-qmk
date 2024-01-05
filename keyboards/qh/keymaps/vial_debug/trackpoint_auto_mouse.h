#pragma once

#include QMK_KEYBOARD_H
#include <string.h>

#include "report.h"
#include "print.h"

/* check settings and set defaults */
#ifndef TRACKPOINT_AUTO_MOUSE_ENABLE
#    error "TRACKPOINT_AUTO_MOUSE_ENABLE not defined! check config settings"
#endif

#ifndef TRACKPOINT_AUTO_MOUSE_DEFAULT_LAYER
#    define TRACKPOINT_AUTO_MOUSE_DEFAULT_LAYER 1
#endif
#ifndef TACKPOINT_AUTO_MOUSE_TIMEOUT
#    define TACKPOINT_AUTO_MOUSE_TIMEOUT 650
#endif
#ifndef TACKPOINT_AUTO_MOUSE_DEBOUNCE
#    define TACKPOINT_AUTO_MOUSE_DEBOUNCE 25
#endif

/* track_point structure */
typedef struct {
    struct {
        //// auto mouse
        bool     is_enabled;
        uint8_t  layer;
        uint16_t timeout;
        uint8_t  debounce;
    } config;
    struct {
        uint16_t active;
    } timer;
    struct {
        /* track_point是否被触发 */
        bool   is_activated;
    } status;
} trackpoint_auto_mouse_context_t;


/* ----------Set up and control------------------------------------------------------------------------------ */
void    set_trackpoint_auto_mouse_enable(bool enable);                       // enable/disable auto mouse feature

/* ----------For custom pointing device activation----------------------------------------------------------- */
/**
 * 判断是否移动（按下)
 */
bool    auto_mouse_activation(report_mouse_t mouse_report); // handles pointing device trigger conditions for target layer activation (overwritable)

/* ----------Core functions (only used in custom pointing devices or key processing)------------------------- */
void    trackpoint_auto_mouse(report_mouse_t mouse_report); // add to pointing_device_task_*
