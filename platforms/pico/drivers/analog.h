
#pragma once

#include <stdint.h>
#include "quantum.h"

typedef struct {
    pin_t pin;
    uint8_t adc;
} adc_mux;

#define TO_MUX(i, a) \
    (adc_mux) { i, a }

int16_t analogReadPin(pin_t pin);
adc_mux pinToMux(pin_t pin);

#define adc_read(mux) adc_read_pico(mux)
int16_t adc_read_pico(adc_mux mux);
