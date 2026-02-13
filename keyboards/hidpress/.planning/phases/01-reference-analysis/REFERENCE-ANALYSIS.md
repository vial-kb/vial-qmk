# Reference Analysis: Split Matrix Conventions

**Date:** 2026-02-13
**Purpose:** Structured reference document comparing Sofle rev1 Vial (known-working split) against Bipedal Ambi (broken) to establish the correct matrix conventions, identify all mismatches, and provide actionable position maps and EEPROM calculations for subsequent phases.

**Source data:** EXTRACTED-DATA.md (Plan 01 output, 13 source files)

---

## 1. Sofle rev1 Vial Reference Data

The Sofle rev1 is a split keyboard with a verified working Vial configuration from the upstream vial-qmk repository.

| Property | Value | Source File |
|----------|-------|-------------|
| Physical row pins (per side) | 5 (`C6, D7, E6, B4, B5`) | `keyboards/sofle/rev1/keyboard.json` |
| Physical col pins (per side) | 6 (`F6, F7, B1, B3, B2, B6`) | `keyboards/sofle/rev1/keyboard.json` |
| MATRIX_ROWS (compiled) | 10 (= 5 rows x 2 sides) | Derived from `keyboard.json` (QMK auto-doubles for split) |
| MATRIX_COLS (compiled) | 6 | `keyboards/sofle/rev1/keyboard.json` |
| vial.json matrix.rows | **10** | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| vial.json matrix.cols | **6** | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| **rows match? (compiled vs vial.json)** | **YES (10 = 10)** | |
| **cols match? (compiled vs vial.json)** | **YES (6 = 6)** | |
| Layout left-half rows | 0, 1, 2, 3, 4 | `keyboards/sofle/rev1/keyboard.json` layouts.LAYOUT |
| Layout right-half rows | 5, 6, 7, 8, 9 | `keyboards/sofle/rev1/keyboard.json` layouts.LAYOUT |
| Left-half key count | 30 (6 keys x 5 rows) | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| Right-half key count | 30 (6 keys x 5 rows) | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| Dynamic keymap layers | 4 | `keyboards/sofle/rev1/keymaps/vial/keymap.c` |
| Encoders (hardware) | 2 (one per side) | `keyboards/sofle/rev1/keymaps/vial/keymap.c` encoder_map |
| "encoders" JSON key in vial.json | **Not present** | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| ENCODER_MAP_ENABLE | yes | `keyboards/sofle/rev1/keymaps/vial/rules.mk` |
| VIAL_UNLOCK_COMBO_ROWS | { 0, 5, 3, 8 } | `keyboards/sofle/rev1/keymaps/vial/config.h` |

---

## 2. Bipedal Ambi Current State

The Bipedal Ambi is a split keyboard where each half builds and flashes independently. Each half has its own vial.json.

