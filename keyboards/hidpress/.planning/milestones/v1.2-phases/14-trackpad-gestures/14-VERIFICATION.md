---
phase: 14-trackpad-gestures
verified: 2026-02-22T19:30:00+11:00
status: gaps_found
score: 4/5 must-haves verified
gaps:
  - truth: "Horizontal swipe gestures register as browser back/forward on host"
    status: failed
    reason: "TPS43 hardware swipe detection unreliable on 43mm pad — requires software-based approach"
    artifacts:
      - path: "keyboards/hidpress/bipedalambi/config.h"
        issue: "AZOTEQ_IQS5XX_SWIPE_X_ENABLE commented out (line 82)"
    missing:
      - "Software-based swipe detection algorithm in pointing_device_task_user"
      - "Velocity tracking and threshold-based swipe recognition"
      - "Mapping detected swipes to POINTING_DEVICE_BUTTON4/BUTTON5"
human_verification:
  - test: "Verify phantom right-click filter works correctly"
    expected: "Two-finger tap after 2+ seconds idle should be suppressed (unless double-tapped within 500ms)"
    why_human: "EMI-induced phantom events require real hardware observation across idle/active states"
  - test: "Verify all working gestures feel responsive"
    expected: "Tap, two-finger tap, scroll, and drag should feel natural with no latency or missed inputs"
    why_human: "User experience quality requires human judgment of timing and feel"
---

# Phase 14: Trackpad Gestures Verification Report

**Phase Goal:** All TPS43 gesture types register as the correct mouse events -- taps, scrolls, drag, and navigation swipes
**Verified:** 2026-02-22T19:30:00+11:00
**Status:** gaps_found
**Re-verification:** No — initial verification

## Goal Achievement

### Observable Truths

| #   | Truth                                                                   | Status     | Evidence                                                                                                                           |
| --- | ----------------------------------------------------------------------- | ---------- | ---------------------------------------------------------------------------------------------------------------------------------- |
| 1   | Single-finger tap on trackpad registers as left click on host          | ✓ VERIFIED | Default enabled (AZOTEQ_IQS5XX_TAP_ENABLE=true), driver wiring confirmed (pointing_device_drivers.c:163-165), hardware verified   |
| 2   | Two-finger tap on trackpad registers as right click on host            | ✓ VERIFIED | Default enabled (AZOTEQ_IQS5XX_TWO_FINGER_TAP_ENABLE=true), driver wiring confirmed (line 166-168), phantom filter added          |
| 3   | Two-finger vertical slide scrolls content up/down on host              | ✓ VERIFIED | Default enabled (AZOTEQ_IQS5XX_SCROLL_ENABLE=true), driver wiring confirmed (line 193-196), hardware verified                      |
| 4   | Press-and-hold on trackpad enables drag (held left click) on host      | ✓ VERIFIED | Enabled via config.h override (line 79), driver wiring confirmed (line 163-165), hardware verified                                |
| 5   | Horizontal swipe gestures register as browser back/forward on host     | ✗ FAILED   | Disabled in config.h (line 82 commented out) — TPS43 hardware swipe unreliable on 43mm pad, deferred to software-based detection |

**Score:** 4/5 truths verified

### Required Artifacts

| Artifact                                     | Expected                                            | Status     | Details                                                                                         |
| -------------------------------------------- | --------------------------------------------------- | ---------- | ----------------------------------------------------------------------------------------------- |
| `keyboards/hidpress/bipedalambi/config.h`    | Gesture enable overrides                            | ✓ VERIFIED | AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE=true (line 79), SWIPE_X_ENABLE commented out (line 82)     |
| `keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c` | Phantom right-click filter (bonus artifact) | ✓ VERIFIED | pointing_device_task_user (lines 343-380): 2s idle gate, double-tap override, right-master only |

### Key Link Verification

| From                                         | To                                    | Via                                                   | Status     | Details                                                                                                           |
| -------------------------------------------- | ------------------------------------- | ----------------------------------------------------- | ---------- | ----------------------------------------------------------------------------------------------------------------- |
| `keyboards/hidpress/bipedalambi/config.h`    | `drivers/sensors/azoteq_iqs5xx.c`     | #ifndef guard — config.h defines override defaults   | ✓ WIRED    | azoteq_iqs5xx.c lines 32-33 check for PRESS_AND_HOLD_ENABLE, lines 41-42 check for SWIPE_X_ENABLE                |
| `drivers/sensors/azoteq_iqs5xx.c`            | `quantum/pointing_device/pointing_device_drivers.c` | Gesture events → button mapping | ✓ WIRED    | Tap/hold→BTN1 (163-165), two-finger→BTN2 (166-168), scroll→h/v (193-196), swipe_x→BTN4/5 (169-176)              |

### Requirements Coverage

| Requirement | Description                                         | Status       | Blocking Issue                                     |
| ----------- | --------------------------------------------------- | ------------ | -------------------------------------------------- |
| TPAD-02     | Single-finger tap registers as left click          | ✓ SATISFIED  | —                                                  |
| TPAD-03     | Two-finger tap registers as right click            | ✓ SATISFIED  | —                                                  |
| TPAD-04     | Two-finger scroll sends scroll events              | ✓ SATISFIED  | —                                                  |
| TPAD-05     | Press-and-hold emulates held left click (drag)     | ✓ SATISFIED  | —                                                  |
| TPAD-06     | Swipe gestures register as mouse buttons 4/5       | ✗ BLOCKED    | TPS43 hardware swipe unreliable, needs software approach |

