# Roadmap: Bipedal Ambi EEPROM / Vial Layer Fix

## Overview

This roadmap fixes the confirmed matrix dimension mismatch (vial.json rows=4 vs config.h MATRIX_ROWS=8) that causes layer offset bugs in the Bipedal Ambi split keyboard. The work progresses from reference analysis through surgical configuration fixes, defensive improvements, and rigorous per-half verification. Every phase produces an observable, verifiable outcome before proceeding to the next.

## Phases

**Phase Numbering:**
- Integer phases (1, 2, 3): Planned milestone work
- Decimal phases (2.1, 2.2): Urgent insertions (marked with INSERTED)

Decimal phases appear between their surrounding integers in numeric order.

- [x] **Phase 1: Reference Analysis** - Cross-reference Sofle rev1 Vial split configuration as known-working baseline
- [ ] **Phase 2: Matrix Dimension Audit** - Document current state of all dimension sources and identify every disagreement
- [ ] **Phase 3: vial.json Matrix Fix** - Fix rows mismatch and right-half layout positions in both vial.json files
- [ ] **Phase 4: Peripheral Matrix Mapping** - Verify and fix thumbstick and encoder matrix positions in vial.json
- [ ] **Phase 5: EEPROM Budget Verification** - Calculate complete EEPROM address map and confirm no region overlaps
- [ ] **Phase 6: Defensive EEPROM Improvements** - Add eeconfig_init_user defaults and QK_CLEAR_EEPROM keycode
- [ ] **Phase 7: Build and Flash** - Compile both halves, clear EEPROM on both halves, flash firmware
- [ ] **Phase 8: End-to-End Verification** - Verify all layers, persistence, and KC_TRNS placement in Vial GUI

## Phase Details

### Phase 1: Reference Analysis
**Goal**: Establish Sofle rev1 Vial keymap as the known-working reference for split matrix conventions in vial-qmk
**Depends on**: Nothing (first phase)
**Requirements**: MTRX-04, XVAL-03
**Success Criteria** (what must be TRUE):
  1. Sofle rev1 Vial config.h MATRIX_ROWS value is documented alongside its vial.json rows value, confirming they match
  2. Sofle rev1 vial.json layout positions for the right half are documented, showing which row numbers the right side uses
  3. Sofle rev1 encoder mapping in vial.json is documented as reference for the Bipedal Ambi right-half encoder
  4. A clear list of "what Sofle does that Bipedal Ambi must also do" exists as a checklist for subsequent phases
**Plans:** 3 plans

Plans:
- [x] 01-01-PLAN.md -- Extract raw values from all Sofle + Ambi source files into EXTRACTED-DATA.md
- [x] 01-02-PLAN.md -- Synthesize REFERENCE-ANALYSIS.md with comparison tables, position maps, and EEPROM calculations
- [x] 01-03-PLAN.md -- Derive fix checklist from reference analysis, cross-validate against all 15 requirements

### Phase 2: Matrix Dimension Audit
**Goal**: Every source of matrix dimensions (config.h, info.json, vial.json, LAYOUT macro) is documented in a single cross-reference table showing current values and disagreements
**Depends on**: Phase 1
**Requirements**: XVAL-01, MTRX-03
**Success Criteria** (what must be TRUE):
  1. A cross-reference table exists showing config.h MATRIX_ROWS, config.h MATRIX_COLS, info.json dimensions, left vial.json rows/cols, right vial.json rows/cols, and LAYOUT macro row/col counts
  2. Every disagreement between sources is explicitly flagged with the expected correct value (derived from Phase 1 reference)
  3. info.json matrix dimensions agree with config.h (or the required fix is documented if they disagree)
**Plans:** 1 plan

Plans:
- [ ] 02-01-PLAN.md -- Extract all dimension values from source files and create cross-reference table with disagreement flags

### Phase 3: vial.json Matrix Fix
**Goal**: Both vial.json files declare rows=8 to match config.h MATRIX_ROWS, and the right-half layout positions reference rows 4-7
**Depends on**: Phase 2
**Requirements**: MTRX-01, MTRX-02
**Success Criteria** (what must be TRUE):
  1. Left vial.json declares "rows": 8 and "cols": 8, matching config.h MATRIX_ROWS=8 and MATRIX_COLS=8
  2. Right vial.json declares "rows": 8 and "cols": 8, matching config.h
  3. Right vial.json layout positions use rows 4-7 (not 0-3) for the right half's physical keys, following the split keyboard convention confirmed in Phase 1
  4. Left vial.json layout positions remain on rows 0-3 for the left half's physical keys
**Plans**: TBD

Plans:
- [ ] 03-01: Fix left vial.json matrix dimensions
- [ ] 03-02: Fix right vial.json matrix dimensions and layout row positions

### Phase 4: Peripheral Matrix Mapping
**Goal**: Thumbstick (left half, col 7) and encoder (right half) matrix positions are correctly represented in vial.json
**Depends on**: Phase 3
**Requirements**: MTRX-05, MTRX-06
**Success Criteria** (what must be TRUE):
  1. Left vial.json includes thumbstick positions at rows 0-3, col 7 (matching the dynamic keymap positions used by matrix_scan_user for custom keys mode)
  2. Right vial.json encoder mapping references valid matrix positions within the 8-row matrix bounds
  3. Both peripheral mappings are cross-referenced against Sofle rev1 encoder mapping conventions from Phase 1
