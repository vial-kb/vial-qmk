// Copyright 2022 Markus Knutsson (@TweetyDaBird)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define VIAL_KEYBOARD_UID {0x5F, 0xEC, 0xD8, 0x46, 0x91, 0x40, 0x1B, 0x09}

#define VIAL_UNLOCK_COMBO_ROWS {0, 0}
#define VIAL_UNLOCK_COMBO_COLS {0, 5}

// Static glow is ALWAYS on with RGBLIGHT
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define LAYER_STATE_8BIT

// VIAL specific reduce memory
#define VIAL_COMBO_ENTRIES 4
#define VIAL_TAP_DANCE_ENTRIES 4
#define VIAL_KEY_OVERRIDE_ENTRIES 4
