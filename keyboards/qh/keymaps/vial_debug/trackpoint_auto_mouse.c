#ifdef TRACKPOINT_AUTO_MOUSE_ENABLE
#    include "trackpoint_auto_mouse.h"

/* local data structure for tracking auto mouse and tap */
static trackpoint_auto_mouse_context_t trackpoint_auto_mouse_context = {
    .config.layer    = (uint8_t)(TRACKPOINT_AUTO_MOUSE_DEFAULT_LAYER),
    .config.timeout  = (uint16_t)(TACKPOINT_AUTO_MOUSE_TIMEOUT),
    .config.debounce = (uint8_t)(TACKPOINT_AUTO_MOUSE_DEBOUNCE),
};

/**
 * 重置track point context
 */
static inline void trackpoint_auto_mouse_reset(void) {
    memset(&trackpoint_auto_mouse_context.status, 0, sizeof(trackpoint_auto_mouse_context.status));
    memset(&trackpoint_auto_mouse_context.timer, 0, sizeof(trackpoint_auto_mouse_context.timer));
}

static inline bool context_auto_mouse_is_enabled(void) {
    return trackpoint_auto_mouse_context.config.is_enabled;
}

static inline bool context_is_activated(void) {
    return trackpoint_auto_mouse_context.status.is_activated;
}

static inline bool context_timer_timeout(void) {
    return timer_elapsed(trackpoint_auto_mouse_context.timer.active) > trackpoint_auto_mouse_context.config.timeout;
}

static inline bool context_timer_in_debounce(void) {
    return timer_elapsed(trackpoint_auto_mouse_context.timer.active) <= trackpoint_auto_mouse_context.config.debounce;
}

static inline uint8_t context_layer(void) {
    return trackpoint_auto_mouse_context.config.layer;
}

static inline void context_auto_mouse_reset_timer(void) {
    trackpoint_auto_mouse_context.timer.active = 0;
}

static inline void context_auto_mouse_set_timer_current(void) {
    trackpoint_auto_mouse_context.timer.active = timer_read();
}

static inline void context_decide_is_activated(report_mouse_t mouse_report) {
    trackpoint_auto_mouse_context.status.is_activated = auto_mouse_activation(mouse_report);
}

/**
 * 判断track point是否触发
 * 
 * @param[in] mouse_report report_mouse_t
 * @return bool of track point activation
 */
__attribute__((weak)) bool auto_mouse_activation(report_mouse_t mouse_report) {
    return mouse_report.x != 0 || mouse_report.y != 0 || mouse_report.h != 0 || mouse_report.v != 0 || mouse_report.buttons;
}

/**
 * 启用禁用track point
 * @param[in] state bool
 */
void set_trackpoint_auto_mouse_enable(bool enable) {
    // skip if unchanged
    if (trackpoint_auto_mouse_context.config.is_enabled == enable ) return;
    trackpoint_auto_mouse_context.config.is_enabled = enable;
    trackpoint_auto_mouse_reset();
}

// static report_mouse_t static_mouse_report = {};
/**
 * void pointing_device_task_auto_mouse(report_mouse_t mouse_report);
 * @brief Update the auto mouse based on mouse_report
 *
 * Handel activation/deactivation of target layer based on auto_mouse_activation and state timers and local key/layer tracking data
 *
 * @param[in] mouse_report report_mouse_t
 */
void trackpoint_auto_mouse(report_mouse_t mouse_report) {
    // skip if disabled, delay timer running, or debounce
    if (!context_auto_mouse_is_enabled() || context_timer_in_debounce()) {
        return;
    }
    // update activation and reset debounce
    context_decide_is_activated(mouse_report);
    if (context_is_activated()) {
        context_auto_mouse_set_timer_current();
        if (!layer_state_is(context_layer())) {
            layer_on((context_layer()));
        }
    } else if (layer_state_is(context_layer()) && context_timer_timeout()) {
        layer_off(context_layer());
        context_auto_mouse_reset_timer();
    }
}


#endif // TRACKPOINT_AUTO_MOUSE_ENABLE