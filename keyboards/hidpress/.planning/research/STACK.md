# Technology Stack: EEPROM Diagnostics for Bipedal Ambi

**Project:** Bipedal Ambi EEPROM/Vial Layer Offset Fix
**Researched:** 2026-02-13
**Overall confidence:** HIGH (root cause identified from source analysis + official docs)

## Root Cause Analysis

The Bipedal Ambi has a **critical matrix dimension mismatch** between `vial.json` and `config.h` that directly causes the layer offset bug. This is the primary finding of this research.

### The Problem

| Source | rows | cols |
|--------|------|------|
| `config.h` (`MATRIX_ROWS`) | **8** | 8 |
| `vial.json` (left) `matrix.rows` | **4** | 8 |
| `vial.json` (right) `matrix.rows` | **4** | 8 |

**Why this breaks everything:** The firmware's `dynamic_keymap_key_to_eeprom_address()` calculates byte offsets using the firmware's `MATRIX_ROWS` (8), but the Vial GUI believes the matrix has only 4 rows. When Vial writes a keycode to layer 1, row 0, col 0, the GUI calculates the offset as `1 * 4 * 8 * 2 = 64 bytes` past the keymap base. But the firmware reads that same logical position as `1 * 8 * 8 * 2 = 128 bytes` past the base. The result: layer 1 in Vial maps to the middle of layer 0 in firmware, and every subsequent layer is similarly shifted.

**Confidence: HIGH** -- Verified from vial-qmk source code and Vial porting documentation. The Vial docs explicitly state: "rows: enter the number of rows your keyboard has, this value should match MATRIX_ROWS you have in config.h."

---

## QMK EEPROM Layout (Complete Address Chain)

Understanding where every byte lives is essential for diagnosing collisions. The EEPROM is laid out as a sequential chain of regions. Each region's start address depends on the size of the previous region.

### Region 1: eeconfig (QMK Core) -- Bytes 0 to ~EECONFIG_SIZE

The base QMK configuration occupies the lowest EEPROM addresses.

| Offset | Size | Contents | Confidence |
|--------|------|----------|------------|
| 0 | 2 bytes | `EECONFIG_MAGIC` (0xFEED when valid) | HIGH |
| 2 | 1 byte | `EECONFIG_DEBUG` | HIGH |
| 3 | 1 byte | `EECONFIG_DEFAULT_LAYER` | HIGH |
| 4 | 1 byte | `EECONFIG_KEYMAP` (NKRO, etc.) | HIGH |
| 5 | 1 byte | `EECONFIG_MOUSEKEY_ACCEL` | HIGH |
| 6 | 1 byte | `EECONFIG_BACKLIGHT` | HIGH |
| 7+ | varies | Audio, RGB, Unicode, Steno, Haptic, etc. | MEDIUM |
| ~14-15 | 4 bytes | `eeconfig_user` (your layer_modes + actuation) | HIGH |
| ~18+ | varies | `eeconfig_kb` data (keyboard-level) | MEDIUM |
| ... | ... | Additional features if enabled | LOW |

The exact value of `EECONFIG_SIZE` varies by QMK version and enabled features, but is typically 30-50 bytes for a standard build. When VIA is enabled, QMK ensures at least 1024 bytes for the total EEPROM.

**Confidence on exact offsets past byte 6: MEDIUM** -- QMK has restructured eeconfig across versions; the vial-qmk fork may differ from upstream. The specific byte for `eeconfig_user` depends on which features are compiled in.

### Region 2: VIA Header -- Bytes EECONFIG_SIZE to EECONFIG_SIZE+3+

| Offset from EECONFIG_SIZE | Size | Contents |
|----------------------------|------|----------|
| +0 | 3 bytes | `VIA_EEPROM_MAGIC` (validity flag) |
| +3 | 1-4 bytes | `VIA_EEPROM_LAYOUT_OPTIONS` (default: 1 byte) |
| +4 | 0+ bytes | `VIA_EEPROM_CUSTOM_CONFIG` (default: 0 bytes) |

