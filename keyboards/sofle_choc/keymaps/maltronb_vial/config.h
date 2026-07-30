// Sofle Choc Maltron-B — keymap-level config.h
// Note: VENDOR_ID, PRODUCT_ID, MANUFACTURER, PRODUCT, WS2812_DI_PIN,
// ENCODERS_PAD, NO_LED — all OWNED BY keyboard.json. DO NOT define here.

#pragma once

// ─── Combo / tap timing ───────────────────────────────────────
#define TAPPING_TERM             200
#define COMBO_TERM               35
#define COMBO_ONLY_FROM_LAYER    0
#define PERMISSIVE_HOLD

// ─── Split keyboard ───────────────────────────────────────────
#define MASTER_LEFT
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_MODS_ENABLE

// ─── RGB matrix ───────────────────────────────────────────────
// Note: RGB_MATRIX_LED_COUNT and RGB_MATRIX_SPLIT owned by keyboard.json.

// LED never shuts off except after 2 hours of total key inactivity
// 2 hours × 3600 s × 1000 ms = 7,200,000 ms
#define RGB_MATRIX_TIMEOUT       7200000


// We have 9 layers (BASE, NUM, SYM, NAV, CFG, CAT, GAME, NUMPAD, WIN).
// QMK's default DYNAMIC_KEYMAP_LAYER_COUNT is 4-8; raise it for headroom.
#define DYNAMIC_KEYMAP_LAYER_COUNT 10

// ─── OLED ─────────────────────────────────────────────────────
#define OLED_TIMEOUT             0   // never time out (matches RGB philosophy)
// layer state: 8 bits is enough for 9 layers, but 16 bits gives us headroom for more layers if we want to add them later.
#define LAYER_STATE_16BIT