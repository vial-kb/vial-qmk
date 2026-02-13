# Fix Checklist: Bipedal Ambi EEPROM / Vial Layer Fix

**Date:** 2026-02-13
**Derived from:** [REFERENCE-ANALYSIS.md](./REFERENCE-ANALYSIS.md) (Plan 02 output)
**Purpose:** Actionable checklist for every subsequent phase. Each item is concrete enough that Phase 2-8 executors never need to re-read Sofle source files or re-derive conventions.

---

## Status Legend

- `[ ]` = Not yet done
- `[x]` = Completed in a specific phase (phase noted in item)
- `[~]` = Already correct, no change needed (verified against reference)

---

## Phase 1: Reference Analysis

**Requirements:** MTRX-04, XVAL-03

- [x] **MTRX-04:** Sofle rev1 Vial keymap cross-referenced as known-working split baseline
  - File: `keyboards/sofle/rev1/keymaps/vial/vial.json`, `keyboards/sofle/rev1/keyboard.json`
  - Evidence: REFERENCE-ANALYSIS.md Section 1 -- Sofle `vial.json matrix.rows = 10` matches compiled `MATRIX_ROWS = 10` (5 physical rows x 2 sides)
  - Completed in: Plan 01-02

- [x] **XVAL-03:** Sofle rev1 configuration compared as known-working reference for split row-doubling convention
  - File: REFERENCE-ANALYSIS.md Sections 1, 4, 5
  - Evidence: Side-by-side comparison table (Section 4) confirms pattern: `vial.json rows` must equal `physical_rows x 2` for split boards. Sofle left rows 0-4, right rows 5-9. Bipedal Southpaw (non-split) confirms no doubling for non-split (Section 3).
  - Completed in: Plans 01-01, 01-02

---

## Phase 2: Matrix Dimension Audit

**Requirements:** XVAL-01, MTRX-03

- [ ] **XVAL-01:** Create cross-reference table showing all matrix dimension sources and their values
  - Sources to compare: `config.h` MATRIX_ROWS/COLS, `info.json` matrix_pins row/col counts, left `vial.json` rows/cols, right `vial.json` rows/cols, LAYOUT macro dimensions
  - Expected values: MATRIX_ROWS=8, MATRIX_COLS=8, info.json rows=4 (physical pins per side), left vial.json rows=4 (WRONG, should be 8), right vial.json rows=4 (WRONG, should be 8)
  - File: `keyboards/hidpress/bipedalambi/config.h` (MATRIX_ROWS=8, MATRIX_COLS=8)
  - File: `keyboards/hidpress/bipedalambi/info.json` (matrix_pins defines 4 rows of pins per side)
  - File: `keymaps/vial_left/vial.json` (matrix.rows=4, matrix.cols=8)
  - File: `keymaps/vial_right/vial.json` (matrix.rows=4, matrix.cols=8)
  - Reference: REFERENCE-ANALYSIS.md Section 2 (Bipedal Ambi Current State), Section 4 (Side-by-Side Comparison)

- [ ] **MTRX-03:** Flag every disagreement between dimension sources with expected correct value
  - Disagreement 1: Left vial.json `rows: 4` vs config.h `MATRIX_ROWS: 8` -- must change vial.json to 8
  - Disagreement 2: Right vial.json `rows: 4` vs config.h `MATRIX_ROWS: 8` -- must change vial.json to 8
  - Reference: REFERENCE-ANALYSIS.md Section 4, "Key mismatches requiring action" items 1-2

- [~] **XVAL-01 (partial):** Confirm info.json dimensions agree with config.h
  - File: `keyboards/hidpress/bipedalambi/info.json`
  - Current: info.json defines 4 physical row pins and 8 col pins (7 + NO_PIN) per side
  - Expected: config.h MATRIX_ROWS=8 (= 4 physical x 2 for split), MATRIX_COLS=8 -- this is correct, QMK auto-doubles the row count from info.json physical pins for split boards
  - Reference: REFERENCE-ANALYSIS.md Section 2, Section 5 (Matrix Row Doubling Convention)

