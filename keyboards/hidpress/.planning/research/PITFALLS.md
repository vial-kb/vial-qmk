# Domain Pitfalls

**Domain:** QMK/Vial EEPROM fixes on RP2040 split keyboards
**Researched:** 2026-02-13
**Overall confidence:** HIGH (verified against project source, QMK docs, and community patterns)

## Critical Pitfalls

Mistakes that cause data corruption, bricked keymaps, or require rework.

---

### Pitfall 1: vial.json Matrix Dimensions Do Not Match MATRIX_ROWS/MATRIX_COLS

**What goes wrong:** The `vial.json` file declares `"rows": 4, "cols": 8` but config.h defines `MATRIX_ROWS 8` (4 rows per hand x 2 = 8) and `MATRIX_COLS 8`. Vial GUI reads dimensions from `vial.json` to calculate EEPROM offsets for each layer. With `rows=4`, Vial calculates each layer as `4 * 8 * 2 = 64 bytes`. But the firmware's dynamic keymap allocates `8 * 8 * 2 = 128 bytes per layer`. Every layer after layer 0 is read from the wrong EEPROM address.

**Why it happens:** The Bipedal Ambi builds separate firmware for left and right halves (vial_left / vial_right keymaps). The developer naturally set `vial.json` rows to 4, thinking "this half only has 4 rows." But QMK's split keyboard convention is that `MATRIX_ROWS` is always the combined total (both halves), and Vial's documentation states `vial.json` rows must match `MATRIX_ROWS` from config.h. The firmware sees an 8x8 matrix; Vial GUI sees a 4x8 matrix. They disagree on layer boundaries.

**Consequences:**
- Layer 0 works correctly (starts at offset 0 regardless of dimension calculation)
- Layer 1 content appears shifted to layer 2 in Vial (Vial reads at byte 64 for layer 1, but firmware wrote at byte 128)
- KC_TRNS displays on wrong layers (layers 2 and 4 instead of 1 and 3)
- Odd-numbered layers appear broken -- classic off-by-one-layer-size pattern
- Keycodes set in Vial for layers 1-3 write to wrong EEPROM addresses from firmware's perspective

**THIS IS THE CONFIRMED ROOT CAUSE of the layer offset bug described in PROJECT.md.**

**Warning signs:**
- Layer 0 works but higher layers show wrong content
- Layers appear "shifted by one" in Vial
- Odd-numbered layers are broken, even-numbered show stale data
- Dynamic keymap size reported in compile output does not match expectation

**Prevention:**
1. Set `vial.json` matrix rows to match `MATRIX_ROWS` from config.h exactly (8, not 4)
2. For both left AND right vial.json files, use `"rows": 8, "cols": 8`
3. Update the KLE layout positions in vial.json to use rows 0-3 for one half and rows 4-7 for the other half (standard split convention)
4. Verify with formula: `DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2` should give the same result whether computed from config.h values or vial.json values

**Detection after fix:** After changing vial.json dimensions, clear EEPROM on both halves, reflash, and verify all 4 layers display correctly in Vial GUI.

**Phase:** This must be the FIRST fix. Everything else depends on correct layer addressing.

**Confidence:** HIGH -- verified by comparing project source (vial.json rows=4 vs config.h MATRIX_ROWS=8), QMK split keyboard docs ("matrix has double the rows"), and Vial docs ("rows should match MATRIX_ROWS").

