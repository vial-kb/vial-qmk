# Phase 5: EEPROM Budget Verification - Research

**Researched:** 2026-02-14
**Domain:** EEPROM address map calculation and overlap verification for vial-qmk on RP2040 with wear-leveling emulation
**Confidence:** HIGH

## Summary

Phase 5 is a pure calculation and documentation phase. No code changes are needed -- the goal is to trace the complete EEPROM address chain from `dynamic_keymap.c` and related headers, compute every region's start address and size, and confirm three things: (1) no regions overlap, (2) total usage fits within the 4096-byte wear-leveling logical size, and (3) `eeconfig_user` (bytes 19-22) does not collide with VIA/dynamic keymap regions (which start at byte 36+).

The EEPROM layout is entirely determined by preprocessor macros in `dynamic_keymap.c`, `via.h`, `eeconfig.h`, and `vial.h`. There is no runtime computation -- all addresses are compile-time constants. This means the address map can be calculated definitively from the source code without building the firmware.

The Bipedal Ambi has two independent firmwares (left and right) with slightly different EEPROM layouts because the right half enables `ENCODER_ENABLE` and `ENCODER_MAP_ENABLE` while the left half does not. Both halves compile with `MATRIX_ROWS=8`, `MATRIX_COLS=8`, and `DYNAMIC_KEYMAP_LAYER_COUNT=4`. The right half has `NUM_ENCODERS=1` (explicitly set in Phase 4). Neither half enables TAP_DANCE, COMBO, KEY_OVERRIDE, or QMK_SETTINGS -- so those Vial EEPROM regions are all zero-sized.

**Primary recommendation:** Calculate the address map from source code constants, produce a per-half EEPROM map table, and verify no overlaps. This is arithmetic, not engineering. The prior research (Phase 1 Section 6, PITFALLS.md budget estimate) already approximated the answer at ~568/4096 bytes for the right half -- this phase produces the exact, verified calculation.

## Standard Stack

This is a documentation-only phase. No files are modified. The "stack" is the set of source files to read and the formulas to apply.

### Source Files to Read (Authoritative)

| File | What It Provides |
|------|-----------------|
| `quantum/eeconfig.h` | `eeprom_core_t` struct layout, `EECONFIG_BASE_SIZE`, `EECONFIG_SIZE` |
| `quantum/via.h` | VIA magic address, layout options, custom config, `VIA_EEPROM_CONFIG_END` |
| `quantum/dynamic_keymap.c` | `DYNAMIC_KEYMAP_EEPROM_ADDR`, encoder EEPROM addr, QMK settings, tap dance, combo, key override, macro regions -- the complete chain |
| `quantum/dynamic_keymap.h` | `DYNAMIC_KEYMAP_LAYER_COUNT` default (4), `DYNAMIC_KEYMAP_MACRO_COUNT` default (16) |
| `quantum/vial.h` | `VIAL_TAP_DANCE_ENTRIES`, `VIAL_COMBO_ENTRIES`, `VIAL_KEY_OVERRIDE_ENTRIES` (all gated by feature enables) |
| `quantum/encoder.h` | `NUM_ENCODERS` split-doubling logic |
| `platforms/chibios/drivers/wear_leveling/wear_leveling_rp2040_flash_config.h` | `WEAR_LEVELING_BACKING_SIZE` (8192), `WEAR_LEVELING_LOGICAL_SIZE` (4096) |
| `platforms/eeprom.h` | `TOTAL_EEPROM_BYTE_COUNT = WEAR_LEVELING_LOGICAL_SIZE` for wear-leveling drivers |
| `keyboards/hidpress/bipedalambi/config.h` | `MATRIX_ROWS=8`, `MATRIX_COLS=8` |
| `keyboards/hidpress/bipedalambi/keymaps/vial_left/config.h` | `DYNAMIC_KEYMAP_LAYER_COUNT=4`, no encoder defines |
| `keyboards/hidpress/bipedalambi/keymaps/vial_right/config.h` | `DYNAMIC_KEYMAP_LAYER_COUNT=4`, `NUM_ENCODERS=1`, `ENCODERS_PAD_A/B` |
| `keyboards/hidpress/bipedalambi/keymaps/vial_left/rules.mk` | `ENCODER_MAP_ENABLE` commented out, no TAP_DANCE/COMBO/KEY_OVERRIDE |
| `keyboards/hidpress/bipedalambi/keymaps/vial_right/rules.mk` | `ENCODER_ENABLE=yes`, `ENCODER_MAP_ENABLE=yes` |

