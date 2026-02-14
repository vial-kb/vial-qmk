---
phase: 09-configuration-audit
plan: 01
subsystem: serial-communication
tags: [rp2040, pio, serial, split-keyboard, chibios, sio, uart, trrs]

# Dependency graph
requires:
  - phase: 01-reference-analysis
    provides: "Pin mapping and peripheral assignment reference"
  - phase: 04-peripheral-matrix-mapping
    provides: "Per-half matrix pin assignments"
provides:
  - "Complete serial/split configuration audit (SERIAL-AUDIT.md)"
  - "Prioritized hypothesis list (H1-H5) for Phase 10 diagnostic testing"
  - "Confirmed HAL_USE_SIO misconfiguration as primary suspect"
  - "Confirmed WS2812 PIO conflict is a non-issue (driver never compiled)"
affects: [10-diagnostic-firmware-tests, 11-verdict-and-resolution]

# Tech tracking
tech-stack:
  added: []
  patterns:
    - "Audit-then-test diagnostic funnel: exhaustive config audit before any firmware changes"
    - "Cross-reference known-working board (bipedal65) to validate config expectations"

key-files:
  created:
    - ".planning/phases/09-configuration-audit/SERIAL-AUDIT.md"
  modified: []

key-decisions:
  - "HAL_USE_SIO identified as unnecessary for vendor (PIO) serial driver -- recommend removing in Phase 10"
  - "WS2812 PIO conflict hypothesis eliminated via build system analysis (driver never compiled)"
  - "H1 (SIO cleanup) ranked above H2 (wiring) because it is the only confirmed misconfiguration and has zero risk to test"
  - "DIAG-00 proposed as new first test (remove SIO config) before existing DIAG-01"

patterns-established:
  - "Driver path tracing: follow SERIAL_DRIVER value through builddefs/common_features.mk to actual compiled source"
  - "Build guard verification: check WS2812_DRIVER_REQUIRED gate before assuming driver is active"

# Metrics
duration: 5min
completed: 2026-02-14
---

# Phase 9 Plan 1: Serial Configuration Audit Summary

**Exhaustive audit of 9 firmware config files and 3 driver sources identified HAL_USE_SIO as the only confirmed misconfiguration, with TX/RX wiring as the primary unverifiable risk factor**

## Performance

- **Duration:** 5 min
- **Started:** 2026-02-14T11:45:52Z
- **Completed:** 2026-02-14T11:51:08Z
- **Tasks:** 2
- **Files modified:** 1

## Accomplishments

- Audited all 7 serial/split config requirements (AUDIT-01 through AUDIT-07) with per-requirement evidence and status
- Identified HAL_USE_SIO + RP_SIO_USE_UART0/UART1 as unnecessary for the PIO-based vendor serial driver (AUDIT-06: SUSPECT)
- Eliminated WS2812 PIO conflict hypothesis entirely via build system analysis (ws2812_vendor.c never compiled)
- Produced ranked hypothesis list (H1-H5) with confidence levels and mapped DIAG test IDs for Phase 10

## Task Commits

Each task was committed atomically:

1. **Task 1: Audit all serial/split config surfaces and trace driver paths** - `df659e8f35` (docs)
2. **Task 2: Produce prioritized hypothesis list for Phase 10** - `81cafddce6` (docs)

## Files Created/Modified

- `.planning/phases/09-configuration-audit/SERIAL-AUDIT.md` - Complete audit findings with 7 requirement sections, 5 ranked hypotheses, and Phase 10 test order

## Decisions Made

1. **HAL_USE_SIO is unnecessary:** The vendor serial driver uses PIO directly via the Pico SDK. It never calls `sioStart()` or references any ChibiOS SIO API. The `HAL_USE_SIO TRUE` config was added based on a misunderstanding (the comment "Required for serial communication" is wrong). The bipedal65 reference board (non-split, working) does not enable SIO.

2. **WS2812 PIO conflict is a non-issue:** Build system analysis proves `ws2812_vendor.c` is only compiled when `WS2812_DRIVER_REQUIRED = yes`, which requires `RGBLIGHT_ENABLE = yes` or `RGB_MATRIX_ENABLE = yes`. Neither is enabled for the bipedalambi. PIO0 is completely free.

3. **H1 ranked above H2 despite lower severity:** H1 (SIO cleanup) is the only confirmed misconfiguration and can be tested with zero risk in a single firmware flash. H2 (wiring mismatch) has higher severity but cannot be verified from firmware alone and requires PCB schematic review or physical testing.

4. **New DIAG-00 proposed:** Insert a new first diagnostic test (remove SIO config) before the existing DIAG test sequence. This is the fastest, safest way to eliminate the only known config error.

## Deviations from Plan

### Auto-fixed Issues

**1. [Rule 2 - Missing Critical] WS2812 compilation guard analysis**
- **Found during:** Task 1 (AUDIT-03: PIO Peripheral Assignments)
- **Issue:** Plan assumed WS2812 driver might initialize on right half. Build system analysis revealed WS2812 driver is never compiled because RGBLIGHT is disabled.
- **Fix:** Traced `WS2812_DRIVER_REQUIRED` through `builddefs/common_features.mk` to prove the guard prevents compilation
- **Files modified:** SERIAL-AUDIT.md (stronger finding than planned)
- **Verification:** `grep "WS2812_DRIVER_REQUIRED" builddefs/common_features.mk` confirms compilation gate
- **Committed in:** df659e8f35 (Task 1 commit)

**2. [Rule 2 - Missing Critical] ChibiOS SIO init deep analysis**
- **Found during:** Task 1 (AUDIT-06: ChibiOS Peripheral Activation)
- **Issue:** Plan stated SIO might configure GPIO mux. Source analysis of `hal_sio_lld.c` revealed `sio_lld_init()` only resets UART peripherals and `sio_lld_start()` (which touches UART registers) is never called.
- **Fix:** Read ChibiOS SIO HAL source to determine exact init behavior, confirmed no GPIO mux impact
- **Files modified:** SERIAL-AUDIT.md (more nuanced finding than planned)
- **Verification:** `grep "sioStart\|QMKSerialDriver" serial_vendor.c` returns no matches
- **Committed in:** df659e8f35 (Task 1 commit)

---

**Total deviations:** 2 auto-fixed (2 missing critical analysis)
**Impact on plan:** Both deviations strengthened audit findings. H4 (WS2812 PIO conflict) was definitively eliminated rather than left as MEDIUM confidence. H1 (SIO config) was refined from "possible GPIO mux conflict" to "unnecessary but likely benign init."

## Issues Encountered

None.

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness

- Phase 10 (Diagnostic Firmware Tests) has a clear test execution order derived from the hypothesis ranking
- H1 test (DIAG-00: remove SIO config) is the recommended first action
- User will need to flash firmware and report results for each DIAG test
- PCB schematic review (DIAG-03) can be done in parallel with firmware tests

## Self-Check: PASSED

- FOUND: `.planning/phases/09-configuration-audit/SERIAL-AUDIT.md`
- FOUND: `.planning/phases/09-configuration-audit/09-01-SUMMARY.md`
- FOUND: `df659e8f35` (Task 1 commit)
- FOUND: `81cafddce6` (Task 2 commit)

---
*Phase: 09-configuration-audit*
*Completed: 2026-02-14*
