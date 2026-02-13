# Architecture: QMK/Vial EEPROM Layout for Split Keyboards on RP2040

**Domain:** QMK Firmware EEPROM Architecture (Vial-enabled Split Keyboard)
**Researched:** 2026-02-13
**Confidence:** MEDIUM -- based on web research of QMK/Vial source, verified against local keyboard source code; unable to directly read QMK core source files during this session

## Critical Discovery: Matrix Dimension Mismatch

The Bipedal Ambi has a **config.h vs vial.json matrix dimension disagreement** that is the likely root cause of the layer offset bug.

| Source | MATRIX_ROWS | MATRIX_COLS | Notes |
|--------|-------------|-------------|-------|
| `config.h` (keyboard level) | **8** | **8** | "4 rows per hand x 2 hands" |
| `vial.json` (both sides) | **4** | **8** | Per-side matrix |
| `info.json` | 4 rows defined | 8 cols defined | Left-side pin definitions |

**The firmware compiles with MATRIX_ROWS=8, MATRIX_COLS=8 (the full split matrix), but Vial thinks the matrix is 4x8 (one side only).** This means:

- Firmware allocates EEPROM for `8 * 8 * 4 layers * 2 bytes = 512 bytes` of keymap
- Vial GUI addresses only `4 * 8 * 4 layers * 2 bytes = 256 bytes` of keymap
- **Layer N in Vial's view maps to a different EEPROM offset than Layer N in firmware's view**

This is the layer offset bug.

## EEPROM Memory Map (Complete)

The EEPROM layout is a contiguous chain of regions. Each region's start address depends on the size of all preceding regions.

### Region 1: eeconfig (QMK Core Settings)

Bytes 0 through EECONFIG_SIZE-1. Based on QMK source analysis, the eeconfig block is a packed struct (`nvm_eeconfig_t`) containing:

```
Offset  Size    Field                   Notes
------  ------  ----------------------  ---------------------------
0x00    2       magic (uint16_t)        0xFEEA = valid config
0x02    1       debug (uint8_t)         Debug flags
0x03    1       default_layer (uint8_t) Default layer
0x04    2       keymap (uint16_t)       Keymap config flags
0x06    1       backlight (uint8_t)     Backlight level
0x07    1       audio (uint8_t)         Audio config
0x08    4       rgblight (uint32_t)     RGB config (HSV + mode)
0x0C    1       unicode (uint8_t)       Unicode mode
0x0D    1       steno (uint8_t)         Steno mode
0x0E    1       handedness (uint8_t)    Split side (0xFF=left,0x00=right)
0x0F    4       keyboard (uint32_t)     eeconfig_kb data (DWORD)
0x13    4       user (uint32_t)         eeconfig_user data (DWORD)  <-- YOUR DATA
0x17    4       rgb_matrix (uint32_t)   RGB matrix config
0x1B    4       led_matrix (uint32_t)   LED matrix config
0x1F    4       haptic (uint32_t)       Haptic feedback
0x23    1       velocikey (uint8_t)     Velocikey speed
  ...   ...     (kb_data, user_data)    Variable size if EECONFIG_KB/USER_DATA_SIZE > 0
```

**EECONFIG_SIZE is approximately 0x24-0x30 (36-48 bytes)** depending on enabled features and QMK version. The exact value in vial-qmk's `vial` branch needs verification by reading `quantum/eeconfig.h`.

**Confidence: MEDIUM** -- the byte layout comes from training data and older QMK source. Modern QMK may have rearranged this into a packed struct via `nvm_eeconfig_t`. The exact EECONFIG_SIZE value determines all downstream addresses.

### Region 2: VIA Header

Immediately after eeconfig:

```
Offset                  Size    Field
----------------------  ------  ----------------------------
EECONFIG_SIZE + 0       3       VIA magic (BCD build date YYMMDD)
EECONFIG_SIZE + 3       1-4     Layout options (VIA_EEPROM_LAYOUT_OPTIONS_SIZE, default 1)
EECONFIG_SIZE + 4       0       Custom config (VIA_EEPROM_CUSTOM_CONFIG_SIZE, default 0)
```

The address chain:

```c
#define VIA_EEPROM_MAGIC_ADDR           (EECONFIG_SIZE)
#define VIA_EEPROM_LAYOUT_OPTIONS_ADDR  (VIA_EEPROM_MAGIC_ADDR + 3)
#define VIA_EEPROM_CUSTOM_CONFIG_ADDR   (VIA_EEPROM_LAYOUT_OPTIONS_ADDR + VIA_EEPROM_LAYOUT_OPTIONS_SIZE)
```

**Confidence: HIGH** -- confirmed across multiple sources including VIA docs and QMK via.h references.

### Region 3: Dynamic Keymap (THE CRITICAL REGION)

```c
#define DYNAMIC_KEYMAP_EEPROM_ADDR  (VIA_EEPROM_CUSTOM_CONFIG_ADDR + VIA_EEPROM_CUSTOM_CONFIG_SIZE)
```

**Size formula:**

```
keymap_size = DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2 bytes
```

For Bipedal Ambi firmware (config.h values):
```
keymap_size = 4 layers * 8 rows * 8 cols * 2 bytes = 512 bytes
```

For Vial GUI's understanding (vial.json values):
```
keymap_size = 4 layers * 4 rows * 8 cols * 2 bytes = 256 bytes
```

**This 2x size mismatch is the root of the layer offset bug.**

Each keycode is stored as a big-endian 16-bit value. The offset formula for a specific key:

```
byte_offset = DYNAMIC_KEYMAP_EEPROM_ADDR
            + (layer * MATRIX_ROWS * MATRIX_COLS * 2)
            + (row * MATRIX_COLS * 2)
            + (col * 2)
```

#### Worked Example: Layer 2, Row 1, Col 3

**Firmware calculation (8x8 matrix):**
```
offset = base + (2 * 8 * 8 * 2) + (1 * 8 * 2) + (3 * 2)
       = base + 256 + 16 + 6
       = base + 278
```

**Vial GUI calculation (4x8 matrix):**
```
offset = base + (2 * 4 * 8 * 2) + (1 * 8 * 2) + (3 * 2)
       = base + 128 + 16 + 6
       = base + 150
```

**Result: Firmware and Vial disagree by 128 bytes for layer 2.** Layer 2 in Vial actually maps to the middle of layer 1 in firmware's view.

**Confidence: HIGH** -- formula confirmed across multiple QMK sources and VIA docs.

### Region 4: Encoder Map (conditional)

Only present when `ENCODER_MAP_ENABLE = yes`:

```c
#define DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR  (DYNAMIC_KEYMAP_EEPROM_ADDR + keymap_size)
```

```
encoder_size = DYNAMIC_KEYMAP_LAYER_COUNT * NUM_ENCODERS * 2 directions * 2 bytes
```

For vial_right (1 encoder):
```
encoder_size = 4 * 1 * 2 * 2 = 16 bytes
```

For vial_left (0 encoders): This region may still be allocated but empty.

### Region 5: Dynamic Macros

```c
#define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR  (end of encoder region, or end of keymap if no encoders)
#define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE  (total EEPROM - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR)
```

Macros fill the remainder of available EEPROM. Default macro count: 16.

### Complete Map Visualization

Assuming EECONFIG_SIZE = 46 (a reasonable estimate for vial-qmk with common features):

```
Byte Offset    Region                          Size (bytes)
-----------    ------------------------------  -----------
0x0000         eeconfig (magic, debug, etc.)    ~46
0x002E         VIA magic (3 bytes)              3
0x0031         Layout options                   1
0x0032         Custom config                    0
0x0032         Dynamic Keymap START             512  (firmware: 8x8x4x2)
               Layer 0: 0x0032 - 0x00B1        128
               Layer 1: 0x00B2 - 0x0131        128
               Layer 2: 0x0132 - 0x01B1        128
               Layer 3: 0x01B2 - 0x0231        128
0x0232         Encoder map (if enabled)         16
0x0242         Macros                           remaining
```

**Confidence: MEDIUM** -- exact EECONFIG_SIZE value unverified; all downstream addresses shift if it differs.

## Data Flow: config.h to EEPROM to Vial Protocol