### Files NOT Modified

All of them. This phase produces only documentation.

## Architecture Patterns

### Pattern 1: The EEPROM Address Chain

**What:** The vial-qmk fork uses a linear chain of `#define` macros in `dynamic_keymap.c` to lay out EEPROM regions sequentially. Each region's start address is the previous region's end address. The chain is:

```
EECONFIG_SIZE (eeprom_core_t struct)
  -> VIA_EEPROM_MAGIC_ADDR (= EECONFIG_SIZE)
  -> VIA_EEPROM_LAYOUT_OPTIONS_ADDR (= MAGIC + 3)
  -> VIA_EEPROM_CUSTOM_CONFIG_ADDR (= LAYOUT_OPTIONS + OPTIONS_SIZE)
  -> VIA_EEPROM_CONFIG_END (= CUSTOM_CONFIG + CUSTOM_CONFIG_SIZE)
  -> DYNAMIC_KEYMAP_EEPROM_ADDR (= VIA_EEPROM_CONFIG_END)
  -> VIAL_ENCODERS_EEPROM_ADDR (= KEYMAP + keymap_size)
  -> VIAL_QMK_SETTINGS_EEPROM_ADDR (= ENCODERS + encoder_size)
  -> VIAL_TAP_DANCE_EEPROM_ADDR (= QMK_SETTINGS + settings_size)
  -> VIAL_COMBO_EEPROM_ADDR (= TAP_DANCE + td_size)
  -> VIAL_KEY_OVERRIDE_EEPROM_ADDR (= COMBO + combo_size)
  -> DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (= KEY_OVERRIDE + ko_size)
  -> macro region extends to DYNAMIC_KEYMAP_EEPROM_MAX_ADDR
```

**Source:** `quantum/dynamic_keymap.c` lines 28-129, `quantum/via.h` lines 28-58

**Why this matters:** Because the chain is linear and each region is sized by compile-time constants, calculating the map is deterministic. There is no dynamic allocation. If you know the constant values, you know the exact byte addresses.

### Pattern 2: The eeprom_core_t Struct (EECONFIG region)

**What:** QMK's core EEPROM is a PACKED struct `eeprom_core_t` defined in `eeconfig.h`. The struct is 36 bytes with no padding (PACKED attribute). The fields and their byte offsets are:

```
Byte  Field              Size
----  -----------------  ----
0-1   magic              2
2     debug              1
3     default_layer      1
4-5   keymap             2
6     backlight          1
7     audio              1
8-11  rgblight           4
12    unicode            1
13    steno              1
14    handedness         1
15-18 keyboard           4
19-22 user               4    <-- eeconfig_user lives here
23-30 led_matrix/rgb_matrix union  8
31-34 haptic             4
35    rgblight_ext       1
----                     --
Total                    36 bytes
```

**Critical:** `eeconfig_user` (the 4 bytes used by Bipedal Ambi for layer modes and actuation index) occupies bytes 19-22. This is inside the `eeprom_core_t` struct, well before the VIA region starts at byte 36. There is a 13-byte gap between `eeconfig_user` end (byte 22) and VIA magic start (byte 36), occupied by the union and haptic fields.

**Source:** `quantum/eeconfig.h` lines 32-51 (struct definition), verified by manual offset calculation

### Pattern 3: Macro Region Fills Remaining Space

**What:** The dynamic macro region is not a fixed size. It is defined as:

```c
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 1)
```

