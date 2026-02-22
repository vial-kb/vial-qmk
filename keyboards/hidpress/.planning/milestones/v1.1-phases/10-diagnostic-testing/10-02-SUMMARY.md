---
phase: 10-diagnostic-testing
plan: 02
subsystem: firmware-config
tags: [serial, half-duplex, pio, rp2040, split-keyboard, trrs, diagnostic]

# Dependency graph
requires:
  - phase: 10-diagnostic-testing
    plan: 01
    provides: "DIAG-00 FAIL result -- SIO cleanup applied but serial still broken"
provides:
  - "config.h with SERIAL_USART_FULL_DUPLEX commented out for half-duplex diagnostic"
  - "Compiled UF2 firmware for both halves in half-duplex mode"
  - "DIAG-02 test result: determines if wiring (H2) or deeper issue"
affects: [10-diagnostic-testing, 11-verdict]

# Tech tracking
tech-stack:
  added: []
  patterns:
    - "Half-duplex PIO serial uses only TX pin -- eliminates RX pin and TX/RX crossing as variables"

key-files:
  created: []
  modified:
    - "keyboards/hidpress/bipedalambi/config.h"

key-decisions:
  - "Commented out SERIAL_USART_FULL_DUPLEX rather than deleting -- easily restorable after diagnostic"
  - "RX pin defines left in keymap configs -- driver ignores them in half-duplex mode"
  - "DIAG-02 result FAIL -- half-duplex also fails, H2 (wiring) ELIMINATED as root cause"
  - "Problem is deeper than wiring: PIO init, GPIO pin, signal integrity, or fundamental driver issue"
  - "Next diagnostic path: Plan 10-03 PATH B (MASTER_LEFT, then console debug)"

patterns-established:
  - "Half-duplex serial: single-wire bidirectional on TX pin only"

# Metrics
duration: 2min
completed: 2026-02-14
status: complete
test-result: FAIL
---

# Phase 10 Plan 02: DIAG-02 Half-Duplex Fallback Test Summary

**DIAG-02 FAIL: Half-duplex serial (TX-only, single wire) also fails -- eliminates wiring hypothesis (H2), problem is deeper than TX/RX crossing (PIO init, GPIO, or signal integrity)**

## Performance

- **Duration:** 2 min (automation) + user flash time
- **Started:** 2026-02-14T12:50:05Z
- **Completed:** 2026-02-14
- **Tasks:** 2 of 2 complete
- **Files modified:** 1
- **Test result:** FAIL

## Accomplishments

- Commented out `SERIAL_USART_FULL_DUPLEX` in config.h (line 6) -- switches serial driver to half-duplex mode
- Both halves compile cleanly in half-duplex mode: left 126,464 bytes, right 109,568 bytes
- Half-duplex eliminates RX pin (GP1 left / GP16 right) and TX/RX crossing as variables
- Only TX pin used for bidirectional communication on a single wire
- SIO cleanup from DIAG-00 (Plan 10-01) remains in place
- **DIAG-02 test result: FAIL** -- slave-side keys still do not register in half-duplex mode
- H2 (wiring / TX/RX crossing) ELIMINATED -- half-duplex removes wiring as a variable entirely
- Problem is deeper: PIO initialization, GPIO pin configuration, signal integrity, or fundamental driver issue

## Task Commits

Each task was committed atomically:

1. **Task 1: Switch to half-duplex mode and compile both halves** - `a007619ece` (fix)
2. **Task 2: User flashes DIAG-02 firmware and tests** - No commit (user action, result: FAIL)

## Files Created/Modified

- `keyboards/hidpress/bipedalambi/config.h` - Commented out SERIAL_USART_FULL_DUPLEX for half-duplex diagnostic test

## Build Artifacts (not tracked in git)

- `hidpress_bipedalambi_vial_left.uf2` - 126,464 bytes (left half firmware, half-duplex)
- `hidpress_bipedalambi_vial_right.uf2` - 109,568 bytes (right half firmware, half-duplex)

## Decisions Made

1. **Commented out rather than deleted SERIAL_USART_FULL_DUPLEX** -- This is a diagnostic test. The define should be easily restorable. If half-duplex works, we may want to restore full-duplex with PIN_SWAP. If it fails, we restore full-duplex anyway for the next test.

2. **Left RX pin defines in keymap configs** -- The half-duplex driver ignores SERIAL_USART_RX_PIN entirely. No need to modify keymap-level configs for this diagnostic.

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered

None.

## DIAG-02 Test Result: FAIL

**Result:** FAIL -- slave-side keys do NOT register on master in half-duplex mode.

**User report (verbatim):**
> "Same result unfortunately"

**Analysis:**
- **Half-duplex mode:** Uses only TX pin (GP0 left, GP17 right) for bidirectional single-wire communication
- **RX pin completely unused:** GP1 (left) and GP16 (right) are not involved at all
- **TX/RX crossing eliminated:** Half-duplex does not require crossed wiring -- single wire, single pin
- **Result:** Same failure as full-duplex -- slave-side keys do not register on master
- **Both directions tested:** Neither direction works (same behavior as DIAG-00)

**Hypothesis elimination:**
- H1 (HAL_USE_SIO / UART Peripheral Misconfiguration): **ELIMINATED in DIAG-00** -- removing SIO had no effect
- H2 (TRRS TX/RX Wiring / Crossing): **ELIMINATED in DIAG-02** -- half-duplex removes all wiring variables and still fails
- Both halves boot and run correctly (OLEDs work through TRRS)
- Power path confirmed working, serial data path broken in both full-duplex and half-duplex

**Diagnostic significance:**
The fact that BOTH full-duplex and half-duplex fail identically means:
1. The problem is NOT wiring-related (RX pin, TX/RX crossing, TRRS cable routing)
2. The problem is NOT ChibiOS SIO HAL related (already removed)
3. The problem must be in: PIO initialization, GPIO pin mux, signal integrity, USB master detection (SPLIT_USB_DETECT), or a fundamental serial driver issue
4. The GPIO pins themselves may not be outputting signal, OR the PIO program is not loading correctly

**Remaining hypotheses:**
- PIO1 initialization failure (PIO program not loading or executing)
- GPIO pin not being configured for PIO function (pin mux issue)
- SPLIT_USB_DETECT not correctly determining master/slave roles
- Signal integrity issue (damaged trace, cold solder joint on data pins)
- Clock/timing issue in PIO serial protocol

## Next Step

Proceed to **Plan 10-03 PATH B** -- the problem is NOT wiring:
1. **DIAG-05: MASTER_LEFT** -- Remove SPLIT_USB_DETECT, use explicit MASTER_LEFT/MASTER_RIGHT to eliminate USB detection as a variable
2. **DIAG-06: Console debug** -- Enable QMK console output to see if serial driver reports errors, timeouts, or initialization failures

## Self-Check: PASSED

- FOUND: keyboards/hidpress/bipedalambi/config.h (SERIAL_USART_FULL_DUPLEX commented out)
- FOUND: commit a007619ece (Task 1: half-duplex config change)
- Task 2: user action complete (result: FAIL)
- Both UF2 files exist with fresh timestamps

---
*Phase: 10-diagnostic-testing*
*Completed: 2026-02-14*
