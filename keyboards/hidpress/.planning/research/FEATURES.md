# Feature Landscape: EEPROM / Vial Diagnostics for Bipedal Ambi

**Domain:** QMK/Vial split keyboard EEPROM diagnostics and configuration validation
**Researched:** 2026-02-13
**Overall confidence:** HIGH (codebase analysis) / MEDIUM (QMK internal EEPROM layout details)

## Table Stakes

Features that must be verified/fixed or the keyboard will not work correctly with Vial.

| # | Diagnostic Check | Expected | Actual (Current) | Complexity | Dependency |
|---|-----------------|----------|-------------------|------------|------------|
| T1 | Matrix dimension agreement: `config.h` vs `vial.json` vs `info.json` | All three sources agree on rows/cols seen by firmware | **MISMATCH**: `config.h` says `MATRIX_ROWS=8, MATRIX_COLS=8`. `vial.json` says `"rows": 4, "cols": 8`. `info.json` defines 4 row pins and 8 col pins but declares `"split": {"enabled": true}`. | Low | None -- check first |
| T2 | EEPROM layer size calculation: firmware vs Vial | Layer size = `MATRIX_ROWS * MATRIX_COLS * 2` bytes, same value used by both firmware and Vial GUI | **LIKELY MISMATCH**: Firmware compiles with `MATRIX_ROWS=8` (the `#define` in config.h), so `dynamic_keymap.c` allocates `8 * 8 * 2 = 128 bytes/layer`. Vial GUI reads vial.json `rows=4`, so it calculates `4 * 8 * 2 = 64 bytes/layer`. Every layer after layer 0 is offset by 64 bytes in Vial's view vs firmware's view. | Low | Depends on T1 |
| T3 | Layer indexing: Vial layer N maps to firmware layer N | Setting a key on "Layer 1" in Vial writes to the same EEPROM offset that firmware reads for layer 1 | **BROKEN**: Because of T2, Vial's layer 1 data (starting at byte 64) falls in the middle of firmware's layer 0 region (bytes 0-127). Vial layer 2 starts at byte 128, which is firmware layer 1. This explains the "layer 1 content appears on layer 2" symptom. | Low | Depends on T2 |
| T4 | KC_TRNS placement on odd vs even layers | KC_TRNS appears on layers 1 and 3 (where user put them) | **SHIFTED**: KC_TRNS shows on layers 2 and 4 instead of 1 and 3. Direct consequence of the off-by-one from T3. | Low | Depends on T3 |
| T5 | Dynamic keymap persistence across power cycles | Keycodes written by Vial survive reboot | **BROKEN**: If firmware reads layer data at wrong offsets (T2/T3), it reads stale/wrong data after power cycle. Additionally, if EEPROM was never properly initialized after a matrix dimension change, the stored data is laid out for a different matrix geometry. | Low | Depends on T2 |
| T6 | EEPROM clear after geometry fix | After changing MATRIX_ROWS/COLS or vial.json matrix dimensions, EEPROM must be cleared | EEPROM has not been cleared since the current (mismatched) configuration was flashed | Low | Depends on T1 resolution |
| T7 | vial.json layout positions reference valid matrix coordinates | Every `"row,col"` in vial.json keymap must exist within the declared matrix dimensions | LEFT vial.json references `0,7`, `1,7`, `2,7`, `3,7` (col 7) -- these are the virtual joystick columns. With `rows=4, cols=8`, these are valid. With `rows=8, cols=8`, they are also valid. Need to verify no position exceeds bounds after fix. | Low | Depends on T1 resolution |

### Resolution Path for T1-T6

The core question is: **should the firmware compile with `MATRIX_ROWS=8` or `MATRIX_ROWS=4` for each independent half?**

**Option A -- Each half is a 4-row keyboard (vial.json is correct, config.h is wrong):**
- Change `config.h` to `MATRIX_ROWS 4` (or remove it and let info.json drive it with 4 row pins)
- vial.json stays at `"rows": 4`
- Layer size = `4 * 8 * 2 = 64 bytes/layer`
- Total dynamic keymap = `4 layers * 64 = 256 bytes`
- **Risk**: QMK's split keyboard feature (`"split": {"enabled": true}` in info.json) expects doubled rows. If split is enabled, QMK internally doubles MATRIX_ROWS to 8 regardless of what config.h says. Need to verify whether vial-qmk's split implementation respects or overrides the config.h value.

