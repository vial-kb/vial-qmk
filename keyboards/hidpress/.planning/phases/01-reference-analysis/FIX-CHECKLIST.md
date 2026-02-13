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

---

## Phase 5: EEPROM Budget Verification

**Requirements:** EEPR-04, XVAL-02

- [ ] **EEPR-04:** Calculate dynamic keymap region size
  - Formula: `DYNAMIC_KEYMAP_EEPROM_ADDR + (4 layers * 8 rows * 8 cols * 2 bytes) = base + 512 bytes`
  - File: vial-qmk fork `quantum/dynamic_keymap.c` (verify formula against source, NOT upstream QMK docs)
  - Reference: REFERENCE-ANALYSIS.md Section 6 (Calculation: Correct -- layer_size=128, total=512)

- [ ] **EEPR-04:** Calculate encoder map region size
  - Formula: `VIAL_ENCODERS_EEPROM_ADDR + (2 encoders * 4 layers * 2 directions * 2 bytes) = +32 bytes`
  - Note: NUM_ENCODERS may be 2 (split doubling) even though only 1 physical encoder exists -- verify in Phase 4 first
  - File: vial-qmk fork `keyboards/vial/vial.c` or `quantum/encoder_map.c`

- [ ] **EEPR-04:** Calculate total EEPROM usage and confirm < 4096 bytes
  - Budget: eeconfig (~14 bytes) + VIA magic (~4 bytes) + layout options (~4 bytes) + dynamic keymap (512 bytes) + encoder map (32 bytes) + dynamic macros (remaining)
  - Total must fit within 4096-byte RP2040 wear-leveling logical size
  - Reference: REFERENCE-ANALYSIS.md Section 6 ("well within 4096-byte wear-leveling budget")

- [ ] **XVAL-02:** Verify eeconfig_user region does not overlap with VIA/dynamic keymap region
  - eeconfig_user region: bytes ~14-17 (4 bytes, via `eeconfig_read_user()` / `eeconfig_update_user()`)
  - VIA dynamic keymap region: starts at ~byte 50 (after eeconfig + VIA magic + layout options)
  - Gap: ~33 bytes between end of eeconfig_user and start of dynamic keymap -- no overlap expected
  - File: vial-qmk fork `tmk_core/protocol/chibios/eeprom_driver.c` or `quantum/eeconfig.h` for region definitions

- [ ] **XVAL-02:** All EEPROM calculations must use vial-qmk fork source (dynamic_keymap.c), not upstream QMK docs
  - Rationale: Vial fork may differ from upstream QMK in EEPROM layout and address calculations
  - File: `quantum/dynamic_keymap.c` in the vial-qmk repo (not docs.qmk.fm)

---

## Phase 6: Defensive EEPROM Improvements

**Requirements:** DFNS-01, DFNS-02, EEPR-01

- [ ] **DFNS-01:** Add `eeconfig_init_user()` to both keymap.c files with sane defaults
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_left/keymap.c`
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_right/keymap.c`
  - Defaults to set: actuation_index=2 (middle sensitivity), layer_modes=defaults
  - Purpose: After EEPROM clear, keyboard boots with sane defaults without requiring Vial reconfiguration
  - Reference: PROJECT.md constraint ("After EEPROM clear, keyboard boots with sane defaults")

