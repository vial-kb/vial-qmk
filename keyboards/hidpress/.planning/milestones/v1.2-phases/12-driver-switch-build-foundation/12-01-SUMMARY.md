---
phase: 12-driver-switch-build-foundation
plan: 01
subsystem: firmware
tags: [azoteq_iqs5xx, tps43, i2c, pointing-device, split-keyboard, rp2040]

# Dependency graph
requires: []
provides:
  - azoteq_iqs5xx driver selected in rules.mk (replaces analog_joystick)
  - AZOTEQ_IQS5XX_TPS43 model define in config.h
  - POINTING_DEVICE_RIGHT and SPLIT_POINTING_ENABLE configured
  - I2C bus coexistence verified (OLED 0x3C + TPS43 0x74 on I2C1)
  - Both halves compile cleanly with new driver
affects: [13-trackpad-initialization, 14-trackpad-input-mapping, 15-oled-trackpad-integration]

# Tech tracking
tech-stack:
  added: [azoteq_iqs5xx driver]
  patterns: [I2C bus sharing between OLED and trackpad on right half]

key-files:
  created: []
  modified:
    - keyboards/hidpress/bipedalambi/rules.mk
    - keyboards/hidpress/bipedalambi/config.h

key-decisions:
  - "Kept JOYSTICK_ENABLE + JOYSTICK_DRIVER=analog -- joystick hardware still used for custom keys/scroll modes via direct ADC reads"
  - "Kept SRC += analog.c explicitly -- azoteq_iqs5xx sets I2C_DRIVER_REQUIRED not ANALOG_DRIVER_REQUIRED, so analog.c must be listed for ADC"
  - "AZOTEQ_IQS5XX_TPS43 defined unconditionally (not inside #ifdef RIGHT_SIDE) -- driver header needs it at compile time for both halves when split pointing enabled"

patterns-established:
  - "I2C bus sharing: OLED (0x3C) and TPS43 (0x74) coexist on I2C1 without address collision"
  - "SIDE=right build flag for right-half-specific compilation continues to work with new driver"

requirements-completed: [BLD-01, BLD-02, TPAD-07]

# Metrics
duration: 1min
completed: 2026-02-22
---

# Phase 12 Plan 01: Driver Switch and Build Foundation Summary

**Switched pointing device driver from analog_joystick to azoteq_iqs5xx (TPS43 43mm trackpad) with I2C bus sharing on right half**

## Performance

- **Duration:** 1 min
- **Started:** 2026-02-22T05:46:09Z
- **Completed:** 2026-02-22T05:47:38Z
- **Tasks:** 2
- **Files modified:** 2

## Accomplishments
- Switched POINTING_DEVICE_DRIVER from analog_joystick to azoteq_iqs5xx in rules.mk
- Configured config.h with TPS43 model define, POINTING_DEVICE_RIGHT, and removed all analog joystick defines
- Verified I2C address coexistence: OLED at 0x3C and TPS43 at 0x74 share I2C1 on right half
- Both halves (left and right) compile cleanly with new driver, producing UF2 firmware files

## Task Commits

Each task was committed atomically:

1. **Task 1: Switch pointing device driver and update build/hardware config** - `1dec097b17` (feat)
2. **Task 2: Build both halves and verify clean compilation** - No source changes; build verification only

## Files Created/Modified
- `keyboards/hidpress/bipedalambi/rules.mk` - Changed POINTING_DEVICE_DRIVER to azoteq_iqs5xx, kept SRC += analog.c and JOYSTICK_ENABLE
- `keyboards/hidpress/bipedalambi/config.h` - Removed ANALOG_JOYSTICK_* defines, added AZOTEQ_IQS5XX_TPS43, changed POINTING_DEVICE_LEFT to POINTING_DEVICE_RIGHT, removed POINTING_DEVICE_INVERT_X

## Decisions Made
- Kept JOYSTICK_ENABLE and JOYSTICK_DRIVER=analog because the joystick hardware on the left half is still used for custom keys and scroll modes via direct analogReadPin() calls in matrix_scan_user()
- Kept explicit SRC += analog.c because the azoteq_iqs5xx driver sets I2C_DRIVER_REQUIRED (not ANALOG_DRIVER_REQUIRED), so analog.c would not be pulled in automatically
- Defined AZOTEQ_IQS5XX_TPS43 unconditionally (outside #ifdef RIGHT_SIDE) because the driver header needs it at compile time for both halves when SPLIT_POINTING_ENABLE is set

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered

None.

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness
- Build foundation established: azoteq_iqs5xx driver compiles and links for both halves
- Ready for Phase 13: TPS43 trackpad initialization (I2C communication, interrupt handling, hardware init sequence)
- I2C bus sharing confirmed safe at the address level; runtime bus arbitration will be tested in Phase 13

## Self-Check: PASSED

- FOUND: keyboards/hidpress/bipedalambi/rules.mk
- FOUND: keyboards/hidpress/bipedalambi/config.h
- FOUND: 12-01-SUMMARY.md
- FOUND: commit 1dec097b17

---
*Phase: 12-driver-switch-build-foundation*
*Completed: 2026-02-22*
