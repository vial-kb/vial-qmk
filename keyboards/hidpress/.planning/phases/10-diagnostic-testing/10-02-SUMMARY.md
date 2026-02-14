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

patterns-established:
  - "Half-duplex serial: single-wire bidirectional on TX pin only"

# Metrics
duration: 2min
completed: 2026-02-14
status: checkpoint-paused
test-result: PENDING
---

# Phase 10 Plan 02: DIAG-02 Half-Duplex Fallback Test Summary

**Switched serial from full-duplex to half-duplex mode (TX-only, single wire) to isolate whether broken serial is caused by TRRS TX/RX wiring (H2) or a deeper PIO/signal issue**

## Performance

- **Duration:** 2 min (automation) + awaiting user flash/test
- **Started:** 2026-02-14T12:50:05Z
- **Completed:** PENDING (checkpoint: awaiting user flash and test)
- **Tasks:** 1 of 2 complete (Task 2 is user action)
- **Files modified:** 1

## Accomplishments

- Commented out `SERIAL_USART_FULL_DUPLEX` in config.h (line 6) -- switches serial driver to half-duplex mode
- Both halves compile cleanly in half-duplex mode: left 126,464 bytes, right 109,568 bytes
- Half-duplex eliminates RX pin (GP1 left / GP16 right) and TX/RX crossing as variables
- Only TX pin used for bidirectional communication on a single wire
- SIO cleanup from DIAG-00 (Plan 10-01) remains in place

## Task Commits

Each task was committed atomically:

1. **Task 1: Switch to half-duplex mode and compile both halves** - `a007619ece` (fix)
2. **Task 2: User flashes DIAG-02 firmware and tests** - PENDING (checkpoint:human-action)

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

## DIAG-02 Test Result: PENDING

**Status:** Awaiting user flash and test

**What half-duplex changes:**
- Driver uses only TX pin (GP0 left, GP17 right) for bidirectional communication
- RX pin is completely unused -- eliminates TRRS TX/RX crossing as a variable
- If half-duplex WORKS: wiring hypothesis (H2) confirmed -- full-duplex requires proper TX/RX crossing
- If half-duplex FAILS: wiring ruled out -- problem is PIO init, signal integrity, or fundamental

## Next Step

Awaiting user test result to determine:
- **PASS** -> Plan 10-03 PATH A: restore full-duplex + try SERIAL_USART_PIN_SWAP
- **FAIL** -> Plan 10-03 PATH B: try MASTER_LEFT, then console debug
- **PARTIAL** -> Plan 10-03 with partial diagnosis info

## Self-Check: PASSED

- FOUND: keyboards/hidpress/bipedalambi/config.h (SERIAL_USART_FULL_DUPLEX commented out)
- FOUND: commit a007619ece (Task 1: half-duplex config change)
- Task 2: checkpoint:human-action (awaiting user)
- Both UF2 files exist with fresh timestamps

---
*Phase: 10-diagnostic-testing*
*Status: checkpoint-paused (2026-02-14)*
