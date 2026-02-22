---
phase: 13-trackpad-cursor-auto-mouse
plan: 01
verified: 2026-02-22T17:35:00Z
status: human_needed
score: 4/4 must-haves verified (1 automated, 3 hardware)
human_verification:
  - test: "Touch and slide finger on TPS43 trackpad on right half"
    expected: "Cursor moves smoothly following finger direction, no jitter, no stuck axes"
    why_human: "Requires actual hardware testing with physical trackpad"
    hardware_checkpoint_status: "approved (Task 2)"
  - test: "Observe layer activation in Vial while touching trackpad"
    expected: "Layer 3 activates when trackpad touched, deactivates after ~650ms when released"
    why_human: "Requires Vial GUI observation and timing verification"
    hardware_checkpoint_status: "approved (Task 2)"
  - test: "Test joystick custom keys mode on left half"
    expected: "Joystick directional keys still fire correctly"
    why_human: "Requires physical joystick testing"
    hardware_checkpoint_status: "approved (Task 2)"
---

# Phase 13: Trackpad Cursor and Auto Mouse Verification Report

**Phase Goal:** User can move the mouse cursor by touching the TPS43 trackpad on the right half, and an auto mouse layer activates during trackpad movement

**Verified:** 2026-02-22T17:35:00Z
**Status:** human_needed
**Re-verification:** No — initial verification

## Goal Achievement

### Observable Truths

| # | Truth | Status | Evidence |
|---|-------|--------|----------|
| 1 | Touching the TPS43 trackpad on the right half moves the mouse cursor on screen | ✓ VERIFIED (HUMAN) | Hardware checkpoint (Task 2) approved by user — cursor movement confirmed smooth |
| 2 | Cursor movement is smooth and responsive (no jitter, no stuck axes) | ✓ VERIFIED (HUMAN) | Hardware checkpoint (Task 2) approved by user — "cursor movement smooth" |
| 3 | Auto mouse layer activates when the trackpad is touched and deactivates after movement stops | ✓ VERIFIED (HUMAN) | Hardware checkpoint (Task 2) approved by user — "auto mouse layer activates/deactivates" |
| 4 | Joystick custom keys mode still works on the left half (matrix_scan_user unchanged) | ✓ VERIFIED | matrix_scan_user function intact (lines 281-331), reads ADC from GP28/GP29, fires dynamic keymap keycodes |

**Score:** 4/4 truths verified (1 automated, 3 via hardware checkpoint)

### Required Artifacts

| Artifact | Expected | Status | Details |
|----------|----------|--------|---------|
| keyboards/hidpress/bipedalambi/config.h | POINTING_DEVICE_AUTO_MOUSE_ENABLE and AUTO_MOUSE_DEFAULT_LAYER defines | ✓ VERIFIED | Lines 70-73: POINTING_DEVICE_AUTO_MOUSE_ENABLE, AUTO_MOUSE_DEFAULT_LAYER 3, AUTO_MOUSE_TIME 650, AUTO_MOUSE_THRESHOLD 10 |
| keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c | pointing_device_init_user enabling auto mouse, simplified pointing_device_task_user for TPS43 | ✓ VERIFIED | Line 80-82: pointing_device_init_user calls set_auto_mouse_enable(true). Lines 339-342: pointing_device_task_user is substantive pass-through (registers OLED activity, returns report unchanged) |

### Key Link Verification

| From | To | Via | Status | Details |
|------|-----|-----|--------|---------|
| config.h | quantum/pointing_device/pointing_device_auto_mouse.c | POINTING_DEVICE_AUTO_MOUSE_ENABLE preprocessor define | ✓ WIRED | Build output confirms: "Compiling: quantum/pointing_device/pointing_device_auto_mouse.c [OK]" |
| keymap.c | quantum/pointing_device/pointing_device_auto_mouse.h | set_auto_mouse_enable(true) call in pointing_device_init_user | ✓ WIRED | Function call present at line 81, declaration in auto_mouse.h, no build errors |
| quantum/pointing_device/pointing_device_drivers.c (azoteq_iqs5xx_get_report) | keymap.c (pointing_device_task_user) | QMK pointing device pipeline: driver -> task_user -> HID report | ✓ WIRED | Build output confirms: "Compiling: drivers/sensors/azoteq_iqs5xx.c [OK]", task_user is pass-through at lines 339-342 |

### Requirements Coverage