Where `DYNAMIC_KEYMAP_EEPROM_MAX_ADDR = TOTAL_EEPROM_BYTE_COUNT - 1 = 4095`. This means macros consume ALL remaining EEPROM space after the other regions. The more space used by keymaps/encoders, the less available for macros.

**Constraint:** A `_Static_assert` at line 123 of `dynamic_keymap.c` requires at least 100 bytes available for macros:

```c
_Static_assert(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR >= DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 100, ...);
```

**Source:** `quantum/dynamic_keymap.c` lines 114-129

### Pattern 4: Per-Half EEPROM Differences

**What:** Because each half builds independently with different `rules.mk` feature flags, the EEPROM layout differs slightly between halves:

| Feature | Left Half | Right Half |
|---------|-----------|------------|
| ENCODER_ENABLE | No | Yes |
| ENCODER_MAP_ENABLE | No | Yes |
| NUM_ENCODERS (effective) | 0 | 1 |
| VIAL_ENCODERS_SIZE | 0 bytes | 16 bytes |
| Macro region start | byte 552 | byte 568 |
| Macro region size | 3544 bytes | 3528 bytes |

**Source:** `keymaps/vial_left/rules.mk` (ENCODER_MAP_ENABLE commented out), `keymaps/vial_right/rules.mk` (ENCODER_ENABLE=yes, ENCODER_MAP_ENABLE=yes), `keymaps/vial_right/config.h` (NUM_ENCODERS=1)

### Anti-Patterns to Avoid

- **Using prior research estimates as final values:** The PITFALLS.md budget estimate (~686 bytes, ~30 bytes for eeconfig) was an approximation. The actual EECONFIG_BASE_SIZE is exactly 36 bytes. Use the verified values from this research.
- **Calculating for only one half:** The left and right halves have different EEPROM layouts. Document both.
- **Confusing eeconfig_user with VIA_EEPROM_CUSTOM_CONFIG_SIZE:** `eeconfig_user` is a 4-byte field inside the `eeprom_core_t` struct (bytes 19-22). `VIA_EEPROM_CUSTOM_CONFIG_SIZE` is a separate region for VIA-specific keyboard configuration (default 0). They are completely unrelated.
- **Assuming upstream QMK addresses:** The vial-qmk fork has a different EEPROM chain than upstream QMK. The Vial-specific regions (encoders, QMK settings, tap dance, combos, key overrides) are inserted between the dynamic keymap and the macro region. Upstream QMK goes directly from keymap to macro.

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| Address calculation | Mental arithmetic | Python script tracing the #define chain | One mistake cascades through all downstream addresses |
| Struct size | Manual byte counting | Read the PACKED struct definition + manual addition (verified: 36 bytes) | The union field (8 bytes) is easy to miscalculate |
| Overlap detection | Visual inspection of ranges | Automated check: for each pair of regions, verify end_A <= start_B | Humans miss adjacent regions that technically don't overlap but would if off-by-one |

**Key insight:** The entire calculation is deterministic from compile-time constants. There are no conditionals to evaluate at runtime. The planner should produce a task that mechanically traces the chain and outputs a table.

## Common Pitfalls

### Pitfall 1: Wrong EECONFIG_BASE_SIZE

**What goes wrong:** The executor estimates EECONFIG_SIZE as "approximately 30 bytes" or uses an older QMK version's struct layout.
**Why it happens:** The `eeprom_core_t` struct has been modified across QMK versions (fields added/reordered). Prior research used estimates.
**How to avoid:** Read the struct definition from `quantum/eeconfig.h` in the vial-qmk fork directly. The struct is PACKED, so sizeof = sum of field sizes. For this fork: 36 bytes.
**Warning signs:** If the calculated EECONFIG_SIZE doesn't match 36, something was miscounted.

### Pitfall 2: Forgetting EECONFIG_KB_DATA_SIZE and EECONFIG_USER_DATA_SIZE

