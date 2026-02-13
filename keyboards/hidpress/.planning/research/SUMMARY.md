# Project Research Summary

**Project:** Bipedal Ambi EEPROM/Vial Layer Offset Fix
**Domain:** QMK/Vial Firmware EEPROM Diagnostics and Split Keyboard Configuration
**Researched:** 2026-02-13
**Confidence:** HIGH

## Executive Summary

The Bipedal Ambi split keyboard has a **critical matrix dimension mismatch** between `config.h` (which defines `MATRIX_ROWS=8`) and `vial.json` (which declares `"rows": 4`). This is the confirmed root cause of the layer offset bug where layer 1 content appears on layer 2, and odd-numbered layers display KC_TRNS incorrectly. The firmware allocates 512 bytes of EEPROM for the dynamic keymap (8 rows × 8 cols × 4 layers × 2 bytes), but Vial GUI calculates only 256 bytes (4 rows × 8 cols × 4 layers × 2 bytes). This 256-byte discrepancy causes Vial to write keycodes at wrong EEPROM addresses, resulting in layer data appearing shifted by one layer.

The fix is straightforward: update both `vial.json` files (left and right) to declare `"rows": 8` to match the firmware's `MATRIX_ROWS`, update the KLE layout positions in the right vial.json to reference rows 4-7 instead of 0-3, clear EEPROM on both halves, and reflash. The EEPROM budget after fix is 512 bytes for keymap + ~174 bytes overhead = ~686 bytes total, well within the RP2040's 4096-byte wear-leveling logical size (83% headroom). The custom `eeconfig_user` data (layer modes + actuation index) is safely stored in QMK's eeconfig region and does NOT collide with Vial's dynamic keymap region.

The key risk is **failing to clear EEPROM after changing matrix dimensions**. Old EEPROM data written with 4-row dimensions will be misinterpreted under 8-row dimensions, causing corrupted keycodes. Both halves must be cleared independently since each has its own RP2040 with independent flash storage.

## Key Findings

### Root Cause Identified

**From STACK.md:**
- **Matrix dimension mismatch verified:** `config.h` defines `MATRIX_ROWS=8` (split keyboard convention: 4 physical rows per hand × 2 = 8), but both `vial.json` files declare `"rows": 4`
- **EEPROM offset discrepancy:** Firmware calculates layer boundaries at 128-byte intervals (8×8×2), Vial GUI calculates at 64-byte intervals (4×8×2)
- **Result:** Layer N in Vial maps to a different physical EEPROM address than Layer N in firmware
- **Vial documentation requirement:** "rows: enter the number of rows your keyboard has, this value should match MATRIX_ROWS you have in config.h"
- **Confidence: HIGH** — verified from vial-qmk source code analysis and official Vial porting documentation

### EEPROM Architecture

**Complete address chain (from STACK.md):**
```
Byte 0-46:    eeconfig block (QMK core, includes eeconfig_user at ~byte 14-17)
Byte 46-49:   VIA magic (3 bytes)
Byte 49-50:   Layout options (1 byte)
Byte 50:      Dynamic keymap START
              - Firmware: 512 bytes (8×8×4×2)
              - Vial thinks: 256 bytes (4×8×4×2)
Byte 562:     Encoder map (right half: 16 bytes, left: 0 bytes)
Byte 578:     Dynamic macros (remainder up to 4096 bytes)
```

**eeconfig_user safety confirmed:** The custom EEPROM data (layer modes + actuation index) is stored via `eeconfig_update_user()` which writes to a QMK-managed 4-byte slot at ~byte 14-17. This is well before the VIA/dynamic keymap region starting at byte 50. **No collision detected.** The EEPROM collision hypothesis from PROJECT.md (Issue B) is ruled out as the cause.

### Diagnostic Features Required

**From FEATURES.md — Table Stakes:**
1. **Matrix dimension agreement (T1):** `config.h` MATRIX_ROWS/COLS must match `vial.json` matrix.rows/cols and `info.json` matrix_pins count
2. **Layer size calculation correctness (T2):** Both firmware and Vial must calculate layer byte size identically
3. **Layer indexing correctness (T3):** Vial layer N must map to firmware layer N in EEPROM
4. **KC_TRNS placement verification (T4):** Transparent keys must appear on intended layers (1 and 3)
5. **Persistence across power cycles (T5):** Keycodes written by Vial must survive reboot
6. **EEPROM clear after fix (T6):** Old data must be erased before testing
7. **Layout position validity (T7):** All `"row,col"` positions in vial.json must be within matrix bounds

