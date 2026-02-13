# Extracted Data: Source File Values

**Extracted:** 2026-02-13
**Source files read:** 13
**Purpose:** Raw configuration values for Plan 02 synthesis into REFERENCE-ANALYSIS.md

---

## 1. Sofle rev1 Vial -- Raw Values

### keyboard.json

| Property | Value | Source |
|----------|-------|--------|
| matrix_pins.rows | `["C6", "D7", "E6", "B4", "B5"]` (5 pins) | `keyboards/sofle/rev1/keyboard.json` |
| matrix_pins.cols | `["F6", "F7", "B1", "B3", "B2", "B6"]` (6 pins) | `keyboards/sofle/rev1/keyboard.json` |
| split.enabled | Not explicitly declared; split implied by `split.encoder.right` presence | `keyboards/sofle/rev1/keyboard.json` |
| Layout left-half rows | 0, 1, 2, 3, 4 | `keyboards/sofle/rev1/keyboard.json` layouts.LAYOUT |
| Layout right-half rows | 5, 6, 7, 8, 9 | `keyboards/sofle/rev1/keyboard.json` layouts.LAYOUT |

### vial.json

| Property | Value | Source |
|----------|-------|--------|
| name | "Sofle" | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| vendorId | "0xFC32" | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| productId | "0x0287" | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| matrix.rows | **10** | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| matrix.cols | **6** | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| "encoders" JSON key | **Not present** | `keyboards/sofle/rev1/keymaps/vial/vial.json` |

**Left-half key positions (rows 0-4):**

| Row | Positions | Count |
|-----|-----------|-------|
| 0 | 0,0 / 0,1 / 0,2 / 0,3 / 0,4 / 0,5 | 6 |
| 1 | 1,0 / 1,1 / 1,2 / 1,3 / 1,4 / 1,5 | 6 |
| 2 | 2,0 / 2,1 / 2,2 / 2,3 / 2,4 / 2,5 | 6 |
| 3 | 3,0 / 3,1 / 3,2 / 3,3 / 3,4 / 3,5 | 6 |
| 4 | 4,0 / 4,1 / 4,2 / 4,3 / 4,4 / 4,5 | 6 |
| **Total** | | **30** |

**Right-half key positions (rows 5-9):**

| Row | Positions | Count |
|-----|-----------|-------|
| 5 | 5,0 / 5,1 / 5,2 / 5,3 / 5,4 / 5,5 | 6 |
| 6 | 6,0 / 6,1 / 6,2 / 6,3 / 6,4 / 6,5 | 6 |
| 7 | 7,0 / 7,1 / 7,2 / 7,3 / 7,4 / 7,5 | 6 |
| 8 | 8,0 / 8,1 / 8,2 / 8,3 / 8,4 / 8,5 | 6 |
| 9 | 9,0 / 9,1 / 9,2 / 9,3 / 9,4 / 9,5 | 6 |
| **Total** | | **30** |

**Encoder KLE entries (with `\ne` suffix):**

| Entry | Encoder Index | Direction |
|-------|---------------|-----------|
| `"0,1\n\n\n\n\n\n\n\n\ne"` | 0 | CW (display) |
| `"1,1\n\n\n\n\n\n\n\n\ne"` | 1 | CW (display) |
| `"0,0\n\n\n\n\n\n\n\n\ne"` | 0 | CCW (display) |
| `"1,0\n\n\n\n\n\n\n\n\ne"` | 1 | CCW (display) |

### config.h (keymap)

| Property | Value | Source |
|----------|-------|--------|
| VIAL_KEYBOARD_UID | `{ 0x05, 0xCD, 0x9F, 0x8A, 0xF4, 0xDF, 0xDE, 0xB2 }` | `keyboards/sofle/rev1/keymaps/vial/config.h` |
| VIAL_UNLOCK_COMBO_ROWS | **{ 0, 5, 3, 8 }** | `keyboards/sofle/rev1/keymaps/vial/config.h` |
| VIAL_UNLOCK_COMBO_COLS | **{ 0, 0, 0, 0 }** | `keyboards/sofle/rev1/keymaps/vial/config.h` |

### keymap.c

| Property | Value | Source |
|----------|-------|--------|
| keymaps array dimensions | `[4][MATRIX_ROWS][MATRIX_COLS]` = `[4][10][6]` | `keyboards/sofle/rev1/keymaps/vial/keymap.c` |
| Layer count | 4 (layers 0-3) | `keyboards/sofle/rev1/keymaps/vial/keymap.c` |
| encoder_map layers | 4 | `keyboards/sofle/rev1/keymaps/vial/keymap.c` |
| encoder_map encoders/layer | 2 (NUM_ENCODERS=2) | `keyboards/sofle/rev1/keymaps/vial/keymap.c` |
| encoder_map default actions | All KC_TRNS (all layers, both encoders) | `keyboards/sofle/rev1/keymaps/vial/keymap.c` |