| Property | Value | Source File |
|----------|-------|-------------|
| Physical row pins (per side) | 4 (left: `GP27, GP25, GP18, GP17`; right: `GP0, GP11, GP25, GP26`) | `info.json`, `keymaps/vial_left/config.h`, `keymaps/vial_right/config.h` |
| Physical col pins (per side) | 8 (7 + NO_PIN) | `keyboards/hidpress/bipedalambi/info.json` |
| MATRIX_ROWS (config.h) | **8** (= 4 rows x 2 sides) | `keyboards/hidpress/bipedalambi/config.h` |
| MATRIX_COLS (config.h) | **8** | `keyboards/hidpress/bipedalambi/config.h` |
| split.enabled | true | `keyboards/hidpress/bipedalambi/info.json` |
| Left vial.json matrix.rows | **4** | `keymaps/vial_left/vial.json` |
| Left vial.json matrix.cols | **8** | `keymaps/vial_left/vial.json` |
| Right vial.json matrix.rows | **4** | `keymaps/vial_right/vial.json` |
| Right vial.json matrix.cols | **8** | `keymaps/vial_right/vial.json` |
| **Left rows match? (compiled vs vial.json)** | **NO (8 != 4)** | |
| **Right rows match? (compiled vs vial.json)** | **NO (8 != 4)** | |
| Left-half layout rows | 0, 1, 2, 3 | `keymaps/vial_left/vial.json` |
| Right-half layout rows (current) | 0, 1, 2, 3 | `keymaps/vial_right/vial.json` |
| Right-half layout rows (correct) | **4, 5, 6, 7** | Derived from split convention |
| Left-half key count | 29 (includes 4 thumbstick at col 7) | `keymaps/vial_left/vial.json` |
| Right-half key count | 25 (no thumbstick) | `keymaps/vial_right/vial.json` |
| Dynamic keymap layers | 4 | `keymaps/vial_left/config.h`, `keymaps/vial_right/config.h` |
| Encoders (hardware) | 1 (right side only) | `keymaps/vial_right/config.h` |
| "encoders" JSON key | Present in right vial.json only (1 encoder, 4 layers) | `keymaps/vial_right/vial.json` |
| VIAL_UNLOCK_COMBO_ROWS | { 0, 0 } (both halves) | `keymaps/vial_left/config.h`, `keymaps/vial_right/config.h` |

---

## 3. Bipedal Southpaw Validation

The Southpaw is a non-split macropad. It serves as a sanity check: for non-split boards, vial.json rows equals the physical row count directly (no doubling).

| Property | config.h | vial.json | Match? |
|----------|----------|-----------|--------|
| MATRIX_ROWS | 4 | 4 | YES |
| MATRIX_COLS | 7 | 7 | YES |

**Conclusion:** Non-split boards do NOT double. The Southpaw confirms: vial.json rows must always equal the compiled MATRIX_ROWS value. For split boards, that compiled value is already doubled.

---

## 4. Side-by-Side Comparison Table

| Property | Sofle rev1 | Ambi LEFT | Ambi RIGHT | Sofle Match? | Action Needed |
|----------|-----------|-----------|------------|--------------|---------------|
| Physical row pins | 5 | 4 | 4 | N/A (different board) | None |
| Physical col pins | 6 | 8 (7+NO_PIN) | 8 (7+NO_PIN) | N/A | None |
| MATRIX_ROWS (compiled) | 10 (5x2) | 8 (4x2) | 8 (4x2) | Pattern matches | None |
| MATRIX_COLS (compiled) | 6 | 8 | 8 | N/A | None |
| vial.json matrix.rows | **10** | **4** | **4** | **NO** | **Change to 8** |
| vial.json matrix.cols | 6 | 8 | 8 | Pattern matches | None |
| Layout left rows | 0-4 | 0-3 | -- | Pattern matches | None |
| Layout right rows | 5-9 | -- | **0-3** | **NO** | **Remap to 4-7** |
| "encoders" JSON key | Absent | Absent | Present | Partial | See Section 8 |
| ENCODER_MAP_ENABLE | yes | -- | -- | Unknown | Verify in Phase 4 |
| Layers | 4 | 4 | 4 | YES | None |
| VIAL_UNLOCK_COMBO_ROWS | {0, 5, 3, 8} | {0, 0} | {0, 0} | Different | Review (Phase 4+) |

**Key mismatches requiring action:**

1. Both vial.json files declare `rows: 4` but compiled MATRIX_ROWS is `8` -- must change to `8`
2. Right vial.json layout positions use rows 0-3 but must use rows 4-7 (right half of the doubled matrix)

---

## 5. Matrix Row Doubling Convention

### The Pattern

Split keyboards in QMK double MATRIX_ROWS so that both halves share a single logical matrix. The formula (from `quantum/matrix.c`):

```
ROWS_PER_HAND = MATRIX_ROWS / 2
```

- **Left half** occupies rows `0` to `ROWS_PER_HAND - 1`
- **Right half** occupies rows `ROWS_PER_HAND` to `MATRIX_ROWS - 1`

### Evidence: Sofle rev1

