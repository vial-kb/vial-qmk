# EEPROM Address Map: Bipedal Ambi (vial-qmk fork)

**Date:** 2026-02-14
**Purpose:** Document the complete EEPROM address layout for both halves of the Bipedal Ambi split keyboard, verify no region overlaps, and confirm total usage fits within 4096 bytes.
**Requirements satisfied:** EEPR-04 (EEPROM budget documented with no overlaps), XVAL-02 (verified against vial-qmk fork source, not upstream docs)

---

## 1. Constants Table

Every constant used in the address calculation, its value, and the source file reference.

| Constant | Value | Source File | Line/Context |
|----------|-------|-------------|--------------|
| `sizeof(eeprom_core_t)` | 36 bytes | `quantum/eeconfig.h` | Lines 32-51, PACKED struct definition |
| `EECONFIG_BASE_SIZE` | 36 | `quantum/eeconfig.h` | Line 72: `#define EECONFIG_BASE_SIZE ((uint8_t)sizeof(eeprom_core_t))` |
| `EECONFIG_KB_DATA_SIZE` | 0 | `quantum/eeconfig.h` | Line 76: default 0, not overridden by keyboard |
| `EECONFIG_USER_DATA_SIZE` | 0 | `quantum/eeconfig.h` | Line 82: default 0, not overridden by keyboard |
| `EECONFIG_SIZE` | 36 | `quantum/eeconfig.h` | Line 92: `EECONFIG_BASE_SIZE + KB_DATA_SIZE + USER_DATA_SIZE = 36 + 0 + 0` |
| `VIA_EEPROM_MAGIC_ADDR` | 36 | `quantum/via.h` | Line 29: `#define VIA_EEPROM_MAGIC_ADDR (EECONFIG_SIZE)` |
| `VIA_EEPROM_LAYOUT_OPTIONS_ADDR` | 39 | `quantum/via.h` | Line 32: `VIA_EEPROM_MAGIC_ADDR + 3 = 36 + 3` |
| `VIA_EEPROM_LAYOUT_OPTIONS_SIZE` | 1 | `quantum/via.h` | Line 38: default 1, not overridden by keyboard |
| `VIA_EEPROM_CUSTOM_CONFIG_ADDR` | 40 | `quantum/via.h` | Line 52: `LAYOUT_OPTIONS_ADDR + LAYOUT_OPTIONS_SIZE = 39 + 1` |
| `VIA_EEPROM_CUSTOM_CONFIG_SIZE` | 0 | `quantum/via.h` | Line 55: default 0, not overridden by keyboard |
| `VIA_EEPROM_CONFIG_END` | 40 | `quantum/via.h` | Line 58: `CUSTOM_CONFIG_ADDR + CUSTOM_CONFIG_SIZE = 40 + 0` |
| `DYNAMIC_KEYMAP_EEPROM_ADDR` | 40 | `quantum/dynamic_keymap.c` | Line 30: `VIA_EEPROM_CONFIG_END` (VIA_ENABLE path) |
| `MATRIX_ROWS` | 8 | `keyboards/hidpress/bipedalambi/config.h` | Line 28: `#define MATRIX_ROWS 8` |
| `MATRIX_COLS` | 8 | `keyboards/hidpress/bipedalambi/config.h` | Line 29: `#define MATRIX_COLS 8` |
| `DYNAMIC_KEYMAP_LAYER_COUNT` | 4 | `keyboards/hidpress/bipedalambi/keymaps/vial_right/config.h` | Line 10 (both keymaps) |
| Keymap size | 512 | `quantum/dynamic_keymap.c` | Line 71 formula: `LAYERS * ROWS * COLS * 2 = 4 * 8 * 8 * 2` |
| `VIAL_ENCODERS_EEPROM_ADDR` | 552 | `quantum/dynamic_keymap.c` | Line 71: `DYNAMIC_KEYMAP_EEPROM_ADDR + keymap_size = 40 + 512` |
| `NUM_ENCODERS` (right) | 1 | `keyboards/hidpress/bipedalambi/keymaps/vial_right/config.h` | Line 38: `#define NUM_ENCODERS 1` |
| `NUM_ENCODERS` (left) | 0 | `quantum/dynamic_keymap.c` | Line 43: `#define NUM_ENCODERS 0` (ENCODER_ENABLE not defined) |
| `VIAL_ENCODERS_SIZE` (right) | 16 | `quantum/dynamic_keymap.c` | Line 74: `NUM_ENCODERS * LAYERS * 2 * 2 = 1 * 4 * 2 * 2` |
| `VIAL_ENCODERS_SIZE` (left) | 0 | `quantum/dynamic_keymap.c` | Line 74: `0 * 4 * 2 * 2 = 0` |
| `VIAL_QMK_SETTINGS_SIZE` | 0 | `quantum/dynamic_keymap.c` | Line 83: `QMK_SETTINGS` not defined |
| `VIAL_TAP_DANCE_SIZE` | 0 | `quantum/dynamic_keymap.c` | Line 92: `VIAL_TAP_DANCE_ENABLE` not defined |
| `VIAL_COMBO_SIZE` | 0 | `quantum/dynamic_keymap.c` | Line 101: `VIAL_COMBO_ENABLE` not defined |
| `VIAL_KEY_OVERRIDE_SIZE` | 0 | `quantum/dynamic_keymap.c` | Line 110: `VIAL_KEY_OVERRIDE_ENABLE` not defined |
| `WEAR_LEVELING_BACKING_SIZE` | 8192 | `platforms/chibios/drivers/wear_leveling/wear_leveling_rp2040_flash_config.h` | Line 16 |
| `WEAR_LEVELING_LOGICAL_SIZE` | 4096 | `platforms/chibios/drivers/wear_leveling/wear_leveling_rp2040_flash_config.h` | Line 21: `BACKING_SIZE / 2 = 8192 / 2` |
| `TOTAL_EEPROM_BYTE_COUNT` | 4096 | `platforms/eeprom.h` | Line 40: `WEAR_LEVELING_LOGICAL_SIZE` (EEPROM_WEAR_LEVELING path) |
| `DYNAMIC_KEYMAP_EEPROM_MAX_ADDR` | 4095 | `quantum/dynamic_keymap.c` | Line 51: `TOTAL_EEPROM_BYTE_COUNT - 1 = 4096 - 1` |

