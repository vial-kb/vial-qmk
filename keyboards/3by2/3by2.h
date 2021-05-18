#pragma once

#include "quantum.h"

/* LAYOUT
 * │K00│K01│K02│
 * ├───┼───┼───┤
 * │K03│K04│K05│
 * └───┴───┴───┘
 */

#define LAYOUT_h( K00, K01, K02, K03, K04, K05 ) \
{ { K00, K01, K02 }, { K03, K04, K05 } }
#define LAYOUT LAYOUT_h