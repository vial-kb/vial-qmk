#include "quantum.h"
#include "boards/pico_boards.h"
#include "analog.h"
#undef adc_read

#include "hardware/adc.h"

int16_t analogReadPin(pin_t pin) { return adc_read_pico(pinToMux(pin)); }

__attribute__((weak)) adc_mux pinToMux(pin_t pin) {
    switch (pin) {
        case 26 ... 29:
            return TO_MUX(pin, pin - 26);
        default:
            return TO_MUX(0, 0xff);
    }
}

int16_t adc_read_pico(adc_mux mux) {
    adc_gpio_init(mux.pin);
    adc_select_input(mux.adc);
    return adc_read();
}
