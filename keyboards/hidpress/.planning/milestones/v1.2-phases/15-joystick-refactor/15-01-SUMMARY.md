---
phase: 15-joystick-refactor
plan: 01
subsystem: firmware
tags: [qmk, joystick, scroll, adc, eeprom, oled]

# Dependency graph
requires:
  - phase: 13-trackpad-cursor-auto-mouse
    provides: "TPS43 trackpad handling all mouse cursor movement, making joystick mouse mode dead code"
provides:
  - "Two-mode joystick: MODE_CUSTOM_KEYS (0) and MODE_SCROLLING (1)"
  - "Scroll mode emitting KC_MS_WH_UP/DOWN/LEFT/RIGHT from ADC deflection"
  - "Clean OLED display with only scroll and custom keys icons"
  - "EEPROM encoding updated for 2-mode system"
affects: []

# Tech tracking
tech-stack:
  added: []
  patterns:
    - "tap_code() for discrete scroll steps (one deflection = one scroll event)"
    - "scroll_active[] state array to prevent retriggering while joystick deflected"

key-files:
  created: []
  modified:
    - "keyboards/hidpress/bipedalambi/bipedalambi.h"
    - "keyboards/hidpress/bipedalambi/bipedalambi.c"
    - "keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c"
    - "keyboards/hidpress/bipedalambi/EEPROM-CLEAR-PROCEDURE.md"

key-decisions:
  - "MODE_CUSTOM_KEYS=0 as default (was MODE_MOUSE=0) — EEPROM value 0x200 maps correctly without migration"
  - "tap_code() for scroll (discrete steps, no repeat/acceleration) — simple model matching joystick hardware"
  - "scroll_active[] state prevents retriggering while deflected — user must return to center for next scroll"

patterns-established:
  - "Joystick modes: MODE_CUSTOM_KEYS (0) and MODE_SCROLLING (1), cycled by TMB_MODE"

requirements-completed: [JOY-01, JOY-02, JOY-03, JOY-04, JOY-05]

# Metrics
duration: 4min
completed: 2026-02-22
---

# Phase 15 Plan 01: Joystick Refactor Summary

**Removed mouse mode from joystick, leaving 2 modes (custom keys + scroll) with wheel keycode emission from ADC**

## Performance

- **Duration:** 4 min
- **Started:** 2026-02-22T08:10:26Z
- **Completed:** 2026-02-22T08:14:29Z
- **Tasks:** 2
- **Files modified:** 4

## Accomplishments
- Removed MODE_MOUSE entirely from enum, OLED arrays, and keymap defaults (~252 bytes flash saved from OLED arrays)
- Added scroll mode logic emitting KC_MS_WH_UP/DOWN/LEFT/RIGHT via tap_code() using same actuation threshold
- TMB_MODE now cycles between exactly 2 modes (custom keys and scroll) with EEPROM persistence

## Task Commits

Each task was committed atomically:

1. **Task 1: Remove mouse mode from enum and update OLED display** - `bd49d8b0f8` (feat)
2. **Task 2: Add scroll mode wheel keycodes, update TMB_MODE cycling, and fix EEPROM encoding** - `844b7d2c58` (feat)
3. **Auto-fix: Update EEPROM doc for stale MODE_MOUSE references** - `01ff79bad8` (fix)

## Files Created/Modified
- `keyboards/hidpress/bipedalambi/bipedalambi.h` - Enum reduced to MODE_CUSTOM_KEYS=0, MODE_SCROLLING=1, MODE_COUNT=2
- `keyboards/hidpress/bipedalambi/bipedalambi.c` - Removed 4 mouse OLED arrays, updated render_layer_state() for 2 modes, default current_mode changed
- `keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c` - Added scroll mode handler with wheel keycodes, updated defaults and EEPROM fallback
- `keyboards/hidpress/bipedalambi/EEPROM-CLEAR-PROCEDURE.md` - Updated stale MODE_MOUSE references to MODE_CUSTOM_KEYS

## Decisions Made
- MODE_CUSTOM_KEYS=0 as enum default aligns with existing EEPROM value 0x200, so no EEPROM migration needed
- tap_code() used for scroll events (press+release per threshold crossing) rather than register/unregister because scroll is discrete, not held
- scroll_active[] array uses same pattern as customkeys[] for consistent state tracking

## Deviations from Plan

### Auto-fixed Issues

**1. [Rule 1 - Bug] Fixed stale MODE_MOUSE references in EEPROM documentation**
- **Found during:** Phase-level verification (grep across all files)
- **Issue:** EEPROM-CLEAR-PROCEDURE.md referenced "MODE_MOUSE" and "mouse mode" which no longer exist
- **Fix:** Updated to reference MODE_CUSTOM_KEYS and "custom keys mode"
- **Files modified:** keyboards/hidpress/bipedalambi/EEPROM-CLEAR-PROCEDURE.md
- **Verification:** grep -r "MODE_MOUSE" returns 0 matches in bipedalambi/
- **Committed in:** 01ff79bad8

---

**Total deviations:** 1 auto-fixed (1 bug - stale documentation)
**Impact on plan:** Minor doc fix, no scope creep.

## Issues Encountered
None

## User Setup Required
None - no external service configuration required.

## Next Phase Readiness
- Joystick refactor complete with 2 clean modes
- UF2 files ready for flashing: hidpress_bipedalambi_vial_LEFT.uf2 and hidpress_bipedalambi_vial_RIGHT.uf2
- Hardware verification needed: flash both halves, confirm TMB_MODE cycles between 2 modes, confirm scroll mode sends wheel events, confirm custom keys mode unchanged

---
*Phase: 15-joystick-refactor*
*Completed: 2026-02-22*