- [ ] **MTRX-03 (partial):** Verify LAYOUT macro accepts 8 rows
  - File: `keyboards/hidpress/bipedalambi/info.json` (layouts.LAYOUT definition) or `bipedalambi.h`
  - Check: LAYOUT macro must define key positions spanning rows 0-7 (left 0-3, right 4-7)
  - Reference: REFERENCE-ANALYSIS.md Section 5 (Application to Bipedal Ambi)

---

## Phase 3: vial.json Matrix Fix

**Requirements:** MTRX-01, MTRX-02

- [ ] **MTRX-01:** Change left vial.json `"rows": 4` to `"rows": 8`
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_left/vial.json`
  - Current value: `"rows": 4`
  - Target value: `"rows": 8`
  - Rationale: Must match config.h MATRIX_ROWS=8 so Vial computes correct layer sizes (128 bytes, not 64)
  - Reference: REFERENCE-ANALYSIS.md Section 4 (vial.json matrix.rows row, Action: "Change to 8"), Section 6 (EEPROM Layer Size Impact)

- [ ] **MTRX-01:** Change right vial.json `"rows": 4` to `"rows": 8`
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json`
  - Current value: `"rows": 4`
  - Target value: `"rows": 8`
  - Rationale: Same as left -- must match config.h MATRIX_ROWS=8
  - Reference: REFERENCE-ANALYSIS.md Section 4

- [ ] **MTRX-02:** Update right vial.json layout positions -- every key position row must change from R to R+4
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json`
  - Complete position change map (from REFERENCE-ANALYSIS.md Section 8):

  | # | Current Position | Target Position | Row Change |
  |---|-----------------|-----------------|------------|
  | 1 | `"0,0"` | `"4,0"` | 0 -> 4 |
  | 2 | `"0,1"` | `"4,1"` | 0 -> 4 |
  | 3 | `"0,2"` | `"4,2"` | 0 -> 4 |
  | 4 | `"0,3"` | `"4,3"` | 0 -> 4 |
  | 5 | `"0,4"` | `"4,4"` | 0 -> 4 |
  | 6 | `"0,5"` | `"4,5"` | 0 -> 4 |
  | 7 | `"1,0"` | `"5,0"` | 1 -> 5 |
  | 8 | `"1,1"` | `"5,1"` | 1 -> 5 |
  | 9 | `"1,2"` | `"5,2"` | 1 -> 5 |
  | 10 | `"1,3"` | `"5,3"` | 1 -> 5 |
  | 11 | `"1,4"` | `"5,4"` | 1 -> 5 |
  | 12 | `"1,5"` | `"5,5"` | 1 -> 5 |
  | 13 | `"2,0"` | `"6,0"` | 2 -> 6 |
  | 14 | `"2,1"` | `"6,1"` | 2 -> 6 |
  | 15 | `"2,2"` | `"6,2"` | 2 -> 6 |
  | 16 | `"2,3"` | `"6,3"` | 2 -> 6 |
  | 17 | `"2,4"` | `"6,4"` | 2 -> 6 |
  | 18 | `"2,5"` | `"6,5"` | 2 -> 6 |
  | 19 | `"2,6"` | `"6,6"` | 2 -> 6 |
  | 20 | `"3,1"` | `"7,1"` | 3 -> 7 |
  | 21 | `"3,2"` | `"7,2"` | 3 -> 7 |
  | 22 | `"3,3"` | `"7,3"` | 3 -> 7 |
  | 23 | `"3,4"` | `"7,4"` | 3 -> 7 |
  | 24 | `"3,5"` | `"7,5"` | 3 -> 7 |
  | 25 | `"3,6"` | `"7,6"` | 3 -> 7 |

  **Total:** 25 key positions remapped
  - Reference: REFERENCE-ANALYSIS.md Section 8 (Right-Half Layout Position Map)

- [~] **MTRX-02 (verified):** Left vial.json layout positions DO NOT change
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_left/vial.json`
  - Left-half rows 0-3 are already correct for the left half of the split matrix
  - Reference: REFERENCE-ANALYSIS.md Section 5 (left layout rows: 0, 1, 2, 3 -- already correct)

