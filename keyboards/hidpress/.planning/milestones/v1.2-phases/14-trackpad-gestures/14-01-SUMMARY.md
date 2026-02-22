# Summary: 14-01 — Trackpad Gestures

## Result: PARTIAL — 4/5 gesture types working

**Duration:** ~45min (including hardware debug iterations)
**Tasks:** 2/2 complete (Task 1 auto, Task 2 hardware checkpoint)
**Deviation:** TPAD-06 (swipe/back-forward) deferred — TPS43 hardware swipe unreliable on 43mm pad

## What Was Built

Enabled TPS43 trackpad gestures via config.h overrides and added a phantom right-click filter for right-side-master EMI noise.

### Gestures Working
- **Single-finger tap** → left click (TPAD-02) — already enabled by default
- **Two-finger tap** → right click (TPAD-03) — already enabled by default, phantom filter added
- **Two-finger scroll** → scroll up/down (TPAD-04) — already enabled by default
- **Press-and-hold** → drag / held left click (TPAD-05) — enabled via config.h override

### Gestures Not Working
- **Horizontal swipe** → back/forward (TPAD-06) — TPS43 hardware gesture engine cannot reliably detect swipes on a 43mm pad. Tested with thresholds from 300 down to 50 units, 100ms to 500ms window. Gesture fires intermittently. Disabled in config. Requires software-based swipe detection in a future phase.

### Phantom Right-Click Filter
When the right side is USB master, EMI causes false `two_finger_tap` events ~3s after idle. Filter in `pointing_device_task_user`:
- Only active when right side is master (`!is_keyboard_left() && is_keyboard_master()`)
- Suppresses BUTTON2 when no touch activity for >2 seconds
- Double two-finger-tap within 500ms overrides the suppression
- No effect when left side is master (normal use)

## Decisions

- TPAD-06 deferred: TPS43 hardware swipe detection unreliable on 43mm pad, needs software approach
- Phantom filter only on right-master: left-master has no EMI issue, zero overhead
- Double-tap override: user can force right-click after idle with two quick two-finger taps

## Key Files

### Modified
- `keyboards/hidpress/bipedalambi/config.h` — gesture enable overrides
- `keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c` — phantom right-click filter

### Commits
- `e7da44de` — Task 1: initial gesture config (press-and-hold + swipe enables)
- `3a4bf1e6` — Task 2: disable unreliable swipe, add phantom filter with double-tap override

## Self-Check: PARTIAL

- [x] config.h contains AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE=true
- [x] Both halves compile cleanly
- [x] TPAD-02: Single-finger tap → left click verified on hardware
- [x] TPAD-03: Two-finger tap → right click verified on hardware
- [x] TPAD-04: Two-finger scroll verified on hardware
- [x] TPAD-05: Press-and-hold drag verified on hardware
- [ ] TPAD-06: Swipe back/forward — UNRELIABLE, disabled, deferred
- [x] Phantom right-click filter working (right-master only)
- [x] Existing functionality (cursor, auto mouse, joystick, OLED) unaffected
