---
phase: 13-trackpad-cursor-auto-mouse
plan: 01
subsystem: pointing-device
tags: [tps43, azoteq-iqs5xx, auto-mouse, trackpad, cursor, qmk-pointing-device]

# Dependency graph
requires:
  - phase: 12-driver-switch-build-foundation
    provides: "azoteq_iqs5xx driver compiled with POINTING_DEVICE_DRIVER=azoteq_iqs5xx and SPLIT_POINTING_ENABLE"
provides:
  - "TPS43 trackpad cursor movement via azoteq_iqs5xx driver pass-through"
  - "QMK auto mouse layer 3 activation on trackpad touch with 650ms timeout"
  - "Simplified pointing_device_task_user (no scroll accumulator, driver handles gestures)"
affects: [14-trackpad-gesture-tuning, 15-mode-refactor]

# Tech tracking
tech-stack:
  added: []
  patterns:
    - "Auto mouse layer pattern: pointing_device_init_user calls set_auto_mouse_enable(true)"
    - "TPS43 pass-through pattern: pointing_device_task_user returns report unchanged (driver handles all gestures)"

key-files:
  created: []
  modified:
    - keyboards/hidpress/bipedalambi/config.h
    - keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c

key-decisions:
  - "Auto mouse layer set to layer 3 (layer 1 used by MO(1) function layer)"
  - "AUTO_MOUSE_TIME 650ms (QMK default, good balance)"
  - "AUTO_MOUSE_THRESHOLD 10 (prevents accidental activation from noise)"
  - "Removed scroll accumulator variables (TPS43 driver produces scroll values directly)"
  - "Kept MODE_MOUSE/MODE_SCROLLING/MODE_CUSTOM_KEYS enum and TMB_MODE cycling (still used by joystick and OLED, refactored in Phase 15)"

patterns-established:
  - "TPS43 driver pass-through: let azoteq_iqs5xx handle all gesture processing (taps, scroll, swipe), only register OLED activity in task_user"
  - "Auto mouse layer activation via QMK built-in (no custom layer switching for trackpad)"

requirements-completed: [TPAD-01, TPAD-08]

# Metrics
duration: 3min
completed: 2026-02-22
---

# Phase 13 Plan 01: Trackpad Cursor and Auto Mouse Summary

**TPS43 trackpad cursor movement via azoteq_iqs5xx pass-through with QMK auto mouse layer 3 activation on touch**

## Performance

- **Duration:** 3 min (code changes + build verification; hardware verification by user)
- **Started:** 2026-02-22T06:10:00Z
- **Completed:** 2026-02-22T06:18:36Z
- **Tasks:** 2
- **Files modified:** 2

## Accomplishments
- TPS43 trackpad on right half produces smooth cursor movement on screen
- Auto mouse layer 3 activates on trackpad touch and deactivates after 650ms timeout
- Joystick custom keys mode on left half completely unaffected
- OLED display continues to function correctly
- Removed dead scroll accumulator code (TPS43 driver handles scroll natively)

## Task Commits

Each task was committed atomically:

1. **Task 1: Enable auto mouse and update pointing device callbacks for TPS43** - `1444a10` (feat)
2. **Task 2: Flash and verify trackpad cursor movement and auto mouse layer** - hardware verification (checkpoint:human-verify, approved)

## Files Created/Modified
- `keyboards/hidpress/bipedalambi/config.h` - Added POINTING_DEVICE_AUTO_MOUSE_ENABLE, AUTO_MOUSE_DEFAULT_LAYER=3, AUTO_MOUSE_TIME=650, AUTO_MOUSE_THRESHOLD=10
- `keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c` - Added pointing_device_init_user with set_auto_mouse_enable(true), simplified pointing_device_task_user to pass-through, removed scroll accumulator variables and SCROLL_DIR key handling

## Decisions Made
- Auto mouse layer set to layer 3 to avoid conflict with MO(1) function layer on layer 1
- AUTO_MOUSE_TIME kept at 650ms (QMK default) -- confirmed good balance during hardware testing
- AUTO_MOUSE_THRESHOLD set to 10 to prevent accidental activation from sensor noise
- Removed SCROLL_DIVISOR_H/V, scroll_accumulated_h/v, scroll_inverted, and SCROLL_DIR key case since TPS43 azoteq_iqs5xx driver produces h/v scroll values directly
- Preserved MODE enum and TMB_MODE cycling logic for Phase 15 refactoring

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered

None.

## User Setup Required

None - no external service configuration required.

## Next Phase Readiness
- Trackpad cursor movement and auto mouse layer confirmed working on hardware
- Ready for Phase 14 (gesture tuning) to fine-tune sensitivity, scroll speed, and tap behavior
- TPS43 driver pass-through pattern established for future gesture customization

## Self-Check: PASSED

- FOUND: keyboards/hidpress/bipedalambi/config.h
- FOUND: keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c
- FOUND: 13-01-SUMMARY.md
- FOUND: commit 1444a10 (Task 1)
- FOUND: POINTING_DEVICE_AUTO_MOUSE_ENABLE in config.h
- FOUND: AUTO_MOUSE_DEFAULT_LAYER in config.h
- FOUND: set_auto_mouse_enable in keymap.c

---
*Phase: 13-trackpad-cursor-auto-mouse*
*Completed: 2026-02-22*