```
+-------------------+     +-----------------+     +------------------+
| config.h          |     | Compiler        |     | Firmware Binary  |
| MATRIX_ROWS = 8   | --> | Preprocessor    | --> | EEPROM allocator |
| MATRIX_COLS = 8   |     | via.h formulas  |     | uses 8x8 matrix  |
| LAYER_COUNT = 4   |     | eeconfig.h size |     |                  |
+-------------------+     +-----------------+     +------------------+
                                                         |
                                                         v
+-------------------+     +-----------------+     +------------------+
| vial.json         |     | Vial GUI        |     | EEPROM           |
| "rows": 4         | --> | Interprets      | --> | Read/Write via   |
| "cols": 8         |     | matrix as 4x8   |     | HID raw protocol |
+-------------------+     +-----------------+     +------------------+
                                                         |
        MISMATCH! Firmware writes 8x8 offsets            |
        Vial reads/writes 4x8 offsets                    v
                                                  +------------------+
                                                  | CORRUPTION       |
                                                  | Layer N in Vial  |
                                                  | != Layer N in    |
                                                  | firmware          |
                                                  +------------------+
```

### Step-by-step data flow:

1. **Compile time:** `config.h` defines `MATRIX_ROWS=8`, `MATRIX_COLS=8`. The preprocessor calculates `DYNAMIC_KEYMAP_EEPROM_ADDR` and the keymap region size as `8*8*4*2 = 512 bytes`.

2. **First boot:** `dynamic_keymap_reset()` copies the `keymaps[]` array from flash (PROGMEM) into EEPROM at the calculated offsets. The flash keymaps are defined as `keymaps[][MATRIX_ROWS][MATRIX_COLS]` which is `[4][8][8]` -- but the LAYOUT macros only populate 4 rows of actual keys (rows 0-3), leaving rows 4-7 as `KC_NO` (0x0000).

3. **Runtime keycode lookup:** `dynamic_keymap_get_keycode(layer, row, col)` computes `offset = base + layer*8*8*2 + row*8*2 + col*2` and reads 2 bytes from EEPROM.

4. **Vial protocol:** Vial GUI sends raw HID commands to read/write keycodes. The Vial protocol uses `dynamic_keymap_get_buffer()` and `dynamic_keymap_set_buffer()` which operate on raw byte offsets relative to the dynamic keymap start.

5. **The mismatch:** Vial GUI calculates offsets using its vial.json matrix (4x8). When it requests "layer 2, row 0, col 0" it computes `offset = 2*4*8*2 = 128`. But the firmware's layer 2 starts at `offset = 2*8*8*2 = 256`. Vial is reading the middle of firmware's layer 1.

## The eeconfig_user Interaction

The keyboard uses `eeconfig_read_user()` and `eeconfig_update_user()` to store:

```c
// Bits 0-7: Layer modes (2 bits per layer * 4 layers = 8 bits)
// Bits 8-10: Global actuation index (3 bits)
// Total: 11 bits used of 32 available
```

This is stored at the **eeconfig_user** field (approximately offset 0x13, size 4 bytes). This is **well before** the VIA/dynamic keymap region and **does not overlap** with it. The eeconfig_user data is safe from the matrix dimension mismatch.

**However:** if `eeconfig_init()` is called (e.g., by VIA magic mismatch or EE_CLR), it resets eeconfig_user to 0, wiping the joystick actuation and scroll direction settings. The `eeconfig_init_user()` callback should be implemented to set sane defaults.

**Confidence: HIGH** -- verified directly from keyboard source code.

## Critical Architecture Issue: This Is NOT a Normal Split Keyboard

### Normal QMK Split Keyboard Architecture:

In a standard QMK split keyboard, MATRIX_ROWS is doubled (e.g., 4 physical rows x 2 halves = 8 rows in config.h). **Both halves share one firmware binary.** The split transport layer handles remapping the "other half" rows into the upper half of the matrix. The vial.json describes the **full** matrix (8 rows x N cols) and both halves' keys are in one layout.

### Bipedal Ambi Architecture:

The Bipedal Ambi uses **separate firmware per side** (vial_left and vial_right keymaps). Each side:
- Includes `config.h` which sets `MATRIX_ROWS=8, MATRIX_COLS=8` (the full split matrix)
- But each vial.json declares `"rows": 4, "cols": 8` (only its own side)
- Each side's LAYOUT macro only populates rows 0-3