---

## 2. Right Half Address Map (ENCODER_ENABLE=yes, NUM_ENCODERS=1)

Source: `keyboards/hidpress/bipedalambi/keymaps/vial_right/rules.mk` (ENCODER_ENABLE=yes, ENCODER_MAP_ENABLE=yes)

| Byte Range | Size (bytes) | Region Name | Source File |
|------------|-------------|-------------|-------------|
| **0-35** | **36** | **eeconfig (eeprom_core_t)** | `quantum/eeconfig.h` lines 32-51 |
| 0-1 | 2 | magic (uint16_t) | `quantum/eeconfig.h` line 33 |
| 2 | 1 | debug (uint8_t) | `quantum/eeconfig.h` line 34 |
| 3 | 1 | default_layer (uint8_t) | `quantum/eeconfig.h` line 35 |
| 4-5 | 2 | keymap (uint16_t) | `quantum/eeconfig.h` line 36 |
| 6 | 1 | backlight (uint8_t) | `quantum/eeconfig.h` line 37 |
| 7 | 1 | audio (uint8_t) | `quantum/eeconfig.h` line 38 |
| 8-11 | 4 | rgblight (uint32_t) | `quantum/eeconfig.h` line 39 |
| 12 | 1 | unicode (uint8_t) | `quantum/eeconfig.h` line 40 |
| 13 | 1 | steno (uint8_t) | `quantum/eeconfig.h` line 41 |
| 14 | 1 | handedness (uint8_t) | `quantum/eeconfig.h` line 42 |
| 15-18 | 4 | keyboard (uint32_t) | `quantum/eeconfig.h` line 43 |
| **19-22** | **4** | **user (uint32_t) -- eeconfig_user** | `quantum/eeconfig.h` line 44 |
| 23-30 | 8 | led_matrix/rgb_matrix union (max(uint32_t, uint64_t)) | `quantum/eeconfig.h` lines 45-48 |
| 31-34 | 4 | haptic (uint32_t) | `quantum/eeconfig.h` line 49 |
| 35 | 1 | rgblight_ext (uint8_t) | `quantum/eeconfig.h` line 50 |
| **36-38** | **3** | **VIA magic (build date BCD)** | `quantum/via.h` line 29 |
| **39** | **1** | **VIA layout options** | `quantum/via.h` lines 32, 38 |
| | 0 | VIA custom config (zero-sized) | `quantum/via.h` lines 52, 55 |
| **40-551** | **512** | **Dynamic keymap (4 layers x 8 rows x 8 cols x 2 bytes)** | `quantum/dynamic_keymap.c` lines 30, 67, 71 |
| 40-167 | 128 | Layer 0 (8 rows x 8 cols x 2 bytes) | `quantum/dynamic_keymap.c` line 141 |
| 168-295 | 128 | Layer 1 | |
| 296-423 | 128 | Layer 2 | |
| 424-551 | 128 | Layer 3 | |
| **552-567** | **16** | **Encoder map (1 encoder x 4 layers x 2 directions x 2 bytes)** | `quantum/dynamic_keymap.c` lines 71-74 |
| | 0 | QMK settings (zero-sized, QMK_SETTINGS not defined) | `quantum/dynamic_keymap.c` lines 77, 83 |
| | 0 | Tap dance (zero-sized, VIAL_TAP_DANCE_ENABLE not defined) | `quantum/dynamic_keymap.c` lines 87, 92 |
| | 0 | Combos (zero-sized, VIAL_COMBO_ENABLE not defined) | `quantum/dynamic_keymap.c` lines 96, 101 |
| | 0 | Key overrides (zero-sized, VIAL_KEY_OVERRIDE_ENABLE not defined) | `quantum/dynamic_keymap.c` lines 105, 110 |
| **568-4095** | **3528** | **Dynamic macros** | `quantum/dynamic_keymap.c` lines 114-129 |
| | | **TOTAL** | **4096** |

