# Phase 1: Reference Analysis - Research

**Researched:** 2026-02-13
**Domain:** QMK/Vial split keyboard matrix conventions -- Sofle rev1 Vial as known-working reference
**Confidence:** HIGH

<user_constraints>
## User Constraints (from CONTEXT.md)

### Locked Decisions
- Layer 0 = full keymap, layers 1-3 = KC_TRNS except specific overrides (standard QMK pattern)
- 4 layers required (DYNAMIC_KEYMAP_LAYER_COUNT=4)
- Both layer mapping AND persistence are equally important to verify
- Both halves must show up correctly in Vial independently (each half is configured separately via USB)
- Each half builds and flashes separately: `make hidpress/bipedalambi:vial_left` and `:vial_right`
- Each half has its own vial.json: `keymaps/vial_left/vial.json` and `keymaps/vial_right/vial.json`
- When plugged into USB, Vial only shows keys for the connected half (not full keyboard)
- Either half can be USB master -- no fixed master side
- This means the MATRIX_ROWS doubling convention may work differently than single-binary split boards -- the reference analysis must determine whether each independent half should use doubled rows or per-side rows
- Written fresh using Sofle rev1 Vial keymap AND the Bipedal Southpaw macropad as dual references
- Matrix dimensions between Sofle and Ambi are not known to match -- need side-by-side comparison
- Key count difference unknown -- need to count
- Sofle Vial config is assumed working (from upstream vial-qmk repo) but not personally tested
- The reference analysis should extract the specific conventions Sofle uses, not blindly copy its values
- **DO NOT break**: OLED display, layer state display, actuation level system, actuation value display, screensaver animation, joystick modes, encoder functionality
- These features are existing and working -- the fix must preserve them, not modify them
- Any vial.json changes must maintain existing thumbstick and encoder matrix positions

### Claude's Discretion
- How to structure the reference comparison document (table, narrative, etc.)
- Which specific Sofle files to prioritize reading
- Level of detail in the "what Ambi must also do" checklist

### Deferred Ideas (OUT OF SCOPE)
None -- discussion stayed within phase scope
</user_constraints>

## Summary

The Sofle rev1 Vial keymap in the upstream vial-qmk repository provides a definitive reference for how split keyboard matrix conventions work with Vial. The Sofle has 5 physical row pins per side and 6 column pins. Its `vial.json` declares `"rows": 10, "cols": 6` -- the full doubled matrix (5 rows/hand x 2 hands = 10). The left-half keys use rows 0-4 and the right-half keys use rows 5-9 in the KLE layout positions. This is the standard QMK split keyboard convention, and it matches the firmware's compiled `MATRIX_ROWS` value which QMK derives from the keyboard.json `matrix_pins` (5 pins x 2 for split = 10).

The critical finding for the Bipedal Ambi is that **MATRIX_ROWS=8 in config.h is correct and must NOT be changed**. QMK's matrix scanning code explicitly defines `ROWS_PER_HAND = MATRIX_ROWS / 2` when `SPLIT_KEYBOARD` is defined (verified in `quantum/matrix.c:29`). With MATRIX_ROWS=8, each side scans exactly 4 physical rows -- matching the 4 row pins defined. The fix must change both vial.json files from `"rows": 4` to `"rows": 8` to match, and update the right-side vial.json layout positions from rows 0-3 to rows 4-7.

An additional finding about the Ambi's encoder: the right-side vial.json uses an `"encoders"` key (a Vial-specific JSON structure) while the Sofle uses only the KLE `\n\n\n\n\n\n\n\n\ne` notation without any `"encoders"` key. Both approaches are valid for Vial. The Ambi's encoder positions in vial.json (using row 0 col 0 and row 0 col 1 in the KLE) are display-only references for the GUI -- the actual encoder actions are controlled by the `encoder_map` in keymap.c and overridden by Vial's encoder EEPROM region. These encoder display positions do NOT need row-number adjustment because they are separate from the matrix key positions.