**What goes wrong:** The executor uses EECONFIG_BASE_SIZE directly as EECONFIG_SIZE, forgetting to add KB/USER data sizes.
**Why it happens:** EECONFIG_SIZE = EECONFIG_BASE_SIZE + EECONFIG_KB_DATA_SIZE + EECONFIG_USER_DATA_SIZE. If KB or USER data sizes are non-zero, EECONFIG_SIZE is larger.
**How to avoid:** Check whether the keyboard defines `EECONFIG_KB_DATA_SIZE` or `EECONFIG_USER_DATA_SIZE` in any config.h. For Bipedal Ambi: neither is defined, so both default to 0, and EECONFIG_SIZE = EECONFIG_BASE_SIZE = 36.
**Warning signs:** If EECONFIG_SIZE > 36 for this keyboard, check for unexpected data size definitions.

### Pitfall 3: Confusing Left-Half and Right-Half Encoder EEPROM

**What goes wrong:** The executor calculates one EEPROM map and applies it to both halves.
**Why it happens:** Both halves share the same `config.h` for MATRIX_ROWS/COLS and DYNAMIC_KEYMAP_LAYER_COUNT. The difference (encoder) is in per-keymap rules.mk.
**How to avoid:** Calculate separate maps for left and right halves. The divergence point is VIAL_ENCODERS_SIZE: 0 for left, 16 for right.
**Warning signs:** If the documented map shows encoder space for the left half, it's wrong.

### Pitfall 4: Using Upstream QMK EEPROM Layout

**What goes wrong:** The executor references upstream QMK/VIA documentation for EEPROM addresses. Upstream QMK does not have the Vial-specific regions (QMK settings, tap dance, combos, key overrides between encoders and macros).
**Why it happens:** Upstream QMK documentation is more readily available than vial-qmk fork details.
**How to avoid:** Read the address chain from `quantum/dynamic_keymap.c` in the vial-qmk fork (this repo), not upstream QMK. Requirement XVAL-02 explicitly mandates this.
**Warning signs:** If the map shows macros immediately after encoders with no intermediate regions, the executor used the upstream chain.

### Pitfall 5: Miscounting the Union Size in eeprom_core_t

**What goes wrong:** The executor counts the union as 4 bytes (uint32_t led_matrix) instead of 8 bytes (the max of uint32_t and uint64_t).
**Why it happens:** The union contains `uint32_t led_matrix` and `uint64_t rgb_matrix`. A union's size is the maximum of its members.
**How to avoid:** The union size is 8 bytes (sizeof(uint64_t)). Verify the total struct size = 36.
**Warning signs:** If sizeof(eeprom_core_t) computes to 32 instead of 36, the union was miscounted.

## Code Examples

### Complete EEPROM Address Chain (From Source)

```c
// Source: quantum/dynamic_keymap.c lines 28-129, quantum/via.h lines 28-58
// All values calculated for Bipedal Ambi

// Region 1: eeconfig (QMK core)
// Source: quantum/eeconfig.h
EECONFIG_BASE_SIZE = sizeof(eeprom_core_t) = 36
EECONFIG_KB_DATA_SIZE = 0     // not defined by keyboard
EECONFIG_USER_DATA_SIZE = 0   // not defined by keyboard
EECONFIG_SIZE = 36 + 0 + 0 = 36

// Region 2: VIA header
// Source: quantum/via.h
VIA_EEPROM_MAGIC_ADDR = EECONFIG_SIZE = 36
VIA_EEPROM_LAYOUT_OPTIONS_ADDR = 36 + 3 = 39
VIA_EEPROM_LAYOUT_OPTIONS_SIZE = 1  // default
VIA_EEPROM_CUSTOM_CONFIG_ADDR = 39 + 1 = 40
VIA_EEPROM_CUSTOM_CONFIG_SIZE = 0   // default, not overridden
VIA_EEPROM_CONFIG_END = 40 + 0 = 40

// Region 3: Dynamic keymap
// Source: quantum/dynamic_keymap.c
DYNAMIC_KEYMAP_EEPROM_ADDR = VIA_EEPROM_CONFIG_END = 40
// Size = LAYERS * ROWS * COLS * 2 = 4 * 8 * 8 * 2 = 512

// Region 4: Encoder map (RIGHT HALF ONLY)
// Source: quantum/dynamic_keymap.c line 71-74
VIAL_ENCODERS_EEPROM_ADDR = 40 + 512 = 552
// Right: VIAL_ENCODERS_SIZE = 1 * 4 * 2 * 2 = 16
// Left:  VIAL_ENCODERS_SIZE = 0 (no ENCODER_ENABLE)

// Region 5-8: QMK Settings, Tap Dance, Combos, Key Overrides
// All SIZE = 0 (features not enabled)
// Source: quantum/dynamic_keymap.c lines 77-116, quantum/vial.h

// Region 9: Dynamic macros
// Right: DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR = 552 + 16 = 568
// Left:  DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR = 552 + 0 = 552
DYNAMIC_KEYMAP_EEPROM_MAX_ADDR = TOTAL_EEPROM_BYTE_COUNT - 1 = 4095
// Right: DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE = 4095 - 568 + 1 = 3528
// Left:  DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE = 4095 - 552 + 1 = 3544
```

