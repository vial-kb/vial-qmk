/*
Audio Driver: PWM

the duty-cycle is always kept at 50%, and the pwm-period is adjusted to match
the frequency of a note to be played back.

this driver uses the chibios-PWM system to produce a square-wave on specific
output pins that are connected to the PWM hardware. The hardware directly
toggles the pin via its alternate function. see your MCUs data-sheet for which
pin can be driven by what timer - looking for TIMx_CHy and the corresponding
alternate function.

 */

#include "audio.h"

#include "hardware/pwm.h"
#include "hardware/irq.h"
#include "hardware/clocks.h"

#if !defined(AUDIO_PIN)
#    error \
        "Audio feature enabled, but no pin selected - see docs/feature_audio under the ARM PWM settings"
#endif

extern bool    playing_note;
extern bool    playing_melody;
extern uint8_t note_timbre;

#define WRAP_MAX 65534
#define CLOCK_DIV 100

static void              pwm_callback(void);

static uint              pwm_clock   = 12000000 / CLOCK_DIV;
static volatile uint32_t isr_counter = 0;

static float channel_1_frequency = 0.0f;
void         channel_1_set_frequency(float freq) {
    channel_1_frequency = freq;

    if (freq <= 0.0)  // a pause/rest has freq=0
        return;

    // enable channel

    uint     slice = pwm_gpio_to_slice_num(AUDIO_PIN);
    uint16_t wrap  = pwm_clock / freq;
    pwm_set_wrap(slice, wrap);
    pwm_set_gpio_level(AUDIO_PIN, wrap * note_timbre / 100);
}

float channel_1_get_frequency(void) { return channel_1_frequency; }

void channel_1_start(void) {
    uint slice = pwm_gpio_to_slice_num(AUDIO_PIN);
    pwm_set_enabled(slice, true);
}

void channel_1_stop(void) {
    uint slice = pwm_gpio_to_slice_num(AUDIO_PIN);
    pwm_set_enabled(slice, false);
}

void audio_driver_initialize(void) {
    channel_1_stop();
    gpio_set_function(AUDIO_PIN, GPIO_FUNC_PWM);
    uint slice = pwm_gpio_to_slice_num(AUDIO_PIN);

    pwm_clear_irq(slice);
    pwm_set_irq_enabled(slice, true);
    irq_set_exclusive_handler(PWM_IRQ_WRAP, pwm_callback);
    irq_set_enabled(PWM_IRQ_WRAP, true);

    pwm_set_clkdiv(slice, CLOCK_DIV);
    pwm_clock = clock_get_hz(clk_sys) / CLOCK_DIV;
    pwm_set_wrap(slice, WRAP_MAX);
}

void audio_driver_start(void) {
    channel_1_stop();
    channel_1_start();

    if (playing_note || playing_melody) {
        channel_1_set_frequency(audio_get_processed_frequency(0));
    }
}

void audio_driver_stop(void) { channel_1_stop(); }

static void pwm_callback(void) {
    pwm_clear_irq(pwm_gpio_to_slice_num(AUDIO_PIN));

    isr_counter++;
    if (isr_counter < channel_1_frequency / (64)) return;

    isr_counter        = 0;
    bool state_changed = audio_update_state();

    if (!playing_note && !playing_melody) {
        channel_1_stop();
        return;
    }

    if (state_changed) {
        channel_1_set_frequency(audio_get_processed_frequency(0));
    }
}