The chain:
```
VIA_EEPROM_MAGIC_ADDR          = EECONFIG_SIZE
VIA_EEPROM_LAYOUT_OPTIONS_ADDR = VIA_EEPROM_MAGIC_ADDR + 3
VIA_EEPROM_CUSTOM_CONFIG_ADDR  = VIA_EEPROM_LAYOUT_OPTIONS_ADDR + VIA_EEPROM_LAYOUT_OPTIONS_SIZE
```

**Confidence: HIGH** -- Verified from QMK via.h source.

### Region 3: Dynamic Keymap -- The Big One

```
DYNAMIC_KEYMAP_EEPROM_ADDR = VIA_EEPROM_CUSTOM_CONFIG_ADDR + VIA_EEPROM_CUSTOM_CONFIG_SIZE
```

**Size calculation:**
```
keymap_bytes = DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2
```

For the Bipedal Ambi (firmware values):
```
keymap_bytes = 4 layers * 8 rows * 8 cols * 2 bytes = 512 bytes
```

For what Vial GUI *thinks* (vial.json values):
```
keymap_bytes = 4 layers * 4 rows * 8 cols * 2 bytes = 256 bytes
```

**This 256-byte discrepancy is the layer offset bug.** When Vial writes to what it thinks is layer 1 offset, the firmware interprets it as a completely different position.

**Address-to-keycode function** (from vial-qmk `dynamic_keymap.c`):
```c
void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column) {
    return ((void *)DYNAMIC_KEYMAP_EEPROM_ADDR)
        + (layer * MATRIX_ROWS * MATRIX_COLS * 2)
        + (row * MATRIX_COLS * 2)
        + (column * 2);
}
```

**Confidence: HIGH** -- Verified from vial-qmk source code on GitHub.

### Region 4: Vial Encoder Map

```
VIAL_ENCODERS_EEPROM_ADDR = DYNAMIC_KEYMAP_EEPROM_ADDR
    + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2)
```

**Size calculation:**
```
VIAL_ENCODERS_SIZE = NUMBER_OF_ENCODERS * DYNAMIC_KEYMAP_LAYER_COUNT * 2 * 2
```

For split keyboards: `NUMBER_OF_ENCODERS = 2 * (sizeof(encoders_pad_a) / sizeof(pin_t))`

For the right side build (1 encoder, split): `2 * 1 * 4 * 2 * 2 = 32 bytes`
For the left side build (no encoder): 0 bytes

**Confidence: HIGH** -- Verified from vial-qmk source.

### Region 5: Dynamic Macros

```
DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR = VIAL_ENCODERS_EEPROM_ADDR + VIAL_ENCODERS_SIZE
```

Macros fill the remaining EEPROM up to `DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE` or the end of available EEPROM.

### Region 6: Total EEPROM Boundary

```
TOTAL_EEPROM_BYTE_COUNT = DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE
```

This must not exceed the wear-leveling logical size.

---

## RP2040 Wear-Leveling Configuration

The RP2040 has no internal EEPROM. QMK emulates EEPROM using a wear-leveling algorithm over the RP2040's external SPI flash (XIP flash).

| Parameter | Default Value | What It Means |
|-----------|---------------|---------------|
| `WEAR_LEVELING_DRIVER` | `rp2040_flash` (automatic) | Uses XIP flash at end of program memory |
| `WEAR_LEVELING_BACKING_SIZE` | 8192 bytes | Raw flash bytes reserved for wear-leveling |
| `WEAR_LEVELING_LOGICAL_SIZE` | 4096 bytes (backing/2) | Usable EEPROM bytes exposed to QMK |
| `WEAR_LEVELING_RP2040_FLASH_SIZE` | `PICO_FLASH_SIZE_BYTES` | Total flash on board |
| `WEAR_LEVELING_RP2040_FLASH_BASE` | End of flash minus backing size | Physical location in flash |
| `BACKING_STORE_WRITE_SIZE` | 2 bytes | Minimum write granularity |

**Key constraint:** The total EEPROM usage (all regions above) must fit within `WEAR_LEVELING_LOGICAL_SIZE` (default 4096 bytes). For the Bipedal Ambi at 8x8 matrix with 4 layers, the dynamic keymap alone is 512 bytes, which fits comfortably.

