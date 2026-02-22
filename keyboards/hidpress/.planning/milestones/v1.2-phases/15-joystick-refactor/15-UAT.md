---
status: diagnosed
phase: 15-joystick-refactor
source: 15-01-SUMMARY.md
started: 2026-02-22T20:00:00Z
updated: 2026-02-22T20:15:00Z
---

## Current Test
<!-- OVERWRITE each test - shows where we are -->

[testing complete]

## Tests

### 1. Scroll Mode — Wheel Events
expected: Set joystick to scroll mode via TMB_MODE. Deflect joystick in each direction. Each deflection sends exactly 1 scroll event (up/down/left/right). Holding deflected does NOT repeat — must return to center for next scroll.
result: issue
reported: "Wheel events dont fire continuously when joystick is held (expected), both x and y axis are also inverted"
severity: major

### 2. Mode Cycling — TMB_MODE
expected: Press TMB_MODE repeatedly. OLED cycles between exactly 2 icons: custom keys and scroll. No third mode (mouse) appears. After 2 presses, returns to starting mode.
result: issue
reported: "TMB_MODE does fire with right as master (corrected), but OLED does not update to show the mode change"
severity: major

### 3. Custom Keys Mode — Regression
expected: In custom keys mode (OLED shows keycode icon), deflect joystick in all 4 directions. Directional keycodes fire as expected (same behavior as before refactor). Keycodes are remappable in Vial.
result: pass

### 4. EEPROM Persistence
expected: Set joystick to scroll mode. Power cycle (unplug/replug USB). After reboot, OLED still shows scroll mode. Mode persists across power cycles.
result: issue
reported: "Works for left but the mode does not persist when right is master"
severity: major

### 5. Joystick Works with Right as Master
expected: Plug USB into right half. Joystick on left half fires keycodes/scroll events correctly (split transport syncing ADC from slave to master).
result: issue
reported: "fires but issues with tmb mode not registering and persisting in power cycles or switch events from left to right"
severity: major

### 6. OLED Wakes on Keypress (Both Halves)
expected: Let OLED enter screensaver on both halves. Press any key. Both OLEDs wake from screensaver and show normal display — regardless of which half is USB master.
result: pass

### 7. No Key Spam with Right as Master
expected: Plug USB into right half. No phantom keypresses or repeating characters. QMK console shows no unexpected key events.
result: pass

## Summary

total: 7
passed: 3
issues: 4
pending: 0
skipped: 0

## Gaps

- truth: "Scroll mode sends correct directional scroll events matching joystick deflection direction"
  status: fixed
  reason: "User reported: both x and y axis are also inverted"
  severity: major
  test: 1
  root_cause: "WH_UP/DOWN/LEFT/RIGHT mapped opposite to natural scrolling — push-up sent WH_UP (viewport up) instead of WH_DOWN (content up)"
  artifacts:
    - path: "keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c"
      issue: "Scroll keycodes inverted in process_joystick() scroll mode branch"
  missing:
    - "Swap WH_UP↔WH_DOWN and WH_LEFT↔WH_RIGHT"
  fix: "a5a6c04c6e"

- truth: "OLED updates to show mode change when TMB_MODE is pressed with right as master"
  status: fixed
  reason: "User reported: TMB_MODE does fire with right as master, but OLED does not update to show the mode change"
  severity: major
  test: 2
  root_cause: "current_mode is a local variable per half — process_record_user only runs on master, slave OLED reads stale local current_mode"
  artifacts:
    - path: "keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c"
      issue: "No split transport for current_mode from master to slave"
    - path: "keyboards/hidpress/bipedalambi/config.h"
      issue: "Only USER_SYNC_JOYSTICK defined, no state sync transaction"
  missing:
    - "Add USER_SYNC_STATE split transaction pushing current_mode master→slave"
  fix: "a5a6c04c6e"

- truth: "Joystick mode persists in EEPROM across power cycles regardless of which half is USB master"
  status: fixed
  reason: "User reported: Works for left but the mode does not persist when right is master"
  severity: major
  test: 4
  root_cause: "Same as test 2 — slave OLED showed stale mode from its own EEPROM. Master EEPROM persisted correctly but slave never received the update"
  artifacts:
    - path: "keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c"
      issue: "No state sync from master to slave"
  missing:
    - "USER_SYNC_STATE pushes current_mode so slave OLED reflects master state on boot"
  fix: "a5a6c04c6e"

- truth: "Joystick fires keycodes/scroll and TMB_MODE works with right as master, persisting across power cycles and master switches"
  status: fixed
  reason: "User reported: fires but issues with tmb mode not registering and persisting in power cycles or switch events from left to right"
  severity: major
  test: 5
  root_cause: "Same as tests 2 and 4 — current_mode not synced across halves"
  artifacts:
    - path: "keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c"
      issue: "No state sync from master to slave"
  missing:
    - "USER_SYNC_STATE split transport"
  fix: "a5a6c04c6e"
