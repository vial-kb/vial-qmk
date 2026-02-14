---
phase: 07-build-and-flash
verified: 2026-02-14T10:17:32Z
status: passed
score: 9/9 must-haves verified
re_verification: false
---

# Phase 7: Build and Flash Verification Report

**Phase Goal:** Both halves compile cleanly with all fixes applied, EEPROM is cleared on both halves, and new firmware is flashed
**Verified:** 2026-02-14T10:17:32Z
**Status:** passed
**Re-verification:** No — initial verification

## Goal Achievement

### Observable Truths

| # | Truth | Status | Evidence |
|---|-------|--------|----------|
| 1 | Left half firmware compiles without errors | ✓ VERIFIED | .build/hidpress_bipedalambi_vial_left.uf2 exists (127,488 bytes, 249 blocks) |
| 2 | Right half firmware compiles without errors | ✓ VERIFIED | .build/hidpress_bipedalambi_vial_right.uf2 exists (110,592 bytes, 216 blocks) |
| 3 | Both UF2 files exist and are non-zero size | ✓ VERIFIED | Left: 125KB, Right: 108KB (both > 50KB threshold) |
| 4 | All working tree changes committed before build | ✓ VERIFIED | Commit ffc8137922 committed config.h and mcuconf.h |
| 5 | EEPROM is cleared on the left half | ✓ VERIFIED | 07-02-SUMMARY confirms user executed EEPROM clear, left half working in Vial |
| 6 | EEPROM is cleared on the right half | ✓ VERIFIED | 07-02-SUMMARY confirms EEPROM cleared after vial.json fix |
| 7 | Left half flashed with new firmware and boots successfully | ✓ VERIFIED | 07-02-SUMMARY confirms left half boots and shows correct keycodes in Vial |
| 8 | Right half flashed with new firmware and boots successfully | ✓ VERIFIED | 07-02-SUMMARY confirms right half boots and shows correct keycodes after fix |
| 9 | Right half vial.json KLE positions corrected to rows 0-3 | ✓ VERIFIED | Commit f9eb193f88 reverted rows 4-7 → 0-3, rebuild and re-flash successful |

**Score:** 9/9 truths verified

### Required Artifacts

| Artifact | Expected | Status | Details |
|----------|----------|--------|---------|
| `.build/hidpress_bipedalambi_vial_left.uf2` | Left half firmware binary | ✓ VERIFIED | 127,488 bytes, UF2 firmware for RP2040, 249 blocks, modified Feb 14 18:32 |
| `.build/hidpress_bipedalambi_vial_right.uf2` | Right half firmware binary | ✓ VERIFIED | 110,592 bytes, UF2 firmware for RP2040, 216 blocks, modified Feb 14 21:00 (after vial.json fix) |
| `bipedalambi/config.h` | SERIAL_PIO_USE_PIO1 config | ✓ VERIFIED | Line 8: `#define SERIAL_PIO_USE_PIO1` present |
| `bipedalambi/mcuconf.h` | UART0/UART1 enable | ✓ VERIFIED | Lines 18-23: RP_SIO_USE_UART0 and RP_SIO_USE_UART1 set to TRUE |
| `keymaps/vial_left/keymap.c` | eeconfig_init_user | ✓ VERIFIED | Line 92: eeconfig_init_user() implemented |
| `keymaps/vial_right/keymap.c` | eeconfig_init_user | ✓ VERIFIED | Line 80: eeconfig_init_user() implemented |
| `keymaps/vial_left/vial.json` | EE_CLR keycode | ✓ VERIFIED | Line 108: EE_CLR on layer 1 |
| `keymaps/vial_right/vial.json` | EE_CLR keycode | ✓ VERIFIED | Line 96: EE_CLR on layer 1 |
| `keymaps/vial_right/vial.json` | Rows 0-3 KLE positions | ✓ VERIFIED | All keys use rows 0-3 (not 4-7), commit f9eb193f88 |
| `bipedalambi/EEPROM-CLEAR-PROCEDURE.md` | EEPROM clear documentation | ✓ VERIFIED | 5048 bytes, modified Feb 14 16:44 |