### Right Half EEPROM Address Map (Complete)

```
Byte Range    Size    Region                          Source
----------    ----    -----                           ------
0-35          36      eeconfig (eeprom_core_t)        eeconfig.h
  0-1           2       magic
  2             1       debug
  3             1       default_layer
  4-5           2       keymap
  6             1       backlight
  7             1       audio
  8-11          4       rgblight
  12            1       unicode
  13            1       steno
  14            1       handedness
  15-18         4       keyboard (eeconfig_kb)
  19-22         4       user (eeconfig_user)          <-- layer modes + actuation
  23-30         8       led_matrix/rgb_matrix union
  31-34         4       haptic
  35            1       rgblight_ext
36-38         3       VIA magic (build date BCD)      via.h
39            1       VIA layout options              via.h
40-551        512     Dynamic keymap (4L x 8R x 8C)   dynamic_keymap.c
  40-167        128     Layer 0
  168-295       128     Layer 1
  296-423       128     Layer 2
  424-551       128     Layer 3
552-567       16      Encoder map (1E x 4L x 2D x 2) dynamic_keymap.c
568-4095      3528    Dynamic macros                  dynamic_keymap.c
----------    ----
TOTAL         4096    (= WEAR_LEVELING_LOGICAL_SIZE)
```

### Left Half EEPROM Address Map (Complete)

```
Byte Range    Size    Region                          Source
----------    ----    -----                           ------
0-35          36      eeconfig (eeprom_core_t)        eeconfig.h
  19-22         4       user (eeconfig_user)          <-- layer modes + actuation
36-38         3       VIA magic (build date BCD)      via.h
39            1       VIA layout options              via.h
40-551        512     Dynamic keymap (4L x 8R x 8C)   dynamic_keymap.c
552-4095      3544    Dynamic macros                  dynamic_keymap.c
----------    ----
TOTAL         4096    (= WEAR_LEVELING_LOGICAL_SIZE)
```

### eeconfig_user Usage in Bipedal Ambi

```c
// Source: keymaps/vial_left/keymap.c (and vial_right/keymap.c -- identical logic)
// eeconfig_user is a uint32_t at bytes 19-22

void save_layer_config_to_eeprom(void) {
    uint32_t data = 0;
    // Bits 0-7: Layer modes (2 bits per layer, 4 layers)
    for (int i = 0; i < 4; i++) {
        data |= ((uint32_t)layer_modes[i] & 0x03) << (i * 2);
    }
    // Bits 8-10: Global actuation index
    data |= ((uint32_t)current_actuation_index & 0x07) << 8;
    eeconfig_update_user(data);  // writes to bytes 19-22
}
```

### Overlap Verification Script

