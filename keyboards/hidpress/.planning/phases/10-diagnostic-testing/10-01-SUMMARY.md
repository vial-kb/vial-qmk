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
  - "DIAG-00 result FAIL -- SIO removal was correct but not the root cause of serial failure"
  - "SIO removal retained permanently -- config was wrong regardless of test outcome"

patterns-established:
  - "Vendor (PIO) serial driver requires zero ChibiOS SIO/UART configuration"

# Metrics
duration: 2min
completed: 2026-02-14
status: complete
test-result: FAIL
---

# Phase 10 Plan 01: DIAG-00 SIO/UART Config Removal Summary

**DIAG-00 FAIL: Removed unnecessary HAL_USE_SIO/UART config (correct cleanup) but serial communication still broken -- eliminates ChibiOS SIO HAL as root cause, proceed to DIAG-02 half-duplex test**

## Performance

- **Duration:** 2 min (automation) + user flash time
- **Started:** 2026-02-14T12:10:46Z
- **Completed:** 2026-02-14
- **Tasks:** 3 of 3 complete
- **Files modified:** 2
- **Test result:** FAIL

## Accomplishments

- Removed `HAL_USE_SIO TRUE` from halconf.h (was incorrectly labeled "Required for serial communication")
- Removed `RP_SIO_USE_UART0 TRUE` and `RP_SIO_USE_UART1 TRUE` blocks from mcuconf.h
- Preserved all necessary config: HAL_USE_I2C, HAL_USE_ADC, I2C0, I2C1, ADC1
- Both halves compile cleanly: left UF2 = 125,952 bytes, right UF2 = 108,544 bytes
- DIAG-01 (PIO conflict hypothesis) documented as skipped -- Phase 9 audit AUDIT-03 proved WS2812 driver is never compiled
- **DIAG-00 test result: FAIL** -- slave-side keys still do not register on master
- User confirmed: power flows through TRRS (slave OLED fully functional), but serial data does not
- H1 (SIO/UART misconfiguration) eliminated as root cause -- ChibiOS SIO HAL init is not the problem

## Task Commits

Each task was committed atomically:

1. **Task 1: Remove SIO/UART config and document DIAG-01 skip** - `0dddbd763b` (fix)
2. **Task 2: Compile both halves** - No commit (build-only task, no tracked files changed)
3. **Task 3: User flashes and tests** - No commit (user action, result: FAIL)

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

## DIAG-00 Test Result: FAIL

**Result:** FAIL -- slave-side keys do NOT register on master after SIO/UART config removal.

**User report (verbatim):**
> "Same results as before, which ever side does not have the direct connection does not work. however it must get power as when the right side is plugged with usb, the left side's oled turns on and is functional (startup animation, screen saver, correct graphics displayed)."

**Analysis:**
- **Power path (VCC/GND):** CONFIRMED working through TRRS -- slave OLED is fully functional (startup animation, screensaver, correct graphics)
- **Serial data path:** NOT working -- slave-side key presses do not register on master side
- **Both directions tested:** Neither direction works (right-USB-left-slave and left-USB-right-slave both fail)
- **Conclusion:** ChibiOS SIO HAL initialization (sio_lld_init resetting UART peripherals) is NOT the root cause. The SIO config removal was correct cleanup but did not fix serial communication.

**Hypothesis elimination:**
- H1 (HAL_USE_SIO / UART Peripheral Misconfiguration): **ELIMINATED** -- removing it had no effect on serial behavior
- SIO removal retained permanently -- it was incorrect config regardless

**Diagnostic significance:**
The fact that OLED works perfectly through TRRS confirms:
1. VCC and GND traces on the TRRS PCB routing are correct
2. I2C is NOT involved in cross-half communication (each OLED uses its own I2C bus)
3. The OLED working confirms the slave MCU is booting and running firmware correctly
4. The failure is isolated to the PIO serial data path (TX/RX pins or wiring)

## Next Step

Proceed to **Plan 10-02: DIAG-02 half-duplex fallback test**. Switching from full-duplex (2-wire TX+RX) to half-duplex (1-wire TX only) will isolate whether the problem is:
- **Wiring:** TX/RX crossing issue on TRRS (H2) -- if half-duplex works, full-duplex wiring is wrong
- **Deeper:** PIO serial init, clock, or pin mux issue -- if half-duplex also fails, problem is fundamental

## Self-Check: PASSED

- FOUND: keyboards/hidpress/bipedalambi/halconf.h
- FOUND: keyboards/hidpress/bipedalambi/mcuconf.h
- FOUND: 10-01-SUMMARY.md
- FOUND: STATE.md
- FOUND: commit 0dddbd763b (Task 1: SIO/UART removal)
- FOUND: commit 88aee6c84e (docs: checkpoint pause)
- Task 3 result: FAIL recorded from user report

---
*Phase: 10-diagnostic-testing*
*Completed: 2026-02-14*
