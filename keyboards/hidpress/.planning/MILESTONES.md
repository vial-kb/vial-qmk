# Milestones

## v1.0 EEPROM / Vial Layer Fix (Shipped: 2026-02-14)

**Phases completed:** 8 phases, 10 plans
**Timeline:** 2026-02-13 to 2026-02-14 (2 days)

**Delivered:** Fixed the Vial layer offset bug on the Bipedal Ambi split keyboard — keycodes now persist correctly and layers display without offset in the Vial GUI.

**Key accomplishments:**
- Fixed vial.json matrix rows (4 to 8) in both halves to match config.h MATRIX_ROWS
- Remapped right-half KLE positions for standalone operation (rows 0-3, not 4-7)
- Fixed NUM_ENCODERS split-doubling (set to 1 explicitly)
- Verified EEPROM budget: 568 bytes / 4096 bytes (13.9%) — no collisions
- Added eeconfig_init_user for safe EEPROM clear defaults on both halves
- Added EE_CLR keycode to both keymaps for easy EEPROM clearing
- Compiled, flashed, and verified both halves working in Vial

**Archive:** `milestones/v1.0-ROADMAP.md`, `milestones/v1.0-REQUIREMENTS.md`

---

## v1.1 Split Serial Communication Fix (Shipped: 2026-02-22)

**Phases completed:** 3 phases (9-11), 4 plans, 10 tasks
**Timeline:** 2026-02-14 to 2026-02-22 (8 days)

**Delivered:** Diagnosed and fixed split serial communication failure — root cause was `MASTER_LEFT` misidentifying the right half. Replaced with `EE_HANDS` + `SPLIT_USB_DETECT` for permanent per-side handedness via EEPROM.

**Key accomplishments:**
- Exhaustive serial/split configuration audit: identified HAL_USE_SIO misconfiguration, eliminated WS2812 PIO conflict hypothesis
- Diagnostic testing funnel: 4 of 7 tests executed (DIAG-00, DIAG-02, DIAG-05, DIAG-06), all firmware config hypotheses eliminated
- Root cause identified: `MASTER_LEFT` misidentified right half — broke serial transport, bootmagic, and joystick reads
- Fix: `EE_HANDS` + `SPLIT_USB_DETECT` + `INIT_EE_HANDS_LEFT/RIGHT` — serial working, USB from either side
- Unified keymap (`vial_left` + `vial_right` → `vial`) with compile-time `SIDE=right` selection
- Added split bootmagic, ENC_MOD keycode, fixed joystick X-axis inversion in custom key mode

**Known Gaps:**
- DIAG-01, DIAG-03, DIAG-04: Not tested (mooted by finding the actual root cause)
- DIAG-06: Inconclusive (debug_config.enable was false at runtime)
- Phase 11 (Verdict): Never formally planned/executed — root cause found outside GSD workflow

**Archive:** `milestones/v1.1-ROADMAP.md`, `milestones/v1.1-REQUIREMENTS.md`

---


## v1.2 TPS43 Trackpad (Shipped: 2026-02-22)

**Phases completed:** 4 phases (12-15), 4 plans
**Timeline:** 2026-02-22 (1 day)

**Delivered:** Added Azoteq TPS43 trackpad to the right half as the primary pointing device, refactored joystick to custom keys and scroll modes only.

**Key accomplishments:**
- Switched pointing device driver to azoteq_iqs5xx (TPS43 43mm trackpad) with I2C bus sharing on right half
- TPS43 trackpad cursor movement with QMK auto mouse layer 3 activation on touch
- Enabled 4/5 gesture types: single-finger tap, two-finger tap, scroll, press-and-hold drag
- Phantom right-click filter for TPS43 EMI false positives when right side is USB master
- Removed joystick mouse mode, added scroll wheel keycodes from ADC (2-mode system)
- Split transport for joystick ADC sync (slave-to-master) and state sync (master-to-slave for OLED)

**Known Gaps:**
- TPAD-06: Swipe gestures (back/forward) deferred — TPS43 hardware swipe unreliable on 43mm pad, needs software-based approach

**Archive:** `milestones/v1.2-ROADMAP.md`, `milestones/v1.2-REQUIREMENTS.md`

---