### Per-Layer Keymap Byte Ranges (Right Half)

Each layer stores 8 rows x 8 cols x 2 bytes = 128 bytes.

| Layer | Start Address | End Address | Formula |
|-------|--------------|-------------|---------|
| 0 | 40 | 167 | 40 + (0 * 128) to 40 + (1 * 128) - 1 |
| 1 | 168 | 295 | 40 + (1 * 128) to 40 + (2 * 128) - 1 |
| 2 | 296 | 423 | 40 + (2 * 128) to 40 + (3 * 128) - 1 |
| 3 | 424 | 551 | 40 + (3 * 128) to 40 + (4 * 128) - 1 |

---

## 3. Left Half Address Map (ENCODER_ENABLE=no, NUM_ENCODERS=0)

Source: `keyboards/hidpress/bipedalambi/keymaps/vial_left/rules.mk` (ENCODER_MAP_ENABLE commented out, ENCODER_ENABLE not defined)

| Byte Range | Size (bytes) | Region Name | Source File |
|------------|-------------|-------------|-------------|
| **0-35** | **36** | **eeconfig (eeprom_core_t)** | `quantum/eeconfig.h` lines 32-51 |
| **19-22** | **4** | **user (uint32_t) -- eeconfig_user** | `quantum/eeconfig.h` line 44 |
| **36-38** | **3** | **VIA magic (build date BCD)** | `quantum/via.h` line 29 |
| **39** | **1** | **VIA layout options** | `quantum/via.h` lines 32, 38 |
| | 0 | VIA custom config (zero-sized) | `quantum/via.h` lines 52, 55 |
| **40-551** | **512** | **Dynamic keymap (4 layers x 8 rows x 8 cols x 2 bytes)** | `quantum/dynamic_keymap.c` lines 30, 67, 71 |
| 40-167 | 128 | Layer 0 | |
| 168-295 | 128 | Layer 1 | |
| 296-423 | 128 | Layer 2 | |
| 424-551 | 128 | Layer 3 | |
| | 0 | Encoder map (zero-sized, NUM_ENCODERS=0) | `quantum/dynamic_keymap.c` lines 71-74 |
| | 0 | QMK settings (zero-sized) | `quantum/dynamic_keymap.c` lines 77, 83 |
| | 0 | Tap dance (zero-sized) | `quantum/dynamic_keymap.c` lines 87, 92 |
| | 0 | Combos (zero-sized) | `quantum/dynamic_keymap.c` lines 96, 101 |
| | 0 | Key overrides (zero-sized) | `quantum/dynamic_keymap.c` lines 105, 110 |
| **552-4095** | **3544** | **Dynamic macros** | `quantum/dynamic_keymap.c` lines 114-129 |
| | | **TOTAL** | **4096** |

### Left vs Right Difference

The only difference between the two halves is the encoder map region:

| Aspect | Left Half | Right Half |
|--------|-----------|------------|
| Encoder map size | 0 bytes | 16 bytes |
| Macro region start | byte 552 | byte 568 |
| Macro region size | 3544 bytes | 3528 bytes |
| Total EEPROM usage | 4096 bytes | 4096 bytes |