**Option B -- Each half sees the full 8-row matrix (config.h is correct, vial.json is wrong):**
- Change vial.json to `"rows": 8, "cols": 8`
- `config.h` stays at `MATRIX_ROWS 8`
- Layer size = `8 * 8 * 2 = 128 bytes/layer`
- Total dynamic keymap = `4 layers * 128 = 512 bytes`
- The vial.json layout positions for the "other half" rows (4-7) would be KC_NO/unused
- **Risk**: Wasted EEPROM (half the keymap space is for the phantom other side). But it eliminates the mismatch.

**Option C -- Disable split, treat each half as independent (the Southpaw model):**
- Remove `"split": {"enabled": true}` from info.json
- Set `MATRIX_ROWS 4` in config.h
- vial.json stays at `"rows": 4`
- Each half is truly independent -- no row doubling
- **Risk**: Losing `SPLIT_LAYER_STATE_ENABLE` and other split sync features. The halves already use separate serial pins and separate firmware, so this may already be the de facto reality.

**Recommendation**: Investigate Option C first because the firmware already treats each half independently (separate keymaps, separate vial.json, separate compile targets). If split sync features (SPLIT_LAYER_STATE_ENABLE) are actively needed for OLED/layer display on the non-USB half, then Option B is the fallback. Option A is dangerous because QMK may auto-double rows.

## Differentiators

Nice-to-have diagnostic capabilities that go beyond fixing the immediate bug.

| # | Diagnostic Feature | Value Proposition | Complexity | Notes |
|---|-------------------|-------------------|------------|-------|
| D1 | EEPROM budget calculator | Compute total EEPROM usage: eeconfig base + VIA header + dynamic keymap + macros. Compare against 4096-byte wear-leveling logical limit. | Med | Prevents future overflow if more layers or features are added. Currently: ~256-512 bytes keymap + eeconfig overhead = well within 4KB. |
| D2 | Console debug output for layer reads | Temporarily enable `CONSOLE_ENABLE=yes`, add `dprintf()` calls in `layer_state_set_user` and `dynamic_keymap_get_keycode` to trace which EEPROM offsets are actually read at runtime | Med | Would definitively confirm the offset mismatch theory. Can be removed after diagnosis. |
| D3 | eeconfig_user vs dynamic_keymap collision audit | Map exact EEPROM byte ranges: eeconfig block (bytes 0-~33), VIA header (bytes ~34-~37), custom config, dynamic keymap region, macro region. Verify no overlap. | Med | The `eeconfig_update_user()` function writes to a QMK-reserved slot within the eeconfig block (~byte 20), which is well before the dynamic keymap start (~byte 38+). **Likely NOT colliding** based on address chain analysis, but worth confirming. |
| D4 | Automated vial.json matrix validator | Script or manual check that every `"row,col"` in vial.json keymap section is within `0..rows-1` and `0..cols-1` | Low | Prevents layout bugs silently breaking Vial display |
| D5 | Split-half firmware identity check | Log or display which half firmware was compiled for (left vs right) on OLED at boot | Low | Prevents flashing wrong firmware to wrong half -- a real risk with separate vial_left/vial_right builds |
| D6 | EEPROM dump comparison tool | Dump raw EEPROM via QMK console, compare layer 0 against compiled keymap to detect drift | High | Gold standard for proving EEPROM content matches expectations. Requires console and custom dump code. |
| D7 | Post-fix validation keymap | Create a test keymap where each layer has distinct, recognizable keycodes (not KC_TRNS) so layer offset bugs are immediately visible in Vial | Low | KC_TRNS on layers 1-3 makes offset bugs hard to spot. A validation keymap with e.g. KC_1 on layer 1, KC_2 on layer 2 makes the problem obvious. |

## Anti-Features

Things to deliberately NOT do during diagnosis.

