#include <stdbool.h>
#include "matrix.h"
#include "action.h"
#include "suspend.h"
#include "timer.h"
#include "led.h"
#include "host.h"

#include "tusb.h"

#ifdef BACKLIGHT_ENABLE
#    include "backlight.h"
#endif

#ifdef AUDIO_ENABLE
#    include "audio.h"
#endif /* AUDIO_ENABLE */

#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
#    include "rgblight.h"
#endif

/** \brief Suspend idle
 *
 * FIXME: needs doc
 */
void suspend_idle(uint8_t time) {
}

// TODO: This needs some cleanup

/** \brief Run keyboard level Power down
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_power_down_user(void) {}
/** \brief Run keyboard level Power down
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_power_down_kb(void) { suspend_power_down_user(); }


/** \brief Suspend power down
 *
 * FIXME: needs doc
 */
void suspend_power_down(void) {
    if (!tud_suspended()) return;

    suspend_power_down_kb();

#ifndef NO_SUSPEND_POWER_DOWN
    // Turn off backlight
#    ifdef BACKLIGHT_ENABLE
    backlight_set(0);
#    endif

    // Turn off LED indicators
    uint8_t leds_off = 0;
#    if defined(BACKLIGHT_CAPS_LOCK) && defined(BACKLIGHT_ENABLE)
    if (is_backlight_enabled()) {
        // Don't try to turn off Caps Lock indicator as it is backlight and backlight is already off
        leds_off |= (1 << USB_LED_CAPS_LOCK);
    }
#    endif
    led_set(leds_off);

    // Turn off audio
#    ifdef AUDIO_ENABLE
    stop_all_notes();
#    endif

    // Turn off underglow
#    if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    rgblight_suspend();
#    endif

    // Enter sleep state if possible (ie, the MCU has a watchdog timeout interrupt)
#    if defined(WDT_vect)
    power_down(WDTO_15MS);
#    endif
#endif
}

__attribute__((weak)) void matrix_power_up(void) {}
__attribute__((weak)) void matrix_power_down(void) {}
bool                       suspend_wakeup_condition(void) {
    matrix_power_up();
    matrix_scan();
    matrix_power_down();
    for (uint8_t r = 0; r < MATRIX_ROWS; r++) {
        if (matrix_get_row(r)) return true;
    }
    return false;
}

/** \brief run user level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_wakeup_init_user(void) {}

/** \brief run keyboard level code immediately after wakeup
 *
 * FIXME: needs doc
 */
__attribute__((weak)) void suspend_wakeup_init_kb(void) { suspend_wakeup_init_user(); }

/** \brief run immediately after wakeup
 *
 * FIXME: needs doc
 */
void suspend_wakeup_init(void) {
    // clear keyboard state
    clear_keyboard();

    // Turn on backlight
#ifdef BACKLIGHT_ENABLE
    backlight_init();
#endif

    // Restore LED indicators
    led_set(host_keyboard_leds());

    // Wake up underglow
#if defined(RGBLIGHT_SLEEP) && defined(RGBLIGHT_ENABLE)
    rgblight_wakeup();
#endif

    suspend_wakeup_init_kb();
}

#if !defined(NO_SUSPEND_POWER_DOWN) && defined(WDT_vect)
/* watchdog timeout */
ISR(WDT_vect) {
    // compensate timer for sleep
    switch (wdt_timeout) {
        case WDTO_15MS:
            timer_count += 15 + 2;  // WDTO_15MS + 2(from observation)
            break;
        default:;
    }
}
#endif