---

## 4. Overlap Verification

For each pair of adjacent regions, confirm no overlap exists (end of region A < start of region B, or exactly adjacent where end + 1 = start).

### Right Half Overlap Check

| Region A | Region A End | Region B | Region B Start | Gap (bytes) | Status |
|----------|-------------|----------|----------------|-------------|--------|
| eeconfig | 35 | VIA magic | 36 | 0 (adjacent) | OK |
| VIA magic | 38 | VIA layout options | 39 | 0 (adjacent) | OK |
| VIA layout options | 39 | Dynamic keymap | 40 | 0 (adjacent) | OK |
| Dynamic keymap | 551 | Encoder map | 552 | 0 (adjacent) | OK |
| Encoder map | 567 | Dynamic macros | 568 | 0 (adjacent) | OK |

### Left Half Overlap Check

| Region A | Region A End | Region B | Region B Start | Gap (bytes) | Status |
|----------|-------------|----------|----------------|-------------|--------|
| eeconfig | 35 | VIA magic | 36 | 0 (adjacent) | OK |
| VIA magic | 38 | VIA layout options | 39 | 0 (adjacent) | OK |
| VIA layout options | 39 | Dynamic keymap | 40 | 0 (adjacent) | OK |
| Dynamic keymap | 551 | Dynamic macros | 552 | 0 (adjacent) | OK |

### eeconfig_user Non-Overlap Verification

The `eeconfig_user` field (uint32_t) occupies bytes 19-22 within the `eeprom_core_t` struct. The first region after eeconfig is VIA magic, starting at byte 36.

- eeconfig_user end: byte 22
- VIA magic start: byte 36
- Gap: 36 - 22 - 1 = **13 bytes** (occupied by led_matrix/rgb_matrix union at 23-30, haptic at 31-34, rgblight_ext at 35)
- **eeconfig_user does NOT overlap with VIA magic or any subsequent region.**

### Result: No overlaps detected.

All regions are exactly adjacent with no gaps and no overlaps. The entire 4096-byte EEPROM address space is fully allocated.

---

## 5. Budget Summary

### Right Half

| Category | Bytes | Percentage of 4096 |
|----------|-------|-------------------|
| eeconfig (core settings) | 36 | 0.9% |
| VIA header (magic + layout options) | 4 | 0.1% |
| Dynamic keymap (4 layers) | 512 | 12.5% |
| Encoder map (1 encoder) | 16 | 0.4% |
| **Total fixed regions** | **568** | **13.9%** |
| Dynamic macros (remaining) | 3528 | 86.1% |
| **Grand total** | **4096** | **100.0%** |

Static assert check: `DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (4095) >= DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 100 (568 + 100 = 668)` -- **PASSES** with 3427 bytes of headroom.

### Left Half

| Category | Bytes | Percentage of 4096 |
|----------|-------|-------------------|
| eeconfig (core settings) | 36 | 0.9% |
| VIA header (magic + layout options) | 4 | 0.1% |
| Dynamic keymap (4 layers) | 512 | 12.5% |
| Encoder map (none) | 0 | 0.0% |
| **Total fixed regions** | **552** | **13.5%** |
| Dynamic macros (remaining) | 3544 | 86.5% |
| **Grand total** | **4096** | **100.0%** |

Static assert check: `DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (4095) >= DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 100 (552 + 100 = 652)` -- **PASSES** with 3443 bytes of headroom.

### Conclusion

Both halves use less than 14% of EEPROM for fixed-size regions. Over 86% is available for dynamic macros. The `_Static_assert` requiring at least 100 bytes for macros passes with over 3400 bytes of headroom for both halves.

---

## 6. Source Cross-References

Every address in this map traces to a specific source file and `#define` or struct definition in the vial-qmk fork. This satisfies requirement XVAL-02.