**From FEATURES.md — Differentiators:**
- EEPROM budget calculator (validates total usage < 4096 bytes)
- Console debug output for layer reads (confirm EEPROM offsets during diagnosis)
- eeconfig_user collision audit (verify address ranges don't overlap)
- Validation keymap with distinct keycodes per layer (makes offset bugs immediately visible)

**From FEATURES.md — Anti-Features (DO NOT do):**
- Do NOT manually set `DYNAMIC_KEYMAP_EEPROM_ADDR` (masks root cause)
- Do NOT refactor during fix (PROJECT.md: bug fix only)
- Do NOT skip EEPROM clear after dimension changes (most common Vial bug)
- Do NOT add `VIA_EEPROM_CUSTOM_CONFIG_SIZE` for eeconfig_user data (wrong region)

### Architecture Patterns

**From ARCHITECTURE.md:**
- **Single source of truth:** All matrix dimensions (`config.h`, `vial.json`, `info.json`, LAYOUT macros) must match
- **Split keyboard independence:** Each half has its own RP2040, own EEPROM, must be cleared/flashed separately
- **eeconfig_user init defaults:** Must implement `eeconfig_init_user()` to set sane defaults after EEPROM clear (currently missing)
- **Diagnostic verification:** Use `dynamic_keymap_get_keycode(layer, row, col)` with debug output to verify EEPROM reads match expectations

**Component boundaries:**
```
Vial GUI (uses vial.json rows=4)
  ↓ HID Raw Reports
Vial Protocol Handler (quantum/via.c)
  ↓
Dynamic Keymap API (uses MATRIX_ROWS=8 from config.h)
  ↓
NVM/EEPROM Abstraction (RP2040 wear-leveling)
  ↓
Flash Memory (last sectors of XIP)
```

**Critical architectural issue:** The Bipedal Ambi uses **separate firmware builds per side** (vial_left and vial_right keymaps) instead of the standard single-binary split keyboard approach. This is unusual but valid. However, both sides compile with `MATRIX_ROWS=8` because `config.h` defines it at the keyboard level. The fix must keep `MATRIX_ROWS=8` and update `vial.json` to match, not the reverse.

### Critical Pitfalls

**From PITFALLS.md — Top 5:**

1. **Matrix dimension mismatch (Pitfall 1 — CRITICAL):** vial.json rows=4 vs config.h MATRIX_ROWS=8 causes every layer after layer 0 to read from wrong EEPROM address. Fix: change vial.json to `"rows": 8` and update layout positions. **This is the confirmed root cause.**

2. **Forgetting EEPROM clear after fix (Pitfall 2 — CRITICAL):** Old EEPROM data persists across firmware flashes. After changing dimensions, old 4-row data will be misinterpreted as 8-row data, causing garbled keycodes. Fix: clear EEPROM on BOTH halves (hold bootmagic key or use `QK_CLEAR_EEPROM`) before testing.

3. **Split EEPROM independence (Pitfall 6 — MODERATE):** Each half has its own flash storage. Clearing only the left half leaves the right half with corrupted data. Fix: clear and reflash both halves independently.

4. **KLE layout row numbers not updated (Pitfall 8 — MODERATE):** After changing vial.json to rows=8, the right-side vial.json layout positions must be updated from rows 0-3 to rows 4-7 (split convention: left uses rows 0-3, right uses rows 4-7). Otherwise Vial maps keys to wrong matrix positions.

5. **Inconsistent vial.json files (Pitfall 5 — MODERATE):** Separate left/right firmware builds mean two vial.json files. Both must be updated identically (same UID, same matrix dimensions, same custom keycodes order). Changing one but not the other causes different behavior depending on which half is USB host.

**From PITFALLS.md — Phase warnings:**
- **Diagnosis phase:** Pitfall 1 (verify dimension mismatch), Pitfall 4 (calculate EEPROM budget: 512 bytes keymap + overhead < 4096 bytes)
- **Fix phase:** Pitfall 2 (EEPROM clear on both halves), Pitfall 6 (both halves independently), Pitfall 8 (KLE row numbers)
- **Verification phase:** Pitfall 3 (verify eeconfig_user doesn't corrupt after toggling actuation), Pitfall 10 (verify defaults after EEPROM clear)

## Implications for Roadmap

Based on research, the fix can be structured as a **single-phase bug fix** or broken into **diagnosis + fix + validation** phases. Given the high confidence in root cause and straightforward fix, a single phase is recommended.

### Phase 1: Matrix Dimension Fix and EEPROM Reset
**Rationale:** Root cause is confirmed with HIGH confidence. The fix is mechanical: update vial.json dimensions, adjust layout positions, clear EEPROM, reflash. All steps are deterministic and low-risk.

**Delivers:**
- Both vial.json files updated to `"rows": 8, "cols": 8`
- Right vial.json layout positions updated to reference rows 4-7
- EEPROM cleared on both left and right halves
- Firmware reflashed to both halves
- All 4 layers display correctly in Vial GUI
- KC_TRNS appears on layers 1 and 3 as intended
- Keycodes persist across power cycles

**Addresses features:**
- T1: Matrix dimension agreement ✓
- T2: Layer size calculation correctness ✓
- T3: Layer indexing correctness ✓
- T4: KC_TRNS placement ✓
- T5: Persistence across power cycles ✓
- T6: EEPROM clear ✓
- T7: Layout position validity ✓

**Avoids pitfalls:**
- Pitfall 1: Fix by updating vial.json to rows=8
- Pitfall 2: Clear EEPROM after dimension change
- Pitfall 5: Update both vial.json files identically
- Pitfall 6: Clear and flash both halves independently
- Pitfall 8: Update right vial.json layout positions to rows 4-7

**Detailed steps:**
1. Update `keymaps/vial_left/vial.json`: change `"rows": 4` to `"rows": 8`
2. Update `keymaps/vial_right/vial.json`: change `"rows": 4` to `"rows": 8`
3. Update `keymaps/vial_right/vial.json` layout section: change all row references from 0-3 to 4-7
4. Compile left firmware, compile right firmware
5. Clear EEPROM on left half (bootmagic key while plugging in)
6. Flash left half with new firmware
7. Clear EEPROM on right half
8. Flash right half with new firmware
9. Connect to Vial GUI and verify all layers display correctly
10. Test key presses on both sides, verify correct keycodes
11. Power cycle, verify persistence

**Optional enhancements (can be done in same phase or deferred):**
- Add `eeconfig_init_user()` to set sane defaults (actuation_index=2) after EEPROM clear
- Add console debug output temporarily to verify EEPROM addresses if verification fails

### Phase 2: Validation and Documentation (Optional)
**Rationale:** If Phase 1 completes successfully, no further phases are needed. However, if deeper validation is desired, or if the fix doesn't resolve the issue (LOW probability), this phase provides systematic verification.

**Delivers:**
- EEPROM budget calculator output (verify 512 bytes keymap + overhead < 4096 bytes)
- eeconfig_user collision audit (confirm no address overlap)
- Validation keymap with distinct keycodes per layer (KC_1 on layer 1, KC_2 on layer 2, etc.) to make any offset bugs immediately visible
- Documentation of EEPROM clear procedure for future firmware updates

**Research flag:** Skip this phase unless Phase 1 fix does not resolve the issue. Standard patterns apply (well-documented Vial bug with established fix).

### Phase Ordering Rationale

- **Single-phase approach recommended:** The root cause is confirmed with HIGH confidence (matrix dimension mismatch verified from source code). The fix is mechanical and well-documented in Vial/QMK community resources. Breaking into multiple phases adds unnecessary overhead for a bug fix.
- **Validation phase optional:** Only needed if the primary fix fails (LOW probability) or if comprehensive EEPROM documentation is desired for long-term maintenance.
- **No feature development needed:** This is a bug fix, not a feature. PROJECT.md explicitly states "no refactoring" during fix. The EEPROM architecture is already functional; only the configuration is incorrect.

### Research Flags

**Skip research-phase for implementation:**
- **Phase 1:** Well-documented pattern. Vial porting documentation explicitly addresses this matrix dimension mismatch. QMK split keyboard conventions are standardized. No unknowns remain.
- **Phase 2 (if needed):** EEPROM budget calculation is simple arithmetic. eeconfig_user address verification can be done via source code reading (already completed in STACK.md).

**No phases require deeper research.** All necessary information is captured in the four research files.

## Confidence Assessment

| Area | Confidence | Notes |
|------|------------|-------|
| Stack | **HIGH** | Root cause identified from vial-qmk source code. EEPROM address chain verified against QMK docs. RP2040 wear-leveling defaults confirmed. |
| Features | **HIGH** | Table stakes features are all verification steps for the fix. Differentiators are diagnostic tools, all of which are well-documented. |
| Architecture | **MEDIUM** | EEPROM memory map estimated based on typical EECONFIG_SIZE (~46 bytes); exact value unverified but does not affect fix. Component boundaries verified from source. |
| Pitfalls | **HIGH** | All critical pitfalls verified against project source code. Matrix dimension mismatch confirmed by comparing config.h and vial.json. EEPROM clear requirement confirmed from community docs. |

**Overall confidence:** **HIGH**

The root cause is definitively identified. The fix is mechanical and low-risk. The only execution risk is procedural: ensuring both halves are cleared and flashed correctly.

### Gaps to Address

**Minor gap:** Exact value of `EECONFIG_SIZE` in vial-qmk not verified. Estimated at ~46 bytes based on QMK structure. This shifts all downstream EEPROM addresses but does NOT affect the fix because the matrix dimension mismatch is independent of absolute addresses.

**Resolution:** Not needed for fix. If post-fix diagnostics are required, read `quantum/eeconfig.h` from vial-qmk to get exact size.

**Minor gap:** Whether `eeconfig_init_user()` is already implemented. Source code review showed it is NOT in current keymap.c files. Without it, EEPROM clear leaves actuation_index=0 (highest sensitivity) instead of intended default (middle, index 2).

**Resolution:** Add `eeconfig_init_user()` implementation to both keymap.c files during Phase 1 fix. Simple 3-line function:
```c
void eeconfig_init_user(void) {
    eeconfig_update_user(0x200);  // actuation_index=2 (bits 8-10), layer_modes=0 (MODE_MOUSE)
}
```

**No major gaps remain.** All information required for a successful fix is captured.

## Sources

### Primary (HIGH confidence)
- [Vial Porting Guide](https://get.vial.today/docs/porting-to-via.html) — matrix rows/cols must match config.h
- [vial-qmk dynamic_keymap.c](https://github.com/vial-kb/vial-qmk/blob/c9c90c06b798f22591b98f8e0de34bde297c6ef5/quantum/dynamic_keymap.c) — EEPROM offset calculation formula
- [QMK Split Keyboard Documentation](https://docs.qmk.fm/features/split_keyboard) — MATRIX_ROWS doubling convention
- [QMK EEPROM Driver Configuration](https://docs.qmk.fm/drivers/eeprom) — RP2040 wear-leveling defaults (4096 bytes logical size)
- [QMK Persistent Configuration](https://docs.qmk.fm/feature_eeprom) — eeconfig_user API
- Project source code: `keyboards/hidpress/bipedalambi/config.h`, `keymaps/vial_left/vial.json`, `keymaps/vial_right/vial.json`, `keymaps/vial_left/keymap.c`, `keymaps/vial_right/keymap.c` (all read directly)

### Secondary (MEDIUM confidence)
- [VIA Configuring QMK](https://caniusevia.com/docs/configuring_qmk/) — VIA EEPROM address chain
- [QMK via.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/via.h) — VIA region size defines
- [QMK eeconfig.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/eeconfig.h) — eeconfig block structure
- [splitkb EEPROM Reset Guide](https://docs.splitkb.com/resources/reset-eeprom) — clearing procedure
- [Keebio EEPROM Reset Guide](https://docs.keeb.io/reset-eeprom) — RP2040 clear methods

### Tertiary (LOW confidence)
- [DeepWiki vial-qmk Features](https://deepwiki.com/vial-kb/vial-qmk/5-features-and-customization) — Vial-specific EEPROM handling (supplementary)

---
*Research completed: 2026-02-13*
*Ready for roadmap: yes*
