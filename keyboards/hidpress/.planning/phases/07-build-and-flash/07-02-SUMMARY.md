---
phase: 07-build-and-flash
plan: 02
subsystem: firmware
tags: [flash, uf2, rp2040, eeprom-clear, split-keyboard, vial]

# Dependency graph
requires:
  - phase: 07-build-and-flash
    plan: 01
    provides: Compiled UF2 firmware binaries for both halves
provides:
  - Both keyboard halves running firmware with all Phase 3-6 fixes
  - Clean EEPROM state on both halves
  - Corrected right half vial.json KLE positions (rows 0-3, not 4-7)
affects: [08-end-to-end-verification]

# Tech tracking
tech-stack:
  added: []
  patterns: [standalone-half-uses-rows-0-3]

key-files:
  created: []
  modified:
    - keymaps/vial_right/vial.json

key-decisions:
  - "Right half vial.json KLE positions reverted from rows 4-7 to rows 0-3 -- each half operates standalone and scans its own 4 physical row pins as rows 0-3"
  - "Phase 3 row remapping was incorrect for standalone split halves -- split row offset (rows 4-7) only applies in combined split mode, not when each half has its own firmware"

patterns-established:
  - "Both halves use KLE rows 0-3 in vial.json because each operates independently with 4 physical row pins"
  - "matrix.rows=8 in vial.json is correct (matches config.h), but KLE positions must match actual firmware matrix scanning (rows 0-3)"

# Metrics
duration: user-executed
completed: 2026-02-14
---

# Phase 7 Plan 2: Flash and EEPROM Clear Summary

**Both halves flashed with corrected firmware, EEPROM cleared, and verified working in Vial GUI**

## Performance

- **Duration:** User-executed (physical hardware task)
- **Completed:** 2026-02-14
- **Tasks:** 1 (checkpoint:human-action)

## Accomplishments
- Left half flashed and EEPROM cleared -- working correctly in Vial
- Right half flashed and EEPROM cleared -- initially showed blank keys in Vial
- Diagnosed root cause: Phase 3 incorrectly remapped right half KLE positions to rows 4-7, but standalone operation scans rows 0-3
- Fixed right half vial.json: reverted KLE positions from rows 4-7 back to rows 0-3
- Rebuilt right half firmware, re-flashed, re-cleared EEPROM -- confirmed working

## Task Commits

1. **Task 1: Flash and clear EEPROM on both halves** - User-executed physical hardware task
2. **Fix commit:** `f9eb193f88` - Revert right half vial.json KLE positions to rows 0-3

## Deviations from Plan

**CRITICAL DEVIATION:** The right half showed blank keys after initial flash. Root cause analysis revealed Phase 3's row remapping (0-3 → 4-7) was incorrect for this keyboard's architecture:

- Each half has its own separate firmware (vial_left, vial_right)
- When connected standalone via USB, each half scans its own 4 physical row pins as rows 0-3
- The split row offset (rows 4-7 for right half) only applies in combined split mode with a single firmware
- The LAYOUT_right macro explicitly places keys at matrix[0-3], confirming rows 0-3 is correct

**Fix applied:** Reverted right half vial.json KLE positions from rows 4-7 back to rows 0-3, rebuilt, re-flashed, and re-cleared EEPROM. Both halves now working correctly.

## Issues Encountered
- Right half blank keys in Vial GUI due to KLE row mismatch (diagnosed and fixed during this plan)

## Self-Check: PASSED

- CONFIRMED: Left half boots and shows correct keycodes in Vial
- CONFIRMED: Right half boots and shows correct keycodes in Vial (after fix)
- CONFIRMED: Both halves EEPROM cleared
- FOUND: commit f9eb193f88 (right half vial.json fix)

---
*Phase: 07-build-and-flash*
*Completed: 2026-02-14*
