// Copyright 2024 Tustation
// SPDX-License-Identifier: GPL-2.0-or-later

#include "tq63.h"

void board_init(void) {
    AFIO->MAPR |= AFIO_MAPR_SWJ_CFG_DISABLE;
}