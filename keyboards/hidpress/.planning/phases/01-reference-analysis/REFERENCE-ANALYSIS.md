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