- [~] **MTRX-02 (verified):** Encoder display entries (with `\ne` suffix) DO NOT change row numbers
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json`
  - Entries: `"0,0\n\n\n\n\n\n\n\n\ne"` and `"0,1\n\n\n\n\n\n\n\n\ne"` use encoder index/direction, NOT matrix row numbers
  - Reference: REFERENCE-ANALYSIS.md Section 8 (Encoder KLE Entries table: "NO -- encoder index, not matrix row")

- [~] **MTRX-05 (verified):** Thumbstick positions in left vial.json DO NOT change
  - Positions: (0,7), (1,7), (2,7), (3,7) -- rows 0-3, col 7
  - Already within left-half row range (0-3), no adjustment needed
  - Reference: REFERENCE-ANALYSIS.md Section 9 (Thumbstick Position Verification)

- [ ] **MTRX-01 (verify):** `"cols": 8` remains unchanged in both vial.json files
  - File: `keymaps/vial_left/vial.json` -- current cols=8, must stay 8
  - File: `keymaps/vial_right/vial.json` -- current cols=8, must stay 8
  - Reference: REFERENCE-ANALYSIS.md Section 2 (MATRIX_COLS=8 in config.h, cols=8 in both vial.json)

---

## Phase 4: Peripheral Matrix Mapping

**Requirements:** MTRX-05, MTRX-06

- [~] **MTRX-05:** Verify left-half thumbstick positions (0,7), (1,7), (2,7), (3,7) are within rows 0-3 range
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_left/vial.json`
  - Current: Row 0 col 7, row 1 col 7, row 2 col 7, row 3 col 7
  - Status: Already correct -- all within left-half row range 0-3
  - Reference: REFERENCE-ANALYSIS.md Section 9

- [ ] **MTRX-06:** Verify right-half encoder display positions in KLE are NOT adjusted during row remapping
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json`
  - Encoder KLE entries: `"0,0\n\n\n\n\n\n\n\n\ne"` and `"0,1\n\n\n\n\n\n\n\n\ne"`
  - Rule: These use encoder index (0) and direction (0=CW, 1=CCW), NOT matrix row/col. Must NOT be changed.
  - Reference: REFERENCE-ANALYSIS.md Section 7 (Key Difference) and Section 8 (Encoder KLE Entries)

- [ ] **MTRX-06:** Investigate encoder_map dimension mismatch
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_right/keymap.c`
  - Issue: Right-side keymap.c defines 1 encoder entry per layer but split config implies NUM_ENCODERS=2 (QMK doubles for split). Determine if this compiles without error and whether it causes incorrect EEPROM sizing.
  - Reference: REFERENCE-ANALYSIS.md Section 7 (Bipedal Ambi Approach -- "ENCODER_MAP_ENABLE: Unknown (needs Phase 4 check)")
  - Possible fix: Add a second dummy encoder entry per layer OR define `ENCODER_ENCODERS_PAD_A_RIGHT` to set NUM_ENCODERS_RIGHT=0

- [ ] **MTRX-06:** If encoder_map mismatch is confirmed as a problem, apply the appropriate fix
  - Options: (a) Add second dummy encoder entry per layer in keymap.c, (b) Define encoder pin config to set NUM_ENCODERS_RIGHT=0
  - Decision deferred to Phase 4 execution

- [ ] **MTRX-06:** Verify "encoders" key in right vial.json is preserved unchanged
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json`
  - The "encoders" JSON key defines encoder actions per layer -- it must not be removed or modified during the row fix
  - Reference: REFERENCE-ANALYSIS.md Section 7 (Ambi uses "encoders" JSON key, different from Sofle approach)
