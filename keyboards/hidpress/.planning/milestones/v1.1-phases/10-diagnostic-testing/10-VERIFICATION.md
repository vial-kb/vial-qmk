---
phase: 10-diagnostic-testing
verified: 2026-02-15T14:30:00Z
status: gaps_found
score: 4/5 must-haves verified
gaps:
  - truth: "If no single test resolves the issue, console debug output from the serial driver is captured and available for verdict analysis"
    status: partial
    reason: "DIAG-06 executed with CONSOLE_ENABLE and SERIAL_DEBUG but produced zero debug output because debug_config.enable runtime flag defaults to false -- all dprintf/dprintln calls are gated by this flag"
    artifacts:
      - path: "keyboards/hidpress/bipedalambi/config.h"
        issue: "SERIAL_DEBUG defined but not sufficient -- need debug_enable=true at runtime"
      - path: "keyboards/hidpress/bipedalambi/rules.mk"
        issue: "CONSOLE_ENABLE added but console output gated by runtime flag"
    missing:
      - "Set debug_enable = true in keyboard_post_init_user() in keymap.c files"
      - "OR add DB_TOGG key to keymap for user to enable debug at runtime"
      - "Reflash and capture console output showing PIO init state and transaction failures"
---

# Phase 10: Diagnostic Testing Verification Report

**Phase Goal:** Each suspected misconfiguration is tested with an isolated, reversible firmware change -- user flashes and reports results for each test

**Verified:** 2026-02-15T14:30:00Z
**Status:** gaps_found
**Re-verification:** No -- initial verification

## Goal Achievement

### Observable Truths

| # | Truth | Status | Evidence |
|---|-------|--------|----------|
| 1 | PIO conflict between WS2812 and serial is either confirmed fixed (slave keys register) or ruled out as the cause | ✓ VERIFIED | DIAG-01 SKIPPED -- Phase 9 audit AUDIT-03 proved WS2812 driver never compiled (RGBLIGHT disabled), no conflict exists |
| 2 | Full-duplex vs half-duplex communication mode is either confirmed working or ruled out, with user-reported test results | ✓ VERIFIED | DIAG-02 EXECUTED: switched to half-duplex (commented SERIAL_USART_FULL_DUPLEX), user tested, result FAIL -- both modes fail identically, wiring hypothesis (H2) eliminated |
| 3 | Each diagnostic test that was executed has a clear pass/fail result documented with the exact config change made and the user-observed behavior | ✓ VERIFIED | All executed tests (DIAG-00, DIAG-02, DIAG-05, DIAG-06) documented in SUMMARYs with: config changes (commits 0dddbd7, a007619, af3429c, 1ff504e), user reports verbatim, pass/fail results |
| 4 | Tests skipped (because a prior test resolved the issue or audit ruled out the hypothesis) are documented with the reason for skipping | ✓ VERIFIED | DIAG-01 skipped (audit eliminated WS2812 conflict), DIAG-03 skipped (DIAG-02 FAIL eliminated wiring), DIAG-04 skipped (PATH A only, DIAG-02 was FAIL = PATH B) -- all documented with reasons in 10-03-SUMMARY.md |
| 5 | If no single test resolves the issue, console debug output from the serial driver is captured and available for verdict analysis | ✗ PARTIAL | DIAG-06 executed: CONSOLE_ENABLE added to rules.mk, SERIAL_DEBUG added to config.h (commit 1ff504e), console connected successfully BUT zero debug output because debug_config.enable runtime flag was false -- all dprintf/dprintln calls gated by this flag (see gaps) |