### Key Link Verification

| From | To | Via | Status | Details |
|------|----|----|--------|---------|
| `bipedalambi/config.h` | `.build/hidpress_bipedalambi_vial_left.uf2` | `make hidpress/bipedalambi:vial_left` | ✓ WIRED | UF2 produced, commit ffc8137922 includes config.h |
| `bipedalambi/config.h` | `.build/hidpress_bipedalambi_vial_right.uf2` | `make hidpress/bipedalambi:vial_right` | ✓ WIRED | UF2 produced after vial.json fix, rebuilt Feb 14 21:00 |
| `.build/hidpress_bipedalambi_vial_left.uf2` | Left half RP2040 flash | UF2 mass storage copy | ✓ WIRED | 07-02-SUMMARY confirms flash and boot success |
| `.build/hidpress_bipedalambi_vial_right.uf2` | Right half RP2040 flash | UF2 mass storage copy | ✓ WIRED | 07-02-SUMMARY confirms flash (twice: initial + after fix) and boot success |

### Requirements Coverage

**Phase 7 enables verification of EEPR-02 and EEPR-03** (actual verification in Phase 8)

| Requirement | Status | Evidence |
|-------------|--------|----------|
| DFNS-01 (eeconfig_init_user) | ✓ SATISFIED | Both keymap.c files implement eeconfig_init_user |
| DFNS-02 (QK_CLEAR_EEPROM key) | ✓ SATISFIED | Both halves have EE_CLR on layer 1 |
| EEPR-01 (EEPROM clear documentation) | ✓ SATISFIED | EEPROM-CLEAR-PROCEDURE.md exists |

### Anti-Patterns Found

| File | Line | Pattern | Severity | Impact |
|------|------|---------|----------|--------|
| None | - | - | - | No anti-patterns detected |

**Scan results:**
- No TODO/FIXME/PLACEHOLDER comments in config.h, mcuconf.h
- No empty implementations or console.log-only stubs
- Both UF2 files are valid RP2040 firmware images
- All modified files committed to git

### Critical Issue Resolved During Execution

**CRITICAL DEVIATION (discovered in 07-02):**

The right half initially showed blank keys in Vial GUI after flash and EEPROM clear. Root cause analysis revealed:

- **Issue:** Phase 3 incorrectly remapped right half vial.json KLE positions from rows 0-3 to rows 4-7
- **Cause:** Phase 3 applied split keyboard row offset (rows 4-7 for right half) assuming combined split mode
- **Reality:** Each half has separate firmware (vial_left, vial_right) and scans its own 4 row pins as rows 0-3 when standalone
- **Evidence:** LAYOUT_right macro explicitly places keys at matrix[0-3], confirming rows 0-3 is correct
- **Fix:** Commit f9eb193f88 reverted right half vial.json KLE positions from rows 4-7 back to rows 0-3
- **Validation:** Right half rebuilt (Feb 14 21:00), re-flashed, EEPROM re-cleared — confirmed working in Vial

**Impact:** This fix was essential for Phase 7 goal achievement. Without it, the right half would have failed end-to-end verification in Phase 8.

### Human Verification Required

None. All automated checks passed and user confirmed both halves working correctly in Vial GUI.

### Verification Summary

All Phase 7 must-haves verified:

**Plan 07-01 (Compilation):**
- ✓ Both halves compile without errors
- ✓ UF2 binaries exist with correct sizes
- ✓ Pre-existing config committed to git
- ✓ Build artifacts valid RP2040 firmware images

**Plan 07-02 (Flash and EEPROM Clear):**
- ✓ Both halves flashed successfully
- ✓ EEPROM cleared on both halves
- ✓ Both halves boot and enumerate as USB HID devices
- ✓ Both halves show correct keycodes in Vial (after right half fix)

**Additional verification:**
- ✓ Critical vial.json row mapping issue discovered and fixed
- ✓ Right half rebuilt with corrected KLE positions
- ✓ User confirmed both halves working correctly

---

_Verified: 2026-02-14T10:17:32Z_
_Verifier: Claude (gsd-verifier)_