```python
# Verify no EEPROM region overlaps for the right half
regions = [
    ("eeconfig",        0,   35),
    ("VIA magic",       36,  38),
    ("VIA layout opts", 39,  39),
    ("Dynamic keymap",  40,  551),
    ("Encoder map",     552, 567),
    ("Dynamic macros",  568, 4095),
]

for i in range(len(regions)):
    for j in range(i + 1, len(regions)):
        name_a, start_a, end_a = regions[i]
        name_b, start_b, end_b = regions[j]
        if end_a >= start_b:
            print(f"OVERLAP: {name_a} ({start_a}-{end_a}) overlaps {name_b} ({start_b}-{end_b})")
        else:
            gap = start_b - end_a - 1
            if gap == 0:
                print(f"OK: {name_a} -> {name_b} (adjacent, no gap)")
            else:
                print(f"OK: {name_a} -> {name_b} (gap of {gap} bytes)")

# Verify total fits in 4096
total = regions[-1][2] + 1
print(f"\nTotal: {total} bytes (limit: 4096, {'OK' if total <= 4096 else 'EXCEEDS LIMIT'})")
```

## Detailed Findings

### Finding 1: EECONFIG_BASE_SIZE = 36 bytes (Verified)

The `eeprom_core_t` struct in `quantum/eeconfig.h` is PACKED and totals 36 bytes. The critical fields for this project are:
- `user` at bytes 19-22 (used by both keymaps for layer_modes + actuation_index)
- `keyboard` at bytes 15-18 (not used by Ambi, but exists)

Neither `EECONFIG_KB_DATA_SIZE` nor `EECONFIG_USER_DATA_SIZE` is defined by the Ambi keyboard, so both default to 0. `EECONFIG_SIZE = 36`.

**Confidence:** HIGH -- struct read directly from `quantum/eeconfig.h`, byte offsets computed manually and verified

### Finding 2: eeconfig_user Does NOT Overlap with VIA/Dynamic Keymap

The eeconfig_user region occupies bytes 19-22. The VIA magic region starts at byte 36 (= EECONFIG_SIZE). There is a 13-byte gap between them (bytes 23-35, occupied by the led_matrix/rgb_matrix union, haptic, and rgblight_ext fields). The dynamic keymap starts at byte 40.

**No overlap is possible** because eeconfig_user is inside the eeprom_core_t struct, which ends at byte 35, and all VIA/Vial regions start at byte 36 or later.

**Confidence:** HIGH -- verified by struct layout analysis

### Finding 3: Right Half Total Fixed Usage = 568 bytes (13.9% of 4096)

The right half uses 568 bytes for fixed-size regions (eeconfig through encoder map). The remaining 3528 bytes are available for dynamic macros. This is well within the 4096-byte limit.

**Confidence:** HIGH -- all values traced from source code

### Finding 4: Left Half Total Fixed Usage = 552 bytes (13.5% of 4096)

The left half is 16 bytes smaller because it has no encoder map. The remaining 3544 bytes are available for dynamic macros.

**Confidence:** HIGH -- all values traced from source code

### Finding 5: _Static_assert Passes for Both Halves

The `_Static_assert` in `dynamic_keymap.c` line 123 requires `DYNAMIC_KEYMAP_EEPROM_MAX_ADDR >= DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 100`:
- Right: 4095 >= 568 + 100 = 668 (PASS, 3427 bytes of headroom)
- Left: 4095 >= 552 + 100 = 652 (PASS, 3443 bytes of headroom)

**Confidence:** HIGH -- arithmetic

### Finding 6: TOTAL_EEPROM_BYTE_COUNT = 4096 (RP2040 Default)

The RP2040 uses `EEPROM_WEAR_LEVELING` with:
- `WEAR_LEVELING_BACKING_SIZE = 8192` (from `wear_leveling_rp2040_flash_config.h`)
- `WEAR_LEVELING_LOGICAL_SIZE = BACKING_SIZE / 2 = 4096`
- `TOTAL_EEPROM_BYTE_COUNT = WEAR_LEVELING_LOGICAL_SIZE = 4096`

The Ambi does not override any of these values.

**Confidence:** HIGH -- read directly from platform header

### Finding 7: No Vial-Specific Optional Features Enabled