**Primary recommendation:** Change both vial.json files to `"rows": 8, "cols": 8`. Update right-side vial.json layout positions to use rows 4-7 instead of rows 0-3 for regular keys. Keep left-side layout positions at rows 0-3. Do NOT change the thumbstick positions (col 7, rows 0-3 on left) or encoder display positions.

## Standard Stack

This phase is a documentation/analysis phase, not a coding phase. No libraries are installed. The relevant "stack" is the set of files that must be read and compared.

### Core Reference Files (Sofle rev1 Vial)
| File | Location | Purpose | Trust Level |
|------|----------|---------|-------------|
| keyboard.json | `keyboards/sofle/rev1/keyboard.json` | Physical matrix pins (5 rows x 6 cols per side) | HIGH -- upstream vial-qmk |
| vial.json | `keyboards/sofle/rev1/keymaps/vial/vial.json` | Vial matrix declaration (`rows: 10, cols: 6`) and KLE layout | HIGH -- upstream vial-qmk |
| config.h | `keyboards/sofle/rev1/keymaps/vial/config.h` | VIAL_KEYBOARD_UID, unlock combos (rows 0,5,3,8) | HIGH -- upstream vial-qmk |
| keymap.c | `keyboards/sofle/rev1/keymaps/vial/keymap.c` | `keymaps[][MATRIX_ROWS][MATRIX_COLS]`, encoder_map (2 encoders) | HIGH -- upstream vial-qmk |
| rules.mk | `keyboards/sofle/rev1/keymaps/vial/rules.mk` | ENCODER_MAP_ENABLE=yes, VIA_ENABLE=yes, VIAL_ENABLE=yes | HIGH -- upstream vial-qmk |

### Core Target Files (Bipedal Ambi)
| File | Location | Purpose | Current State |
|------|----------|---------|---------------|
| config.h | `keyboards/hidpress/bipedalambi/config.h` | MATRIX_ROWS=8, MATRIX_COLS=8 | Correct -- do not change |
| info.json | `keyboards/hidpress/bipedalambi/info.json` | `"split": {"enabled": true}`, 4 row pins, 8 col pins | Correct |
| vial.json (left) | `keymaps/vial_left/vial.json` | `"rows": 4, "cols": 8` | **WRONG -- must be rows: 8** |
| vial.json (right) | `keymaps/vial_right/vial.json` | `"rows": 4, "cols": 8`, layout rows 0-3 | **WRONG -- must be rows: 8, layout rows 4-7** |

### Validation Reference (Bipedal Southpaw)
| File | Location | Purpose | Status |
|------|----------|---------|--------|
| config.h | `keyboards/hidpress/bipedalsouthpaw/config.h` | MATRIX_ROWS=4, MATRIX_COLS=7 | Known-good (not split) |
| vial.json | `keymaps/vial/vial.json` | `"rows": 4, "cols": 7` | Known-good (rows match MATRIX_ROWS) |

## Architecture Patterns

### Pattern 1: Split Keyboard Row Doubling Convention

**What:** In QMK split keyboards, `MATRIX_ROWS` is always doubled: physical rows per hand x 2. The firmware scans `ROWS_PER_HAND = MATRIX_ROWS / 2` physical pins. The left half populates rows 0 to (ROWS_PER_HAND-1), and the right half populates rows ROWS_PER_HAND to (MATRIX_ROWS-1).

**Verified from:** `quantum/matrix.c:29` and `quantum/matrix_common.c:12`:
```c
#ifdef SPLIT_KEYBOARD
#    define ROWS_PER_HAND (MATRIX_ROWS / 2)
#else
#    define ROWS_PER_HAND (MATRIX_ROWS)
#endif
```

And from `quantum/matrix.c:299`:
```c
thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
thatHand = ROWS_PER_HAND - thisHand;
```

