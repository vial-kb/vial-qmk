#ifndef SWITCH_BOARD_H
#define SWITCH_BOARD_H

#include <stdint.h>
#include <stdbool.h>

#define GPIO_OUTPUT_MODE (PAL_MODE_OUTPUT_PUSHPULL)
#define GETKEY_INPUT_MODE (has_extra_pull_up? (PAL_MODE_INPUT_PULLDOWN) : (PAL_MODE_INPUT_PULLUP))

extern bool is_ver5020;
extern bool has_extra_pull_up;

//SDI PB13
static inline void KEY_SDI_OFF(void) {
    if (is_ver5020) {
        palClearPad(GPIOB, 13);
    } else {
        palSetPad(GPIOB, 13);
    }
}
static inline void KEY_SDI_ON(void) {
    if (is_ver5020) {
        palSetPad(GPIOB, 13);
    } else {
        palClearPad(GPIOB, 13);
    }
}

static inline void sleep_us(int us){
    for (int i = 0; i < us*10; i++) {
        __asm__("nop");
    }
}

static inline void get_key_ready(void) {
    // PB13 input
    palSetPadMode(GPIOB, 13, GETKEY_INPUT_MODE);
    sleep_us(2);
}

static inline void select_key_ready(void) {
    palSetPadMode(GPIOB, 13, GPIO_OUTPUT_MODE);
} 

//SCK PB12
//asm("nop");
#define CLOCK_PULSE() \
    do { \
        palSetPad(GPIOB, 12); \
        palClearPad(GPIOB, 12); \
    } while(0)

//RCK PB11
#if 0
#define KEYS_LATCH() \
    do { \
        palSetPad(GPIOB, 11); \
        palClearPad(GPIOB, 11); \
    } while(0)

#endif
#endif