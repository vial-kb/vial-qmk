---
phase: 15-joystick-refactor
verified: 2026-02-22T19:30:00Z
status: passed
score: 5/5 must-haves verified
---

# Phase 15: Joystick Refactor Verification Report

**Phase Goal:** Joystick operates in only two modes (custom keys and scroll), with scroll mode sending mouse wheel keycodes directly from ADC, and mode cycling updated

**Verified:** 2026-02-22T19:30:00Z

**Status:** passed

**Re-verification:** No — initial verification

## Goal Achievement

### Observable Truths

| # | Truth | Status | Evidence |
|---|-------|--------|----------|
| 1 | Joystick custom keys mode fires directional keycodes from dynamic keymap (unchanged behavior) | ✓ VERIFIED | matrix_scan_user() MODE_CUSTOM_KEYS branch (lines 286-331) reads keycodes via dynamic_keymap_get_keycode() and fires them with handle_joystick_keycode() |
| 2 | Joystick scroll mode sends KC_MS_WH_UP/DOWN/LEFT/RIGHT based on ADC deflection | ✓ VERIFIED | matrix_scan_user() MODE_SCROLLING branch (lines 332-368) uses tap_code() to send all 4 wheel keycodes based on actuation threshold |
| 3 | TMB_MODE keycode cycles between exactly 2 modes: custom keys and scroll | ✓ VERIFIED | TMB_MODE handler (line 184) uses modulo MODE_COUNT, where MODE_COUNT=2 per enum in bipedalambi.h line 9 |
| 4 | Selected joystick mode persists in EEPROM across power cycles | ✓ VERIFIED | save_layer_config_to_eeprom() encodes mode in bits 0-7 (line 38-48), load_layer_config_from_eeprom() decodes and validates mode < MODE_COUNT (line 51-64) |
| 5 | No mouse mode code remains — joystick never moves the mouse cursor | ✓ VERIFIED | Zero matches for MODE_MOUSE and _on_mouse across entire bipedalambi/ directory, only 2 modes in enum |

**Score:** 5/5 truths verified

### Required Artifacts

| Artifact | Expected | Status | Details |
|----------|----------|--------|---------|
| keyboards/hidpress/bipedalambi/bipedalambi.h | Two-mode enum with MODE_COUNT | ✓ VERIFIED | Enum contains MODE_CUSTOM_KEYS=0, MODE_SCROLLING=1, MODE_COUNT=2 (lines 6-10). Comment clarifies "2 modes, no mouse" |
| keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c | Scroll mode wheel keycode emission, updated TMB_MODE cycling, updated EEPROM defaults | ✓ VERIFIED | 4 tap_code() calls for KC_MS_WH_UP/DOWN/LEFT/RIGHT (lines 340,348,356,364). TMB_MODE cycles via % MODE_COUNT (line 184). Default MODE_CUSTOM_KEYS in layer_modes[] (line 22), load_layer_config_from_eeprom() fallback (line 56), eeconfig_init_user() comment (line 67) |
| keyboards/hidpress/bipedalambi/bipedalambi.c | OLED display with mouse mode arrays removed | ✓ VERIFIED | Zero matches for _on_mouse arrays. render_layer_state() switch statements (lines 102-134) only handle MODE_SCROLLING and MODE_CUSTOM_KEYS. Default case falls back to "LAYER: UNKNOWN". current_mode initialized to MODE_CUSTOM_KEYS (line 4) |

**All artifacts verified at 3 levels:**
- Level 1 (exists): All files present
- Level 2 (substantive): All files contain expected patterns and logic
- Level 3 (wired): All artifacts properly imported and used

### Key Link Verification

| From | To | Via | Status | Details |
|------|-----|-----|--------|---------|
| keymap.c | bipedalambi.h | MODE_CUSTOM_KEYS and MODE_SCROLLING enum values | ✓ WIRED | 2 matches in keymap.c: line 286 (if current_mode == MODE_CUSTOM_KEYS), line 332 (else if current_mode == MODE_SCROLLING). Enum defined in bipedalambi.h lines 7-8 |
| keymap.c | EEPROM | save/load_layer_config_to_eeprom with 1-bit mode encoding | ✓ WIRED | save_layer_config_to_eeprom() calls eeconfig_update_user() (line 48), load_layer_config_from_eeprom() calls eeconfig_read_user() (line 52). 2-bit mode encoding (2 bits * 4 layers = 8 bits total in bits 0-7) |
| bipedalambi.c | bipedalambi.h | OLED render_layer_state uses MODE_SCROLLING and MODE_CUSTOM_KEYS only | ✓ WIRED | 8 matches: 4 for MODE_SCROLLING (lines 105,112,119,126), 4 for MODE_CUSTOM_KEYS (lines 106,113,120,127). Each layer's switch statement references both modes from enum |

### Requirements Coverage

