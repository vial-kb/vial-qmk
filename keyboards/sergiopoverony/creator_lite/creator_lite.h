#pragma once
#include "quantum.h"

/* Use VIA layout from David Doan*/
/*layout*/
#define LAYOUT( \
    k01, k02, k03, k04, k05\
  ) { \
    { k01, k02, k03, k04, k05} \
}

/*led work*/
void turn_off_leds(void);
void turn_on_led(pin_t pin);