| Metric | Value | Source |
|--------|-------|--------|
| Physical row pins per side | 5 | `keyboards/sofle/rev1/keyboard.json` |
| ROWS_PER_HAND | 5 | Derived: 10 / 2 |
| MATRIX_ROWS (compiled) | 10 | QMK auto-doubles for `split.enabled` boards |
| vial.json matrix.rows | 10 | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| Left layout rows | 0, 1, 2, 3, 4 | rows 0 to 4 (= ROWS_PER_HAND - 1) |
| Right layout rows | 5, 6, 7, 8, 9 | rows 5 to 9 (= ROWS_PER_HAND to MATRIX_ROWS - 1) |

### Application to Bipedal Ambi

| Metric | Current (Wrong) | Correct | Source |
|--------|----------------|---------|--------|
| Physical row pins per side | 4 | 4 | No change |
| ROWS_PER_HAND | 4 | 4 | 8 / 2 = 4 |
| MATRIX_ROWS (config.h) | 8 | 8 | Already correct |
| vial.json matrix.rows | **4** | **8** | Must change |
| Left layout rows | 0, 1, 2, 3 | 0, 1, 2, 3 | Already correct |
| Right layout rows | **0, 1, 2, 3** | **4, 5, 6, 7** | Must remap |

### Why This Matters (EEPROM Impact)

Vial uses `matrix.rows` and `matrix.cols` from vial.json to calculate EEPROM offsets for dynamic keymap layers:

```
layer_size = rows * cols * 2 bytes
layer_N_start = base_offset + (N * layer_size)
```

When vial.json says `rows: 4` but the firmware uses `MATRIX_ROWS = 8`, Vial computes layer sizes as 64 bytes but the firmware expects 128 bytes. This causes every layer after layer 0 to be read from the wrong EEPROM address -- explaining the observed layer offset bug.

---

## 6. EEPROM Layer Size Impact

### Formula

```
layer_size = MATRIX_ROWS * MATRIX_COLS * 2 bytes
```

Each keycode occupies 2 bytes. The dynamic keymap stores `DYNAMIC_KEYMAP_LAYER_COUNT` layers contiguously in EEPROM.

### Calculation: Current (Wrong)

Vial reads `matrix.rows` and `matrix.cols` from vial.json to determine layout size:

| Parameter | Vial reads (from vial.json) | Firmware uses (from config.h) |
|-----------|---------------------------|-------------------------------|
| rows | 4 | 8 |
| cols | 8 | 8 |
| layer_size | 4 * 8 * 2 = **64 bytes** | 8 * 8 * 2 = **128 bytes** |

### Layer Offset Breakdown

| Layer | Vial writes at byte offset | Firmware reads at byte offset | Delta |
|-------|---------------------------|-------------------------------|-------|
| 0 | base + 0 | base + 0 | 0 (correct) |
| 1 | base + 64 | base + 128 | 64 bytes off |
| 2 | base + 128 | base + 256 | 128 bytes off |
| 3 | base + 192 | base + 384 | 192 bytes off |

**This explains the symptoms exactly:**
- Layer 0 works because both agree on offset 0
- Layer 1 content appears shifted because Vial writes it at byte 64 but firmware reads layer 1 at byte 128
- The "off-by-one" layer appearance (layer 1 content on layer 2) occurs because Vial's layer-1 data (bytes 64-127) overlaps with the firmware's layer-0 region (bytes 0-127)

### Calculation: Correct (After Fix)

After changing vial.json `matrix.rows` to 8:

| Parameter | Vial reads | Firmware uses | Match? |
|-----------|-----------|---------------|--------|
| rows | 8 | 8 | YES |
| cols | 8 | 8 | YES |
| layer_size | 128 bytes | 128 bytes | YES |

| Layer | Vial writes at | Firmware reads at | Delta |
|-------|---------------|-------------------|-------|
| 0 | base + 0 | base + 0 | 0 |
| 1 | base + 128 | base + 128 | 0 |
| 2 | base + 256 | base + 256 | 0 |
| 3 | base + 384 | base + 384 | 0 |