### rules.mk

| Property | Value | Source |
|----------|-------|--------|
| VIA_ENABLE | yes | `keyboards/sofle/rev1/keymaps/vial/rules.mk` |
| VIAL_ENABLE | yes | `keyboards/sofle/rev1/keymaps/vial/rules.mk` |
| ENCODER_MAP_ENABLE | yes | `keyboards/sofle/rev1/keymaps/vial/rules.mk` |
| ENCODER_ENABLE | yes | `keyboards/sofle/rev1/keymaps/vial/rules.mk` |
| OLED_ENABLE | yes | `keyboards/sofle/rev1/keymaps/vial/rules.mk` |

---

## 2. Bipedal Ambi -- Raw Values

### config.h (board-level)

| Property | Value | Source | Expected | Match? |
|----------|-------|--------|----------|--------|
| MATRIX_ROWS | **8** | `keyboards/hidpress/bipedalambi/config.h` | 8 | YES |
| MATRIX_COLS | **8** | `keyboards/hidpress/bipedalambi/config.h` | 8 | YES |
| SPLIT_USB_DETECT | defined | `keyboards/hidpress/bipedalambi/config.h` | -- | -- |
| SERIAL_USART_FULL_DUPLEX | defined | `keyboards/hidpress/bipedalambi/config.h` | -- | -- |
| SPLIT_LAYER_STATE_ENABLE | defined | `keyboards/hidpress/bipedalambi/config.h` | -- | -- |

### info.json

| Property | Value | Source | Expected | Match? |
|----------|-------|--------|----------|--------|
| matrix_pins.rows | `["GP27", "GP25", "GP18", "GP17"]` (4 pins) | `keyboards/hidpress/bipedalambi/info.json` | 4 pins | YES |
| matrix_pins.cols | `["GP24", "GP23", "GP21", "GP20", "GP19", "GP26", "GP16", "NO_PIN"]` (7+1) | `keyboards/hidpress/bipedalambi/info.json` | 8 (7+NO_PIN) | YES |
| split.enabled | **true** | `keyboards/hidpress/bipedalambi/info.json` | true | YES |
| diode_direction | COL2ROW | `keyboards/hidpress/bipedalambi/info.json` | -- | -- |

### vial_left/vial.json

| Property | Value | Source | Expected | Match? |
|----------|-------|--------|----------|--------|
| matrix.rows | **4** | `keymaps/vial_left/vial.json` | **8** | **NO** |
| matrix.cols | **8** | `keymaps/vial_left/vial.json` | 8 | YES |
| "encoders" JSON key | Not present | `keymaps/vial_left/vial.json` | -- | -- |

**Left-half key positions (all rows 0-3):**

| Row | Positions | Count | Notes |
|-----|-----------|-------|-------|
| 0 | 0,0 / 0,1 / 0,2 / 0,3 / 0,4 / 0,5 / 0,7 | 7 | Col 7 = thumbstick UP |
| 1 | 1,0 / 1,1 / 1,2 / 1,3 / 1,4 / 1,5 / 1,7 | 7 | Col 7 = thumbstick DOWN |
| 2 | 2,0 / 2,1 / 2,2 / 2,3 / 2,4 / 2,5 / 2,6 / 2,7 | 8 | Col 6 = key, Col 7 = thumbstick LEFT |
| 3 | 3,1 / 3,2 / 3,3 / 3,4 / 3,5 / 3,6 / 3,7 | 7 | Col 6 = key, Col 7 = thumbstick RIGHT |
| **Total** | | **29** | 4 thumbstick at col 7, 2 extra at col 6 |

**Thumbstick positions (col 7, left-half rows 0-3 -- CORRECT range):**

| Direction | Position | Status |
|-----------|----------|--------|
| Up | 0,7 | In left-half range (row 0) -- no change needed |
| Down | 1,7 | In left-half range (row 1) -- no change needed |
| Left | 2,7 | In left-half range (row 2) -- no change needed |
| Right | 3,7 | In left-half range (row 3) -- no change needed |

### vial_right/vial.json

| Property | Value | Source | Expected | Match? |
|----------|-------|--------|----------|--------|
| matrix.rows | **4** | `keymaps/vial_right/vial.json` | **8** | **NO** |
| matrix.cols | **8** | `keymaps/vial_right/vial.json` | 8 | YES |
| "encoders" JSON key | **Yes** (1 encoder, 4 layers) | `keymaps/vial_right/vial.json` | -- | -- |