**Confidence: HIGH** -- Verified from QMK official EEPROM driver documentation.

### What NOT to touch

- **Do NOT increase `WEAR_LEVELING_BACKING_SIZE` beyond defaults** unless you have confirmed the flash chip size. Larger backing = longer erase cycles during writes, which can cause noticeable input lag.
- **Do NOT manually set `EEPROM_SIZE` or `WEAR_LEVELING_LOGICAL_SIZE`** unless the build fails with an EEPROM overflow error. The defaults (4096 logical bytes) are more than sufficient for this keyboard.
- **Do NOT use raw `eeprom_read_byte()`/`eeprom_write_byte()`** for custom data. Always use `eeconfig_update_user()` / `eeconfig_read_user()` which write to the pre-allocated user region within eeconfig, safely below the VIA region.

---

## The eeconfig_user Region: Is It Safe?

**Yes. The current `eeconfig_update_user()` / `eeconfig_read_user()` usage is safe and does NOT collide with VIA/dynamic keymap data.**

Here is why:

1. `eeconfig_user` occupies a fixed 4-byte (uint32_t) slot within the eeconfig region (Region 1), at approximately byte offset 14-17 (exact offset varies by build).
2. The VIA region (Region 2) starts at `EECONFIG_SIZE`, which is always higher than the eeconfig_user slot.
3. The dynamic keymap region (Region 3) starts even further past the VIA header.

The layer_modes + actuation_index data in both `keymap.c` files uses exactly 11 bits of the 32-bit eeconfig_user word:
- Bits 0-7: 4 layer modes at 2 bits each
- Bits 8-10: actuation index (3 bits)

**This is not the cause of the layer offset bug.** The eeconfig_user writes are safely contained within their allocated region.

**Confidence: HIGH** -- The eeconfig_user slot is part of the QMK core allocation chain, allocated before VIA's region begins.

---

## Recommended Diagnostic and Fix Stack

### Subsystem 1: Matrix Dimension Alignment (THE FIX)

| Item | Action | Why |
|------|--------|-----|
| `vial.json` (left) | Change `"rows": 4` to `"rows": 8` | Must match firmware `MATRIX_ROWS` so Vial GUI and firmware agree on EEPROM offsets |
| `vial.json` (right) | Change `"rows": 4` to `"rows": 8` | Same reason |
| `vial.json` layouts | Update keymap layout to include rows 4-7 positions for the "other half" | Split keyboards expose both halves' rows in the full matrix |

**Critical detail for split keyboards:** In QMK split architecture, `MATRIX_ROWS` is doubled (4 physical rows per hand x 2 hands = 8). The matrix scanning first populates the left half's rows (0-3), then the right half's rows (4-7). The vial.json must reflect this full 8-row matrix, with the layout mapping physical keys to their correct row positions across both halves.

However, this keyboard uses **separate firmware builds** for left and right (`vial_left` and `vial_right` keymaps), each flashed independently. This is an unusual split configuration. In this case:

- The left firmware only scans rows 0-3 directly and gets rows 4-7 from the right half via serial
- The right firmware similarly scans its own rows and gets the other half via serial
- But `MATRIX_ROWS=8` means the firmware allocates EEPROM space for all 8 rows
- `vial.json` with `rows: 4` makes Vial think only 4 rows exist, causing the offset mismatch

**The fix is still the same:** `vial.json` must say `"rows": 8` to match the firmware's `MATRIX_ROWS`.

**Confidence: HIGH**

### Subsystem 2: EEPROM Reset After Fix

| Tool | Purpose | How |
|------|---------|-----|
| Bootmagic Lite | Reset EEPROM to defaults | Hold Esc (or top-left key) while plugging in USB |
| `eeconfig_init_via()` | Triggered automatically when VIA magic is invalid | After EEPROM reset, VIA copies flash keymap to EEPROM |
| `dynamic_keymap_reset()` | Called by `eeconfig_init_via()` | Iterates all layers/rows/cols and writes default keycodes from flash |

**After changing vial.json and reflashing, you MUST reset EEPROM.** The old EEPROM data was written with the wrong offset calculations. Simply reflashing firmware does not clear EEPROM -- the wear-leveling flash retains old data across reflashes.