**Total dynamic keymap size:** 4 layers x 128 bytes = **512 bytes** (well within 4096-byte wear-leveling budget)

---

## 7. Encoder Configuration Comparison

### Sofle rev1 Approach

| Aspect | Value | Source |
|--------|-------|--------|
| Hardware encoders | 2 (one per side) | `keyboards/sofle/rev1/keyboard.json` split.encoder.right |
| ENCODER_MAP_ENABLE | yes | `keyboards/sofle/rev1/keymaps/vial/rules.mk` |
| "encoders" JSON key in vial.json | **Not present** | `keyboards/sofle/rev1/keymaps/vial/vial.json` |
| encoder_map in keymap.c | Present (4 layers, 2 encoders each) | `keyboards/sofle/rev1/keymaps/vial/keymap.c` |
| Default encoder actions | All KC_TRNS | `keyboards/sofle/rev1/keymaps/vial/keymap.c` |
| Encoder KLE entries in vial.json | 4 entries with `\ne` suffix (encoder indices 0-1, CW/CCW) | `keyboards/sofle/rev1/keymaps/vial/vial.json` |

**Sofle uses `ENCODER_MAP_ENABLE` + `encoder_map[][]` in keymap.c.** Vial detects encoder support via the encoder KLE entries (strings ending with `\ne`) in the layout definition. No separate "encoders" JSON key is needed.

### Bipedal Ambi Approach

| Aspect | Value | Source |
|--------|-------|--------|
| Hardware encoders | 1 (right side only) | `keymaps/vial_right/config.h` ENCODERS_PAD_A/B |
| ENCODER_MAP_ENABLE | Unknown (needs Phase 4 check) | `keymaps/vial_right/rules.mk` |
| "encoders" JSON key in vial.json | **Present** (1 encoder, 4 layers) | `keymaps/vial_right/vial.json` |
| Encoder KLE entries in vial.json | 2 entries with `\ne` suffix (encoder index 0, CW/CCW) | `keymaps/vial_right/vial.json` |
| Default encoder actions (from JSON) | Layer 0: QK_KB_2/QK_KB_1; Layers 1-3: KC_TRNS | `keymaps/vial_right/vial.json` |

### Key Difference

| Feature | Sofle | Ambi Right | Implication |
|---------|-------|------------|-------------|
| "encoders" JSON key | Absent | Present | Ambi uses an older/alternative Vial encoder config style |
| encoder_map in keymap.c | Present | Needs verification | If Ambi uses "encoders" JSON key, encoder_map may not be used |
| Encoder count | 2 | 1 | Different hardware -- expected |

**What must stay the same:** The encoder KLE entries in vial.json define display positions for the encoder actions. These entries use encoder indices (0,0 and 0,1 for CW/CCW), NOT matrix row/col numbers. **Do NOT adjust row numbers in encoder KLE entries during the right-half row remapping.**

**What requires Phase 4 investigation:** Whether the "encoders" JSON key approach or the ENCODER_MAP_ENABLE approach is correct for the Ambi, and whether they conflict or complement each other.

---

## 8. Right-Half Layout Position Map

This is the complete line-by-line change map for the right vial.json layout positions. Every position string in the right-half KLE layout is listed with its current (wrong) and target (correct) row number.

**Rule:** Right-half rows must be offset by ROWS_PER_HAND (4). New row = current row + 4. Columns remain unchanged.

### Key Positions (rows must change)

