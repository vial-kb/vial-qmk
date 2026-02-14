---
phase: 10-diagnostic-testing
plan: 01
subsystem: firmware-config
tags: [chibios, halconf, mcuconf, sio, uart, pio, rp2040, split-keyboard]

# Dependency graph
requires:
  - phase: 09-configuration-audit
    provides: "SERIAL-AUDIT.md hypothesis list identifying HAL_USE_SIO as unnecessary"
provides:
  - "halconf.h with SIO removed -- clean HAL config matching vendor driver requirements"
  - "mcuconf.h with UART0/UART1 removed -- only I2C and ADC peripherals enabled"
  - "Compiled UF2 firmware for both halves with SIO/UART config eliminated"
  - "DIAG-01 (PIO conflict) documented as skipped with audit evidence"
affects: [10-diagnostic-testing, 11-verdict]

# Tech tracking
tech-stack:
  added: []
  patterns:
    - "ChibiOS HAL config should only enable peripherals actually used by active drivers"

key-files:
  created: []
  modified:
    - "keyboards/hidpress/bipedalambi/halconf.h"
    - "keyboards/hidpress/bipedalambi/mcuconf.h"

key-decisions:
  - "Removed HAL_USE_SIO and UART0/UART1 config -- vendor serial driver uses PIO directly, never touches ChibiOS SIO HAL"
  - "DIAG-01 (PIO conflict) skipped -- audit proved WS2812 driver never compiled, no conflict to test"

patterns-established:
  - "Vendor (PIO) serial driver requires zero ChibiOS SIO/UART configuration"

# Metrics
duration: 2min
completed: 2026-02-14
status: paused-at-checkpoint
---

# Phase 10 Plan 01: DIAG-00 SIO/UART Config Removal Summary

**Removed unnecessary HAL_USE_SIO and UART peripheral config from ChibiOS HAL; both halves compile cleanly; awaiting user flash test**

## Performance

- **Duration:** 2 min
- **Started:** 2026-02-14T12:10:46Z
- **Paused:** 2026-02-14T12:12:37Z
- **Tasks:** 2 of 3 complete (Task 3 is checkpoint:human-action)
- **Files modified:** 2

## Accomplishments

- Removed `HAL_USE_SIO TRUE` from halconf.h (was incorrectly labeled "Required for serial communication")
- Removed `RP_SIO_USE_UART0 TRUE` and `RP_SIO_USE_UART1 TRUE` blocks from mcuconf.h
- Preserved all necessary config: HAL_USE_I2C, HAL_USE_ADC, I2C0, I2C1, ADC1
- Both halves compile cleanly: left UF2 = 125,952 bytes, right UF2 = 108,544 bytes
- DIAG-01 (PIO conflict hypothesis) documented as skipped -- Phase 9 audit AUDIT-03 proved WS2812 driver is never compiled

## Task Commits

Each task was committed atomically:

1. **Task 1: Remove SIO/UART config and document DIAG-01 skip** - `0dddbd763b` (fix)
2. **Task 2: Compile both halves** - No commit (build-only task, no tracked files changed)
3. **Task 3: User flashes and tests** - PENDING (checkpoint:human-action)

## Files Created/Modified

- `keyboards/hidpress/bipedalambi/halconf.h` - Removed HAL_USE_SIO TRUE; now only enables I2C and ADC
- `keyboards/hidpress/bipedalambi/mcuconf.h` - Removed UART0/UART1 blocks; now only configures I2C0, I2C1, ADC1

## Build Artifacts (not tracked in git)

- `hidpress_bipedalambi_vial_left.uf2` - 125,952 bytes (left half firmware)
- `hidpress_bipedalambi_vial_right.uf2` - 108,544 bytes (right half firmware)

## Decisions Made

1. **Removed SIO config rather than commenting it out** -- This is a permanent fix. The vendor serial driver never uses ChibiOS SIO. The "Required for serial communication" comment was incorrect. Aligns config with bipedal65 (known working RP2040 board).

2. **DIAG-01 skipped with audit evidence** -- Phase 9 AUDIT-03 proved the WS2812 driver is never compiled (RGBLIGHT disabled, no RGB_MATRIX_ENABLE). PIO0 is completely free. No PIO conflict exists to test.

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered

None.

## User Setup Required

None - no external service configuration required.

## Checkpoint: Awaiting User Flash Test

**Status:** Task 3 (checkpoint:human-action) reached. User must physically flash both halves and report whether slave-side keys register.

**UF2 file locations:**
- Left: `/Users/matthewthomas/dev/vial-qmk/hidpress_bipedalambi_vial_left.uf2`
- Right: `/Users/matthewthomas/dev/vial-qmk/hidpress_bipedalambi_vial_right.uf2`

**Expected results:**
- PASS: Serial communication fixed, proceed to Phase 11 (Verdict)
- FAIL: SIO removal was not the cause, proceed to Plan 10-02 (DIAG-02: half-duplex fallback)
- PARTIAL: Describe behavior, informs next diagnostic step

## Next Phase Readiness

- Both UF2 files ready for flashing
- If PASS: Phase 10 complete, skip remaining diagnostics, proceed to Phase 11
- If FAIL: SIO config removal stays in place (it was correct regardless), proceed to Plan 10-02

## Self-Check: PASSED

- FOUND: keyboards/hidpress/bipedalambi/halconf.h
- FOUND: keyboards/hidpress/bipedalambi/mcuconf.h
- FOUND: hidpress_bipedalambi_vial_left.uf2
- FOUND: hidpress_bipedalambi_vial_right.uf2
- FOUND: 10-01-SUMMARY.md
- FOUND: commit 0dddbd763b

---
*Phase: 10-diagnostic-testing*
*Paused at checkpoint: 2026-02-14*