**Confidence: HIGH**

### Subsystem 3: Diagnostic Tools (If Fix Doesn't Resolve)

| Tool | Purpose | When to Use |
|------|---------|-------------|
| QMK Console (`CONSOLE_ENABLE = yes`) | Print debug messages from firmware | If layer offset persists after fix |
| `dynamic_keymap_get_keycode(layer, row, col)` | Read back what firmware sees at a position | Add debug prints to verify EEPROM reads match expectations |
| Vial "Save" / "Load" JSON | Export current Vial keymap to file | Compare what Vial thinks is stored vs what firmware reads |
| `hid_listen` / QMK Toolbox console | View debug output over USB HID | Monitor in real-time while pressing keys |

**Warning:** Enabling `CONSOLE_ENABLE` adds significant firmware size. May need to disable other features temporarily (e.g., `LTO_ENABLE = yes` helps, which is already enabled).

**Confidence: HIGH**

### Subsystem 4: What NOT to Do

| Anti-Pattern | Why It's Wrong |
|--------------|----------------|
| Set `DYNAMIC_KEYMAP_EEPROM_ADDR` manually | Breaks the address chain; addresses are calculated automatically from EECONFIG_SIZE through VIA headers |
| Use `VIA_EEPROM_CUSTOM_CONFIG_SIZE` for user data | This is VIA's custom config space, not for keymap user preferences; use `eeconfig_update_user()` instead |
| Change `MATRIX_ROWS` in config.h to 4 | This would break split keyboard scanning; the doubled rows are required by QMK's split architecture |
| Write raw EEPROM at hardcoded addresses | Will collide with QMK's managed regions; the address chain shifts when features are added/removed |
| Skip EEPROM reset after reflashing | Old corrupt data persists in wear-leveling flash; firmware won't overwrite unless magic bytes are invalid |

---

## Bipedal Ambi Specific EEPROM Budget

Calculated for the current build (`MATRIX_ROWS=8`, `MATRIX_COLS=8`, `DYNAMIC_KEYMAP_LAYER_COUNT=4`):

| Region | Size (bytes) | Running Total |
|--------|-------------|---------------|
| eeconfig core (incl. user) | ~30-50 | ~50 |
| VIA header (magic + layout opts) | ~4 | ~54 |
| VIA custom config | 0 (default) | ~54 |
| Dynamic keymap (4 x 8 x 8 x 2) | 512 | ~566 |
| Vial encoders (right: 32, left: 0) | 0-32 | ~598 |
| Dynamic macros (remaining) | ~3498 | 4096 |

**Total: well within the 4096-byte wear-leveling logical size.** No EEPROM overflow risk.

**Confidence: HIGH** (calculated from verified formulas)

---

## Sources

- [Vial Porting Guide - Create JSON](https://get.vial.today/docs/porting-to-via.html) -- matrix rows/cols must match config.h
- [vial-qmk dynamic_keymap.c](https://github.com/vial-kb/vial-qmk/blob/c9c90c06b798f22591b98f8e0de34bde297c6ef5/quantum/dynamic_keymap.c) -- EEPROM address chain and offset calculations
- [QMK EEPROM Driver Docs](https://docs.qmk.fm/drivers/eeprom) -- RP2040 wear-leveling configuration
- [QMK Persistent Configuration Docs](https://docs.qmk.fm/feature_eeprom) -- eeconfig_user API
- [QMK via.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/via.h) -- VIA EEPROM size defines
- [VIA Configuring QMK](https://caniusevia.com/docs/configuring_qmk/) -- VIA EEPROM layout options
- [QMK Split Keyboard Docs](https://docs.qmk.fm/features/split_keyboard) -- MATRIX_ROWS doubling for split
- [QMK RP2040 Platform Docs](https://docs.qmk.fm/platformdev_rp2040) -- RP2040 flash architecture
- [Vial Encoder Support](https://get.vial.today/docs/encoders.html) -- Encoder EEPROM size calculation
- [DeepWiki vial-qmk Features](https://deepwiki.com/vial-kb/vial-qmk/5-features-and-customization) -- Vial-specific EEPROM handling
