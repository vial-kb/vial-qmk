---
phase: 05-eeprom-budget-verification
plan: 01
subsystem: eeprom
tags: [eeprom, wear-leveling, rp2040, dynamic-keymap, vial, address-map]

# Dependency graph
requires:
  - phase: 04-peripheral-matrix-mapping
    provides: "NUM_ENCODERS=1 fix and verified MATRIX_ROWS/COLS values"
provides:
  - "EEPROM-ADDRESS-MAP.md with complete per-half address maps"
  - "eeconfig_user non-overlap confirmation (bytes 19-22 vs VIA at byte 36)"
  - "EEPR-04 and XVAL-02 requirements satisfied"
affects: [06-defensive-eeprom, 07-flash-verify, 08-hardware-test]

# Tech tracking
tech-stack:
  added: []
  patterns: ["vial-qmk EEPROM address chain tracing from preprocessor macros"]

key-files:
  created:
    - ".planning/phases/05-eeprom-budget-verification/EEPROM-ADDRESS-MAP.md"
  modified: []

key-decisions:
  - "All addresses verified against vial-qmk fork source files, not upstream QMK docs"
  - "eeconfig_user (bytes 19-22) confirmed 13 bytes away from VIA magic (byte 36) -- no collision possible"
  - "Right half uses 568 bytes fixed (13.9% of 4096), left half uses 552 bytes (13.5%)"

patterns-established:
  - "EEPROM address chain: eeconfig -> VIA header -> dynamic keymap -> encoders -> zero-sized Vial features -> macros"

# Metrics
duration: 3min
completed: 2026-02-14
---

# Phase 5 Plan 1: EEPROM Budget Verification Summary

**Complete EEPROM address map for both Bipedal Ambi halves verified against vial-qmk source, confirming no overlaps and 86%+ macro space within 4096-byte wear-leveling budget**

## Performance

- **Duration:** 3 min
- **Started:** 2026-02-14T05:04:33Z
- **Completed:** 2026-02-14T05:08:00Z
- **Tasks:** 1
- **Files created:** 1

## Accomplishments

- Produced EEPROM-ADDRESS-MAP.md with complete byte-level address maps for both left and right halves
- Verified every constant against vial-qmk fork source files (quantum/eeconfig.h, quantum/via.h, quantum/dynamic_keymap.c, platform headers)
- Confirmed eeconfig_user (bytes 19-22) has a 13-byte gap to VIA magic (byte 36) -- no collision possible
- Verified no region overlaps for either half; all regions are exactly adjacent
- Right half: 568 bytes fixed regions + 3528 bytes macros = 4096 total
- Left half: 552 bytes fixed regions + 3544 bytes macros = 4096 total
- Confirmed _Static_assert for minimum 100 macro bytes passes with 3400+ bytes of headroom
- EEPR-04 (EEPROM budget documented with no overlaps) and XVAL-02 (verified against vial-qmk fork source) satisfied

## Task Commits

Each task was committed atomically:

1. **Task 1: Verify EEPROM address constants against vial-qmk source and produce documented address map** - `8c463eb9e1` (docs)

**Plan metadata:** (pending final commit)

## Files Created/Modified

- `.planning/phases/05-eeprom-budget-verification/EEPROM-ADDRESS-MAP.md` - Complete EEPROM address map for both halves with constants table, overlap verification, budget summary, and source cross-references

## Decisions Made

- All addresses verified against vial-qmk fork source files (quantum/eeconfig.h, quantum/via.h, quantum/dynamic_keymap.c), not upstream QMK documentation -- satisfying XVAL-02
- eeconfig_user at bytes 19-22 confirmed non-overlapping with VIA magic at byte 36 (13-byte gap occupied by union, haptic, rgblight_ext fields)
- Right half uses 568 bytes for fixed regions (13.9% of 4096), left half uses 552 bytes (13.5%) -- 16-byte difference is the encoder map

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered

None.

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness

- EEPROM address map complete and verified -- ready for Phase 6 (defensive EEPROM improvements)
- Phase 6 can reference EEPROM-ADDRESS-MAP.md for exact byte ranges when implementing any EEPROM safety measures
- No blockers for Phase 6

## Self-Check: PASSED

- EEPROM-ADDRESS-MAP.md: FOUND
- 05-01-SUMMARY.md: FOUND
- Commit 8c463eb9e1: FOUND

---
*Phase: 05-eeprom-budget-verification*
*Completed: 2026-02-14*