| # | Current Position | Target Position | Current Row | Target Row | Col | Notes |
|---|-----------------|-----------------|-------------|------------|-----|-------|
| 1 | 0,0 | 4,0 | 0 | 4 | 0 | |
| 2 | 0,1 | 4,1 | 0 | 4 | 1 | |
| 3 | 0,2 | 4,2 | 0 | 4 | 2 | |
| 4 | 0,3 | 4,3 | 0 | 4 | 3 | |
| 5 | 0,4 | 4,4 | 0 | 4 | 4 | |
| 6 | 0,5 | 4,5 | 0 | 4 | 5 | |
| 7 | 1,0 | 5,0 | 1 | 5 | 0 | |
| 8 | 1,1 | 5,1 | 1 | 5 | 1 | |
| 9 | 1,2 | 5,2 | 1 | 5 | 2 | |
| 10 | 1,3 | 5,3 | 1 | 5 | 3 | |
| 11 | 1,4 | 5,4 | 1 | 5 | 4 | |
| 12 | 1,5 | 5,5 | 1 | 5 | 5 | |
| 13 | 2,0 | 6,0 | 2 | 6 | 0 | |
| 14 | 2,1 | 6,1 | 2 | 6 | 1 | |
| 15 | 2,2 | 6,2 | 2 | 6 | 2 | |
| 16 | 2,3 | 6,3 | 2 | 6 | 3 | |
| 17 | 2,4 | 6,4 | 2 | 6 | 4 | |
| 18 | 2,5 | 6,5 | 2 | 6 | 5 | |
| 19 | 2,6 | 6,6 | 2 | 6 | 6 | |
| 20 | 3,1 | 7,1 | 3 | 7 | 1 | |
| 21 | 3,2 | 7,2 | 3 | 7 | 2 | |
| 22 | 3,3 | 7,3 | 3 | 7 | 3 | |
| 23 | 3,4 | 7,4 | 3 | 7 | 4 | |
| 24 | 3,5 | 7,5 | 3 | 7 | 5 | |
| 25 | 3,6 | 7,6 | 3 | 7 | 6 | |

**Total key positions to remap:** 25

### Encoder KLE Entries (DO NOT change rows)

| Entry | Current | After Fix | Change? |
|-------|---------|-----------|---------|
| `"0,0\n\n\n\n\n\n\n\n\ne"` | encoder 0, CW | encoder 0, CW | **NO** -- encoder index, not matrix row |
| `"0,1\n\n\n\n\n\n\n\n\ne"` | encoder 0, CCW | encoder 0, CCW | **NO** -- encoder index, not matrix row |

**Critical:** The `\ne` suffix marks these as encoder entries. The numbers before the comma are encoder indices, not row numbers. They must NOT be incremented by 4.

### Summary by Row

| Current Row | Target Row | Key Count | Positions |
|-------------|------------|-----------|-----------|
| 0 | 4 | 6 | cols 0-5 |
| 1 | 5 | 6 | cols 0-5 |
| 2 | 6 | 7 | cols 0-6 |
| 3 | 7 | 6 | cols 1-6 (no col 0) |
| **Total** | | **25** | |

---

## 9. Thumbstick Position Verification

The left half has a 4-direction thumbstick mapped to matrix positions at column 7 (the NO_PIN column, used for virtual key positions).

| Direction | Position | Row | Col | In Left-Half Range? | Change Needed? |
|-----------|----------|-----|-----|---------------------|----------------|
| Up | 0,7 | 0 | 7 | YES (row 0, left range 0-3) | **NO** |
| Down | 1,7 | 1 | 7 | YES (row 1, left range 0-3) | **NO** |
| Left | 2,7 | 2 | 7 | YES (row 2, left range 0-3) | **NO** |
| Right | 3,7 | 3 | 7 | YES (row 3, left range 0-3) | **NO** |

**Conclusion:** All 4 thumbstick positions are in the left half's row range (0-3). Since left-half layout rows remain at 0-3 after the fix, these positions are unaffected. No changes needed.

The thumbstick uses `matrix_scan_user()` to inject key events at these virtual positions. The positions must match the KLE layout entries in the left vial.json. Since neither the left vial.json layout rows nor the `matrix_scan_user()` code changes, the thumbstick will continue to work correctly after the fix.

---

*Reference analysis complete. This document is self-contained: all values are sourced, all calculations shown, and all position changes enumerated. Subsequent phases should cite this document rather than re-reading source files.*
