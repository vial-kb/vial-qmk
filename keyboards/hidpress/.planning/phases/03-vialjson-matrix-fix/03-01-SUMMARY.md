---
phase: 03-vialjson-matrix-fix
plan: 01
subsystem: firmware-config
tags: [vial, json, matrix, split-keyboard, kle, eeprom]

# Dependency graph
requires:
  - phase: 02-matrix-dimension-audit
    provides: "Confirmed matrix dimension disagreements (rows=4 vs MATRIX_ROWS=8) and right KLE row range issue"
provides:
  - "Corrected left vial.json with rows=8 matching config.h"
  - "Corrected right vial.json with rows=8 and KLE positions remapped to rows 4-7"
  - "MTRX-01 satisfied: vial.json matrix rows match config.h MATRIX_ROWS"
  - "MTRX-02 satisfied: right-side KLE positions use rows 4-7"
affects: [04-encoder-audit, 05-build-verification, 07-flash-firmware]

# Tech tracking
tech-stack:
  added: []
  patterns: ["split keyboard right-half row offset (+ROWS_PER_HAND) in vial.json KLE"]

key-files:
  created: []
  modified:
    - "bipedalambi/keymaps/vial_left/vial.json"
    - "bipedalambi/keymaps/vial_right/vial.json"

key-decisions:
  - "Left KLE positions unchanged (rows 0-3 correct for left half)"
  - "Right KLE positions remapped +4 rows (0-3 to 4-7) per split convention"
  - "Encoder KLE entries preserved as encoder indices, not matrix rows"

patterns-established:
  - "Encoder KLE entries (suffix \\ne) use encoder indices, not matrix rows -- must be excluded from row remapping"

# Metrics
duration: 2min
completed: 2026-02-14
---

# Phase 3 Plan 1: vial.json Matrix Fix Summary

**Fixed vial.json matrix rows from 4 to 8 for both halves and remapped right-half KLE positions from rows 0-3 to rows 4-7**

## Performance

- **Duration:** 2 min
- **Started:** 2026-02-14T03:46:08Z
- **Completed:** 2026-02-14T03:47:56Z
- **Tasks:** 2
- **Files modified:** 2

## Accomplishments
- Left vial.json matrix rows corrected from 4 to 8, matching config.h MATRIX_ROWS=8
- Right vial.json matrix rows corrected from 4 to 8, with all 25 key positions remapped from rows 0-3 to rows 4-7
- Encoder KLE entries and encoders JSON key preserved unchanged
- Requirements MTRX-01 and MTRX-02 satisfied

## Task Commits

Each task was committed atomically:

1. **Task 1: Fix matrix dimensions in left vial.json** - `3f2c4b00e4` (fix)
2. **Task 2: Fix matrix dimensions and remap KLE positions in right vial.json** - `8e5205ed81` (fix)

## Files Created/Modified
- `bipedalambi/keymaps/vial_left/vial.json` - Changed matrix rows from 4 to 8; KLE positions unchanged (29 keys on rows 0-3)
- `bipedalambi/keymaps/vial_right/vial.json` - Changed matrix rows from 4 to 8; remapped 25 key positions from rows 0-3 to rows 4-7; encoder entries preserved

## Decisions Made
None - followed plan as specified.

## Deviations from Plan

### Auto-fixed Issues

**1. [Rule 1 - Bug] Fixed incomplete row remapping on encoder-shared lines**
- **Found during:** Task 2 (right vial.json KLE remap)
- **Issue:** Initial line-skipping approach skipped entire lines containing encoder entries, leaving 6 key positions on those lines un-remapped (2,6/2,5/2,1/2,0 on line 27 and 3,5/3,1 on line 30)
- **Fix:** Switched to token-level regex that inspects each quoted string individually, checking for \n suffix to identify encoder entries vs key positions
- **Files modified:** bipedalambi/keymaps/vial_right/vial.json
- **Verification:** Validation script confirmed 25 keys on rows [4,5,6,7], 2 encoder entries [0,0] and [0,1] unchanged
- **Committed in:** 8e5205ed81 (Task 2 commit)

---

**Total deviations:** 1 auto-fixed (1 bug)
**Impact on plan:** Self-corrected during execution. Final output matches plan specification exactly.

## Issues Encountered
None.

## User Setup Required
None - no external service configuration required.

## Next Phase Readiness
- Both vial.json files are corrected and committed
- Ready for Phase 4 (encoder audit) to verify encoder configuration
- Ready for Phase 5 (build verification) to compile firmware with corrected vial.json files

## Self-Check: PASSED

- [x] bipedalambi/keymaps/vial_left/vial.json exists
- [x] bipedalambi/keymaps/vial_right/vial.json exists
- [x] .planning/phases/03-vialjson-matrix-fix/03-01-SUMMARY.md exists
- [x] Commit 3f2c4b00e4 (Task 1) exists
- [x] Commit 8e5205ed81 (Task 2) exists

---
*Phase: 03-vialjson-matrix-fix*
*Completed: 2026-02-14*