**Sofle demonstrates this pattern:**
| Property | Value | Derivation |
|----------|-------|------------|
| Physical row pins per side | 5 | `keyboard.json` matrix_pins.rows |
| MATRIX_ROWS (compiled) | 10 | 5 x 2 (split doubling) |
| vial.json rows | 10 | Matches MATRIX_ROWS |
| Left-half layout rows | 0-4 | Rows 0 to (ROWS_PER_HAND - 1) |
| Right-half layout rows | 5-9 | Rows ROWS_PER_HAND to (MATRIX_ROWS - 1) |

**Ambi must follow the same pattern:**
| Property | Current Value | Correct Value | Change Needed |
|----------|--------------|---------------|---------------|
| Physical row pins per side | 4 | 4 | None |
| MATRIX_ROWS (config.h) | 8 | 8 | None |
| vial.json rows (both) | 4 | **8** | **YES** |
| Left-half layout rows | 0-3 | 0-3 | None |
| Right-half layout rows | 0-3 | **4-7** | **YES** |

### Pattern 2: vial.json Matrix Must Match Firmware MATRIX_ROWS Exactly

**What:** The Vial GUI reads `vial.json` matrix dimensions to calculate EEPROM byte offsets for each layer. The firmware uses `MATRIX_ROWS` from config.h for the same calculation. If these disagree, every layer after layer 0 is addressed at a different offset.

**Verified from:** Vial porting documentation: "enter the number of rows your keyboard has, this value should match MATRIX_ROWS you have in config.h"

**Verified from firmware source** (`quantum/dynamic_keymap.c:141`):
```c
void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column) {
    return ((void *)DYNAMIC_KEYMAP_EEPROM_ADDR)
        + (layer * MATRIX_ROWS * MATRIX_COLS * 2)
        + (row * MATRIX_COLS * 2)
        + (column * 2);
}
```

**Layer size calculation:**
| Source | Formula | Ambi (current) | Ambi (fixed) |
|--------|---------|----------------|--------------|
| Firmware | `MATRIX_ROWS * MATRIX_COLS * 2` | `8 * 8 * 2 = 128` bytes/layer | 128 bytes/layer |
| Vial GUI | `vial.json.rows * vial.json.cols * 2` | `4 * 8 * 2 = 64` bytes/layer | `8 * 8 * 2 = 128` bytes/layer |
| Agreement? | Must match | **NO (128 vs 64)** | **YES (128 = 128)** |

### Pattern 3: VIAL_UNLOCK_COMBO Uses Doubled Row Numbers

**What:** The `VIAL_UNLOCK_COMBO_ROWS` macro references the full doubled-matrix row numbers.

**Sofle demonstrates:**
```c
#define VIAL_UNLOCK_COMBO_ROWS { 0, 5, 3, 8 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0, 0, 0 }
```
- Row 0, Col 0 = left top-left key
- Row 5, Col 0 = right top-right key (row 5 = first row of right half in 10-row matrix)
- Row 3, Col 0 = left bottom-left key
- Row 8, Col 0 = right bottom-right key

**Ambi currently uses:**
```c
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }
```
This references rows 0,0 which are both left-half rows. This is valid but only unlocks from the left half. The convention from Sofle shows unlock combos should span both halves for a standard split. However, since each Ambi half runs independently, the current approach (2 keys on whatever half is connected) is functionally correct. No change needed here.

### Pattern 4: Encoder Representation in vial.json

**What:** There are two ways to define encoders in Vial:

1. **KLE-only (Sofle approach):** Encoders are represented as special keys in the KLE layout with the `\n\n\n\n\n\n\n\n\ne` suffix. The `encoder_map` in keymap.c provides default actions. Vial stores overrides in EEPROM via `ENCODER_MAP_ENABLE`.

2. **KLE + "encoders" key (Ambi approach):** The layout has KLE encoder entries AND a separate `"encoders"` JSON key that specifies default actions per encoder per layer. This is an alternative Vial format.

