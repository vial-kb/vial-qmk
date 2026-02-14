---
phase: 06-defensive-eeprom-improvements
plan: 01
subsystem: firmware
tags: [eeprom, eeconfig, qmk, split-keyboard, defensive-defaults]

# Dependency graph
requires:
  - phase: 05-eeprom-budget-verification
    provides: "Verified eeconfig_user at bytes 19-22 with no collision, 0x200 encoding confirmed"
provides:
  - "eeconfig_init_user() override in both keymap.c files writing 0x200 on EEPROM clear"
  - "EE_CLR keycode on layer 1 of both halves for user-accessible EEPROM reset"
  - "EEPROM clear procedure documentation covering both methods and both halves"
affects: [07-build-flash-test, 08-vial-verification]

# Tech tracking
tech-stack:
  added: []
  patterns: ["eeconfig_init_user override for sane EEPROM defaults after clear"]

key-files:
  created:
    - "bipedalambi/EEPROM-CLEAR-PROCEDURE.md"
  modified:
    - "bipedalambi/keymaps/vial_left/keymap.c"
    - "bipedalambi/keymaps/vial_right/keymap.c"

key-decisions:
  - "Left EE_CLR at k17 (KC_DOWN position on layer 0) -- last parameter in LAYOUT_left layer 1"
  - "Right EE_CLR at k35 (KC_EQL position on layer 0) -- second-to-last parameter in LAYOUT_right layer 1, avoiding k31 (MO(1) itself)"
  - "Default value 0x200 = actuation_index=2 (middle sensitivity) + all layers MODE_MOUSE"

patterns-established:
  - "eeconfig_init_user writes hardcoded constant matching save function encoding -- never call load from init"
  - "EE_CLR placed on layer 1 behind MO(1) to prevent accidental EEPROM wipe"

# Metrics
duration: 2min
completed: 2026-02-14
---

# Phase 6 Plan 1: Defensive EEPROM Improvements Summary

**eeconfig_init_user(0x200) override in both halves for sane post-clear defaults, EE_CLR on layer 1 for user-accessible reset, and per-half EEPROM clear procedure documentation**

## Performance

- **Duration:** 2 min
- **Started:** 2026-02-14T05:43:14Z
- **Completed:** 2026-02-14T05:45:08Z
- **Tasks:** 2
- **Files modified:** 3

## Accomplishments

- Added `eeconfig_init_user()` to both keymap.c files that writes `0x200` (actuation_index=2, all layers MODE_MOUSE) after EEPROM clear, preventing QMK default of all-zeros (actuation_index=0, maximum sensitivity)
- Placed `EE_CLR` (QK_CLEAR_EEPROM) on layer 1 of both halves in PROGMEM, requiring intentional MO(1) hold to access
- Created comprehensive EEPROM clear procedure documentation covering both EE_CLR and Bootmagic methods, per-half instructions, and full dual-half reset procedure

## Task Commits

Each task was committed atomically:

1. **Task 1: Add eeconfig_init_user and EE_CLR to both keymap.c files** - `0eded21bc5` (feat)
2. **Task 2: Create EEPROM clear procedure documentation** - `c4501974cd` (docs)

## Files Created/Modified

- `bipedalambi/keymaps/vial_left/keymap.c` - Added eeconfig_init_user() override and EE_CLR at k17 on layer 1
- `bipedalambi/keymaps/vial_right/keymap.c` - Added eeconfig_init_user() override and EE_CLR at k35 on layer 1
- `bipedalambi/EEPROM-CLEAR-PROCEDURE.md` - EEPROM clear procedure for both halves (EE_CLR + Bootmagic)

## Decisions Made

- **Left EE_CLR position:** k17 (KC_DOWN on layer 0, last key in LAYOUT_left) -- bottom-right position, easy to reach while holding MO(1) at k31
- **Right EE_CLR position:** k35 (KC_EQL on layer 0, second-to-last in LAYOUT_right) -- chosen because k31 is MO(1) itself and cannot trigger a different keycode on layer 1 while being held as the layer activator
- **Default value 0x200:** Matches the save function encoding exactly -- `(2 << 8)` gives actuation_index=2 in bits 8-10 and all layer_modes=0 (MODE_MOUSE) in bits 0-7

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered

None.

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness

- Phase 6 is complete with all defensive EEPROM improvements in place
- Both keymap.c files are ready for compilation in Phase 7 (build/flash/test)
- EEPROM clear procedure document serves as Phase 7/8 reference for the user performing physical testing
- Blocker: Phase 7 requires physical keyboard access for flashing and testing

## Self-Check: PASSED

- [x] `bipedalambi/keymaps/vial_left/keymap.c` -- FOUND
- [x] `bipedalambi/keymaps/vial_right/keymap.c` -- FOUND
- [x] `bipedalambi/EEPROM-CLEAR-PROCEDURE.md` -- FOUND
- [x] `.planning/phases/06-defensive-eeprom-improvements/06-01-SUMMARY.md` -- FOUND
- [x] Commit `0eded21bc5` (Task 1) -- FOUND
- [x] Commit `c4501974cd` (Task 2) -- FOUND

---
*Phase: 06-defensive-eeprom-improvements*
*Completed: 2026-02-14*