| # | Anti-Feature | Why Avoid | What to Do Instead |
|---|-------------|-----------|-------------------|
| A1 | Do NOT manually set `DYNAMIC_KEYMAP_EEPROM_ADDR` | Overriding the automatic address chain is fragile and masks the root cause. If the matrix dimensions are wrong, fixing the address just moves the problem. | Fix the matrix dimension mismatch (T1). Let the address chain calculate correctly from correct inputs. |
| A2 | Do NOT refactor the codebase during diagnosis | The PROJECT.md explicitly states "bug fix only -- no feature additions or refactoring." Combining a refactor with a fix makes it impossible to know what fixed the bug. | Fix the EEPROM/layer issue first. Refactoring (shared EEPROM code, etc.) is a separate future milestone. |
| A3 | Do NOT modify the Bipedal Southpaw | It works. The macropad is the known-good reference for custom EEPROM features. Touching it risks breaking a working board. | Use Southpaw as a reference for how eeconfig_user and Vial coexist correctly. |
| A4 | Do NOT skip EEPROM clear after any matrix dimension change | Stale EEPROM data from the old layout WILL cause corruption. This is the #1 most common Vial debugging mistake. | Always flash with EEPROM clear: hold bootmagic key, or use `QK_CLEAR_EEPROM` keycode, or flash with `.uf2` after `EEPROM_RESET` |
| A5 | Do NOT add `VIA_EEPROM_CUSTOM_CONFIG_SIZE` for the eeconfig_user data | The custom EEPROM data uses `eeconfig_update_user()` which writes to the QMK eeconfig region, NOT the VIA custom config region. Setting `VIA_EEPROM_CUSTOM_CONFIG_SIZE` without understanding the address chain could push the dynamic keymap start address into a region that overflows available EEPROM. | Verify that eeconfig_user is in its expected QMK-managed slot (it should be). Only use VIA_EEPROM_CUSTOM_CONFIG_SIZE if you need VIA-protocol-accessible custom config. |
| A6 | Do NOT change `DYNAMIC_KEYMAP_LAYER_COUNT` as a workaround for the offset | Reducing layers does not fix the per-layer size mismatch. It just reduces how many broken layers exist. | Fix the per-layer byte size by fixing matrix dimensions. |
| A7 | Do NOT test persistence without first verifying layer display | If layers display wrong in Vial, persistence tests are meaningless -- you are reading/writing to wrong offsets regardless. | First fix T1-T4 (display correctness), then test T5 (persistence). |

## Feature Dependencies

```
T1 (Matrix dimension agreement)
 |
 +-> T2 (Layer size calculation)
      |
      +-> T3 (Layer indexing correctness)
      |    |
      |    +-> T4 (KC_TRNS placement)
      |
      +-> T5 (Persistence across power cycles)
      |
      +-> T6 (EEPROM clear required)

T7 (Layout position validity) -- depends on T1 resolution

D1 (Budget calculator) -- independent, can run anytime
D2 (Console debug) -- independent, useful for confirming T2/T3
D3 (Collision audit) -- independent, likely to show no collision
D4 (vial.json validator) -- depends on T1 resolution
D5 (Firmware identity) -- independent
D6 (EEPROM dump) -- depends on D2 infrastructure
D7 (Validation keymap) -- independent, should be done BEFORE testing fixes
```

## MVP Diagnostic Sequence

Prioritized order for diagnosis and fix:

1. **D7 -- Create validation keymap** (before any fix): Replace KC_TRNS on layers 1-3 with distinct keycodes so the layer offset is unambiguously visible in Vial.
2. **T1 -- Resolve matrix dimension mismatch**: Determine correct MATRIX_ROWS value. Check whether QMK auto-doubles rows when split is enabled. The answer determines whether vial.json or config.h needs to change.
3. **T7 -- Validate vial.json positions**: After T1 is resolved, verify all layout coordinates fit within the agreed matrix dimensions.
4. **T6 -- Clear EEPROM**: After flashing fixed firmware, clear EEPROM before testing.
5. **T3/T4 -- Verify layer display**: Open Vial, confirm layers 0-3 display with correct keycodes from the validation keymap.
6. **T5 -- Verify persistence**: Set a keycode in Vial, power cycle, confirm it persists.
7. **D3 -- Collision audit** (optional): If persistence still fails after T1-T6, audit eeconfig_user address vs dynamic keymap address to rule out collision.

Defer:
- **D1** (EEPROM budget): Current usage is well within 4KB. Only needed if adding features later.
- **D2** (Console debug): Only needed if T1-T6 fix does not resolve the problem.
- **D6** (EEPROM dump): Heavy diagnostic, only if simpler checks fail.