- [ ] **DFNS-02:** Add QK_CLEAR_EEPROM keycode to at least one layer in both keymaps
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_left/keymap.c`
  - File: `keyboards/hidpress/bipedalambi/keymaps/vial_right/keymap.c`
  - Placement: Accessible layer position that doesn't conflict with normal use
  - Purpose: User can clear EEPROM without needing Bootmagic Lite or external tools

- [ ] **EEPR-01:** Document EEPROM clear procedure for both halves
  - Must document: which keycode to press (or which hold-on-boot sequence), expected behavior after clear, whether Vial reconfiguration is needed
  - Both halves must be documented independently (they flash and clear separately)

---

## Phase 7: Build and Flash

**Requirements:** None new (enables verification of EEPR-02, EEPR-03)

- [ ] `make hidpress/bipedalambi:vial_left` compiles without errors
  - File: All files in `keyboards/hidpress/bipedalambi/` and `keymaps/vial_left/`
  - Note: Compilation is Claude's task; user only handles physical flashing

- [ ] `make hidpress/bipedalambi:vial_right` compiles without errors
  - File: All files in `keyboards/hidpress/bipedalambi/` and `keymaps/vial_right/`

- [ ] EEPROM cleared on left half (mandatory after vial.json dimension change)
  - Method: QK_CLEAR_EEPROM keycode (added in Phase 6) or Bootmagic Lite hold-on-boot
  - **This is a physical user action** -- Claude documents the procedure, user executes

- [ ] EEPROM cleared on right half (mandatory after vial.json dimension change)
  - Method: Same as left half, executed independently
  - **This is a physical user action**

- [ ] Both halves flashed with new firmware
  - **This is a physical user action** -- Claude provides the .uf2 files and procedure

---

## Phase 8: End-to-End Verification

**Requirements:** EEPR-02, EEPR-03

- [ ] **EEPR-02:** All 4 layers visible in Vial when connected to either half
  - Test: Plug in left half via USB, open Vial, verify layers 0-3 are visible and editable
  - Test: Plug in right half via USB, open Vial, verify layers 0-3 are visible and editable
  - **This is a physical user verification**

- [ ] **EEPR-02:** Layer 1 content appears on layer 1 (not shifted to layer 2)
  - Test: Set a distinctive keycode (e.g., KC_A) on layer 1 in Vial, switch to layer 1, verify KC_A appears where placed
  - Expected: No off-by-one shift -- layer N content appears on layer N
  - **This is a physical user verification**

- [ ] **EEPR-03:** KC_TRNS displays on layers 1 and 3 (not layers 2 and 4)
  - Test: View layers 1 and 3 in Vial -- transparent keys should show as KC_TRNS (down arrow icon)
  - Expected: Layers 1 and 3 show KC_TRNS for unassigned keys (standard QMK pattern)
  - **This is a physical user verification**

- [ ] **EEPR-03:** Keycodes set in Vial persist after power cycle on both halves
  - Test: Set a keycode in Vial, unplug keyboard, replug, reopen Vial, verify keycode persists
  - Test on both halves independently
  - **This is a physical user verification**

- [ ] Both halves respond correctly to key presses on all layers
  - Test: Press physical keys on each layer, verify correct keycode output
  - Test: Verify layer switching works (MO(), TG(), etc.)
  - **This is a physical user verification**

---

## Critical Constraints (Apply to ALL Phases)

These constraints are repeated from CONTEXT.md decisions and must be honored in every phase:

1. **DO NOT break existing working features:**
   - OLED display and layer state display
   - Actuation level system and actuation value display
   - Screensaver animation
   - Joystick modes (left half)
   - Encoder functionality (right half)

2. **vial.json position integrity:**
   - Any vial.json changes must maintain existing thumbstick matrix positions (rows 0-3, col 7 in left vial.json)
   - Encoder display positions use encoder_index/direction numbering, NOT matrix row numbers
   - The "encoders" JSON key in right vial.json must be preserved

3. **Scope boundaries:**
   - Only modify files in `keyboards/hidpress/bipedalambi/`
   - Do NOT modify Bipedal Southpaw firmware (reference only)
   - Do NOT modify upstream Sofle files (reference only)
   - This is a bug fix project -- no new features

---

## Quick Reference Values

A single table of key numbers for copy-paste in later phases:

| Value | Number | Source |
|-------|--------|--------|
| MATRIX_ROWS | 8 | `config.h` |
| MATRIX_COLS | 8 | `config.h` |
| ROWS_PER_HAND | 4 | 8 / 2 (split) |
| Left-half rows | 0-3 | Standard split convention |
| Right-half rows | 4-7 | ROWS_PER_HAND to MATRIX_ROWS - 1 |
| Layer count | 4 | DYNAMIC_KEYMAP_LAYER_COUNT |
| Layer size (bytes) | 128 | 8 * 8 * 2 |
| Total keymap EEPROM | 512 | 128 * 4 |
| Encoder EEPROM | 32 | 2 encoders * 4 layers * 2 directions * 2 bytes |
| Left key count | 29 | 25 regular + 4 thumbstick (col 7) |
| Right key count | 25 | No thumbstick |
| Right encoder KLE entries | 2 | CW (0,0) and CCW (0,1) with `\ne` suffix |
| EEPROM total budget | < 4096 | RP2040 wear-leveling logical size |

---

## Requirement Coverage Matrix

Every requirement ID must appear at least once in this checklist. Verification:

| Requirement | Phase(s) | Status |
|-------------|----------|--------|
| MTRX-01 | Phase 3 | Covered -- rows change + cols verify |
| MTRX-02 | Phase 3 | Covered -- right-half position remap (25 keys) |
| MTRX-03 | Phase 2 | Covered -- disagreement flagging |
| MTRX-04 | Phase 1 | Covered -- Sofle cross-reference (completed) |
| MTRX-05 | Phase 3, Phase 4 | Covered -- thumbstick verification (already correct) |
| MTRX-06 | Phase 4 | Covered -- encoder display, encoder_map investigation, "encoders" key preservation |
| EEPR-01 | Phase 6 | Covered -- EEPROM clear documentation |
| EEPR-02 | Phase 8 | Covered -- layer visibility and content verification |
| EEPR-03 | Phase 8 | Covered -- persistence and KC_TRNS verification |
| EEPR-04 | Phase 5 | Covered -- EEPROM budget calculation |
| DFNS-01 | Phase 6 | Covered -- eeconfig_init_user with defaults |
| DFNS-02 | Phase 6 | Covered -- QK_CLEAR_EEPROM keycode |
| XVAL-01 | Phase 2 | Covered -- cross-reference table |
| XVAL-02 | Phase 5 | Covered -- eeconfig_user overlap check + vial-qmk source verification |
| XVAL-03 | Phase 1 | Covered -- Sofle comparison (completed) |

**All 15 requirements covered. No gaps.**

---

## Scope Validation

**No scope creep detected:**

- No items add new features (all items fix the matrix dimension mismatch or add defensive measures for the fix)
- No items modify files outside `keyboards/hidpress/bipedalambi/`
- No items touch the Bipedal Southpaw firmware (referenced only in Phase 1 for validation)
- No items modify OLED, joystick modes, or screensaver code
- All items trace back to the 15 project requirements defined in PROJECT.md and ROADMAP.md

---

*Fix checklist complete. This document is the primary deliverable of Phase 1 and the source of truth for Phases 2-8.*
