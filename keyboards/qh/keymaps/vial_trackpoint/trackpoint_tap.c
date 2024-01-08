#ifdef TRACKPOINT_TAP_ENABLE
#    include "trackpoint_tap.h"
#include "print.h"

/* local data structure for tracking auto mouse and tap */
static trackpoint_tap_context_t trackpoint_tap_context = {
    .config.max_offset = (uint8_t)(TRACKPOINT_MAX_TAP_OFFSET),
};

/**
 * 重置track point context
 */
static inline void trackpoint_tap_reset(void) {
    memset(&trackpoint_tap_context.status, 0, sizeof(trackpoint_tap_context.status));
    memset(&trackpoint_tap_context.timer, 0, sizeof(trackpoint_tap_context.timer));
}

static inline bool context_tap_is_enabled(void) {
    return trackpoint_tap_context.config.is_enabled;
}

static inline bool context_touch_down(void) {
    return trackpoint_tap_context.status.touch_down;
}

static inline bool context_timer_in_tap_term(void) {
    return trackpoint_tap_context.timer.active != 0 && timer_elapsed(trackpoint_tap_context.timer.active) < TRACKPOINT_TAPPING_TERM;
}

static inline bool context_timer_over_debounce(void) {
    return timer_elapsed(trackpoint_tap_context.timer.active) > TRACKPOINT_TOUCH_DEBOUNCE;
}

static inline void context_tap_reset_timer(void) {
    trackpoint_tap_context.timer.active = 0;
    trackpoint_tap_context.status.touch_status_diff_times = 0;
    trackpoint_tap_context.status.ldt = 0;
}

static inline void context_tap_set_timer_current(void) {
    trackpoint_tap_context.timer.active = timer_read();
}

// /**
// * 1 touch change up
// * -1 touch change down
// * 0 no touch change
// */
// static inline uint8_t context_decide_is_touch_changed(report_mouse_t mouse_report) {
//     bool touch_down = trackpoint_touch_down(mouse_report); // false
//     bool current_down = context_touch_down(); // true
//     if(touch_down == current_down) {
//         if(trackpoint_tap_context.status.touch_status_diff_times > 0) {
//             // uprintf("ps2_mouse_moved_user>>>0x:%d, y:%d, v:%d, h:%d", mouse_report.x, mouse_report.y, mouse_report.v, mouse_report.h);
//             // trackpoint_tap_context.status.touch_status_diff_times = trackpoint_tap_context.status.touch_status_diff_times - 1;
//             trackpoint_tap_context.status.touch_status_diff_times = 0;
//         }
//         return 0;
//     }
//     // different
//     if(touch_down) {
//         // touch down
//         trackpoint_tap_context.status.touch_down = true;
//         trackpoint_tap_context.status.touch_status_diff_times = 0;
//         // uprintf("ps2_mouse_moved_user>>>1x:%d, y:%d, v:%d, h:%d, t:%d", mouse_report.x, mouse_report.y, mouse_report.v, mouse_report.h, trackpoint_tap_context.status.touch_status_diff_times);
//         return -1;
//     }
//     // touch up
//     trackpoint_tap_context.status.touch_status_diff_times = trackpoint_tap_context.status.touch_status_diff_times + 1;
//     if(trackpoint_tap_context.status.touch_status_diff_times > 100) {
//         trackpoint_tap_context.status.touch_down = false;
//         trackpoint_tap_context.status.touch_status_diff_times = 0;
//         uprintf("ps2_mouse_moved_user>>>2x:%d, y:%d, v:%d, h:%d, t:%d", mouse_report.x, mouse_report.y, mouse_report.v, mouse_report.h, trackpoint_tap_context.status.touch_status_diff_times);
//         return 1;
//     }
//     // uprintf("ps2_mouse_moved_user>>>3x:%d, y:%d, v:%d, h:%d, t:%d", mouse_report.x, mouse_report.y, mouse_report.v, mouse_report.h, trackpoint_tap_context.status.touch_status_diff_times);
//     return 0;
//     // if(touch_down != context_touch_down()) {
//     //     trackpoint_tap_context.status.touch_status_diff_times = trackpoint_tap_context.status.touch_status_diff_times + 3;
//     //     uprintf("ps2_mouse_moved_user>>>x:%d, y:%d, v:%d, h:%d", mouse_report.x, mouse_report.y, mouse_report.v, mouse_report.h);
//     //     if(trackpoint_tap_context.status.touch_status_diff_times > 10) {
//     //         trackpoint_tap_context.status.touch_down = touch_down;
//     //         trackpoint_tap_context.status.touch_status_diff_times = 0;
//     //         return touch_down ? -1 : 1;
//     //         uprintf("ps2_mouse_moved_user>>trackpoint_tap touch down, %d", touch_down);
//     //     }
//     // } else if(trackpoint_tap_context.status.touch_status_diff_times > 0) {
//     //     uprintf("ps2_mouse_moved_user>>>__x:%d, y:%d, v:%d, h:%d", mouse_report.x, mouse_report.y, mouse_report.v, mouse_report.h);
//     //     trackpoint_tap_context.status.touch_status_diff_times = trackpoint_tap_context.status.touch_status_diff_times - 1;
//     // }
//     // return 0;
// }