**Sofle (KLE-only, no "encoders" key):**
```json
{
    "matrix": { "rows": 10, "cols": 6 },
    "layouts": {
        "keymap": [
            ...
            "0,1\n\n\n\n\n\n\n\n\ne",  // encoder 0 CW display
            "1,1\n\n\n\n\n\n\n\n\ne",  // encoder 0 CCW display (not standard but present)
            ...
        ]
    }
    // NO "encoders" key
}
```

**Ambi right (KLE + "encoders" key):**
```json
{
    "matrix": { "rows": 4, "cols": 8 },
    "layouts": {
        "keymap": [
            ...
            "0,0\n\n\n\n\n\n\n\n\ne",  // encoder display CW
            "0,1\n\n\n\n\n\n\n\n\ne",  // encoder display CCW
            ...
        ]
    },
    "encoders": [
        [
            ["QK_KB_2", "QK_KB_1"],  // Layer 0: CCW=QK_KB_2, CW=QK_KB_1
            ["KC_TRNS", "KC_TRNS"],  // Layer 1
            ["KC_TRNS", "KC_TRNS"],  // Layer 2
            ["KC_TRNS", "KC_TRNS"]   // Layer 3
        ]
    ]
}
```

**Key insight:** The encoder KLE display entries (with `\ne` suffix) use a separate numbering system from the matrix key positions. The "row,col" in encoder entries refers to encoder_index and direction (0=CW, 1=CCW), NOT actual matrix rows. These do NOT need to be adjusted when changing vial.json matrix dimensions. The `"encoders"` key also operates independently of matrix dimensions.

### Pattern 5: Independent-Half Firmware Still Uses Full Doubled Matrix

**What:** Even though the Bipedal Ambi builds separate firmware per half, each half still compiles with the full `MATRIX_ROWS=8`. The `SPLIT_KEYBOARD` define causes `ROWS_PER_HAND = MATRIX_ROWS / 2 = 4`, so only 4 physical row pins are scanned. But the EEPROM allocation uses the full `MATRIX_ROWS=8`, meaning each half allocates EEPROM for 8 rows per layer even though only 4 rows have physical keys.

**This is not a bug -- it is how QMK split keyboards work.** The "wasted" rows 4-7 on the left half (or rows 0-3 on the right half) contain KC_NO (0x0000) in EEPROM and are never scanned. The EEPROM cost is 256 extra bytes (4 unused rows x 8 cols x 4 layers x 2 bytes) per half, which is negligible given the 4096-byte wear-leveling allocation.

**Sofle has the same pattern:** Its keymap defines `keymaps[][MATRIX_ROWS][MATRIX_COLS]` which is `[4][10][6]`, but each physical half only scans 5 rows. The other 5 rows per half are KC_NO or populated by the other side's keys.

## Side-by-Side Comparison: Sofle rev1 vs Bipedal Ambi

### Matrix Dimensions

| Property | Sofle rev1 | Ambi LEFT | Ambi RIGHT |
|----------|-----------|-----------|------------|
| Physical row pins | 5 | 4 | 4 |
| Physical col pins | 6 | 8 (7 physical + 1 NO_PIN) | 8 (7 physical + 1 NO_PIN) |
| MATRIX_ROWS (compiled) | 10 (5x2) | 8 (4x2) | 8 (4x2) |
| MATRIX_COLS (compiled) | 6 | 8 | 8 |
| vial.json rows | **10** | **4 (WRONG)** | **4 (WRONG)** |
| vial.json cols | 6 | 8 | 8 |
| Rows match? | YES (10=10) | **NO (8!=4)** | **NO (8!=4)** |
| Cols match? | YES (6=6) | YES (8=8) | YES (8=8) |

### Key Counts

| Property | Sofle rev1 | Ambi LEFT | Ambi RIGHT |
|----------|-----------|-----------|------------|
| Physical keys per side | 30 | 29 | 25 |
| Encoder(s) | 1 per side | 0 (thumbstick instead) | 1 |
| Total positions in layout | 60 keys + 4 encoder refs | 29 keys | 25 keys + 2 encoder refs |
| Col 7 (virtual) used? | No (6 cols only) | Yes (thumbstick directions) | No (NO_PIN) |