| Address/Region | Derived From | Source File | Mechanism |
|---------------|-------------|-------------|-----------|
| Bytes 0-35 (eeconfig) | `eeprom_core_t` struct, PACKED | `quantum/eeconfig.h` lines 32-51 | `sizeof(eeprom_core_t) = 36` |
| Byte 19-22 (eeconfig_user) | `offsetof(eeprom_core_t, user)` | `quantum/eeconfig.h` line 44 | Struct field offset in PACKED struct |
| EECONFIG_SIZE = 36 | `EECONFIG_BASE_SIZE + 0 + 0` | `quantum/eeconfig.h` line 92 | `#define EECONFIG_SIZE` |
| Byte 36 (VIA magic) | `VIA_EEPROM_MAGIC_ADDR = EECONFIG_SIZE` | `quantum/via.h` line 29 | `#define VIA_EEPROM_MAGIC_ADDR` |
| Byte 39 (VIA layout) | `VIA_EEPROM_MAGIC_ADDR + 3` | `quantum/via.h` line 32 | `#define VIA_EEPROM_LAYOUT_OPTIONS_ADDR` |
| Byte 40 (keymap start) | `VIA_EEPROM_CONFIG_END` | `quantum/via.h` line 58, `quantum/dynamic_keymap.c` line 30 | `#define DYNAMIC_KEYMAP_EEPROM_START` |
| Byte 552 (encoder start) | `DYNAMIC_KEYMAP_EEPROM_ADDR + (4 * 8 * 8 * 2)` | `quantum/dynamic_keymap.c` line 71 | `#define VIAL_ENCODERS_EEPROM_ADDR` |
| 16 bytes encoder (right) | `NUM_ENCODERS * LAYERS * 2 * 2 = 1 * 4 * 2 * 2` | `quantum/dynamic_keymap.c` line 74 | `#define VIAL_ENCODERS_SIZE` |
| NUM_ENCODERS=1 (right) | Explicit define | `keyboards/hidpress/bipedalambi/keymaps/vial_right/config.h` line 38 | `#define NUM_ENCODERS 1` |
| NUM_ENCODERS=0 (left) | ENCODER_ENABLE not defined | `quantum/dynamic_keymap.c` line 43 | `#define NUM_ENCODERS 0` fallback |
| Byte 568 (macros, right) | `VIAL_KEY_OVERRIDE_EEPROM_ADDR + 0` | `quantum/dynamic_keymap.c` line 115 | `#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR` |
| Byte 552 (macros, left) | `VIAL_KEY_OVERRIDE_EEPROM_ADDR + 0` | `quantum/dynamic_keymap.c` line 115 | Same chain, but encoder size = 0 |
| 4095 (max addr) | `TOTAL_EEPROM_BYTE_COUNT - 1` | `quantum/dynamic_keymap.c` line 51 | `#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR` |
| 4096 (total EEPROM) | `WEAR_LEVELING_LOGICAL_SIZE` | `platforms/eeprom.h` line 40, `platforms/chibios/drivers/wear_leveling/wear_leveling_rp2040_flash_config.h` line 21 | `#define TOTAL_EEPROM_BYTE_COUNT` |
| 8192 (backing size) | Default for RP2040 | `platforms/chibios/drivers/wear_leveling/wear_leveling_rp2040_flash_config.h` line 16 | `#define WEAR_LEVELING_BACKING_SIZE` |
| MATRIX_ROWS=8 | Board config | `keyboards/hidpress/bipedalambi/config.h` line 28 | `#define MATRIX_ROWS 8` |
| MATRIX_COLS=8 | Board config | `keyboards/hidpress/bipedalambi/config.h` line 29 | `#define MATRIX_COLS 8` |
| DYNAMIC_KEYMAP_LAYER_COUNT=4 | Keymap config | `keyboards/hidpress/bipedalambi/keymaps/vial_right/config.h` line 10 | `#define DYNAMIC_KEYMAP_LAYER_COUNT 4` |

**No upstream QMK or VIA documentation was used.** All addresses derived from vial-qmk fork source code files in this repository.

---

## 7. eeconfig_user Bit Layout (Bipedal Ambi)

For reference, the `eeconfig_user` field at bytes 19-22 stores Bipedal Ambi-specific configuration:

| Bits | Field | Description |
|------|-------|-------------|
| 0-1 | layer_modes[0] | Layer 0 mode (2 bits) |
| 2-3 | layer_modes[1] | Layer 1 mode (2 bits) |
| 4-5 | layer_modes[2] | Layer 2 mode (2 bits) |
| 6-7 | layer_modes[3] | Layer 3 mode (2 bits) |
| 8-10 | current_actuation_index | Global actuation index (3 bits) |
| 11-31 | (unused) | Reserved (21 bits) |

Source: `keyboards/hidpress/bipedalambi/keymaps/vial_right/keymap.c` and `vial_left/keymap.c`