## Key Reference: Bipedal Southpaw (Known-Good)

The Bipedal Southpaw macropad is the reference implementation where Vial + custom EEPROM coexist correctly:

| Property | Southpaw (working) | Ambi Left (broken) | Ambi Right (broken) |
|----------|-------------------|--------------------|--------------------|
| `MATRIX_ROWS` in config.h | 4 | 8 | (inherits 8 from common config.h) |
| `MATRIX_COLS` in config.h | 7 | 8 | (inherits 8 from common config.h) |
| vial.json `rows` | 4 | 4 | 4 |
| vial.json `cols` | 7 | 8 | 8 |
| Rows match? | YES (4==4) | **NO (8!=4)** | **NO (8!=4)** |
| Cols match? | YES (7==7) | YES (8==8) | YES (8==8) |
| Split enabled? | No | Yes | Yes |
| `DYNAMIC_KEYMAP_LAYER_COUNT` | 4 | 4 | 4 |
| Uses eeconfig_user? | Yes | Yes | Yes |
| Layer offset bug? | No | **Yes** | **Yes** |

The mismatch in `MATRIX_ROWS` is the smoking gun.

## EEPROM Address Chain (Reference)

Based on QMK/VIA source analysis (MEDIUM confidence -- verified against multiple sources but not against the exact vial-qmk fork):

```
Byte 0-33:   QMK eeconfig block
               - Includes: magic bytes, debug, keymap, backlight, audio, rgblight
               - eeconfig_user: 4 bytes at a fixed offset (~byte 20-23)
               - eeconfig_keyboard: 4 bytes at a fixed offset (~byte 24-27)

Byte ~34:    VIA_EEPROM_MAGIC_ADDR (= EECONFIG_SIZE)
               - 3 bytes: VIA magic + version

Byte ~37:    VIA_EEPROM_LAYOUT_OPTIONS_ADDR
               - VIA_EEPROM_LAYOUT_OPTIONS_SIZE bytes (default 1)

Byte ~38:    VIA_EEPROM_CUSTOM_CONFIG_ADDR
               - VIA_EEPROM_CUSTOM_CONFIG_SIZE bytes (default 0)

Byte ~38:    DYNAMIC_KEYMAP_EEPROM_ADDR (starts right after custom config)
               - Size = LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2
               - With ROWS=8, COLS=8, LAYERS=4: 8*8*2*4 = 512 bytes
               - With ROWS=4, COLS=8, LAYERS=4: 4*8*2*4 = 256 bytes

Byte ~550:   DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (after keymap)
               - Remainder up to EEPROM size limit

Total:       Wear-leveling logical size = 4096 bytes (RP2040 default)
```

**Critical insight**: `eeconfig_update_user()` writes to byte ~20-23, which is well before the dynamic keymap region starting at byte ~38. These do NOT overlap. The EEPROM collision hypothesis from PROJECT.md (Issue B) is **likely a non-issue**. The real problem is Issue A: matrix dimension mismatch.

## Sources

- [QMK Split Keyboard Documentation](https://docs.qmk.fm/features/split_keyboard) -- matrix row doubling for split boards
- [QMK EEPROM Driver Documentation](https://docs.qmk.fm/drivers/eeprom) -- RP2040 wear-leveling defaults (4KB logical / 8KB backing)
- [QMK Persistent Configuration](https://docs.qmk.fm/feature_eeprom) -- eeconfig_read_user / eeconfig_update_user API
- [VIA Configuring QMK](https://caniusevia.com/docs/configuring_qmk/) -- VIA_EEPROM address chain, DYNAMIC_KEYMAP_EEPROM_ADDR calculation
- [Vial Porting Guide](https://get.vial.today/docs/porting-to-via.html) -- vial.json matrix rows/cols must match config.h
- [QMK dynamic_keymap.c source](https://github.com/qmk/qmk_firmware/blob/master/quantum/dynamic_keymap.c) -- layer offset = `layer * MATRIX_ROWS * MATRIX_COLS * 2`
- Codebase analysis of `keyboards/hidpress/bipedalambi/` and `keyboards/hidpress/bipedalsouthpaw/` (local files, HIGH confidence)

---

*Feature landscape analysis: 2026-02-13*