// single
// #define DEBOUNCE_THRESHOLD 400
// split
#define DEBOUNCE_THRESHOLD 160
// use console
// #define DEBOUNCE_THRESHOLD 20

// 0 不变
// 5 debounce
// 10 按下
// 20 抬起
uint8_t is_tap(report_mouse_t mouse_report) {
    bool current_touch_down = trackpoint_touch_down(mouse_report);
    uint16_t delta = abs(mouse_report.x) + abs(mouse_report.y);
    if (!trackpoint_tap_context.status.td) {
        uprintf("ps2_mouse_moved_user>>3_1");
        // 当前没有按下
        // 只要点击就认为是按下
        if (current_touch_down) {
            uprintf("ps2_mouse_moved_user>>3_1_1");
            trackpoint_tap_context.status.td = true;
            trackpoint_tap_context.status.ldt = 0;
            trackpoint_tap_context.status.total_delta = 0;
            // 按下
            return 10;
        } else {
            if(delta < TRACKPOINT_MIN_DELTA) {
                trackpoint_tap_context.status.total_delta += delta;
            }
            uprintf("ps2_mouse_moved_user>>3_1_2");
            return 0;
        }
    } else {
        if(delta < TRACKPOINT_MIN_DELTA) {
            trackpoint_tap_context.status.total_delta += delta;
        }
        uprintf("ps2_mouse_moved_user>>3_2");
        // 当前是按下
        // 需要debounce，连续的几个都不是 touch_down才认为是抬起
        if (current_touch_down) {
            uprintf("ps2_mouse_moved_user>>3_2_1");
            trackpoint_tap_context.status.ldt = 0;
            return 0;
        } else {
            uprintf("ps2_mouse_moved_user>>3_2_3,ldt_1:%d", trackpoint_tap_context.status.ldt);
            if(trackpoint_tap_context.status.ldt == 0) {
                trackpoint_tap_context.status.ldt = DEBOUNCE_THRESHOLD;
            }
            (&trackpoint_tap_context)->status.ldt = trackpoint_tap_context.status.ldt - 1;
            uprintf("ps2_mouse_moved_user>>3_2_3,ldt_2:%d", trackpoint_tap_context.status.ldt);
            if (trackpoint_tap_context.status.ldt <= 0) {
                uprintf("ps2_mouse_moved_user>>3_2_2");
                trackpoint_tap_context.status.td = false;
                // 抬起
                return 20;
            } else {
                uprintf("ps2_mouse_moved_user>>3_2_3,ldt_3:%d", trackpoint_tap_context.status.ldt);
                // 抬起debounce中
                return 5;
            }

        }
    }
}


static inline uint8_t trackpoint_handle_buttons(uint8_t buttons, bool pressed, trackpoint_buttons_t button) {
    if (pressed) {
        buttons |= 1 << (button);
    } else {
        buttons &= ~(1 << (button));
    }
    return buttons;
}

/**
 * 判断track point是否触发
 * 
 * @param[in] mouse_report report_mouse_t
 * @return bool of track point activation
 */
__attribute__((weak)) bool trackpoint_touch_down(report_mouse_t mouse_report) {
    bool action = mouse_report.x != 0 || mouse_report.y != 0;
    return action;
    // bool canAsTap = abs(mouse_report.x) <trackpoint_tap_context.config.max_offset && abs(mouse_report.y) <trackpoint_tap_context.config.max_offset;
    // return action && canAsTap;
}

/**
 * 启用禁用track point
 * @param[in] state bool
 */