**Coverage:** 4/5 requirements satisfied (80%)

### Anti-Patterns Found

| File                      | Line | Pattern                                                           | Severity | Impact                                                                                   |
| ------------------------- | ---- | ----------------------------------------------------------------- | -------- | ---------------------------------------------------------------------------------------- |
| config.h                  | 82   | Commented-out define: AZOTEQ_IQS5XX_SWIPE_X_ENABLE                | 🛑 Blocker | TPAD-06 requirement not satisfied — swipe back/forward gestures do not work              |
| SUMMARY.md                | 20   | "TPS43 hardware swipe detection is unreliable on 43mm pad"        | ⚠️ Warning | Root cause documented — gestures fire intermittently despite tuning attempts             |
| config.h                  | 81   | Comment: "TPAD-06 (back/forward) deferred to software-based..."   | ℹ️ Info   | Deviation acknowledged with future work path                                             |

### Human Verification Required

#### 1. Phantom Right-Click Filter Effectiveness

**Test:** 
1. Flash with right side as USB master
2. Touch trackpad, then wait 3+ seconds without touching
3. Two-finger tap should be suppressed
4. Immediately two-finger tap again within 500ms — should NOT be suppressed (override)

**Expected:** First tap after idle is suppressed, second tap within 500ms is allowed

**Why human:** EMI-induced phantom events occur unpredictably after idle. Requires real hardware observation of right-master-only behavior and timing validation.

#### 2. Gesture Responsiveness and Feel

**Test:** 
1. Perform each working gesture 10+ times:
   - Single-finger tap (left click)
   - Two-finger tap (right click)
   - Two-finger vertical scroll
   - Press-and-hold drag
2. Evaluate latency, missed inputs, false positives

**Expected:** All gestures feel responsive, natural, and reliable with no perceptible lag or dropped inputs

**Why human:** User experience quality requires human judgment of timing, tactile feel, and subjective responsiveness.

#### 3. Existing Functionality Regression Check

**Test:** Verify pre-Phase 14 functionality still works:
- Cursor movement (single-finger slide)
- Auto mouse layer activation/deactivation
- Joystick custom keys on left half
- OLED display updates

**Expected:** All existing features work identically to Phase 13

**Why human:** Hardware integration testing — verifies no unintended side effects from gesture config changes or phantom filter logic.

### Gaps Summary

**1 gap blocking full goal achievement:**

**TPAD-06 (Swipe Back/Forward):** The TPS43 hardware gesture engine cannot reliably detect swipes on a 43mm trackpad. The SUMMARY documents tuning attempts (thresholds 300→50 units, windows 100ms→500ms), but gestures fire intermittently. `AZOTEQ_IQS5XX_SWIPE_X_ENABLE` is disabled in config.h (line 82).

**Root cause:** Hardware limitation — TPS43 swipe detection designed for larger touch surfaces.

**Required to close gap:**
1. Implement software-based swipe detection in `pointing_device_task_user`:
   - Track single-finger velocity and distance over time windows
   - Detect quick horizontal movements (swipe pattern)
   - Distinguish swipe from slow cursor movement
   - Map detected swipes to POINTING_DEVICE_BUTTON4 (swipe left / back) and POINTING_DEVICE_BUTTON5 (swipe right / forward)
2. Add EEPROM config for swipe sensitivity (optional)
3. Hardware test to verify false-positive rate is acceptable

**Phase goal partial achievement:** 4/5 gesture types working (80%). TPAD-06 deferred to future phase.

**Bonus work completed (not in original plan):**
- Phantom right-click filter for right-master mode (lines 343-380 in keymap.c)
- 2-second idle gate with double-tap override
- Addresses EMI-induced false two_finger_tap events

### Verification Details

**Build verification:**
```
make hidpress/bipedalambi:vial — compiles cleanly
make hidpress/bipedalambi:vial:clean && make hidpress/bipedalambi:vial SIDE=right — compiles cleanly
```

**Commits verified:**
- `e7da44de` — Initial gesture config (press-and-hold + swipe enables)
- `3a4bf1e6` — Disable unreliable swipe, add phantom filter with double-tap override

**Driver wiring verified:**
- `drivers/sensors/azoteq_iqs5xx.c` lines 29-49: #ifndef guards for all gesture enables
- `quantum/pointing_device/pointing_device_drivers.c` lines 163-196: Gesture event → button/scroll mapping
- Default enables: TAP (true), TWO_FINGER_TAP (true), SCROLL (true)
- Default disables: PRESS_AND_HOLD (false → overridden to true), SWIPE_X/Y (false), ZOOM (false)

**Hardware verification (per SUMMARY self-check):**
- ✓ TPAD-02: Single-finger tap → left click
- ✓ TPAD-03: Two-finger tap → right click
- ✓ TPAD-04: Two-finger scroll
- ✓ TPAD-05: Press-and-hold drag
- ✗ TPAD-06: Swipe back/forward — unreliable, disabled
- ✓ Phantom right-click filter working (right-master only)
- ✓ Existing functionality unaffected

---

_Verified: 2026-02-22T19:30:00+11:00_
_Verifier: Claude Code (gsd-verifier)_