### Layout Row Usage

| Half | Sofle | Ambi (current) | Ambi (correct) |
|------|-------|----------------|-----------------|
| Left | Rows 0-4 | Rows 0-3 | Rows 0-3 (no change) |
| Right | Rows 5-9 | Rows 0-3 | **Rows 4-7** |

### Encoder Configuration

| Property | Sofle rev1 Vial | Ambi RIGHT |
|----------|----------------|------------|
| Encoder count (per-side) | 1 left + 1 right | 0 left + 1 right |
| NUM_ENCODERS (compiled) | 2 | 2 (1+1 because split assumed symmetric) |
| ENCODER_MAP_ENABLE | yes | yes |
| encoder_map entries/layer | 2 (both encoders) | 1 (only 1 encoder defined) |
| vial.json "encoders" key | Not present | Present (4 layers, 1 encoder) |
| KLE encoder display | 4 refs (2 per encoder) | 2 refs (1 encoder) |
| Default layer 0 actions | KC_TRNS, KC_TRNS | QK_KB_2 (CCW), QK_KB_1 (CW) |

**Encoder concern for Phase 4:** The Ambi right-side `encoder_map` defines only 1 entry per layer but `NUM_ENCODERS = 2` because QMK's split encoder logic assumes symmetric encoder counts when `ENCODER_A_PINS_RIGHT` is not defined. This may cause a compilation warning or incorrect EEPROM sizing. This is a Phase 4 concern, not Phase 1.

### Thumbstick Matrix Positions (Left Half)

| Direction | Matrix Position | vial.json Reference | Purpose |
|-----------|----------------|--------------------|---------|
| Up | [0, 7] | "0,7" | Configurable in Vial |
| Down | [1, 7] | "1,7" | Configurable in Vial |
| Left | [2, 7] | "2,7" | (shown as separate key in layout) |
| Right | [3, 7] | "3,7" | (shown as separate key in layout) |

These positions use col 7 (the NO_PIN virtual column). The keymap.c reads them via `dynamic_keymap_get_keycode(layer, row, 7)` in `matrix_scan_user()`. After changing vial.json to rows=8, these positions remain valid because they are rows 0-3 (left-half rows) and col 7 is within the 8-column matrix. **No change needed for thumbstick positions.**

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| Matrix dimension cross-reference | Manual byte-counting | Side-by-side table with formula verification | Error-prone arithmetic; a table makes mismatches immediately visible |
| KLE layout row number updates | Manual find-replace | Scripted extraction and comparison | The right-side vial.json has ~25 position entries; manual editing risks missing one |
| EEPROM offset verification | Mental math | Written formula: `base + (layer * ROWS * COLS * 2) + (row * COLS * 2) + (col * 2)` | The mismatch is a 2x factor that is easy to overlook verbally |

**Key insight:** This phase produces a document, not code. The "don't hand-roll" guidance is about ensuring the reference analysis is systematic, not ad-hoc.

## Common Pitfalls

### Pitfall 1: Assuming Independent Halves Don't Need Doubled Rows
**What goes wrong:** Because each Ambi half builds separately and only scans 4 physical rows, it seems logical that vial.json should say rows=4. But the firmware compiles with MATRIX_ROWS=8 (due to split enabled), and the EEPROM allocation uses MATRIX_ROWS=8. The vial.json must match the compiled value.
**Why it happens:** The per-half firmware model is unusual. Most split keyboards use a single binary.
**How to avoid:** Always check the compiled MATRIX_ROWS value (from config.h + split doubling), not the physical pin count.
**Warning signs:** vial.json rows = number of physical row pins (should be 2x that for split).

