// Copyright 2022 Victor Lucachi (@victorlucachi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* Keyboard Matrix Assignments */
 #define MATRIX_ROW_PINS { F6, F7, B1, B3 }
 #define MATRIX_COL_PINS { F5, F4, B5, B4, E6, D7, C6, D4, D0, D1, D2, D3 }
 #define UNUSED_PINS

/* Force NKRO */
#define FORCE_NKRO

/* disable these deprecated features by default */
#ifndef LINK_TIME_OPTIMIZATION_ENABLE
  #define NO_ACTION_MACRO
  #define NO_ACTION_FUNCTION
#endif

#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
