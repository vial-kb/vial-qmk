---
phase: 01-reference-analysis
plan: 02
subsystem: documentation
tags: [qmk, vial, split-keyboard, matrix-config, eeprom, reference-analysis, position-map]

# Dependency graph
requires:
  - phase: 01-01
    provides: "Raw extracted values from 13 source files in EXTRACTED-DATA.md"
provides:
  - "REFERENCE-ANALYSIS.md with side-by-side comparison tables, EEPROM calculations, and position maps"
  - "Complete right-half position map: 25 keys remapped from rows 0-3 to rows 4-7"
  - "EEPROM layer offset explanation: 64 vs 128 byte discrepancy causing layer shift"
  - "Encoder configuration comparison: Sofle (ENCODER_MAP_ENABLE) vs Ambi ('encoders' JSON key)"
  - "Thumbstick position verification: rows 0-3 col 7 confirmed safe"
affects: [01-03, 02-matrix-dimension-audit, 03-vial-json-fix, 04-peripheral-matrix-mapping, 05-eeprom-budget]

# Tech tracking
tech-stack:
  added: []
  patterns:
    - "Split keyboard vial.json rows must equal compiled MATRIX_ROWS (physical_rows x 2)"
    - "Right-half layout positions use rows ROWS_PER_HAND to MATRIX_ROWS-1"
    - "Encoder KLE entries use encoder indices, NOT matrix row numbers -- do not adjust during row remapping"
    - "EEPROM layer size = MATRIX_ROWS * MATRIX_COLS * 2 bytes"

key-files:
  created:
    - ".planning/phases/01-reference-analysis/REFERENCE-ANALYSIS.md"
  modified: []

key-decisions:
  - "Numbered sections 1-9 covering all 10 plan topics (combined row-doubling convention and EEPROM intro)"
  - "Encoder KLE entries explicitly flagged as DO NOT CHANGE during row remapping"
  - "Documented both Sofle and Ambi encoder approaches as different styles requiring Phase 4 investigation"

patterns-established:
  - "Position map format: current/target row with full enumeration of every key position"
  - "EEPROM offset breakdown table: layer-by-layer byte offset comparison between Vial and firmware"
  - "Self-contained reference document pattern: all values sourced, all calculations shown"

# Metrics
duration: 3min
completed: 2026-02-13
---

# Phase 1 Plan 2: Reference Analysis Summary

**Side-by-side Sofle/Ambi comparison with EEPROM offset calculations showing 64-vs-128-byte layer mismatch, complete 25-key right-half position map, and encoder configuration analysis**

## Performance

- **Duration:** 3 min
- **Started:** 2026-02-13T12:24:17Z
- **Completed:** 2026-02-13T12:27:25Z
- **Tasks:** 2
- **Files created:** 1

## Accomplishments
- Created self-contained REFERENCE-ANALYSIS.md with 9 sections synthesizing all extracted data into actionable analysis
- Calculated EEPROM layer offset breakdown proving the 64-vs-128-byte mismatch causes the observed layer shift symptoms
- Enumerated all 25 right-half key positions with current and target row numbers for Phase 3 execution
- Documented encoder configuration differences between Sofle and Ambi, flagging encoder KLE entries as must-not-change during remapping
- Verified all 4 thumbstick positions (rows 0-3, col 7) remain in valid left-half range after fix

## Task Commits

Each task was committed atomically:

1. **Task 1: Create side-by-side comparison and convention analysis** - `b2facbb75c` (feat)
2. **Task 2: Add EEPROM calculations, position maps, and encoder comparison** - `c5901eb50b` (feat)

**Plan metadata:** (pending)

## Files Created/Modified
- `.planning/phases/01-reference-analysis/REFERENCE-ANALYSIS.md` - Structured reference document with comparison tables, EEPROM calculations, position maps, and encoder analysis

## Decisions Made
- Structured as 9 numbered sections covering all plan-specified topics (merged EEPROM intro into row-doubling section for flow)
- Explicitly called out encoder KLE entries as NOT using matrix row numbers to prevent accidental modification during the Phase 3 row remapping
- Identified the "encoders" JSON key in Ambi's right vial.json as a different approach from Sofle, deferring resolution to Phase 4

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered
None.

## User Setup Required
None - no external service configuration required.

## Next Phase Readiness
- REFERENCE-ANALYSIS.md provides the complete reference for Plan 03 (fix checklist derivation)
- Position map in Section 8 gives Phase 3 the exact line-by-line changes for right vial.json
- EEPROM calculations in Section 6 feed directly into Phase 5 budget verification
- Encoder comparison in Section 7 identifies the Phase 4 investigation needed for ENCODER_MAP_ENABLE vs "encoders" JSON key

## Self-Check: PASSED

- REFERENCE-ANALYSIS.md: FOUND
- 01-02-SUMMARY.md: FOUND
- Commit b2facbb75c: FOUND
- Commit c5901eb50b: FOUND

---
*Phase: 01-reference-analysis*
*Completed: 2026-02-13*