**Right-half key positions (currently rows 0-3 -- WRONG, should be 4-7):**

| Row (current) | Row (correct) | Positions (current) | Count |
|----------------|---------------|---------------------|-------|
| 0 | 4 | 0,0 / 0,1 / 0,2 / 0,3 / 0,4 / 0,5 | 6 |
| 1 | 5 | 1,0 / 1,1 / 1,2 / 1,3 / 1,4 / 1,5 | 6 |
| 2 | 6 | 2,0 / 2,1 / 2,2 / 2,3 / 2,4 / 2,5 / 2,6 | 7 |
| 3 | 7 | 3,1 / 3,2 / 3,3 / 3,4 / 3,5 / 3,6 | 6 |
| **Total** | | | **25** |

**Encoder KLE entries (with `\ne` suffix -- do NOT adjust rows):**

| Entry | Encoder Index | Direction |
|-------|---------------|-----------|
| `"0,0\n\n\n\n\n\n\n\n\ne"` | 0 | CW (display) |
| `"0,1\n\n\n\n\n\n\n\n\ne"` | 0 | CCW (display) |

**Encoders JSON key:**

| Layer | CCW | CW |
|-------|-----|-----|
| 0 | QK_KB_2 | QK_KB_1 |
| 1 | KC_TRNS | KC_TRNS |
| 2 | KC_TRNS | KC_TRNS |
| 3 | KC_TRNS | KC_TRNS |

### vial_left/config.h

| Property | Value | Source |
|----------|-------|--------|
| VIAL_KEYBOARD_UID | `{0x89, 0x4D, 0x6E, 0x12, 0x33, 0x56, 0x78, 0x90}` | `keymaps/vial_left/config.h` |
| VIAL_UNLOCK_COMBO_ROWS | { 0, 0 } | `keymaps/vial_left/config.h` |
| VIAL_UNLOCK_COMBO_COLS | { 0, 1 } | `keymaps/vial_left/config.h` |
| DYNAMIC_KEYMAP_LAYER_COUNT | 4 | `keymaps/vial_left/config.h` |
| MATRIX_ROW_PINS | { GP27, GP25, GP18, GP17 } (4 pins) | `keymaps/vial_left/config.h` |
| MATRIX_COL_PINS | { GP24, GP23, GP21, GP20, GP19, GP26, GP16, NO_PIN } (7+1) | `keymaps/vial_left/config.h` |

### vial_right/config.h

| Property | Value | Source |
|----------|-------|--------|
| VIAL_KEYBOARD_UID | `{0x89, 0x4D, 0x6E, 0x12, 0x33, 0x56, 0x78, 0x90}` | `keymaps/vial_right/config.h` |
| VIAL_UNLOCK_COMBO_ROWS | { 0, 0 } | `keymaps/vial_right/config.h` |
| VIAL_UNLOCK_COMBO_COLS | { 0, 1 } | `keymaps/vial_right/config.h` |
| DYNAMIC_KEYMAP_LAYER_COUNT | 4 | `keymaps/vial_right/config.h` |
| MATRIX_ROW_PINS | { GP0, GP11, GP25, GP26 } (4 pins) | `keymaps/vial_right/config.h` |
| MATRIX_COL_PINS | { GP1, GP2, GP3, GP4, GP5, GP10, GP27, NO_PIN } (7+1) | `keymaps/vial_right/config.h` |
| ENCODERS_PAD_A | { GP28 } (1 encoder) | `keymaps/vial_right/config.h` |
| ENCODERS_PAD_B | { GP29 } | `keymaps/vial_right/config.h` |
| ENCODER_RESOLUTION | 4 | `keymaps/vial_right/config.h` |

---

## 3. Bipedal Southpaw Sanity Check

| Property | Value | Source |
|----------|-------|--------|
| MATRIX_ROWS (config.h) | **4** | `keyboards/hidpress/bipedalsouthpaw/config.h` |
| MATRIX_COLS (config.h) | **7** | `keyboards/hidpress/bipedalsouthpaw/config.h` |
| vial.json matrix.rows | **4** | `keyboards/hidpress/bipedalsouthpaw/keymaps/vial/vial.json` |
| vial.json matrix.cols | **7** | `keyboards/hidpress/bipedalsouthpaw/keymaps/vial/vial.json` |
| **Rows match?** | **YES (4 = 4)** | Not split -- no doubling needed |
| **Cols match?** | **YES (7 = 7)** | |

The Southpaw is a non-split macropad. Its MATRIX_ROWS equals its physical row count (no doubling). Its vial.json rows match config.h MATRIX_ROWS exactly. This confirms the pattern: vial.json rows must always equal the compiled MATRIX_ROWS.