The following Vial EEPROM-consuming features are NOT enabled by the Bipedal Ambi:

| Feature | Gate | Status | EEPROM Size |
|---------|------|--------|-------------|
| QMK Settings | `QMK_SETTINGS` | Not defined | 0 |
| Tap Dance | `TAP_DANCE_ENABLE` | Not in rules.mk | 0 |
| Combos | `COMBO_ENABLE` | Not in rules.mk | 0 |
| Key Overrides | `KEY_OVERRIDE_ENABLE` | Not in rules.mk | 0 |

If any of these were enabled, they would insert between the encoder map and the macro region. For the Ambi, these regions are all zero-sized, meaning the macro region starts immediately after the encoder map (right) or dynamic keymap (left).

**Confidence:** HIGH -- verified by reading all rules.mk files and finding no feature enables

### Finding 8: Macro Count and Size

`DYNAMIC_KEYMAP_MACRO_COUNT` defaults to 16 (from `dynamic_keymap.h`). The Ambi does not override this. However, macro count only controls the number of macro "slots" -- the actual EEPROM usage is the macro buffer, which fills all remaining space:
- Right: 3528 bytes for macros
- Left: 3544 bytes for macros

Both are far more than enough for 16 macros (typical macro is 10-50 bytes).

**Confidence:** HIGH -- read from `dynamic_keymap.h` line 30

## Validation Procedures

### Validation 1: Compile-Time Address Verification

The planner can add a task to insert temporary `#pragma message` directives in `dynamic_keymap.c` to print calculated addresses during compilation. However, this is optional since all values are deterministic from the source.

```c
// Temporary verification (remove after Phase 5)
#pragma message "EECONFIG_SIZE = " STR(EECONFIG_SIZE)
#pragma message "VIA_EEPROM_CONFIG_END = " STR(VIA_EEPROM_CONFIG_END)
#pragma message "DYNAMIC_KEYMAP_EEPROM_ADDR = " STR(DYNAMIC_KEYMAP_EEPROM_ADDR)
#pragma message "VIAL_ENCODERS_EEPROM_ADDR = " STR(VIAL_ENCODERS_EEPROM_ADDR)
#pragma message "DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR = " STR(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR)
#pragma message "DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE = " STR(DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE)
```

### Validation 2: Python Cross-Check

The code example "Overlap Verification Script" above can be run to programmatically verify no overlaps exist between any pair of regions.

### Validation 3: eeconfig_user Non-Overlap Confirmation

Verify that `offsetof(eeprom_core_t, user) + sizeof(uint32_t) <= VIA_EEPROM_MAGIC_ADDR`:
- `19 + 4 = 23 <= 36` -- CONFIRMED, no overlap

## State of the Art