**Score:** 4/5 truths fully verified (Truth #5 partially met)

### Required Artifacts

| Artifact | Expected | Status | Details |
|----------|----------|--------|---------|
| `keyboards/hidpress/bipedalambi/config.h` | Board config modified per diagnostic path | ✓ VERIFIED | Full-duplex restored (line 6), SPLIT_USB_DETECT commented (line 7), MASTER_LEFT added (line 8), SERIAL_DEBUG added (line 10) |
| `keyboards/hidpress/bipedalambi/rules.mk` | CONSOLE_ENABLE for DIAG-06 | ✓ VERIFIED | CONSOLE_ENABLE = yes added (line 16) |
| `keyboards/hidpress/bipedalambi/halconf.h` | SIO removed in DIAG-00 | ✓ VERIFIED | HAL_USE_SIO removed, only HAL_USE_I2C and HAL_USE_ADC remain (5 lines total) |
| `keyboards/hidpress/bipedalambi/mcuconf.h` | UART0/UART1 removed in DIAG-00 | ✓ VERIFIED | UART blocks removed, only I2C0, I2C1, ADC1 config remain (15 lines total) |

**All artifacts exist, substantive, and wired.**

### Key Link Verification

| From | To | Via | Status | Details |
|------|-----|-----|--------|---------|
| config.h SERIAL_USART_PIN_SWAP | serial_vendor.c pio_init() argument order | PIN_SWAP swaps TX/RX args on master init only | N/A | DIAG-04 SKIPPED -- PATH A only (wiring test), DIAG-02 FAIL = PATH B |
| config.h MASTER_LEFT | split detection logic | Replaces SPLIT_USB_DETECT runtime check with compile-time constant | ⚠️ PARTIAL | MASTER_LEFT defined (line 8), SPLIT_USB_DETECT commented (line 7), BUT critical finding: MASTER_LEFT only affects handedness (is_keyboard_left), NOT master detection -- is_keyboard_master still calls usb_bus_detected() |
| config.h SERIAL_DEBUG | serial_vendor.c debug macros | Enables serial_dprintf output | ⚠️ ORPHANED | SERIAL_DEBUG defined (line 10) enabling serial_dprintf macro, BUT all dprintf/dprintln calls gated by runtime debug_config.enable flag (defaults false) -- console output silent |

**Key links present but wiring partially effective** -- MASTER_LEFT and SERIAL_DEBUG less effective than expected due to QMK runtime behavior.

### Requirements Coverage

| Requirement | Description | Status | Blocking Issue |
|-------------|-------------|--------|----------------|
| DIAG-01 | PIO conflict test -- separate WS2812 and serial onto different PIO peripherals | ✓ SATISFIED | SKIPPED with audit evidence -- WS2812 never compiled, no conflict exists |
| DIAG-02 | Half-duplex fallback test -- eliminate TX/RX crossing as variable | ✓ SATISFIED | EXECUTED: half-duplex test FAIL, wiring hypothesis eliminated, user report documented |
| DIAG-03 | Pin swap test -- try SERIAL_USART_PIN_SWAP if full-duplex fails | ✓ SATISFIED | SKIPPED with reason -- PATH A only (wiring path), DIAG-02 FAIL = PATH B (non-wiring) |
| DIAG-04 | TX/RX swap test -- reverse pin assignments as brute-force check | ✓ SATISFIED | SKIPPED with reason -- same as DIAG-03, wiring hypothesis eliminated |
| DIAG-05 | Static master test -- replace SPLIT_USB_DETECT with MASTER_LEFT to eliminate detection variable | ✓ SATISFIED | EXECUTED: MASTER_LEFT added, SPLIT_USB_DETECT disabled, test FAIL BUT critical finding documented (MASTER_LEFT doesn't eliminate USB detection) |
| DIAG-06 | Console debug -- enable CONSOLE_ENABLE to inspect serial driver initialization | ⚠️ PARTIAL | EXECUTED: CONSOLE_ENABLE and SERIAL_DEBUG added, console connects but zero output due to debug_config.enable runtime flag (needs retry with flag enabled) |

**5/6 requirements satisfied, DIAG-06 partially satisfied** (console enabled but output gated).

### Anti-Patterns Found

| File | Line | Pattern | Severity | Impact |
|------|------|---------|----------|--------|
| config.h | 8 | MASTER_LEFT without understanding its scope | ℹ️ Info | MASTER_LEFT only affects handedness logic (is_keyboard_left), not master detection (is_keyboard_master) -- H5 test less conclusive than intended |
| config.h | 10 | SERIAL_DEBUG without runtime debug_enable | ℹ️ Info | All debug macros (dprintf, dprintln, serial_dprintf) gated by debug_config.enable runtime flag -- compile-time define insufficient |

**No blocker anti-patterns.** Issues are QMK architecture behaviors, not code problems.

### Human Verification Required

#### 1. DIAG-06 Console Debug Retry

**Test:** Add `debug_enable = true;` to `keyboard_post_init_user()` in both `keymaps/vial_left/keymap.c` and `keymaps/vial_right/keymap.c`. Recompile, flash both halves, connect left half to USB + QMK Toolbox console, connect TRRS cable, observe console output.

**Expected:** Console shows PIO initialization messages, split transaction attempts, and either:
- Transaction failures with error messages (PIO issue), OR
- No transaction attempts (master detection issue), OR
- Successful transactions but data corruption (protocol issue)

**Why human:** Requires firmware code modification (add debug_enable), reflashing, and real-time console observation during split communication attempts.

#### 2. Verify User Test Reports Match Config State

**Test:** Cross-reference user reports in SUMMARYs against git commits to confirm each test was actually flashed and tested as documented.

**Expected:** User reports timeline matches commit timestamps. DIAG-00 report mentions "left side's oled turns on" confirming TRRS power. DIAG-02 report "Same result" confirms half-duplex test. DIAG-05 report "No result on right half" confirms master/slave still failing.

**Why human:** Requires verifying user report content matches expected observable behavior for each config state.

### Gaps Summary

**Truth #5 gap:** Console debug output not captured for Phase 11 verdict analysis.

**Root cause:** DIAG-06 successfully enabled QMK console endpoint (CONSOLE_ENABLE=yes, console connected) and serial debug macros (SERIAL_DEBUG defined), BUT all debug output calls (dprintf, dprintln, serial_dprintf) are gated at runtime by `debug_config.enable` flag which defaults to `false`. The console was silent not because it wasn't enabled, but because the debug macros check the runtime flag before printing.

**What's missing for Phase 11:**
1. Runtime debug flag enablement: either `debug_enable = true` in firmware or `DB_TOGG` key in keymap
2. Re-flash with debug-enabled firmware
3. Capture console output showing:
   - PIO state machine initialization (success/failure, which SM assigned)
   - Split transaction attempts (if any)
   - Serial driver errors or timeouts
   - Master/slave detection results

**Impact:** Phase 11 verdict analysis will be limited without this debug data. The Phase 11 planner should include DIAG-06 retry as the first task.

**Critical findings documented (not gaps, but important for Phase 11):**
- MASTER_LEFT doesn't eliminate USB detection as intended -- only controls handedness, master detection still uses usb_bus_detected()
- All QMK debug macros require runtime flag, not just compile-time defines

---

## Detailed Verification

### Step 1: Context Loading

**Phase Goal** (from ROADMAP.md):
> Each suspected misconfiguration is tested with an isolated, reversible firmware change -- user flashes and reports results for each test

**Success Criteria** (from ROADMAP.md):
1. PIO conflict between WS2812 and serial is either confirmed fixed (slave keys register) or ruled out as the cause
2. Full-duplex vs half-duplex communication mode is either confirmed working or ruled out, with user-reported test results
3. Each diagnostic test that was executed has a clear pass/fail result documented with the exact config change made and the user-observed behavior
4. Tests skipped (because a prior test resolved the issue or audit ruled out the hypothesis) are documented with the reason for skipping
5. If no single test resolves the issue, console debug output from the serial driver is captured and available for verdict analysis

### Step 2: Must-Haves (from 10-03-PLAN.md frontmatter)

**Truths:**
- Diagnostic path chosen based on DIAG-02 result (wiring vs non-wiring)
- If DIAG-02 PASS: PIN_SWAP test determines whether straight-through wiring is the root cause
- If DIAG-02 FAIL: MASTER_LEFT eliminates USB detection, console debug captures PIO init state
- User has flashed and reported results for each applicable test
- All executed tests have clear pass/fail results with config changes documented

**Artifacts:**
- `keyboards/hidpress/bipedalambi/config.h` -- Board config modified per diagnostic path

**Key Links:**
- config.h SERIAL_USART_PIN_SWAP → serial_vendor.c pio_init() argument order
- config.h MASTER_LEFT → split detection logic

### Step 3: Truth Verification

**Truth 1: PIO conflict confirmed fixed or ruled out**
- **Evidence:** DIAG-01 SKIPPED (10-01-SUMMARY.md lines 65-67) -- Phase 9 audit AUDIT-03 proved WS2812 driver never compiled
- **Supporting artifacts:** 10-01-SUMMARY.md (exists, documents skip reason)
- **Status:** ✓ VERIFIED

**Truth 2: Full-duplex vs half-duplex confirmed working or ruled out**
- **Evidence:** DIAG-02 EXECUTED (10-02-SUMMARY.md) -- commented SERIAL_USART_FULL_DUPLEX (commit a007619), user report "Same result unfortunately" (line 105)
- **Supporting artifacts:** config.h shows SERIAL_USART_FULL_DUPLEX uncommented (restored in af3429c), 10-02-SUMMARY.md documents FAIL result
- **Status:** ✓ VERIFIED

**Truth 3: Each executed test has clear pass/fail with config change and user behavior**
- **Evidence:** 
  - DIAG-00: halconf.h/mcuconf.h changes (commit 0dddbd7), user report in 10-01-SUMMARY.md lines 110-111, result FAIL
  - DIAG-02: config.h change (commit a007619), user report in 10-02-SUMMARY.md line 105, result FAIL
  - DIAG-05: config.h changes (commit af3429c), user report in 10-03-SUMMARY.md line 152, result FAIL
  - DIAG-06: config.h/rules.mk changes (commit 1ff504e), user report in 10-03-SUMMARY.md line 153, result INCONCLUSIVE
- **Supporting artifacts:** All commits exist, all SUMMARYs document results
- **Status:** ✓ VERIFIED

**Truth 4: Skipped tests documented with reasons**
- **Evidence:**
  - DIAG-01: Skipped, reason in 10-01-SUMMARY.md lines 65-67 (audit eliminated WS2812 conflict)
  - DIAG-03: Skipped, reason in 10-03-SUMMARY.md line 103 (wiring verification superseded by DIAG-02 FAIL)
  - DIAG-04: Skipped, reason in 10-03-SUMMARY.md line 104 (PATH A only, DIAG-02 was FAIL = PATH B)
- **Supporting artifacts:** 10-03-SUMMARY.md test matrix (lines 96-106) documents all 7 DIAGs with status/reason
- **Status:** ✓ VERIFIED

**Truth 5: Console debug output captured if no fix found**
- **Evidence:** DIAG-06 EXECUTED (commit 1ff504e adds CONSOLE_ENABLE and SERIAL_DEBUG), BUT console output silent (10-03-SUMMARY.md lines 153, 149-159)
- **Root cause:** All debug macros gated by runtime debug_config.enable flag (10-03-SUMMARY.md lines 130-149)
- **Supporting artifacts:** config.h has SERIAL_DEBUG (line 10), rules.mk has CONSOLE_ENABLE (line 16), BUT debug_enable not set at runtime
- **Status:** ✗ PARTIAL -- console enabled but no output captured, needs retry with debug_enable=true

### Step 4: Artifact Verification

**config.h:**
- EXISTS: Yes (32 lines)
- SUBSTANTIVE: Yes (SERIAL_USART_FULL_DUPLEX line 6, SPLIT_USB_DETECT commented line 7, MASTER_LEFT line 8, SERIAL_DEBUG line 10)
- WIRED: Yes (serial_vendor.c uses these defines, split_util.c checks MASTER_LEFT)
- STATUS: ✓ VERIFIED

**rules.mk:**
- EXISTS: Yes (19 lines)
- SUBSTANTIVE: Yes (CONSOLE_ENABLE = yes line 16)
- WIRED: Yes (QMK build system reads this, console endpoint created)
- STATUS: ✓ VERIFIED

**halconf.h:**
- EXISTS: Yes (6 lines)
- SUBSTANTIVE: Yes (HAL_USE_SIO removed, only I2C and ADC remain)
- WIRED: Yes (ChibiOS HAL initialization reads this)
- STATUS: ✓ VERIFIED

**mcuconf.h:**
- EXISTS: Yes (15 lines)
- SUBSTANTIVE: Yes (UART0/UART1 blocks removed, only I2C0/I2C1/ADC1 remain)
- WIRED: Yes (ChibiOS peripheral initialization reads this)
- STATUS: ✓ VERIFIED

### Step 5: Key Link Verification

**Link 1: config.h SERIAL_USART_PIN_SWAP → serial_vendor.c**
- EXPECTED: If PIN_SWAP defined, master init swaps TX/RX arguments to pio_init()
- ACTUAL: DIAG-04 SKIPPED (not tested, wiring hypothesis eliminated)
- STATUS: N/A (link not exercised in this phase)

**Link 2: config.h MASTER_LEFT → split detection logic**
- EXPECTED: MASTER_LEFT replaces USB detection with compile-time constant
- ACTUAL: MASTER_LEFT defined (config.h line 8), SPLIT_USB_DETECT commented (line 7), BUT analysis shows MASTER_LEFT only affects is_keyboard_left(), not is_keyboard_master() (10-03-SUMMARY.md lines 118-127)
- STATUS: ⚠️ PARTIAL -- link exists but less effective than expected

**Link 3: config.h SERIAL_DEBUG → serial debug macros**
- EXPECTED: SERIAL_DEBUG enables serial_dprintf output in serial driver
- ACTUAL: SERIAL_DEBUG defined (config.h line 10), serial_dprintf expands to dprintf, BUT all dprintf calls gated by runtime debug_config.enable (10-03-SUMMARY.md lines 130-149)
- STATUS: ⚠️ ORPHANED -- define present but output gated at runtime

### Step 6: Requirements Coverage

All 6 DIAG requirements mapped to Phase 10:
- DIAG-01: ✓ SATISFIED (skipped with audit evidence)
- DIAG-02: ✓ SATISFIED (executed, FAIL result documented)
- DIAG-03: ✓ SATISFIED (skipped with reason)
- DIAG-04: ✓ SATISFIED (skipped with reason)
- DIAG-05: ✓ SATISFIED (executed, FAIL result + critical finding documented)
- DIAG-06: ⚠️ PARTIAL (executed but console output not captured due to runtime flag)

### Step 7: Anti-Pattern Scan

Files modified in phase 10 (from SUMMARYs):
- keyboards/hidpress/bipedalambi/config.h
- keyboards/hidpress/bipedalambi/rules.mk
- keyboards/hidpress/bipedalambi/halconf.h
- keyboards/hidpress/bipedalambi/mcuconf.h

**Scanned for:**
- TODO/FIXME/placeholder comments: None found
- Empty implementations: Not applicable (config files)
- Console.log only implementations: Not applicable (config files)

**Notable patterns (not anti-patterns):**
- config.h line 8: MASTER_LEFT used without full understanding of its scope (affects handedness only, not master detection) -- documented as critical finding, not a code issue
- config.h line 10: SERIAL_DEBUG defined without runtime debug_enable -- documented as QMK architecture behavior, not a code issue

### Step 8: Human Verification Needs

**Item 1: DIAG-06 retry with debug_enable=true**
- **Why human:** Requires code modification in keymap.c files, reflashing, and real-time console observation
- **Criticality:** High -- needed for Phase 11 verdict analysis

**Item 2: Verify user test timeline**
- **Why human:** Requires cross-referencing user reports with commit timestamps to confirm tests were actually performed
- **Criticality:** Low -- SUMMARYs appear consistent with user reports

### Step 9: Overall Status

**Status:** gaps_found

**Reason:** Truth #5 only partially verified -- console debug infrastructure added but output not captured due to runtime flag. Phase 11 needs DIAG-06 retry.

**Score:** 4/5 truths verified (80%)

---

_Verified: 2026-02-15T14:30:00Z_
_Verifier: Claude (gsd-verifier)_
