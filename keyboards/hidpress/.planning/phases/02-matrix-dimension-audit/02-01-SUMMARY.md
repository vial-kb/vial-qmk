---
phase: 02-matrix-dimension-audit
plan: 01
subsystem: firmware-audit
tags: [qmk, vial, matrix-dimensions, split-keyboard, eeprom, cross-reference]

# Dependency graph
requires:
  - phase: 01-reference-analysis
    provides: "Reference data (EXTRACTED-DATA.md, REFERENCE-ANALYSIS.md, FIX-CHECKLIST.md) establishing expected values and known disagreements"
provides:
  - "DIMENSION-AUDIT.md with cross-reference table of all 6 matrix dimension sources"
  - "Two documented disagreements with correct values and Phase 3 fix references"
  - "info.json agreement confirmation satisfying MTRX-03"
  - "XVAL-01 requirement satisfied"
affects: [03-vial-json-fix, 04-encoder-config]

# Tech tracking
tech-stack:
  added: []
  patterns:
    - "Cross-reference table format for multi-source dimension auditing"
    - "Disagreement documentation with source-of-truth citation and impact analysis"

key-files:
  created:
    - ".planning/phases/02-matrix-dimension-audit/DIMENSION-AUDIT.md"
  modified: []

key-decisions:
  - "info.json 4 row pins confirmed as correct via QMK split auto-doubling -- no fix needed"
  - "Right vial.json KLE row range issue (rows 0-3 instead of 4-7) documented as separate disagreement from the matrix.rows=4 issue"
  - "Encoder KLE entries confirmed as encoder indices, not matrix rows -- must not be remapped in Phase 3"

patterns-established:
  - "Dimension source cross-referencing: single table with all sources as columns, properties as rows, agreement status, and expected values"

# Metrics
duration: 2min
completed: 2026-02-14
---

# Phase 2 Plan 01: Matrix Dimension Audit Summary

**Cross-reference table of all 6 matrix dimension sources confirming 2 disagreements (vial.json rows=4, right KLE rows 0-3) and info.json/config.h agreement via split auto-doubling**

## Performance

- **Duration:** 2 min
- **Started:** 2026-02-14T03:10:24Z
- **Completed:** 2026-02-14T03:12:43Z
- **Tasks:** 2
- **Files created:** 1

## Accomplishments
- Cross-reference table created covering config.h, info.json (effective), left vial.json, right vial.json, and LAYOUT macro spans with line-number citations for every value
- Two disagreements documented with correct values, impact analysis, and Phase 3 fix references
- info.json agreement with config.h confirmed via 5-step split auto-doubling verification chain (MTRX-03 satisfied)
- Requirements XVAL-01 and MTRX-03 confirmed satisfied

## Task Commits

Each task was committed atomically:

1. **Tasks 1-2: Extract dimension values and create DIMENSION-AUDIT.md** - `e0ab7b49cc` (feat)
   - Task 1 was pure analysis (no files created), so both tasks share one commit containing the deliverable

**Plan metadata:** (pending -- docs commit after summary)

## Files Created/Modified
- `.planning/phases/02-matrix-dimension-audit/DIMENSION-AUDIT.md` - Cross-reference table, disagreement documentation, info.json agreement chain, and requirement satisfaction confirmation

## Decisions Made
- **info.json is correct as-is:** The 4 row pins in info.json are the expected input to QMK's split auto-doubling logic. 4 x 2 = 8 = config.h MATRIX_ROWS. No fix needed.
- **Right vial.json KLE rows are a separate issue from matrix.rows:** The `matrix.rows=4` dimension mismatch and the KLE row range issue (0-3 instead of 4-7) are documented as separate disagreements because they have different fixes and different impacts.
- **Encoder entries must not be remapped:** The `\ne` suffix in encoder KLE entries marks them as encoder indices (0,0 and 0,1), not matrix row/col positions. Phase 3 must skip these during row remapping.

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered

None.

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness
- DIMENSION-AUDIT.md provides the authoritative reference for Phase 3 fixes
- Phase 3 has clear targets: change both vial.json `"rows": 4` to `"rows": 8`, and remap right vial.json KLE rows from 0-3 to 4-7
- Encoder entries are clearly documented as encoder indices (must not be remapped)
- Phase 2 is complete (single-plan phase)

## Self-Check: PASSED

- FOUND: `.planning/phases/02-matrix-dimension-audit/DIMENSION-AUDIT.md`
- FOUND: `.planning/phases/02-matrix-dimension-audit/02-01-SUMMARY.md`
- FOUND: commit `e0ab7b49cc`

---
*Phase: 02-matrix-dimension-audit*
*Completed: 2026-02-14*
