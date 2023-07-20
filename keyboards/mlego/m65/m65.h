// Copyright 2020-2023 alin m elena (@alinelena, @drFaustroll)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define LAYOUT_ortho_5x13_with_encoder( \
																K998, K999, \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, \
    K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312 }, \
    { K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412 }  \
}

#define LAYOUT_ortho_5x13( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, \
    K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312 }, \
    { K400, K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412 }  \
}



enum layer_names {
    _QW = 0,
    _LWR,
    _RSE,
    _ADJ
};

void toggle_leds(const bool, const bool);
void set_led_toggle(const uint8_t, const bool);

static inline void init_lwr_rse_led(void) {
#ifdef LED_LWR_PIN
    setPinOutput(LED_LWR_PIN);
    writePin(LED_LWR_PIN, false);
    wait_ms(30);
#endif

#ifdef LED_RSE_PIN
    setPinOutput(LED_RSE_PIN);
    writePin(LED_RSE_PIN, false);
    wait_ms(30);
#endif
}

static inline void led_lwr(const bool on) {
#ifdef LED_LWR_PIN
    if ((PRODUCT_ID == 0x6064) || (PRODUCT_ID == 0x6065) ||
        (PRODUCT_ID == 0x6066) || (PRODUCT_ID == 0x6067)) {
        writePin(LED_LWR_PIN, !on);
    }else{
        writePin(LED_LWR_PIN, on);
    }
#endif
}

static inline void led_rse(const bool on) {
#ifdef LED_RSE_PIN
    if ((PRODUCT_ID == 0x6064) || (PRODUCT_ID == 0x6065) ||
        (PRODUCT_ID == 0x6066) || (PRODUCT_ID == 0x6067)) {
        writePin(LED_RSE_PIN, !on);
    }else{
        writePin(LED_RSE_PIN, on);
    }
#endif
}