**Sources:**
- [QMK Split Keyboard docs](https://docs.qmk.fm/features/split_keyboard) -- "matrix as QMK views it has double the rows"
- [Vial porting docs](https://get.vial.today/docs/porting-to-via.html) -- "rows should match MATRIX_ROWS"
- Project files: `bipedalambi/config.h:28-29`, `keymaps/vial_left/vial.json:4-7`, `keymaps/vial_right/vial.json:4-7`

---

### Pitfall 2: Forgetting to Clear EEPROM After Matrix Dimension Changes

**What goes wrong:** After fixing vial.json dimensions from `rows=4` to `rows=8`, the EEPROM still contains data written with the old layout. The dynamic keymap was populated assuming 64-byte layers; now firmware expects 128-byte layers. Every stored keycode is read from a wrong offset. The keyboard boots with corrupted keycodes, phantom key assignments, or keys that do nothing.

**Why it happens:** EEPROM persists across firmware flashes. QMK/Vial stores keycodes in EEPROM at addresses calculated from `MATRIX_ROWS * MATRIX_COLS * 2 * layer`. Changing dimensions changes every address. The old data is still physically in flash, now misinterpreted under the new layout.

**Consequences:**
- Garbled keycodes across all layers
- Potential for out-of-range keycode values causing undefined behavior
- User reports "keys stopped working after firmware update"
- May appear as if the fix made things worse, leading to reverting the correct fix

**Warning signs:**
- Keyboard behaves erratically immediately after flashing new firmware
- Random keycodes appear in Vial that were never assigned
- Some keys fire wrong actions or nothing at all

**Prevention:**
1. ALWAYS clear EEPROM on BOTH halves after any change to MATRIX_ROWS, MATRIX_COLS, or DYNAMIC_KEYMAP_LAYER_COUNT
2. Methods for RP2040: hold Bootmagic key while plugging in, or flash the RP2040 EEPROM reset .uf2 file, or use QK_CLEAR_EEPROM keycode
3. Document the clear step prominently in the commit message and any build instructions
4. For split keyboards: both halves must be cleared independently -- clearing one half does not clear the other

**Detection:** After EEPROM clear + reflash, verify in Vial that all layers show the expected default keymap (from PROGMEM keymaps array).

**Phase:** Must be part of every flash procedure during the fix phase. Should become a standard step in build/flash workflow.

**Confidence:** HIGH -- EEPROM persistence across flashes is well-documented QMK behavior.

**Sources:**
- [splitkb EEPROM reset guide](https://docs.splitkb.com/resources/reset-eeprom)
- [Keebio EEPROM reset guide](https://docs.keeb.io/reset-eeprom)

---

### Pitfall 3: Custom eeconfig_user Writes Colliding with Vial's Dynamic Keymap Region

**What goes wrong:** The firmware uses `eeconfig_update_user()` to store layer modes and actuation index (11 bits packed into a uint32_t). If the eeconfig_user EEPROM address overlaps with Vial's dynamic keymap region, writing actuation settings corrupts stored keycodes, and vice versa.

**Why it happens:** QMK allocates EEPROM in a defined order: eeconfig block (keyboard config, user config) at low addresses, then VIA/Vial custom config, then dynamic keymap, then macros, then encoders. The `eeconfig_read_user()` / `eeconfig_update_user()` functions use a fixed 4-byte slot within QMK's eeconfig block at a well-known address (around byte 19-22 in standard QMK EEPROM layout). This address range is SEPARATE from Vial's dynamic keymap region and should NOT collide by default.

However, collision CAN happen if:
- `VIA_EEPROM_CUSTOM_CONFIG_SIZE` is set incorrectly, pushing dynamic keymap into unexpected territory
- The total EEPROM budget (eeconfig + dynamic keymap + macros + encoders) exceeds the wear-leveling logical size
- Custom raw EEPROM writes using `eeprom_update_byte()` at arbitrary addresses (not eeconfig) overlap with Vial regions

**Consequences:**
- Intermittent keycode corruption -- works after clear, breaks after toggling actuation
- Actuation/mode settings randomly reset because Vial overwrites the same bytes
- Extremely difficult to debug because corruption is timing-dependent

**Warning signs:**
- Settings reset after using Vial GUI to change keycodes
- Keycodes corrupt after pressing ACT_UP/ACT_DOWN/TMB_MODE (which call `save_layer_config_to_eeprom`)
- EEPROM dump shows unexpected data patterns in the eeconfig_user region

**Prevention:**
1. Verify that `eeconfig_update_user()` uses QMK's built-in eeconfig_user address, NOT arbitrary EEPROM addresses -- the current code does this correctly
2. Calculate total EEPROM budget: `eeconfig block (~30 bytes) + VIA_EEPROM_CUSTOM_CONFIG_SIZE + dynamic_keymap (MATRIX_ROWS * MATRIX_COLS * DYNAMIC_KEYMAP_LAYER_COUNT * 2) + macros + encoder_map`
3. Verify this total fits within the wear-leveling logical size (default 4096 bytes for RP2040)
4. After fixing matrix dimensions to 8x8: dynamic keymap = `8 * 8 * 4 * 2 = 512 bytes`. This should fit comfortably within 4096 bytes.

**Detection:** Calculate the EEPROM budget explicitly before making changes. Print/log EEPROM addresses at compile time if possible.

**Phase:** Verify during the matrix dimension fix phase. Calculate budget BEFORE changing dimensions to ensure it still fits.

**Confidence:** MEDIUM -- the current code uses `eeconfig_update_user()` correctly, which should be safe. Collision risk is theoretical unless raw EEPROM writes are introduced. The main risk is the budget overflow, not address collision.

**Sources:**
- [QMK Persistent Configuration (EEPROM)](https://docs.qmk.fm/feature_eeprom)
- [VIA Configuring QMK](https://caniusevia.com/docs/configuring_qmk/) -- VIA_EEPROM_CUSTOM_CONFIG_SIZE docs
- [vial-kb/vial-qmk EEPROM issue #455](https://github.com/vial-kb/vial-qmk/issues/455)

---

### Pitfall 4: EEPROM Budget Overflow After Correcting Matrix Dimensions

**What goes wrong:** After changing vial.json from `rows=4` to `rows=8`, the dynamic keymap EEPROM usage doubles (if VIA/Vial was previously using the smaller dimension for allocation). If the total EEPROM usage exceeds the wear-leveling logical size (default 4096 bytes for RP2040), writes wrap around or silently fail, causing data corruption.

**Why it happens:** RP2040 has no physical EEPROM. QMK emulates it using wear-leveling over SPI flash with a default of 8192 bytes backing store and 4096 bytes logical size. The dynamic keymap alone with 8 rows, 8 cols, and 4 layers consumes `8 * 8 * 4 * 2 = 512 bytes`. Adding eeconfig (~30 bytes), macros (varies, typically 128-256 bytes), and encoder map (if enabled), the total should fit well within 4096 bytes.

BUT if someone increases `DYNAMIC_KEYMAP_LAYER_COUNT` or adds large macro storage without recalculating, the budget can overflow. Also, Vial's encoder map storage adds `NUM_ENCODERS * NUM_DIRECTIONS * DYNAMIC_KEYMAP_LAYER_COUNT * 2 bytes`.

**Consequences:**
- Silent EEPROM corruption when budget overflows
- Keymap appears to save in Vial but resets after power cycle
- Wear-leveling algorithm may fail unpredictably
- Difficult to diagnose because there is no error message

**Warning signs:**
- Settings don't persist after power cycle despite appearing to save
- EEPROM-related features work on fresh flash but degrade over time
- Compile output shows total EEPROM usage (if available) exceeding logical size

**Prevention:**
1. Calculate the full budget explicitly:
   - eeconfig block: ~30 bytes
   - VIA/Vial config: VIA_EEPROM_CUSTOM_CONFIG_SIZE (default 0)
   - Dynamic keymap: `MATRIX_ROWS * MATRIX_COLS * DYNAMIC_KEYMAP_LAYER_COUNT * 2` = `8 * 8 * 4 * 2 = 512 bytes`
   - Macros: DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (default varies)
   - Encoder map: `NUM_ENCODERS * 2 * DYNAMIC_KEYMAP_LAYER_COUNT * 2` = small for 1 encoder
   - Total should be well under 4096 bytes
2. If budget is tight, reduce DYNAMIC_KEYMAP_LAYER_COUNT from 4 to 3, or reduce macro space
3. If more space needed, increase `WEAR_LEVELING_BACKING_SIZE` (and thus logical size) in config.h

**Detection:** Run the budget calculation before flashing. Look for QMK compile warnings about EEPROM size.

**Phase:** Calculate during the diagnosis phase, before making matrix dimension changes.

**Confidence:** HIGH -- the math is straightforward and RP2040 defaults are well-documented. Budget for 8x8x4 is 512 bytes dynamic keymap, which fits comfortably in 4096.

**Sources:**
- [QMK EEPROM Driver Configuration](https://docs.qmk.fm/drivers/eeprom) -- RP2040 defaults
- [QMK RP2040 Platform docs](https://docs.qmk.fm/platformdev_rp2040)

---

## Moderate Pitfalls

Mistakes that cause confusion, rework, or subtle bugs.

---

### Pitfall 5: Separate Left/Right Firmware With Inconsistent vial.json Files

**What goes wrong:** The Bipedal Ambi has separate keymaps (vial_left and vial_right), each with its own vial.json. If these files have different matrix dimensions, custom keycode definitions, or UID values, the Vial GUI may show different layouts depending on which half is connected via USB, or fail to recognize the keyboard entirely.

**Why it happens:** Standard QMK split keyboards use one firmware for both halves with handedness detection. The Bipedal Ambi uses separate firmware builds because the halves have different hardware (joystick on left, encoder on right, different I2C buses, different matrix pins). This means two vial.json files must be maintained in sync.

**Consequences:**
- Connecting left half shows 4 rows; connecting right half shows 4 rows -- but the physical layout references for each half use different row ranges
- If `VIAL_KEYBOARD_UID` differs between halves, Vial treats them as different keyboards
- Custom keycode order mismatch between halves causes TMB_MODE on one side to do something different
- EEPROM on each half stores keymap independently but for different matrix subsets

**Warning signs:**
- Different behavior when connecting via USB to left vs right
- Vial shows different layouts depending on which half is primary
- Custom keycodes work on one half but not the other

**Prevention:**
1. Keep `VIAL_KEYBOARD_UID` identical in both vial_left/config.h and vial_right/config.h (already done correctly)
2. Keep `customKeycodes` array identical and in the same order in both vial.json files (already done correctly)
3. When fixing matrix dimensions, update BOTH vial.json files simultaneously
4. Consider whether the right-side vial.json layout should reference rows 4-7 (the right half's matrix positions) while the left references rows 0-3
5. Validate both halves after every change

**Detection:** Connect each half individually via USB and verify Vial GUI shows the expected layout.

**Phase:** Address during the matrix dimension fix. Both vial.json files must be updated together.

**Confidence:** HIGH -- project source confirms two separate vial.json files exist with identical matrix dimensions (both currently wrong at rows=4).

---

### Pitfall 6: Not Understanding Split EEPROM Independence

**What goes wrong:** In a split keyboard with separate firmware per half, each half has its own independent RP2040 with its own flash storage. EEPROM clear on the left half does NOT clear the right half. Fixing the firmware and clearing only one half leaves the other with corrupted EEPROM data.

**Why it happens:** First-time split keyboard developers often think of the keyboard as one unit. Clearing the left half's EEPROM and reflashing feels like "resetting the keyboard." But the right half's RP2040 still has old EEPROM data with the wrong layout dimensions.

**Consequences:**
- Right half sends wrong keycodes to the master (left)
- Keyboard works partially -- one side correct, other side garbled
- Developer thinks the fix didn't work and starts debugging the wrong thing

**Warning signs:**
- One half works correctly after fix, other half does not
- Issues only appear when using keys on one specific side
- Rebooting doesn't fix it because persistent EEPROM is the problem

**Prevention:**
1. Create a checklist: "EEPROM clear left + EEPROM clear right + flash left + flash right"
2. Document the clear/flash procedure for BOTH halves prominently
3. After any dimension change, follow the complete procedure on both halves before testing

**Detection:** Test both sides independently -- press keys on each half and verify correct behavior.

**Phase:** Part of every flash/test cycle during the fix.

**Confidence:** HIGH -- fundamental property of split keyboards with independent MCUs.

---

### Pitfall 7: RP2040 Flash Wear from Frequent eeconfig_update_user Calls

**What goes wrong:** The firmware calls `save_layer_config_to_eeprom()` (which calls `eeconfig_update_user()`) on every ACT_UP, ACT_DOWN, ACT_RESET, and TMB_MODE keypress. RP2040 flash has approximately 20,000 erase cycles (compared to 100,000 for traditional EEPROM). QMK's wear-leveling algorithm extends this significantly, but excessive writes can still degrade flash.

**Why it happens:** The macropad codebase (Bipedal Southpaw) was designed to save settings immediately on every change, which is fine for occasional setting adjustments. When ported to the split keyboard, the same pattern was kept. If a user rapidly toggles actuation levels or modes (especially if held down or in a macro), many writes happen in quick succession.

**Consequences:**
- Long-term flash degradation (thousands of hours of heavy use)
- EEPROM reads start returning corrupt data after flash sectors wear out
- Complete keyboard failure if wear-leveling backing store becomes unwritable

**Warning signs:**
- Settings stop persisting after a long period of use (months/years)
- Random EEPROM corruption that clears with a reset but returns

**Prevention:**
1. The current pattern (save on settings change, not on every keypress) is acceptable for normal use
2. Do NOT add EEPROM writes inside `matrix_scan_user()` or `pointing_device_task_user()` -- these run every scan cycle
3. If adding new persistent settings, debounce writes: save after a 500ms idle period, not on every change
4. Consider a dirty flag + deferred write pattern: set flag on change, write in housekeeping_task after timeout
5. Keep the wear-leveling backing size at default 8192 bytes (2:1 ratio to logical) for adequate leveling

**Detection:** Not easily detectable during development. Becomes apparent only after extended production use.

**Phase:** Review during the EEPROM collision diagnosis phase. Not urgent for the immediate fix but important for long-term health.

**Confidence:** MEDIUM -- the current write frequency is acceptable for normal use. Risk is theoretical unless users create rapid-fire macros for settings keys.

**Sources:**
- [QMK EEPROM docs](https://docs.qmk.fm/feature_eeprom) -- "EEPROM has a limited number of writes"
- [QMK RP2040 EEPROM PR #17519](https://github.com/qmk/qmk_firmware/pull/17519) -- RP2040 wear-leveling implementation

---

### Pitfall 8: KLE Layout Row Numbers in vial.json Not Updated for Split Convention

**What goes wrong:** After fixing the vial.json matrix dimensions to `"rows": 8`, the KLE layout positions in the vial.json `"layouts"` section still reference rows 0-3 for both halves. Vial GUI renders keys at wrong matrix positions or cannot map keys to the correct EEPROM locations.

**Why it happens:** The vial.json layout section uses matrix positions like `"0,3"` meaning row 0, col 3. In a standard split keyboard, the left half uses rows 0-3 and the right half uses rows 4-7 (for 4 rows per side). If the left vial.json references rows 0-3, that is correct. But the right vial.json must reference rows 4-7 for its physical keys. Currently, the right vial.json uses rows 0-3, which would be the left half's matrix positions in an 8-row combined matrix.

**Consequences:**
- Vial GUI shows keys mapped to wrong physical positions
- Changing a key on the "right side" in Vial actually modifies a left-side key's EEPROM entry
- Physical layout in Vial doesn't match what the keyboard actually does
- Encoder mappings may reference wrong matrix positions

**Warning signs:**
- Keys assigned in Vial don't match what the keyboard outputs
- Pressing a key on one side activates the Vial key position on the other side
- Layout looks correct in Vial but keyboard behavior is wrong

**Prevention:**
1. When updating vial.json dimensions, simultaneously update all row references in the layout section
2. Left vial.json: keys use rows 0-3 (no change needed)
3. Right vial.json: keys must use rows 4-7 (add 4 to all row values)
4. Example: right-side key at position `"0,3"` becomes `"4,3"` in the 8-row convention
5. Encoder positions in the right vial.json must also be updated to reflect the right-half row range
6. Test by verifying each physical key matches its Vial GUI position

**Detection:** After fixing dimensions, press each key on each side and verify Vial highlights the correct key.

**Phase:** Must be done simultaneously with the matrix dimension fix (Pitfall 1). They are the same fix.

**Confidence:** HIGH -- verified by examining the project's vial_right/vial.json which uses row references 0-3 that would conflict with the left half in an 8-row matrix.

---

## Minor Pitfalls

Issues that cause small delays or require minor corrections.

---

### Pitfall 9: Duplicated EEPROM Logic Between Left and Right Keymaps

**What goes wrong:** The `save_layer_config_to_eeprom()` and `load_layer_config_from_eeprom()` functions are copy-pasted identically in both `vial_left/keymap.c` and `vial_right/keymap.c`. A fix applied to one file but not the other creates divergent behavior between halves.

**Why it happens:** The separate-firmware-per-half architecture requires duplicating shared logic. Without a shared include file, changes must be manually synchronized.

**Prevention:**
1. After fixing any EEPROM logic, diff the two keymap.c files to ensure identical changes
2. Long-term: extract shared EEPROM functions into a common header (e.g., `bipedalambi_eeprom.h`)
3. For the immediate fix: keep the duplication but be disciplined about synchronizing

**Phase:** Be aware during the fix phase. Refactoring to shared code is out of scope (PROJECT.md says no refactoring).

**Confidence:** HIGH -- verified by examining both keymap.c files which contain identical EEPROM code.

---

### Pitfall 10: eeconfig_init_user Not Implemented for First-Boot Defaults

**What goes wrong:** When EEPROM is cleared (which must happen after dimension changes), `eeconfig_read_user()` returns 0x00000000. The load function interprets all-zeros as: all layer modes = MODE_MOUSE (0x00 & 0x03 = 0, which maps to MODE_MOUSE), actuation index = 0 (maps to actuation value 352, the highest). This may not be the intended default (default actuation index should be 2, value 256).

**Why it happens:** The code has validation for out-of-range values but treats all-zeros as valid. An actuation_index of 0 is valid but means maximum sensitivity, which may surprise users expecting the default middle setting.

**Prevention:**
1. Implement `eeconfig_init_user()` to set sensible defaults on first boot: `eeconfig_update_user(0x200)` (actuation_index=2 in bits 8-10)
2. Or add a magic byte check: if the user data is 0x00000000, treat it as "uninitialized" and apply defaults
3. The current code has partial protection via the fallback in `load_layer_config_from_eeprom()` but the fallback for actuation_index returns 2 only if `act_idx > 4`, not if `act_idx == 0`

**Phase:** Minor fix that can be done alongside the main EEPROM dimension fix.

**Confidence:** HIGH -- verified in source code at `keymaps/vial_left/keymap.c:77-90`.

---

### Pitfall 11: Encoder Map EEPROM Not Accounted for in Budget

**What goes wrong:** The right half has `ENCODER_MAP_ENABLE = yes` with one encoder. Vial stores encoder mappings in EEPROM alongside the dynamic keymap. If the EEPROM budget calculation only counts keymap bytes and forgets encoder map bytes, the total may be underestimated.

**Why it happens:** Encoder map storage is easy to overlook because it is a smaller allocation. For 1 encoder with 2 directions and 4 layers, it adds `1 * 2 * 4 * 2 = 16 bytes`. This is tiny, but in a tight EEPROM budget it matters.

**Prevention:**
1. Include encoder map in the budget calculation
2. For the Bipedal Ambi: 16 bytes for encoder map is negligible given the 4096-byte logical size
3. If encoder is only on the right half but ENCODER_MAP_ENABLE is not set on the left half, the EEPROM layouts may differ between halves

**Phase:** Verify during budget calculation.

**Confidence:** MEDIUM -- the 16-byte encoder map is unlikely to cause overflow but should be accounted for.

---

## Phase-Specific Warnings

| Phase Topic | Likely Pitfall | Mitigation |
|---|---|---|
| Diagnosis / Matrix Audit | Pitfall 1 (vial.json mismatch) | Compare vial.json rows against MATRIX_ROWS; they MUST match |
| Diagnosis / EEPROM Budget | Pitfall 4 (budget overflow) | Calculate: `8*8*4*2 = 512` bytes keymap + overhead; verify < 4096 |
| Fix / Matrix Dimensions | Pitfall 8 (KLE row numbers) | Update layout positions in right vial.json to use rows 4-7 |
| Fix / Apply Changes | Pitfall 2 (EEPROM clear) | Clear EEPROM on BOTH halves after every dimension change |
| Fix / Apply Changes | Pitfall 6 (split independence) | Flash and clear both halves, not just one |
| Fix / Sync Files | Pitfall 5 (inconsistent vial.json) | Update both vial.json files in lockstep |
| Fix / Sync Files | Pitfall 9 (duplicated logic) | Diff both keymap.c files after any EEPROM code changes |
| Verification / Testing | Pitfall 3 (EEPROM collision) | After fix, toggle actuation and verify keycodes don't corrupt |
| Verification / Testing | Pitfall 10 (init defaults) | After EEPROM clear, verify default actuation is reasonable |
| Long-term / Maintenance | Pitfall 7 (flash wear) | Don't add EEPROM writes in scan loops; keep writes to settings changes |

## EEPROM Budget Calculation (Reference)

This is the budget for the Bipedal Ambi after the matrix dimension fix:

```
eeconfig block (QMK core):                      ~30 bytes
  - includes eeconfig_user (4 bytes for layer modes + actuation)

VIA_EEPROM_CUSTOM_CONFIG_SIZE:                   0 bytes (default, not overridden)

Dynamic keymap:
  MATRIX_ROWS(8) * MATRIX_COLS(8) * LAYERS(4) * 2 = 512 bytes

Dynamic macros:
  DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE             ~128 bytes (default varies)

Encoder map (right half only):
  NUM_ENCODERS(1) * 2 * LAYERS(4) * 2          = 16 bytes

TOTAL:                                         ~686 bytes
RP2040 Wear-Leveling Logical Size:              4096 bytes
HEADROOM:                                       ~3410 bytes (83% free)
```

Budget is comfortable. No overflow risk for the current configuration.

## Sources

- [QMK Split Keyboard Documentation](https://docs.qmk.fm/features/split_keyboard)
- [QMK EEPROM Driver Configuration](https://docs.qmk.fm/drivers/eeprom)
- [QMK Persistent Configuration (EEPROM)](https://docs.qmk.fm/feature_eeprom)
- [QMK RP2040 Platform Documentation](https://docs.qmk.fm/platformdev_rp2040)
- [Vial Porting Guide - Create JSON](https://get.vial.today/docs/porting-to-via.html)
- [VIA Configuring QMK](https://caniusevia.com/docs/configuring_qmk/)
- [splitkb EEPROM Reset Guide](https://docs.splitkb.com/resources/reset-eeprom)
- [Keebio EEPROM Reset Guide](https://docs.keeb.io/reset-eeprom)
- [RP2040 EEPROM PR #17519](https://github.com/qmk/qmk_firmware/pull/17519)
- [vial-qmk EEPROM Issue #455](https://github.com/vial-kb/vial-qmk/issues/455)
- [QMK Config Options](https://docs.qmk.fm/config_options)
- [QMK MATRIX_COLS inconsistency Issue #14968](https://github.com/qmk/qmk_firmware/issues/14968)

---

*Pitfalls analysis: 2026-02-13*