| Requirement | Status | Blocking Issue |
|-------------|--------|----------------|
| TPAD-01: TPS43 trackpad moves the mouse cursor on the right half | ✓ SATISFIED | Hardware checkpoint approved — cursor movement confirmed working |
| TPAD-08: Auto mouse layer activates on trackpad movement | ✓ SATISFIED | Hardware checkpoint approved — layer activation/deactivation confirmed |

### Anti-Patterns Found

None. All files clean — no TODOs, FIXMEs, placeholders, or stub implementations.

**Specific checks:**
- No scroll accumulator variables (SCROLL_DIVISOR_H/V, scroll_accumulated_h/v, scroll_inverted) — correctly removed per plan
- SCROLL_DIR case handler removed from process_record_user — confirmed absent
- MODE enum (MODE_MOUSE, MODE_SCROLLING, MODE_CUSTOM_KEYS) preserved for Phase 15 — confirmed present in bipedalambi.h
- matrix_scan_user unchanged — confirmed intact (lines 281-331)
- pointing_device_task_user is not a stub — it registers OLED activity and returns the report (substantive pass-through)

### Build Verification

Both halves compile cleanly:

```
make hidpress/bipedalambi:vial         # Left half — OK
make hidpress/bipedalambi:vial SIDE=right  # Right half — OK
```

Build log confirms auto_mouse and azoteq driver compiled:
- `Compiling: quantum/pointing_device/pointing_device_auto_mouse.c [OK]`
- `Compiling: drivers/sensors/azoteq_iqs5xx.c [OK]`

### Commit Verification

Commit `1444a10156` verified:
- Files modified: config.h, keymaps/vial/keymap.c
- Changes: Added POINTING_DEVICE_AUTO_MOUSE_ENABLE defines, pointing_device_init_user, simplified pointing_device_task_user, removed scroll accumulator code
- Commit message matches plan intent

### Human Verification Required

**All three hardware verification items were completed during Task 2 (hardware checkpoint) and approved by the user.** The user confirmed:

> "All hardware tests pass: cursor movement smooth, auto mouse layer 3 activates on trackpad use and deactivates after timeout, joystick and OLED unaffected."

Specific tests performed:

#### 1. TPS43 Trackpad Cursor Movement

**Test:** Touch and slide finger on TPS43 trackpad on the right half, move cursor across screen in all directions.

**Expected:** Cursor follows finger direction smoothly (no jitter, no stuck axes). Movement feels natural (not too fast, not too slow). Lifting finger stops cursor movement.

**Why human:** Requires actual hardware with physical trackpad and visual observation of on-screen cursor behavior.

**Status:** ✓ Approved by user (Task 2 checkpoint)

#### 2. Auto Mouse Layer Activation/Deactivation

**Test:** Open Vial. Touch trackpad and move cursor. Stop touching. Observe layer indicator in Vial.

**Expected:** Layer 3 activates when trackpad is touched and movement occurs. Layer 3 deactivates approximately 650ms after trackpad is released and movement stops.

**Why human:** Requires Vial GUI observation and timing verification (650ms timeout).

**Status:** ✓ Approved by user (Task 2 checkpoint)

#### 3. Joystick Custom Keys Mode Unaffected

**Test:** With TMB_MODE set to custom keys mode on left half, move joystick in all four cardinal directions. Verify keycodes fire from dynamic keymap positions [0,7], [1,7], [2,7], [3,7].

**Expected:** Joystick still works independently via matrix_scan_user ADC reads. No regression from TPS43 changes.

**Why human:** Requires physical joystick testing.

**Status:** ✓ Approved by user (Task 2 checkpoint)

### Summary

Phase 13 goal achieved. All automated verification passed, and the user completed hardware verification via Task 2 checkpoint with approval. The TPS43 trackpad produces smooth cursor movement on the right half, auto mouse layer 3 activates/deactivates correctly, and joystick custom keys mode remains unaffected on the left half.

**Key accomplishments:**
- TPS43 driver output wired to cursor movement via QMK pointing device pipeline
- Auto mouse layer system configured and enabled (layer 3, 650ms timeout, threshold 10)
- pointing_device_task_user simplified to pass-through (driver handles all gestures)
- Scroll accumulator code removed (TPS43 driver produces scroll values natively)
- Both halves compile cleanly with auto_mouse.c and azoteq_iqs5xx.c
- Hardware tests confirmed working: cursor smooth, auto mouse layer activates/deactivates, joystick unaffected

**Ready for Phase 14:** Trackpad gestures (tap, two-finger tap, scroll, drag, swipe).

---

_Verified: 2026-02-22T17:35:00Z_
_Verifier: Claude (gsd-verifier)_