**The fundamental problem:** `MATRIX_ROWS=8` tells the firmware to allocate EEPROM for 8 rows per layer, but each side only uses 4 rows. The Vial GUI's vial.json correctly describes the physical reality (4 rows per side), but this disagrees with the EEPROM allocation.

### The Fix Decision

There are two approaches:

**Option A: Change vial.json to match config.h (rows: 8, cols: 8)**
- Vial will show 8 rows, half of which are empty/unused
- EEPROM offsets will be consistent
- Wasteful but correct
- The Vial GUI will look odd with blank rows

**Option B: Change config.h to match vial.json (MATRIX_ROWS 4)**
- Since each side compiles separately, each side only needs 4 rows
- EEPROM is compact and correctly sized
- info.json matrix_pins already only defines 4 rows
- This is the architecturally correct fix
- **Risk:** Must verify that SERIAL_USART split transport still works correctly with MATRIX_ROWS=4 on each side, since it normally expects the doubled value

**Recommendation: Option B** -- Set `MATRIX_ROWS 4` in config.h since each side compiles its own firmware. The doubled-rows convention is for single-binary split keyboards. With per-side firmware, the matrix dimensions should reflect the physical matrix of that side only.

**Confidence: MEDIUM** -- the recommendation is architecturally sound but needs verification that the split serial transport does not depend on MATRIX_ROWS being doubled when SPLIT_USB_DETECT is used.

## RP2040 EEPROM Implementation Details

The RP2040 has no hardware EEPROM. QMK uses **wear-leveling flash emulation**:

- Storage: Last sector(s) of the RP2040's XIP flash
- Default logical EEPROM size: 4096 bytes (4 KB)
- Wear-leveling backing size: typically 2x-4x the logical size
- RAM usage: equal to logical EEPROM size (4096 bytes of RAM)
- Write endurance: managed by wear-leveling algorithm

With 4096 bytes available and ~50 bytes for eeconfig + ~4 bytes for VIA header:
- At 8x8x4 matrix: 512 bytes for keymaps, leaving ~3530 bytes for macros
- At 4x8x4 matrix: 256 bytes for keymaps, leaving ~3786 bytes for macros

Neither is close to the limit. The EEPROM size is not a constraint.

**Confidence: MEDIUM** -- RP2040 wear-leveling EEPROM is well-documented in QMK; exact default size may vary by QMK version.

## Component Boundaries

```
+--------------------------+
| Vial GUI (Desktop App)   |  <-- Uses vial.json matrix dimensions
|   matrix: {rows:4,cols:8}|
+-----------+--------------+
            | HID Raw Reports (32 bytes)
            v
+-----------+--------------+
| Vial Protocol Handler    |  <-- quantum/via.c, routes to dynamic_keymap
| (via_receive / via_send) |
+-----------+--------------+
            |
            v
+-----------+--------------+
| Dynamic Keymap API       |  <-- Uses MATRIX_ROWS/MATRIX_COLS from config.h
| dynamic_keymap_get_keycode|     via compile-time calculation
| dynamic_keymap_set_keycode|
+-----------+--------------+
            |
            v
+-----------+--------------+
| NVM / EEPROM Abstraction |  <-- nvm_dynamic_keymap_read/write
| (Wear-leveling on RP2040)|
+-----------+--------------+
            |
            v
+-----------+--------------+
| Flash Memory             |  <-- Physical storage
| (Last sectors of XIP)    |
+--------------------------+
```

## Patterns to Follow

### Pattern 1: Single Source of Truth for Matrix Dimensions

All three config sources must agree on matrix dimensions:

| File | Must Match | Purpose |
|------|-----------|---------|
| `config.h` MATRIX_ROWS/COLS | Compile-time EEPROM layout | Firmware byte offset calculation |
| `vial.json` matrix.rows/cols | Vial GUI EEPROM addressing | GUI byte offset calculation |
| `info.json` matrix_pins count | Physical pin assignment | Hardware reality |
| LAYOUT macro dimensions | Key position mapping | Which keys exist |

**Rule:** If you change one, change all of them.

### Pattern 2: eeconfig_user Must Have init Defaults

```c
void eeconfig_init_user(void) {
    uint32_t default_data = 0;
    // Set default modes to MODE_MOUSE (0x00 for all layers)
    // Set default actuation index to 2 (middle)
    default_data |= (2 << 8);  // actuation index = 2
    eeconfig_update_user(default_data);
}
```

