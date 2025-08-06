// Copyright 2023 The Vial-KB Community (@vial-kb)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Reset to QMK default for STM32042x6. Vial default is currently 8 pages.
#if FEE_PAGE_COUNT != 2
#    define FEE_PAGE_COUNT 2
#endif