| Old Approach | Current Approach | When Changed | Impact |
|--------------|------------------|--------------|--------|
| Upstream QMK EEPROM chain (keymap -> macro) | Vial-fork chain (keymap -> encoders -> QMK settings -> tap dance -> combos -> key overrides -> macro) | vial-qmk fork inception | More regions between keymap and macros; must use vial-qmk source, not upstream docs |
| `eeconfig` as flat byte offsets (#define EECONFIG_USER 14) | `eeprom_core_t` PACKED struct with `offsetof()` | Recent QMK refactor | Exact offsets depend on struct layout, not hardcoded values |
| Fixed EEPROM on AVR chips | Wear-leveling emulated EEPROM on RP2040 | RP2040 platform support | `TOTAL_EEPROM_BYTE_COUNT = WEAR_LEVELING_LOGICAL_SIZE = 4096` (not physical EEPROM size) |

**Deprecated/outdated:**
- The prior research estimate of "~30 bytes" for EECONFIG_SIZE was approximate. The verified value is 36 bytes.
- The prior estimate of "~686 bytes total" (PITFALLS.md) was approximate and included a "~128 bytes" macro estimate. Actual fixed regions total 568 bytes (right) or 552 bytes (left), with macros filling the remainder.

## Open Questions

1. **Whether the compile-time verification (pragma messages) should be a required task or optional**
   - What we know: All addresses are deterministic from source code constants. The calculation in this research was verified by manual tracing.
   - What's unclear: Whether the planner should include a build-based verification task, or whether the source-code-only calculation satisfies EEPR-04 and XVAL-02.
   - Recommendation: The source-code trace satisfies the requirements. A compile-time check is a nice-to-have but not essential. If included, it should be a lightweight verification task, not a separate plan.

2. **Whether EECONFIG_BASE_SIZE could differ if QMK's eeprom_core_t struct changes**
   - What we know: The struct is in `quantum/eeconfig.h` and the vial-qmk fork is pinned to a specific version.
   - What's unclear: If the fork merges upstream changes, the struct could grow.
   - Recommendation: Document the current value (36 bytes) with a note that it comes from the struct definition. Future changes to the struct would change EECONFIG_SIZE and shift all downstream addresses.

## Sources

### Primary (HIGH confidence)
- `quantum/eeconfig.h` -- eeprom_core_t struct (36 bytes), EECONFIG_SIZE formula (direct read, 2026-02-14)
- `quantum/via.h` -- VIA magic, layout options, custom config, VIA_EEPROM_CONFIG_END (direct read, 2026-02-14)
- `quantum/dynamic_keymap.c` -- complete EEPROM address chain: keymap, encoders, QMK settings, tap dance, combos, key overrides, macros (direct read, 2026-02-14)
- `quantum/dynamic_keymap.h` -- DYNAMIC_KEYMAP_LAYER_COUNT=4, DYNAMIC_KEYMAP_MACRO_COUNT=16 defaults (direct read, 2026-02-14)
- `quantum/vial.h` -- Vial feature entry counts and struct sizes (direct read, 2026-02-14)
- `platforms/chibios/drivers/wear_leveling/wear_leveling_rp2040_flash_config.h` -- BACKING_SIZE=8192, LOGICAL_SIZE=4096 (direct read, 2026-02-14)
- `platforms/eeprom.h` -- TOTAL_EEPROM_BYTE_COUNT = WEAR_LEVELING_LOGICAL_SIZE (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/config.h` -- MATRIX_ROWS=8, MATRIX_COLS=8 (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/config.h` -- DYNAMIC_KEYMAP_LAYER_COUNT=4 (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/config.h` -- DYNAMIC_KEYMAP_LAYER_COUNT=4, NUM_ENCODERS=1 (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/rules.mk` -- ENCODER_MAP_ENABLE commented out (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/rules.mk` -- ENCODER_ENABLE=yes, ENCODER_MAP_ENABLE=yes (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/keymap.c` -- eeconfig_user bit layout (direct read, 2026-02-14)

### Secondary (MEDIUM confidence)
- `.planning/phases/01-reference-analysis/REFERENCE-ANALYSIS.md` -- Prior EEPROM layer offset analysis (Phase 1 deliverable)
- `.planning/research/PITFALLS.md` -- Prior approximate EEPROM budget (Phase 0 research)
- `.planning/research/ARCHITECTURE.md` -- Prior EEPROM region documentation (Phase 0 research)

### Tertiary (LOW confidence)
- None -- all findings verified from source code

## Metadata

**Confidence breakdown:**
- EECONFIG_SIZE (36 bytes): HIGH -- struct read directly, byte offsets calculated field by field
- VIA header addresses: HIGH -- constants read from via.h, no conditionals
- Dynamic keymap addresses: HIGH -- formula from dynamic_keymap.c with known constants
- Encoder EEPROM size: HIGH -- NUM_ENCODERS=1 verified in config.h (Phase 4 fix)
- eeconfig_user non-overlap: HIGH -- offset 19-22 vs VIA start at 36, gap of 13 bytes
- Total fits in 4096: HIGH -- 568 << 4096, arithmetic verified
- Left vs right half differences: HIGH -- rules.mk files read directly

**Research date:** 2026-02-14
**Valid until:** Indefinite (all values from static source code in vial-qmk fork)
