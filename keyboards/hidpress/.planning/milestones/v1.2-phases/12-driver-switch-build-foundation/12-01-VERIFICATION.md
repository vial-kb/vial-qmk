---
phase: 12-driver-switch-build-foundation
plan: 01
verified: 2026-02-22T05:52:00Z
status: passed
score: 5/5 truths verified
re_verification: false
---

# Phase 12 Plan 01: Driver Switch and Build Foundation Verification Report

**Phase Goal:** Both halves compile cleanly with the pointing device driver switched from analog_joystick to azoteq_iqs5xx, with I2C bus sharing configured

**Verified:** 2026-02-22T05:52:00Z
**Status:** PASSED
**Re-verification:** No - initial verification

## Goal Achievement

### Observable Truths

| # | Truth | Status | Evidence |
|---|-------|--------|----------|
| 1 | Left half compiles without errors: make hidpress/bipedalambi:vial | ✓ VERIFIED | Build exited 0, produced .build/hidpress_bipedalambi_vial.uf2 |
| 2 | Right half compiles without errors: make hidpress/bipedalambi:vial SIDE=right | ✓ VERIFIED | Build exited 0, produced .build/hidpress_bipedalambi_vial.uf2 |
| 3 | Pointing device driver is azoteq_iqs5xx (not analog_joystick) | ✓ VERIFIED | rules.mk line 7: POINTING_DEVICE_DRIVER = azoteq_iqs5xx; build flags include -DPOINTING_DEVICE_DRIVER_AZOTEQ_IQS5XX |
| 4 | POINTING_DEVICE_RIGHT and SPLIT_POINTING_ENABLE are defined in config | ✓ VERIFIED | config.h lines 66-67: both defines present |
| 5 | TPS43 (0x74) and OLED (0x3C) use different I2C addresses on shared I2C1 bus | ✓ VERIFIED | drivers/sensors/azoteq_iqs5xx.c:10 defines 0x74, drivers/oled/oled_driver.c:184 defines 0x3C - no collision |

**Score:** 5/5 truths verified

### Required Artifacts

| Artifact | Expected | Status | Details |
|----------|----------|--------|---------|
| keyboards/hidpress/bipedalambi/rules.mk | azoteq_iqs5xx driver selection | ✓ VERIFIED | Line 7: POINTING_DEVICE_DRIVER = azoteq_iqs5xx; Line 14: SRC += analog.c (for ADC); Lines 8-9: JOYSTICK_ENABLE/DRIVER retained |
| keyboards/hidpress/bipedalambi/config.h | TPS43 model define, POINTING_DEVICE_RIGHT, I2C config | ✓ VERIFIED | Line 65: AZOTEQ_IQS5XX_TPS43; Line 66: POINTING_DEVICE_RIGHT; Line 67: SPLIT_POINTING_ENABLE; Lines 54-62: I2C1 (GP18/GP19) on right half; No ANALOG_JOYSTICK defines |

### Key Link Verification

| From | To | Via | Status | Details |
|------|----|----|--------|---------|
| rules.mk | builddefs/common_features.mk | POINTING_DEVICE_DRIVER value selects driver source and sets I2C_DRIVER_REQUIRED | ✓ WIRED | Build flags show -DPOINTING_DEVICE_DRIVER_AZOTEQ_IQS5XX; drivers/sensors/azoteq_iqs5xx.c compiled into build |
| config.h | drivers/sensors/azoteq_iqs5xx.c | AZOTEQ_IQS5XX_TPS43 define selects 43mm trackpad resolution | ✓ WIRED | Define present in config.h line 65; driver source compiled with this define in scope |
| config.h | drivers/oled/oled_driver.h | I2C1 bus shared - OLED address 0x3C vs TPS43 address 0x74 must not collide | ✓ WIRED | I2C_DRIVER I2CD1 defined for right half (line 55); addresses verified distinct (0x3C \!= 0x74 << 1); both devices use I2C1 (GP18 SDA, GP19 SCL) |
| keymap.c | pointing device interface | pointing_device_task_user() provides driver-agnostic interface | ✓ WIRED | keymap.c line 343: report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) exists and is called by QMK pointing device subsystem |

