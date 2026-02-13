---
phase: 01-reference-analysis
plan: 01
subsystem: documentation
tags: [qmk, vial, split-keyboard, matrix-config, sofle, reference-extraction]

# Dependency graph
requires:
  - phase: none
    provides: "First plan -- no prior dependencies"
provides:
  - "Raw extracted values from 13 source files in EXTRACTED-DATA.md"
  - "Research verification: all 19 claims from 01-RESEARCH.md confirmed"
  - "Key mismatch table: Ambi vial.json rows=4 vs config.h MATRIX_ROWS=8"
  - "Complete right-half position inventory for row remapping"
affects: [01-02, 01-03, 02-matrix-dimension-audit, 03-vial-json-fix]

# Tech tracking
tech-stack:
  added: []
  patterns:
    - "Split keyboard row doubling: vial.json rows must equal MATRIX_ROWS (physical_rows x 2)"
    - "Right-half layout positions use rows ROWS_PER_HAND to MATRIX_ROWS-1"
    - "Encoder KLE entries use encoder_index/direction, NOT matrix row numbers"

key-files:
  created:
    - ".planning/phases/01-reference-analysis/EXTRACTED-DATA.md"
  modified: []

key-decisions:
  - "Confirmed all 19 research claims pass -- no discrepancies requiring re-evaluation"
  - "Documented encoder KLE entries separately from regular key positions to prevent confusion during row remapping"

patterns-established:
  - "Tabular extraction format: property | value | source file | expected | match?"
  - "Research verification as explicit pass/fail checklist against source files"

# Metrics
duration: 2min
completed: 2026-02-13
---

# Phase 1 Plan 1: Data Extraction Summary

**Extracted raw config values from 13 QMK/Vial source files confirming Ambi vial.json rows=4 mismatch against MATRIX_ROWS=8**

## Performance

- **Duration:** 2 min
- **Started:** 2026-02-13T12:18:57Z
- **Completed:** 2026-02-13T12:21:49Z
- **Tasks:** 2
- **Files created:** 1

## Accomplishments
- Read all 5 Sofle rev1 Vial files and extracted every matrix, encoder, and layout data point
- Read all 6 Bipedal Ambi files and 2 Bipedal Southpaw files with full value extraction
- Verified all 19 research claims from 01-RESEARCH.md against actual source file values -- all PASS
- Created structured EXTRACTED-DATA.md with 5 sections: Sofle values, Ambi values, Southpaw sanity check, research verification, key mismatches summary

## Task Commits

Each task was committed atomically:

1. **Task 1: Read Sofle rev1 Vial source files** -- No file output (data held in memory for Task 2)
2. **Task 2: Read Ambi + Southpaw, verify research, write EXTRACTED-DATA.md** - `bfca6134bc` (feat)

**Plan metadata:** (pending final commit)

## Files Created/Modified
- `.planning/phases/01-reference-analysis/EXTRACTED-DATA.md` - Raw extracted values from all 13 source files organized in tabular format with research verification

## Decisions Made
- Confirmed all 19 research claims pass without discrepancy -- no need to revise research conclusions
- Documented encoder KLE entries as a separate category from regular key positions to prevent accidental row-number adjustment during the vial.json fix (encoder entries use encoder_index/direction, not matrix rows)

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered
None.

## User Setup Required
None - no external service configuration required.

## Next Phase Readiness
- EXTRACTED-DATA.md contains all raw values needed for Plan 02 (synthesis into REFERENCE-ANALYSIS.md)
- Key mismatch table provides the exact changes needed: both vial.json files need rows=8, right-side layout needs rows 4-7
- All 25 right-half key positions inventoried for row remapping
- Thumbstick positions (col 7, rows 0-3) confirmed safe -- no change needed

## Self-Check: PASSED

- EXTRACTED-DATA.md: FOUND
- 01-01-SUMMARY.md: FOUND
- Commit bfca6134bc: FOUND

---
*Phase: 01-reference-analysis*
*Completed: 2026-02-13*
