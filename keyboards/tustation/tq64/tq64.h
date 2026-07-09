// Copyright 2024 Tustation
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "quantum.h"
#define XXX KC_NO
#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211,       K213, \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K310, K311, K312, K313, \
    K40, K41, K42,                   K47,        K49, K410, K411, K412, K413 \
) { \
    { K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K010, K011, K012, K013 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K110, K111, K112, K113 }, \
    { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K210, K211, XXX, K213 }, \
    { K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K310, K311, K312, K313 }, \
    { K40, K41, K42, XXX, XXX, XXX, XXX, K47, XXX, K49, K410, K411, K412, K413 } \
}