### Pitfall 2: Changing Right-Half Layout Rows Without Verifying All Positions
**What goes wrong:** When updating right-half vial.json from rows 0-3 to rows 4-7, one or more positions are missed, causing Vial to map some keys to wrong matrix positions.
**Why it happens:** The KLE format in vial.json is dense and hard to parse visually. Positions are embedded in arrays of objects and strings.
**How to avoid:** Extract all positions programmatically, verify all row references are in range 4-7 after the update.
**Warning signs:** Any key on the right half showing wrong behavior in Vial.

### Pitfall 3: Confusing Encoder KLE Positions with Matrix Key Positions
**What goes wrong:** When updating right-half vial.json layout rows from 0-3 to 4-7, the encoder display entries (with `\ne` suffix) are also updated. But encoder KLE entries use a separate numbering (encoder_index, direction), not matrix row/col.
**Why it happens:** Both use "row,col" syntax in the KLE format. Easy to mistake one for the other.
**How to avoid:** Encoder entries are distinguished by the `\n\n\n\n\n\n\n\n\ne` suffix. Leave their row/col values unchanged.
**Warning signs:** Encoder display disappears or shows wrong values in Vial after update.

### Pitfall 4: Not Documenting the Sofle Reference Clearly Enough for Phase 2
**What goes wrong:** Phase 2 (Matrix Dimension Audit) needs specific numbers from the Sofle reference to build a cross-reference table. If Phase 1 documents only conclusions without the raw data, Phase 2 must re-read all the Sofle files.
**Why it happens:** Phase 1 focuses on understanding; Phase 2 focuses on comparison.
**How to avoid:** Include raw values (not just "they match") so Phase 2 can cite them directly.

## Code Examples

### Sofle rev1 vial.json Matrix Declaration
```json
// Source: keyboards/sofle/rev1/keymaps/vial/vial.json
{
    "name": "Sofle",
    "vendorId": "0xFC32",
    "productId": "0x0287",
    "matrix": { "rows": 10, "cols": 6 },
    ...
}
```

### Sofle rev1 vial.json Right-Half Key Position Example
```json
// Source: keyboards/sofle/rev1/keymaps/vial/vial.json (layout section)
// Right-half keys use rows 5-9:
"5,3"   // Right half, physical row 0, col 3
"6,4"   // Right half, physical row 1, col 4
"7,3"   // Right half, physical row 2, col 3
"8,3"   // Right half, physical row 3, col 3
"9,4"   // Right half, physical row 4, col 4
```

### Sofle rev1 VIAL_UNLOCK_COMBO (Uses Doubled Rows)
```c
// Source: keyboards/sofle/rev1/keymaps/vial/config.h
#define VIAL_UNLOCK_COMBO_ROWS { 0, 5, 3, 8 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 0, 0, 0 }
// Row 0 = left first row, Row 5 = right first row (5 rows per hand)
// Row 3 = left fourth row, Row 8 = right fourth row
```

### Sofle rev1 encoder_map (2 Encoders, Standard Split)
```c
// Source: keyboards/sofle/rev1/keymaps/vial/keymap.c
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
// NUM_ENCODERS = 2 (1 left + 1 right)
// Each layer has 2 encoder entries
```

### QMK Split Row Derivation (from source)
```c
// Source: quantum/matrix.c:25-32
#ifdef SPLIT_KEYBOARD
#    define ROWS_PER_HAND (MATRIX_ROWS / 2)
#else
#    define ROWS_PER_HAND (MATRIX_ROWS)
#endif

// Source: quantum/matrix.c:299-300
thisHand = isLeftHand ? 0 : (ROWS_PER_HAND);
thatHand = ROWS_PER_HAND - thisHand;
```

### Dynamic Keymap EEPROM Formula (from source)
```c
// Source: quantum/dynamic_keymap.c:139-141
void *dynamic_keymap_key_to_eeprom_address(uint8_t layer, uint8_t row, uint8_t column) {
    return ((void *)DYNAMIC_KEYMAP_EEPROM_ADDR)
        + (layer * MATRIX_ROWS * MATRIX_COLS * 2)
        + (row * MATRIX_COLS * 2)
        + (column * 2);
}
// Uses compiled MATRIX_ROWS (8 for Ambi), not vial.json rows
```