void set_trackpoint_tap_enable(bool enable) {
    // skip if unchanged
    if (trackpoint_tap_context.config.is_enabled == enable ) return;
    trackpoint_tap_context.config.is_enabled = enable;
    trackpoint_tap_reset();
}

// static report_mouse_t static_mouse_report = {};
/**
 * report_mouse_t trackpad_tap(report_mouse_t mouse_report, pinnacle_data_t touchData)
 * 
 * @brief Update the auto mouse based on mouse_report
 *
 * Handel activation/deactivation of target layer based on auto_mouse_activation and state timers and local key/layer tracking data
 *
 * @param[in] mouse_report report_mouse_t
 */
void trackpoint_tap(report_mouse_t *mouse_report) {
    // skip if disabled, delay timer running
    // print("ps2_mouse_moved_user>>trackpoint_tap");
    if (!context_tap_is_enabled()) {
        return;
    }
    // uint8_t flag = context_decide_is_touch_changed(*mouse_report);
    uint8_t i_tap = is_tap(*mouse_report);
    uprintf("ps2_mouse_moved_user>>3_2_3,ldt_4:%d", trackpoint_tap_context.status.ldt);

    uprintf("ps2_mouse_moved_user>>1i_tap, %d", i_tap);


    // if (i_tap == 2) {
    //     if (context_timer_in_tap_term()) {
    //         uprintf("ps2_mouse_moved_user>>2bbb, %d, %d", TRACKPOINT_TAPPING_TERM, mouse_report->buttons);
    //     }
    // }

    if (i_tap >= 10) {
        if(i_tap == 20) {
            uprintf("ps2_mouse_moved_user>>2ccc, %d, %d", TRACKPOINT_TAPPING_TERM, timer_elapsed(trackpoint_tap_context.timer.active));
            if (context_timer_in_tap_term()) {
            // if (context_timer_in_tap_term() && trackpoint_tap_context.status.total_delta >= TRACKPOINT_MIN_DELTA) {
                // uprintf("ps2_mouse_moved_user>>trackpoint_tap in term1, %d, %d", TRACKPOINT_TAPPING_TERM, mouse_report->buttons);
                mouse_report->buttons = trackpoint_handle_buttons(mouse_report->buttons, true, TRACKPOINT_BUTTON1);
                uprintf("ps2_mouse_moved_user>>2bbb, %d, %d", TRACKPOINT_TAPPING_TERM, mouse_report->buttons);
                // mouse_report->buttons = 1;
                // uprintf("ps2_mouse_moved_user>>trackpoint_tap in term2, %d", mouse_report->buttons);
            }
            context_tap_reset_timer();
        }
        if(i_tap == 10) {
            context_tap_set_timer_current();
        }
    }
    if (trackpoint_tap_context.status.td && context_timer_in_tap_term() && abs(mouse_report-> x) < 5 && abs(mouse_report-> y) < 5) {
            mouse_report-> x = 0;
            mouse_report-> y = 0;
    }

    // if (flag != 0) {
    //     if(flag == 1) {
    //         if (context_timer_in_tap_term()) {
    //             // uprintf("ps2_mouse_moved_user>>trackpoint_tap in term1, %d, %d", TRACKPOINT_TAPPING_TERM, mouse_report->buttons);
    //             mouse_report->buttons = trackpoint_handle_buttons(mouse_report->buttons, true, TRACKPOINT_BUTTON1);
    //             uprintf("ps2_mouse_moved_user>>2aaa, %d, %d", TRACKPOINT_TAPPING_TERM, mouse_report->buttons);
    //             // mouse_report->buttons = 1;
    //             // uprintf("ps2_mouse_moved_user>>trackpoint_tap in term2, %d", mouse_report->buttons);
    //         }
    //     }
    //     context_tap_set_timer_current();
    // }
    // else {
    //     if(context_timer_in_tap_term()) {
    //         mouse_report->x = 0;
    //         mouse_report->y = 0;
    //         mouse_report->v = 0;
    //         mouse_report->h = 0;

    //     }
    // }
    // if (context_timer_over_debounce()) {
        // uprintf("ps2_mouse_moved_user>>over debounce, %d, %d", TRACKPOINT_TOUCH_DEBOUNCE, mouse_report->buttons);
        // context_tap_reset_timer();
    // }
}

#endif // TRACKPOINT_TAP_ENABLE