### Requirements Coverage

| Requirement | Status | Evidence |
|-------------|--------|----------|
| BLD-01: Both halves compile cleanly with azoteq_iqs5xx driver | ✓ SATISFIED | Both builds exited 0, azoteq_iqs5xx.c compiled, UF2 files produced |
| BLD-02: Split pointing enabled with POINTING_DEVICE_RIGHT | ✓ SATISFIED | config.h lines 66-67: POINTING_DEVICE_RIGHT and SPLIT_POINTING_ENABLE defined |
| TPAD-07: TPS43 coexists with OLED on shared I2C1 bus (GP18/GP19) | ✓ SATISFIED | config.h: I2C1 (GP18/GP19) on right half; mcuconf.h: I2C1 enabled; addresses 0x3C (OLED) vs 0x74 (TPS43) - no collision |

### Anti-Patterns Found

None.

### Human Verification Required

None - all verification is build-time and source inspection.

### Phase Artifacts

**Commit:** 1dec097b17d4c3336e71272f61bf602268230563

**Files Modified:**
- keyboards/hidpress/bipedalambi/rules.mk (POINTING_DEVICE_DRIVER changed to azoteq_iqs5xx)
- keyboards/hidpress/bipedalambi/config.h (AZOTEQ_IQS5XX_TPS43 added, POINTING_DEVICE_RIGHT changed from LEFT, ANALOG_JOYSTICK defines removed)

**Key Decisions:**
- Kept JOYSTICK_ENABLE + JOYSTICK_DRIVER=analog for joystick hardware on left half (still used for custom keys/scroll modes via direct ADC reads)
- Kept SRC += analog.c explicitly (azoteq_iqs5xx sets I2C_DRIVER_REQUIRED not ANALOG_DRIVER_REQUIRED)
- AZOTEQ_IQS5XX_TPS43 defined unconditionally (not inside #ifdef RIGHT_SIDE) - driver header needs it at compile time for both halves when split pointing enabled

### Verification Methods

**Build Verification:**
- Executed `make hidpress/bipedalambi:vial` and `make hidpress/bipedalambi:vial SIDE=right`
- Both builds exited with code 0 and produced UF2 files
- Build dry-run (`make -n`) confirmed azoteq_iqs5xx.c and analog.c compiled

**Source Inspection:**
- rules.mk: POINTING_DEVICE_DRIVER = azoteq_iqs5xx (line 7)
- config.h: AZOTEQ_IQS5XX_TPS43, POINTING_DEVICE_RIGHT, SPLIT_POINTING_ENABLE present (lines 65-67)
- config.h: No ANALOG_JOYSTICK defines (grep returned no matches)
- drivers/sensors/azoteq_iqs5xx.c:10: #define AZOTEQ_IQS5XX_ADDRESS (0x74 << 1)
- drivers/oled/oled_driver.c:184: #define OLED_DISPLAY_ADDRESS 0x3C
- halconf.h: HAL_USE_I2C TRUE (line 3)
- mcuconf.h: RP_I2C_USE_I2C0 TRUE (line 7), RP_I2C_USE_I2C1 TRUE (line 11)
- keymap.c: pointing_device_task_user() defined (line 343)

**Build Flag Verification:**
- Build flags include -DPOINTING_DEVICE_DRIVER_AZOTEQ_IQS5XX
- Build flags include -DPOINTING_DEVICE_DRIVER_azoteq_iqs5xx
- Build flags include -DHAL_USE_I2C=TRUE

**No Anti-Patterns:**
- Searched for TODO/FIXME/PLACEHOLDER in modified files - none found
- No stub implementations (driver is full QMK driver, not placeholder)
- No console.log-only code in modified files

---

_Verified: 2026-02-22T05:52:00Z_
_Verifier: Claude (gsd-verifier)_
_Verification Mode: Initial - Full 3-level verification (exists, substantive, wired)_