### Encoder EEPROM Formula (from source)
```c
// Source: quantum/dynamic_keymap.c:71-74
#define VIAL_ENCODERS_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + \
    (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))
#define VIAL_ENCODERS_SIZE (NUM_ENCODERS * DYNAMIC_KEYMAP_LAYER_COUNT * 2 * 2)

// For Ambi right (NUM_ENCODERS=2 due to split assumption):
// VIAL_ENCODERS_SIZE = 2 * 4 * 2 * 2 = 32 bytes
```

## What Sofle Does That Bipedal Ambi Must Also Do -- Checklist

This is the deliverable checklist for subsequent phases, derived from the reference analysis.

### Matrix Dimension Agreement (Phase 2 + Phase 3)
- [ ] `vial.json` matrix.rows MUST equal config.h `MATRIX_ROWS` (Sofle: 10=10; Ambi needs: 8=8)
- [ ] `vial.json` matrix.cols MUST equal config.h `MATRIX_COLS` (Sofle: 6=6; Ambi: 8=8, already correct)
- [ ] Right-half vial.json layout positions MUST use rows `ROWS_PER_HAND` to `MATRIX_ROWS-1` (Sofle: rows 5-9; Ambi needs: rows 4-7)
- [ ] Left-half vial.json layout positions MUST use rows 0 to `ROWS_PER_HAND-1` (Sofle: rows 0-4; Ambi: rows 0-3, already correct)

### Encoder Mapping (Phase 4)
- [ ] `encoder_map` array in keymap.c must have `NUM_ENCODERS` entries per layer (Sofle: 2 entries/layer for 2 encoders; Ambi right currently has 1 entry for what QMK thinks is 2 encoders -- potential issue)
- [ ] Encoder display positions in vial.json KLE layout (with `\ne` suffix) do NOT use matrix row numbers -- they use encoder_index/direction numbering -- so they should NOT be changed when updating matrix row numbers
- [ ] The `"encoders"` key in Ambi right vial.json (Vial-specific format) is independent of matrix dimensions and should NOT need changes for the row fix

### Peripheral Preservation (Phase 3 + Phase 4)
- [ ] Left-half thumbstick positions at rows 0-3, col 7 remain valid after vial.json rows change to 8 (they are within the left-half row range 0-3)
- [ ] Right-half encoder EEPROM region starts after the full dynamic keymap (MATRIX_ROWS * MATRIX_COLS * LAYERS * 2 bytes); changing vial.json rows to match firmware does not change this address since the firmware already uses MATRIX_ROWS=8

### Layer Configuration (Phase 3)
- [ ] DYNAMIC_KEYMAP_LAYER_COUNT = 4 (Sofle: 4; Ambi: 4, already correct)
- [ ] Layer 0 = full keymap; layers 1-3 = KC_TRNS (Sofle: layers 0-1 full, 2-3 overrides; Ambi: layer 0 full, 1-3 KC_TRNS -- both are valid QMK patterns)

### EEPROM After Fix (Phase 7)
- [ ] EEPROM MUST be cleared on BOTH halves after changing vial.json dimensions (old data is addressed with wrong offsets)
- [ ] After EEPROM clear, default keymap from PROGMEM `keymaps[]` is copied to EEPROM by `dynamic_keymap_reset()`
- [ ] Encoder defaults from `encoder_map[]` are copied to EEPROM by the same reset process

## Open Questions

1. **Ambi right-side encoder_map mismatch with NUM_ENCODERS**
   - What we know: QMK defines `NUM_ENCODERS = NUM_ENCODERS_LEFT + NUM_ENCODERS_RIGHT`. For split keyboards without `ENCODERS_PAD_A_RIGHT`, it assumes `NUM_ENCODERS_RIGHT = NUM_ENCODERS_LEFT`. So the Ambi right side computes `NUM_ENCODERS = 1 + 1 = 2`.
   - What's unclear: The `encoder_map` in `keymaps/vial_right/keymap.c` only defines 1 encoder entry per layer (not 2). This may cause a compilation error, a warning, or silent misalignment.
   - Recommendation: Phase 4 must verify this compiles and either fix the encoder_map to have 2 entries per layer or define `NUM_ENCODERS_RIGHT 0` explicitly in the right-side config.h.