Without this, EE_CLR or VIA magic reset will leave eeconfig_user as all zeros, which happens to map to MODE_MOUSE and actuation_index=0 (lowest sensitivity). The code already handles this gracefully because MODE_MOUSE is 0, but the actuation default of 0 maps to actuation_values[0] = 352 (highest), not the intended default of 256 (index 2).

### Pattern 3: Verify with dynamic_keymap_get_keycode Debug

To diagnose the layer offset bug, add temporary debug logging:

```c
// In matrix_scan_user or process_record_user:
uint16_t kc = dynamic_keymap_get_keycode(0, 0, 0);  // Should be KC_ESC on left
dprintf("L0R0C0 = 0x%04X\n", kc);
uint16_t kc2 = dynamic_keymap_get_keycode(1, 0, 0);  // Should be KC_TRNS on left
dprintf("L1R0C0 = 0x%04X\n", kc2);
```

## Anti-Patterns to Avoid

### Anti-Pattern 1: Doubled MATRIX_ROWS for Per-Side Firmware

**What:** Setting `MATRIX_ROWS = 8` (4 per side x 2) when each side compiles its own firmware.
**Why bad:** Wastes EEPROM, creates offset mismatch with Vial GUI, causes layer corruption.
**Instead:** Use `MATRIX_ROWS = 4` for per-side firmware builds.

### Anti-Pattern 2: Trusting Vial GUI Layer Display Without Verification

**What:** Assuming what Vial shows matches what firmware uses.
**Why bad:** If matrix dimensions disagree, Vial reads/writes wrong EEPROM addresses silently.
**Instead:** Use console debug output to verify `dynamic_keymap_get_keycode()` returns expected values.

### Anti-Pattern 3: Using eeconfig_user Without eeconfig_init_user

**What:** Calling `eeconfig_update_user()` to persist settings but not implementing `eeconfig_init_user()`.
**Why bad:** EEPROM reset events (EE_CLR, magic mismatch) will wipe user data with no recovery to sane defaults.
**Instead:** Always implement `eeconfig_init_user()` with known-good defaults.

## Diagnostic Priority Order

Based on this architecture analysis, the recommended diagnostic sequence is:

1. **Verify the mismatch exists** -- check if `MATRIX_ROWS` in compiled firmware disagrees with `vial.json` matrix.rows
2. **Read EEPROM directly** -- use `dynamic_keymap_get_keycode(layer, row, col)` with debug printf to see what firmware actually reads for each layer
3. **Compare with Vial's view** -- note what Vial shows for the same layer/row/col and compare
4. **Fix matrix dimensions** -- change `MATRIX_ROWS` to 4 in config.h (or change vial.json rows to 8)
5. **Clear EEPROM** -- after fixing dimensions, use EE_CLR to force a clean EEPROM reset
6. **Add eeconfig_init_user** -- ensure custom settings survive EEPROM resets

## Sources

- [QMK EEPROM Documentation](https://docs.qmk.fm/feature_eeprom)
- [QMK EEPROM Driver Configuration](https://docs.qmk.fm/drivers/eeprom)
- [QMK Split Keyboard Documentation](https://docs.qmk.fm/features/split_keyboard)
- [VIA Configuring QMK](https://caniusevia.com/docs/configuring_qmk/)
- [QMK dynamic_keymap.c](https://github.com/qmk/qmk_firmware/blob/master/quantum/dynamic_keymap.c)
- [QMK dynamic_keymap.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/dynamic_keymap.h)
- [QMK via.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/via.h)
- [QMK via.c](https://github.com/qmk/qmk_firmware/blob/master/quantum/via.c)
- [QMK eeconfig.h](https://github.com/qmk/qmk_firmware/blob/master/quantum/eeconfig.h)
- [Vial-QMK DeepWiki](https://deepwiki.com/vial-kb/vial-qmk/5-features-and-customization)
- [Vial Porting Guide](https://get.vial.today/docs/porting-to-vial.html)
- [Vial Firmware Size Guide](https://get.vial.today/docs/firmware-size.html)
- Local source: `/Users/matthewthomas/dev/vial-qmk/keyboards/hidpress/bipedalambi/` (all config.h, vial.json, keymap.c files read directly)