**Plans**: TBD

Plans:
- [ ] 04-01: Verify and fix thumbstick matrix positions in left vial.json
- [ ] 04-02: Verify and fix encoder matrix positions in right vial.json

### Phase 5: EEPROM Budget Verification
**Goal**: Complete EEPROM address map is calculated and documented, confirming no region overlaps and total usage fits within 4096-byte wear-leveling allocation
**Depends on**: Phase 3
**Requirements**: EEPR-04, XVAL-02
**Success Criteria** (what must be TRUE):
  1. A documented EEPROM address map shows byte ranges for: eeconfig block, VIA magic, layout options, dynamic keymap (with corrected 8-row calculation), encoder map, and dynamic macros
  2. Total EEPROM usage is calculated and confirmed to be less than 4096 bytes (the RP2040 wear-leveling logical size)
  3. The eeconfig_user region (bytes ~14-17) is confirmed to not overlap with VIA/dynamic keymap regions (starting at ~byte 50)
  4. All address calculations are verified against vial-qmk fork source code (dynamic_keymap.c), not upstream QMK/VIA documentation alone
**Plans**: TBD

Plans:
- [ ] 05-01: Calculate EEPROM address map from vial-qmk source
- [ ] 05-02: Document address ranges and verify no overlaps

### Phase 6: Defensive EEPROM Improvements
**Goal**: EEPROM clear is safe and recoverable -- defaults are restored automatically, and the user has a keymap shortcut to trigger EEPROM clear
**Depends on**: Phase 5
**Requirements**: DFNS-01, DFNS-02, EEPR-01
**Success Criteria** (what must be TRUE):
  1. Both keymap.c files (vial_left and vial_right) implement eeconfig_init_user() that sets actuation_index=2 and layer_modes to defaults on EEPROM reset
  2. At least one layer in the keymap includes a QK_CLEAR_EEPROM key, accessible without needing Bootmagic Lite
  3. EEPROM clear procedure is documented for both halves independently (which key to hold, or which keycode to press, and the expected behavior after clear)
  4. After EEPROM clear, the keyboard boots with sane defaults (middle actuation sensitivity, mouse mode) without requiring Vial reconfiguration
**Plans**: TBD

Plans:
- [ ] 06-01: Implement eeconfig_init_user in both keymap.c files
- [ ] 06-02: Add QK_CLEAR_EEPROM keycode and document clear procedure

### Phase 7: Build and Flash
**Goal**: Both halves compile cleanly with all fixes applied, EEPROM is cleared on both halves, and new firmware is flashed
**Depends on**: Phase 4, Phase 6
**Requirements**: (No new requirements -- this phase enables verification of EEPR-02 and EEPR-03)
**Success Criteria** (what must be TRUE):
  1. Left half firmware compiles without errors using `make hidpress/bipedalambi:vial_left`
  2. Right half firmware compiles without errors using `make hidpress/bipedalambi:vial_right`
  3. EEPROM is cleared on the left half (via bootmagic or QK_CLEAR_EEPROM)
  4. EEPROM is cleared on the right half independently
  5. Both halves are flashed with the new firmware and boot successfully
**Plans**: TBD

Plans:
- [ ] 07-01: Compile both halves and resolve any build errors
- [ ] 07-02: Document flash and EEPROM clear procedure for user execution

### Phase 8: End-to-End Verification
**Goal**: The Vial layer offset bug is confirmed fixed -- all layers display correctly, keycodes persist, and KC_TRNS appears on the correct layers
**Depends on**: Phase 7
**Requirements**: EEPR-02, EEPR-03
**Success Criteria** (what must be TRUE):
  1. All 4 layers are visible and editable in the Vial desktop app when connected to either half
  2. Layer 1 content appears on layer 1 in Vial (not shifted to layer 2)
  3. KC_TRNS displays on layers 1 and 3 (the transparent layers), not on layers 2 and 4
  4. Keycodes set in Vial on any layer persist after unplugging and reconnecting the keyboard
  5. Both halves respond correctly to key presses on all layers (left side keys and right side keys)
**Plans**: TBD

Plans:
- [ ] 08-01: Create verification test procedure with expected outcomes
- [ ] 08-02: Execute verification and document results

## Progress

**Execution Order:**
Phases execute in numeric order: 1 -> 2 -> 3 -> 4 -> 5 -> 6 -> 7 -> 8
Note: Phase 4 and Phase 5 can run in parallel after Phase 3 completes. Phase 7 depends on both Phase 4 and Phase 6.

| Phase | Plans Complete | Status | Completed |
|-------|----------------|--------|-----------|
| 1. Reference Analysis | 3/3 | ✓ Complete | 2026-02-13 |
| 2. Matrix Dimension Audit | 0/1 | Not started | - |
| 3. vial.json Matrix Fix | 0/2 | Not started | - |
| 4. Peripheral Matrix Mapping | 0/2 | Not started | - |
| 5. EEPROM Budget Verification | 0/2 | Not started | - |
| 6. Defensive EEPROM Improvements | 0/2 | Not started | - |
| 7. Build and Flash | 0/2 | Not started | - |
| 8. End-to-End Verification | 0/2 | Not started | - |