2. **Whether vial.json "encoders" key is redundant with ENCODER_MAP_ENABLE**
   - What we know: The Sofle uses ENCODER_MAP_ENABLE without an "encoders" key in vial.json. The Ambi uses both.
   - What's unclear: Whether the "encoders" key provides additional functionality or is just an alternative way to specify defaults.
   - Recommendation: Preserve the existing "encoders" key in the Ambi right vial.json -- it is working and the encoder is described as functional. Do not change what works.

3. **Whether the left-half vial.json needs thumbstick positions documented in rows 0-3 specifically**
   - What we know: The left vial.json currently has positions at (0,7), (1,7), (2,7), (3,7) for thumbstick directions. These are rows 0-3, which is the correct left-half range in an 8-row matrix.
   - What's unclear: Nothing. These are confirmed correct.
   - Recommendation: No action needed. Just preserve during vial.json edits.

## Sources

### Primary (HIGH confidence)
- `quantum/matrix.c:29` -- ROWS_PER_HAND = MATRIX_ROWS / 2 for split keyboards
- `quantum/matrix.c:299` -- thisHand offset calculation
- `quantum/dynamic_keymap.c:71` -- VIAL_ENCODERS_EEPROM_ADDR formula
- `quantum/dynamic_keymap.c:139-141` -- dynamic_keymap_key_to_eeprom_address formula
- `quantum/encoder.h:52-81` -- NUM_ENCODERS calculation for split keyboards
- `keyboards/sofle/rev1/keymaps/vial/vial.json` -- rows: 10, cols: 6 (the reference)
- `keyboards/sofle/rev1/keyboard.json` -- 5 row pins, 6 col pins per side
- `keyboards/sofle/rev1/keymaps/vial/config.h` -- VIAL_UNLOCK_COMBO_ROWS { 0, 5, 3, 8 }
- `keyboards/sofle/rev1/keymaps/vial/keymap.c` -- encoder_map with 2 entries per layer
- `keyboards/sofle/rev1/keymaps/vial/rules.mk` -- ENCODER_MAP_ENABLE=yes
- `keyboards/hidpress/bipedalambi/config.h` -- MATRIX_ROWS=8, MATRIX_COLS=8
- `keyboards/hidpress/bipedalambi/info.json` -- split enabled, 4 row pins
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/vial.json` -- rows: 4 (wrong)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json` -- rows: 4 (wrong)
- `keyboards/hidpress/bipedalsouthpaw/config.h` -- MATRIX_ROWS=4 matching vial.json rows: 4

### Secondary (MEDIUM confidence)
- Vial porting documentation (https://get.vial.today/docs/porting-to-via.html) -- "rows should match MATRIX_ROWS"
- Vial encoder documentation (https://get.vial.today/docs/encoders.html) -- encoder KLE format
- Lily58 rev1 vial.json -- rows: 10 for 5-pin split (confirms pattern)

### Tertiary (LOW confidence)
- None

## Metadata

**Confidence breakdown:**
- Matrix convention (rows doubling): HIGH -- verified directly from vial-qmk source code (matrix.c, dynamic_keymap.c)
- Sofle reference data: HIGH -- read directly from upstream vial-qmk repo files
- Ambi current state: HIGH -- read directly from project source files
- Encoder handling: MEDIUM -- the interaction between "encoders" key and ENCODER_MAP_ENABLE needs Phase 4 verification
- Fix direction (vial.json rows: 8): HIGH -- confirmed by Sofle pattern + QMK source + Vial docs

**Research date:** 2026-02-13
**Valid until:** Indefinite (QMK split keyboard conventions are stable; vial-qmk fork is mature)