---

## 4. Research Verification

Each claim from `01-RESEARCH.md` verified against actual source file values:

| # | Research Claim | Actual Value | Source File | Verified? |
|---|----------------|--------------|-------------|-----------|
| 1 | Sofle has 5 row pins per side | 5 pins: C6, D7, E6, B4, B5 | `sofle/rev1/keyboard.json` | **PASS** |
| 2 | Sofle has 6 col pins per side | 6 pins: F6, F7, B1, B3, B2, B6 | `sofle/rev1/keyboard.json` | **PASS** |
| 3 | Sofle vial.json rows=10 | 10 | `sofle/rev1/keymaps/vial/vial.json` | **PASS** |
| 4 | Sofle vial.json cols=6 | 6 | `sofle/rev1/keymaps/vial/vial.json` | **PASS** |
| 5 | Right-half layout positions use rows 5-9 | Rows 5,6,7,8,9 confirmed in KLE | `sofle/rev1/keymaps/vial/vial.json` | **PASS** |
| 6 | VIAL_UNLOCK_COMBO_ROWS { 0, 5, 3, 8 } | { 0, 5, 3, 8 } | `sofle/rev1/keymaps/vial/config.h` | **PASS** |
| 7 | encoder_map has 2 entries per layer | 2 entries (NUM_ENCODERS=2) | `sofle/rev1/keymaps/vial/keymap.c` | **PASS** |
| 8 | encoder_map spans 4 layers | 4 layers (0-3) | `sofle/rev1/keymaps/vial/keymap.c` | **PASS** |
| 9 | No "encoders" JSON key in Sofle vial.json | Confirmed absent | `sofle/rev1/keymaps/vial/vial.json` | **PASS** |
| 10 | Ambi config.h MATRIX_ROWS=8 | 8 | `hidpress/bipedalambi/config.h` | **PASS** |
| 11 | Ambi config.h MATRIX_COLS=8 | 8 | `hidpress/bipedalambi/config.h` | **PASS** |
| 12 | Ambi info.json has 4 row pins | 4 pins: GP27, GP25, GP18, GP17 | `hidpress/bipedalambi/info.json` | **PASS** |
| 13 | Ambi info.json split.enabled=true | true | `hidpress/bipedalambi/info.json` | **PASS** |
| 14 | Ambi vial_left/vial.json rows=4 (WRONG) | 4 | `keymaps/vial_left/vial.json` | **PASS** (confirmed wrong) |
| 15 | Ambi vial_right/vial.json rows=4 (WRONG) | 4 | `keymaps/vial_right/vial.json` | **PASS** (confirmed wrong) |
| 16 | Ambi right-side layout rows currently 0-3 | Rows 0,1,2,3 confirmed | `keymaps/vial_right/vial.json` | **PASS** |
| 17 | Ambi right vial.json has "encoders" key | Present with 1 encoder, 4 layers | `keymaps/vial_right/vial.json` | **PASS** |
| 18 | Southpaw MATRIX_ROWS=4 matches vial.json rows=4 | 4=4 | `bipedalsouthpaw/config.h` + `vial.json` | **PASS** |
| 19 | Thumbstick positions at rows 0-3 col 7 | 0,7 / 1,7 / 2,7 / 3,7 confirmed | `keymaps/vial_left/vial.json` | **PASS** |

**Result: All 19 research claims PASS. No discrepancies found.**

---

## 5. Key Mismatches Summary

| Keyboard | Property | config.h / compiled | vial.json | Match? | Action |
|----------|----------|---------------------|-----------|--------|--------|
| Sofle rev1 | MATRIX_ROWS | 10 (5x2 split) | 10 | YES | None (reference) |
| Sofle rev1 | MATRIX_COLS | 6 | 6 | YES | None (reference) |
| Ambi (left) | MATRIX_ROWS | 8 (4x2 split) | **4** | **NO** | Change to 8 |
| Ambi (left) | MATRIX_COLS | 8 | 8 | YES | None |
| Ambi (right) | MATRIX_ROWS | 8 (4x2 split) | **4** | **NO** | Change to 8 |
| Ambi (right) | MATRIX_COLS | 8 | 8 | YES | None |
| Ambi (right) | Layout rows | Should be 4-7 | 0-3 | **NO** | Remap 0->4, 1->5, 2->6, 3->7 |
| Southpaw | MATRIX_ROWS | 4 (not split) | 4 | YES | None (sanity check) |
| Southpaw | MATRIX_COLS | 7 | 7 | YES | None (sanity check) |

---

*Extracted: 2026-02-13*
*Ready for Plan 02 synthesis*
