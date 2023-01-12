// Copyright 2022 Victor Lucachi (@victorlucachi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F6 }

#define ENCODERS_PAD_A_RIGHT { F6 }
#define ENCODERS_PAD_B_RIGHT { F5 }

#define SPLIT_USB_DETECT
