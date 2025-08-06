#pragma once

#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
  #include "ws2812.h"
#endif

#define LAYOUT_crisco( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09,		\
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19		\
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09},	\
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19},	\
}
