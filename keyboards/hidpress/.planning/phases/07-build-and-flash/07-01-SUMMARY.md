---
phase: 07-build-and-flash
plan: 01
subsystem: firmware
tags: [qmk, uf2, rp2040, chibios, split-keyboard, make, gcc]

# Dependency graph
requires:
  - phase: 06-defensive-eeprom-improvements
    provides: eeconfig_init_user and EE_CLR keycode additions
  - phase: 04-peripheral-matrix-mapping
    provides: NUM_ENCODERS=1 fix and peripheral config
  - phase: 03-vialjson-matrix-fix
    provides: Corrected vial.json matrix.rows=8 and right-half KLE row remapping
  - phase: 02-matrix-dimension-audit
    provides: Confirmed info.json 4 row pins correct via QMK auto-doubling
provides:
  - Left half UF2 firmware binary (hidpress_bipedalambi_vial_left.uf2, 127,488 bytes)
  - Right half UF2 firmware binary (hidpress_bipedalambi_vial_right.uf2, 110,592 bytes)
  - Committed pre-existing SERIAL_PIO_USE_PIO1 and UART config
affects: [07-02-flash-and-validate]

# Tech tracking
tech-stack:
  added: []
  patterns: [separate-left-right-keymaps, pio1-for-serial-pio0-for-ws2812]

key-files:
  created:
    - .build/hidpress_bipedalambi_vial_left.uf2
    - .build/hidpress_bipedalambi_vial_right.uf2
  modified:
    - bipedalambi/config.h
    - bipedalambi/mcuconf.h

key-decisions:
  - "Pre-existing SERIAL_PIO_USE_PIO1 and UART0/UART1 config committed as-is -- hardware config from before Phase 1"

patterns-established:
  - "Build from repo root: make hidpress/bipedalambi:vial_left and :vial_right"
  - "Left UF2 ~125KB, right UF2 ~108KB (right has encoder, no joystick/pointing)"

# Metrics
duration: 2min
completed: 2026-02-14
---

# Phase 7 Plan 1: Firmware Compilation Summary

**Clean build of both split halves producing UF2 binaries with all Phases 3-6 fixes (matrix rows, NUM_ENCODERS, eeconfig_init_user, EE_CLR)**

## Performance

- **Duration:** 2 min
- **Started:** 2026-02-14T07:31:36Z
- **Completed:** 2026-02-14T07:32:59Z
- **Tasks:** 1
- **Files modified:** 2 (config.h, mcuconf.h committed)

## Accomplishments
- Committed pre-existing serial PIO1 and UART peripheral config that was in the working tree
- Clean build of left half firmware (127,488 bytes / 124.5 KB)
- Clean build of right half firmware (110,592 bytes / 108 KB)
- Both builds completed with exit code 0 using GCC 15.2.1 (arm-none-eabi)

## Task Commits

Each task was committed atomically:

1. **Task 1: Commit uncommitted config changes and clean build both halves** - `ffc8137922` (fix)

**Plan metadata:** (pending final commit)

## Files Created/Modified
- `bipedalambi/config.h` - Added `#define SERIAL_PIO_USE_PIO1` (PIO0 used by WS2812)
- `bipedalambi/mcuconf.h` - Enabled `RP_SIO_USE_UART0` and `RP_SIO_USE_UART1` for ChibiOS SIO driver
- `.build/hidpress_bipedalambi_vial_left.uf2` - Left half firmware binary (build artifact, not committed)
- `.build/hidpress_bipedalambi_vial_right.uf2` - Right half firmware binary (build artifact, not committed)

## Decisions Made
- Pre-existing SERIAL_PIO_USE_PIO1 and UART0/UART1 config committed as-is rather than investigating whether they are strictly necessary -- these are hardware configuration additions from before Phase 1 and should not hurt even if defensive

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered
- QMK linter warnings about LAYOUT_bipedalambi being defined in .h file and missing keyboard.json build marker -- these are pre-existing structural warnings unrelated to the firmware fix work and do not affect compilation
- LTO linker warning about serial compilation of 2 LTRANS jobs -- informational only, no impact on binary correctness

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness
- Both UF2 firmware files are ready for flashing in Phase 7 Plan 2
- User will need physical access to both keyboard halves to enter bootloader mode (double-tap reset or hold BOOTSEL)
- Flash procedure: drag UF2 file to RP2040 mass storage device

## Self-Check: PASSED

- FOUND: .build/hidpress_bipedalambi_vial_left.uf2 (127,488 bytes)
- FOUND: .build/hidpress_bipedalambi_vial_right.uf2 (110,592 bytes)
- FOUND: 07-01-SUMMARY.md
- FOUND: commit ffc8137922
- Left UF2 > 50KB: PASS
- Right UF2 > 50KB: PASS

---
*Phase: 07-build-and-flash*
*Completed: 2026-02-14*