| Requirement | Status | Blocking Issue |
|-------------|--------|----------------|
| JOY-01: Custom keys mode works unchanged (directional keycodes from dynamic keymap) | ✓ SATISFIED | None — matrix_scan_user() MODE_CUSTOM_KEYS logic unchanged from previous phases |
| JOY-02: Scroll mode sends mouse wheel keycodes (KC_MS_WH_*) directly from ADC reads | ✓ SATISFIED | None — 4 wheel keycodes emitted via tap_code() based on ADC deflection and actuation threshold |
| JOY-03: Mouse mode removed -- only custom keys and scroll modes remain | ✓ SATISFIED | None — MODE_MOUSE completely removed from enum, OLED, and keymap. MODE_COUNT=2 |
| JOY-04: TMB_MODE cycles between custom keys and scroll (2 modes) | ✓ SATISFIED | None — TMB_MODE uses modulo MODE_COUNT where MODE_COUNT=2 |
| JOY-05: Mode selection persists in EEPROM across power cycles | ✓ SATISFIED | None — save/load EEPROM functions encode/decode mode with validation (mode < MODE_COUNT fallback to MODE_CUSTOM_KEYS) |

**All 5 requirements satisfied.** Phase 15 fully meets milestone v1.2 joystick refactor goals.

### Anti-Patterns Found

No anti-patterns detected.

**Scan coverage:**
- TODO/FIXME/PLACEHOLDER comments: 0 matches
- Empty implementations (return null/empty): 0 matches
- Console.log-only handlers: N/A (C firmware)
- Stub patterns: None detected

**Files scanned:**
- keyboards/hidpress/bipedalambi/bipedalambi.h
- keyboards/hidpress/bipedalambi/bipedalambi.c
- keyboards/hidpress/bipedalambi/keymaps/vial/keymap.c
- keyboards/hidpress/bipedalambi/EEPROM-CLEAR-PROCEDURE.md

**Build verification:**
- Left half UF2: hidpress_bipedalambi_vial_LEFT.uf2 (140288 bytes, 2026-02-22 19:14)
- Right half UF2: hidpress_bipedalambi_vial_RIGHT.uf2 (140288 bytes, 2026-02-22 19:14)
- Both halves compiled successfully per SUMMARY commits

### Human Verification Required

#### 1. Scroll Mode Functional Test

**Test:** Flash both halves with phase 15 UF2 files. Connect the keyboard. Press TMB_MODE to cycle to scroll mode (OLED should show scroll icon). Deflect the joystick in all 4 directions (up, down, left, right).

**Expected:** 
- Each joystick deflection past the actuation threshold sends exactly 1 scroll event (page scrolls by 1 line/notch)
- Holding joystick deflected does NOT repeat scroll events — must return to center and deflect again for next scroll
- All 4 directions produce distinct scroll events (up scrolls up, down scrolls down, left scrolls left, right scrolls right)
- Scroll sensitivity matches actuation threshold (adjustable via ACT_UP/ACT_DOWN keys)

**Why human:** 
- Scroll behavior requires visual confirmation in a browser/document
- Wheel keycode emission can't be verified without OS-level scroll events
- Directional mapping (ADC X/Y to scroll LEFT/RIGHT/UP/DOWN) needs real-time testing

#### 2. Mode Cycling Test

**Test:** Flash both halves. Press TMB_MODE repeatedly. Observe OLED display.

**Expected:**
- OLED cycles between exactly 2 icons: custom keys (arrow/keycode icon) and scroll (scroll icon)
- After 2 presses, mode returns to starting mode (cycles in order: custom keys → scroll → custom keys)
- No third mode appears (no mouse cursor icon)
- Mode change persists across power cycles (unplug/replug USB, mode stays as last selected)

**Why human:**
- OLED icon display requires visual confirmation
- Mode persistence across power cycles requires physical USB unplug/replug
- Can't verify mode count without observing full cycle

#### 3. Custom Keys Mode Regression Test

**Test:** Flash both halves. Ensure TMB_MODE is set to custom keys mode (OLED shows keycode icon). Deflect joystick in all 4 directions.

**Expected:**
- Joystick fires directional keycodes exactly as in previous firmware (no behavior change)
- Keycodes can be remapped in Vial (matrix positions 0,7 / 1,7 / 2,7 / 3,7)
- Custom keys mode is the default after EEPROM clear (verified in EEPROM doc)

**Why human:**
- Keycode firing requires application-level verification (text input, key tester)
- Vial dynamic keymap remapping requires GUI interaction
- Regression testing needs comparison with previous phase behavior

#### 4. EEPROM Persistence Test

**Test:** Set joystick to scroll mode via TMB_MODE. Power cycle the keyboard (unplug USB, replug). Change actuation level via ACT_UP. Power cycle again.

**Expected:**
- After first power cycle, joystick mode is still scroll (OLED shows scroll icon)
- After second power cycle, actuation level is still the adjusted value (OLED bar position matches when ACT_UP/DOWN is pressed)
- Mode and actuation persist independently per layer (change layer via encoder, TMB_MODE sets mode for that layer only)

**Why human:**
- Requires physical USB power cycling to verify EEPROM reads on boot
- OLED display state needs visual confirmation
- Per-layer mode persistence requires layer switching and multi-step verification

---

_Verified: 2026-02-22T19:30:00Z_

_Verifier: Claude (gsd-verifier)_
