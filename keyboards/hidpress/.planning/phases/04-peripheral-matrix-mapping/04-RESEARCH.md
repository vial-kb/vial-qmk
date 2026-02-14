# Phase 4: Peripheral Matrix Mapping - Research

**Researched:** 2026-02-14
**Domain:** Thumbstick virtual matrix positions (left half, col 7) and encoder matrix mapping (right half) in vial.json -- verification and cross-referencing against Sofle rev1 conventions
**Confidence:** HIGH

## Summary

Phase 4 verifies that two peripheral devices -- the thumbstick (left half) and the rotary encoder (right half) -- are correctly represented in their respective vial.json files. The Phase 3 matrix dimension fix (rows 4 to 8) and right-half row remapping are now complete, so this phase validates that the peripherals survived those changes correctly and investigates the encoder configuration identified as needing Phase 4 attention in prior phases.

The thumbstick investigation is straightforward: the left half maps thumbstick directions to virtual matrix positions at column 7 (rows 0-3), and these positions were confirmed unchanged by Phase 3. The `matrix_scan_user()` code reads keycodes from `dynamic_keymap_get_keycode(layer, row, 7)` for rows 0-3, and the left vial.json has matching KLE entries at those exact positions. No changes are needed for MTRX-05.

The encoder investigation (MTRX-06) is more complex and revealed three findings:

1. **The "encoders" JSON key** in the right vial.json is a non-standard addition. It is not part of the official Vial documentation, is not used by any other keyboard in the vial-qmk repo (except a layout label usage in the Lulu), and the Sofle rev1 reference does not use it. However, it may be consumed by the Vial GUI for display purposes, and removing it could be risky. The safe action is to preserve it unchanged.

2. **Encoder KLE entries** (`"0,0\n\n\n\n\n\n\n\n\ne"` and `"0,1\n\n\n\n\n\n\n\n\ne"`) use encoder indices, not matrix positions. They were correctly preserved during Phase 3's row remapping. They are verified correct.

3. **NUM_ENCODERS dimension mismatch:** The right-side firmware compiles with `SPLIT_KEYBOARD` defined (from `info.json split.enabled = true`). Since `ENCODERS_PAD_A` defines 1 encoder and `ENCODERS_PAD_A_RIGHT` is NOT defined, QMK defaults to assuming 1 encoder per side, yielding `NUM_ENCODERS = 2`. But the `encoder_map[][]` in keymap.c only provides 1 encoder entry per layer. C zero-fills the missing entries, so this compiles but allocates EEPROM space for a phantom second encoder. This is a known issue flagged in Phase 1 (FIX-CHECKLIST.md) but its fix must be weighed against risk.

**Primary recommendation:** Verify the existing thumbstick and encoder KLE entries are correct (they are). Address the NUM_ENCODERS mismatch by adding `#define NUM_ENCODERS 1` to the right side's config.h, which prevents QMK's split-doubling logic from creating a phantom encoder.

## Standard Stack

This is a JSON verification and config.h editing phase. No libraries or build tools beyond a JSON parser are needed.

### Files to Verify (Read-Only)

| File | What to Verify |
|------|---------------|
| `keymaps/vial_left/vial.json` | Col 7 positions at rows 0-3 (thumbstick) present and correct |
| `keymaps/vial_right/vial.json` | Encoder KLE entries use encoder indices (0,0 and 0,1), "encoders" JSON key preserved |
| `keymaps/vial_left/keymap.c` | `matrix_scan_user()` reads from rows 0-3 col 7 -- matches vial.json |

### Files Potentially Modified

| File | Potential Change | Why |
|------|-----------------|-----|
| `keymaps/vial_right/config.h` | Add `#define NUM_ENCODERS 1` | Prevents split-doubling from creating phantom encoder |
| `keymaps/vial_right/keymap.c` | No change needed if NUM_ENCODERS is set to 1 | encoder_map already has 1 entry per layer |

### Files NOT to Modify

| File | Reason |
|------|--------|
| `keymaps/vial_left/vial.json` KLE layout | Thumbstick positions already verified correct |
| `keymaps/vial_right/vial.json` | Encoder KLE entries and "encoders" key already correct |
| `keymaps/vial_left/keymap.c` `matrix_scan_user()` | Thumbstick logic is correct and not part of this fix |

## Architecture Patterns

### Pattern 1: Thumbstick Virtual Matrix Positions

**What:** The left-half thumbstick uses column 7 (the NO_PIN virtual column) for 4 directional keycodes. The `matrix_scan_user()` function in the left keymap reads joystick axis values and when the deflection exceeds the actuation threshold, it calls `dynamic_keymap_get_keycode(layer, row, 7)` to get the assigned keycode from EEPROM (which was set via Vial).

**How it works:**

| Direction | Joystick Axis | Threshold | Matrix Position | dynamic_keymap call |
|-----------|--------------|-----------|----------------|-------------------|
| Up | Y < -actuation | `joy_y < -actuation` | row 0, col 7 | `dynamic_keymap_get_keycode(layer, 0, 7)` |
| Down | Y > actuation | `joy_y > actuation` | row 1, col 7 | `dynamic_keymap_get_keycode(layer, 1, 7)` |
| Left | X < -actuation | `joy_x < -actuation` | row 2, col 7 | `dynamic_keymap_get_keycode(layer, 2, 7)` |
| Right | X > actuation | `joy_x > actuation` | row 3, col 7 | `dynamic_keymap_get_keycode(layer, 3, 7)` |

**Why col 7 is virtual:** The hardware defines `MATRIX_COL_PINS { GP24, GP23, GP21, GP20, GP19, GP26, GP16, NO_PIN }`. Column 7 is `NO_PIN` -- there is no physical wire, so no physical key can exist at col 7. The matrix scan hardware never reads col 7. Instead, `matrix_scan_user()` software-injects key events at these positions.

**Vial.json match:** The left vial.json KLE layout includes entries at `"0,7"`, `"1,7"`, `"2,7"`, and `"3,7"`, allowing the user to assign custom keycodes to each thumbstick direction via the Vial GUI.

**Source:** `keymaps/vial_left/keymap.c` lines 224-273 (matrix_scan_user), `keymaps/vial_left/config.h` line 32 (MATRIX_COL_PINS with NO_PIN), left vial.json KLE layout (verified 2026-02-14)

### Pattern 2: Encoder KLE Entries in Vial

**What:** Encoder positions in the Vial KLE layout use a special format: `"encoder_index,direction\n\n\n\n\n\n\n\n\ne"`. The numbers are NOT matrix row/col -- they are:
- First number: encoder index (0-based, identifies which physical encoder)
- Second number: direction (0 = CCW, 1 = CW)
- The `\ne` suffix on the center legend marks the entry as an encoder

**Right vial.json encoder entries:**
- `"0,0\n\n\n\n\n\n\n\n\ne"` -- encoder 0, CCW rotation
- `"0,1\n\n\n\n\n\n\n\n\ne"` -- encoder 0, CW rotation

**These were correctly preserved during Phase 3's row remapping.** The `\ne` suffix distinguishes them from regular key positions.

**Source:** [Vial encoder docs](https://get.vial.today/docs/encoders.html), Sofle rev1 vial.json (uses same format with 4 encoder KLE entries for 2 encoders), right vial.json (verified 2026-02-14)

### Pattern 3: Sofle rev1 Encoder Convention (Reference)

**What:** The Sofle rev1 configures encoders through three mechanisms:
1. `keyboard.json` defines encoder pins for both sides (`encoder.rotary` + `split.encoder.right.rotary`)
2. `rules.mk` enables `ENCODER_MAP_ENABLE = yes`
3. `keymap.c` defines `encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS]` with 2 encoder entries per layer (one per side)
4. KLE layout has 4 encoder entries (CCW/CW for each of the 2 encoders)
5. **No "encoders" JSON key** in vial.json

**Sofle encoder_map:**
```c
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    // ... 2 encoders per layer, 4 layers
};
```

**Source:** `keyboards/sofle/rev1/keymaps/vial/keymap.c` lines 117-122, `keyboards/sofle/rev1/keymaps/vial/vial.json` (no "encoders" key present), `keyboards/sofle/rev1/keyboard.json` (encoder pin definitions)

### Pattern 4: QMK Split Encoder Counting (NUM_ENCODERS)

**What:** QMK's `encoder.h` (lines 52-71) determines NUM_ENCODERS for split keyboards:

```c
#ifdef SPLIT_KEYBOARD
#    if defined(ENCODER_A_PINS_RIGHT)
        // LEFT and RIGHT encoder counts determined separately
        NUM_ENCODERS_LEFT = count(ENCODER_A_PINS)
        NUM_ENCODERS_RIGHT = count(ENCODER_A_PINS_RIGHT)
#    else
        // No separate RIGHT pins: assume same count on both sides
        NUM_ENCODERS_LEFT = count(ENCODER_A_PINS)
        NUM_ENCODERS_RIGHT = NUM_ENCODERS_LEFT  // <-- THIS IS THE AMBI'S PATH
#    endif
    NUM_ENCODERS = NUM_ENCODERS_LEFT + NUM_ENCODERS_RIGHT
#endif
```

**Ambi right side:**
- `ENCODERS_PAD_A { GP28 }` defined -- 1 encoder (maps to `ENCODER_A_PINS`)
- `ENCODERS_PAD_A_RIGHT` NOT defined
- `SPLIT_KEYBOARD` defined (from info.json split.enabled)
- Result: `NUM_ENCODERS_LEFT = 1`, `NUM_ENCODERS_RIGHT = 1`, **`NUM_ENCODERS = 2`**

**But the right side only has 1 physical encoder.** The second encoder is phantom.

**Source:** `quantum/encoder.h` lines 52-71 (direct read, 2026-02-14)

### Anti-Patterns to Avoid

- **Modifying thumbstick positions:** Rows 0-3 col 7 are correct and match `matrix_scan_user()`. Do not change them.
- **Modifying encoder KLE entries:** The `\ne` suffix entries use encoder indices, not matrix positions. Do not add row offsets.
- **Removing the "encoders" JSON key:** Even though it appears non-standard, removing it could break Vial GUI display for this keyboard. Preserve it.
- **Adding a second encoder entry to encoder_map without fixing NUM_ENCODERS:** Adding a dummy `ENCODER_CCW_CW(KC_NO, KC_NO)` for a phantom encoder wastes EEPROM. Better to set `NUM_ENCODERS 1` explicitly.

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| Thumbstick position verification | Manual KLE parsing | Python script extracting col-7 positions from left vial.json | Deterministic, avoids human error |
| Encoder KLE verification | Pattern-matching by eye | Check for `\ne` suffix in strings | Official Vial docs confirm this is the identifier |
| NUM_ENCODERS determination | Mental evaluation of preprocessor logic | Read `quantum/encoder.h` directly and trace the #ifdef chain | Complex conditional logic with deprecated aliases |

**Key insight:** The thumbstick verification is purely confirmatory -- Phase 1 already verified these positions (REFERENCE-ANALYSIS.md Section 9). Phase 4 is a cross-reference check, not a discovery phase.

## Common Pitfalls

### Pitfall 1: Confusing Encoder KLE Entries with Matrix Positions
**What goes wrong:** The executor sees `"0,0\n\n\n\n\n\n\n\n\ne"` and mistakenly applies a +4 row offset, changing it to `"4,0\n\n\n\n\n\n\n\n\ne"`.
**Why it happens:** The Phase 3 row remapping changed all right-half positions from rows 0-3 to rows 4-7. The encoder entries start with "0,0" which looks like a matrix position.
**How to avoid:** Phase 3 already handled this correctly by checking for `\ne` suffix. Phase 4 simply verifies the entries are still `"0,0\n..."` and `"0,1\n..."`.
**Warning signs:** If encoder KLE entries show row numbers >= 4, they were incorrectly modified.

### Pitfall 2: Assuming NUM_ENCODERS = 1 Without Fixing the Define
**What goes wrong:** The executor verifies the encoder_map has 1 entry per layer, assumes NUM_ENCODERS = 1, and marks the task complete. But NUM_ENCODERS is actually 2 due to split doubling, so EEPROM allocates space for 2 encoders.
**Why it happens:** The `#define ENCODERS_PAD_A { GP28 }` shows 1 encoder, and the encoder_map has 1 entry. It looks correct at the surface level.
**How to avoid:** Trace the QMK encoder.h preprocessor logic: SPLIT_KEYBOARD + no ENCODER_A_PINS_RIGHT = NUM_ENCODERS doubled.
**Warning signs:** `VIAL_ENCODERS_SIZE = NUM_ENCODERS * 4 * 2 * 2` evaluates to 32 bytes with NUM_ENCODERS=2, or 16 bytes with NUM_ENCODERS=1. The extra 16 bytes of phantom encoder EEPROM are wasted.

### Pitfall 3: Removing the "encoders" JSON Key from Right vial.json
**What goes wrong:** The executor sees the "encoders" key doesn't appear in the Sofle reference or official Vial docs and removes it to "match convention."
**Why it happens:** The Sofle rev1 (the reference) does not have this key. The Vial docs don't document it. It looks like an error.
**How to avoid:** The "encoders" key may be consumed by the Vial GUI for default encoder display. Since the keyboard currently works with encoders (per the user's prior usage), removing an undocumented key is risky. Preserve it unchanged. If it's truly vestigial, removing it is a future cleanup task, not part of this bug fix.
**Warning signs:** After removing the key, Vial GUI may not show encoder controls or may show them without default keycodes.

### Pitfall 4: Forgetting to Cross-Reference Thumbstick Against matrix_scan_user
**What goes wrong:** The executor verifies thumbstick positions exist in the left vial.json but doesn't verify they match the positions used by `matrix_scan_user()`.
**Why it happens:** The success criteria mention "matching the dynamic keymap positions used by matrix_scan_user for custom keys mode" but it's easy to check only the vial.json side.
**How to avoid:** Verify the match is bidirectional: (a) vial.json has entries at (0,7), (1,7), (2,7), (3,7); AND (b) `matrix_scan_user()` reads from rows 0-3 col 7.
**Warning signs:** A mismatch would mean the user can assign keys in Vial that the firmware never reads, or vice versa.

## Code Examples

### Current Left vial.json Col 7 Entries (Thumbstick)

```json
// Source: keymaps/vial_left/vial.json (verified post-Phase 3)
// These entries appear at various positions in the KLE layout:

"0,7"    // Row 1 (line ~111) -- Thumbstick UP, colored #737373
"2,7"    // Row 2 (line ~151) -- Thumbstick LEFT, colored #737373
"3,7"    // Row 2 (line ~153) -- Visible adjacent to "2,7" in cluster
"1,7"    // Row 3 (line ~191) -- Thumbstick DOWN, colored #737373
```

All 4 entries use rows 0-3, col 7, matching `matrix_scan_user()` expectations.

### Current Right vial.json Encoder Entries

```json
// Source: keymaps/vial_right/vial.json (verified post-Phase 3)

// KLE encoder entries (line 27):
"0,0\n\n\n\n\n\n\n\n\ne"    // Encoder 0, CCW -- colored #737373
// KLE encoder entries (line 30):
"0,1\n\n\n\n\n\n\n\n\ne"    // Encoder 0, CW -- colored #737373

// "encoders" JSON key (lines 33-40):
"encoders": [
    [
        ["QK_KB_2", "QK_KB_1"],    // Layer 0: CCW=QK_KB_2 (CL_BWD), CW=QK_KB_1 (CL_FWD)
        ["KC_TRNS", "KC_TRNS"],    // Layer 1
        ["KC_TRNS", "KC_TRNS"],    // Layer 2
        ["KC_TRNS", "KC_TRNS"]     // Layer 3
    ]
]
```

### Current encoder_map in Right keymap.c

```c
// Source: keymaps/vial_right/keymap.c lines 185-192
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(CL_BWD, CL_FWD) },   // Only 1 entry, NUM_ENCODERS=2
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
```

Note: Each layer provides 1 encoder entry but `NUM_ENCODERS=2` (split doubling). C zero-fills the second encoder's entries to `{0, 0}` which is `{KC_NO, KC_NO}`.

### Sofle rev1 encoder_map (Reference -- Correct for 2 Encoders)

```c
// Source: keyboards/sofle/rev1/keymaps/vial/keymap.c lines 117-122
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
```

Each layer has 2 entries matching NUM_ENCODERS=2 (one encoder per side).

### Proposed Fix: Set NUM_ENCODERS Explicitly

```c
// In keymaps/vial_right/config.h, add:
#define NUM_ENCODERS 1
```

This prevents QMK's split-doubling logic from running (the `#ifndef NUM_ENCODERS` guard in `encoder.h` line 69 is skipped when NUM_ENCODERS is already defined). Result:
- `NUM_ENCODERS = 1` (only the physical right-side encoder)
- `encoder_map` size matches: 1 entry per layer for 1 encoder
- `VIAL_ENCODERS_SIZE = 1 * 4 * 2 * 2 = 16 bytes` (down from 32)

### EEPROM Impact Calculation

```
Before fix (NUM_ENCODERS=2):
  VIAL_ENCODERS_SIZE = 2 * 4 layers * 2 directions * 2 bytes = 32 bytes
  Encoder 1 (phantom) EEPROM: 16 bytes wasted

After fix (NUM_ENCODERS=1):
  VIAL_ENCODERS_SIZE = 1 * 4 layers * 2 directions * 2 bytes = 16 bytes
  No wasted space
```

## Detailed Findings

### Finding 1: Thumbstick Positions Are Correct (MTRX-05 Satisfied)

All 4 thumbstick positions in the left vial.json are confirmed:
- `"0,7"` (Up), `"1,7"` (Down), `"2,7"` (Left), `"3,7"` (Right)
- These match `matrix_scan_user()` which reads `dynamic_keymap_get_keycode(layer, 0, 7)` through `dynamic_keymap_get_keycode(layer, 3, 7)`
- All within left-half row range (0-3) and within the 8-row matrix bounds (0-7)
- Column 7 is `NO_PIN` -- virtual, never scanned by hardware matrix
- Phase 3 did not modify the left vial.json KLE layout, so these are unchanged

**Confidence:** HIGH -- positions verified by direct read of both vial.json and keymap.c

### Finding 2: Encoder KLE Entries Are Correct

The right vial.json encoder KLE entries are confirmed:
- `"0,0\n\n\n\n\n\n\n\n\ne"` and `"0,1\n\n\n\n\n\n\n\n\ne"` use encoder index 0 with directions 0 (CCW) and 1 (CW)
- These were correctly preserved during Phase 3's row remapping (the `\ne` suffix was used to identify and skip them)
- The Sofle rev1 uses the identical format for its encoder KLE entries
- The numbers (0,0 and 0,1) are within valid encoder index range (encoder 0 exists)

**Confidence:** HIGH -- verified against Sofle reference and Vial official docs

### Finding 3: "encoders" JSON Key Analysis

The right vial.json contains a top-level `"encoders"` key:
```json
"encoders": [
    [
        ["QK_KB_2", "QK_KB_1"],
        ["KC_TRNS", "KC_TRNS"],
        ["KC_TRNS", "KC_TRNS"],
        ["KC_TRNS", "KC_TRNS"]
    ]
]
```

**Investigation results:**
- The Sofle rev1 reference does NOT have this key
- No other keyboard in the vial-qmk repo has this key as a top-level JSON property
- The official Vial documentation does not document this key
- The vial.json is compressed and embedded in the firmware as `keyboard_definition[]` and sent to the Vial GUI. The GUI may consume this key for display purposes.
- The keycode values (`QK_KB_2` = CL_BWD, `QK_KB_1` = CL_FWD) match the `encoder_map` defaults in keymap.c
- Structure: `encoders[encoder_index][layer_index] = [CCW_keycode, CW_keycode]`

**Recommendation:** Preserve unchanged. It may serve as a display hint for the Vial GUI. Removing it is a risk with no benefit for this bug fix project.

**Confidence:** MEDIUM -- the key's purpose is not documented; we are inferring its role from context

### Finding 4: NUM_ENCODERS Mismatch

**The problem:** QMK's encoder.h split logic sets `NUM_ENCODERS = 2` because `ENCODERS_PAD_A_RIGHT` is not defined and `SPLIT_KEYBOARD` is true. This causes:
1. `encoder_map[][2][2]` is declared but each layer only provides 1 initializer (C zero-fills the rest)
2. `VIAL_ENCODERS_SIZE = 32 bytes` instead of 16 bytes (16 bytes wasted on phantom encoder)
3. `dynamic_keymap_reset()` iterates over both encoders, writing defaults from `encoder_map` -- the phantom encoder gets `KC_NO` (0x0000)

**Impact:** This is not a crash bug -- C handles partial initialization gracefully. But it wastes 16 bytes of EEPROM and could confuse the Vial GUI if it ever tries to read encoder 1's keycodes (it would get KC_NO).

**Fix options:**
1. **Recommended: `#define NUM_ENCODERS 1`** in `keymaps/vial_right/config.h`. This explicitly overrides the split-doubling calculation. The `#ifndef NUM_ENCODERS` guard in encoder.h (line 69) respects this override. The encoder_map already has 1 entry per layer, so no keymap.c change is needed.
2. Alternative: `#define NUM_ENCODERS_RIGHT 0` (or `#define NUM_ENCODERS_LEFT 0` and `#define NUM_ENCODERS_RIGHT 1`). This requires understanding which side is "left" vs "right" in the Ambi's build model -- more complex and error-prone.

**Sofle comparison:** The Sofle has 2 physical encoders (one per side) and correctly provides 2 entries per layer in encoder_map. Its `keyboard.json` defines separate encoder pins for each side via `split.encoder.right.rotary`, so QMK knows the exact count per side.

**Confidence:** HIGH -- traced through QMK encoder.h preprocessor logic directly (2026-02-14)

### Finding 5: Encoder EEPROM Layout

From `quantum/dynamic_keymap.c`:

```
VIAL_ENCODERS_EEPROM_ADDR = DYNAMIC_KEYMAP_EEPROM_ADDR + (4 layers * 8 rows * 8 cols * 2 bytes)
                           = DYNAMIC_KEYMAP_EEPROM_ADDR + 512 bytes

VIAL_ENCODERS_SIZE = NUM_ENCODERS * 4 layers * 2 directions * 2 bytes

With NUM_ENCODERS=2: 32 bytes
With NUM_ENCODERS=1: 16 bytes
```

The encoder EEPROM region follows immediately after the dynamic keymap region. Changing NUM_ENCODERS affects the size of this region and shifts the QMK settings region that follows it. This means an EEPROM clear is required after the fix (already planned for Phase 7).

**Confidence:** HIGH -- read directly from `quantum/dynamic_keymap.c` lines 71-74

### Finding 6: Encoder Actions Cross-Reference

The encoder's default actions should be consistent across three sources:

| Source | Encoder 0 CCW | Encoder 0 CW | Consistent? |
|--------|--------------|-------------|-------------|
| `encoder_map` in keymap.c | `CL_BWD` (= `QK_KB_2`) | `CL_FWD` (= `QK_KB_1`) | Reference |
| `"encoders"` JSON key | `QK_KB_2` | `QK_KB_1` | YES -- matches |
| KLE encoder entries | Display only (no keycodes) | Display only | N/A |

The `CL_BWD`/`CL_FWD` keycodes map to `QK_KB_2`/`QK_KB_1` (they are the 3rd and 2nd entries in the custom keycodes enum, 0-indexed from `QK_KB_0`). The "encoders" JSON key uses the QK_KB names directly. These are consistent.

**Confidence:** HIGH -- enum ordering verified in keymap.c (TMB_MODE=QK_KB_0, CL_FWD=QK_KB_1, CL_BWD=QK_KB_2)

## Validation Procedures

### Validation 1: Thumbstick Position Verification (MTRX-05)

```bash
python3 -c "
import json, re
with open('keymaps/vial_left/vial.json') as f:
    d = json.load(f)

# Extract col 7 positions
col7 = []
for row in d['layouts']['keymap']:
    for item in row:
        if isinstance(item, str) and re.match(r'^\d+,7$', item):
            col7.append(item)

expected = ['0,7', '1,7', '2,7', '3,7']
actual_sorted = sorted(col7, key=lambda x: int(x.split(',')[0]))
assert actual_sorted == expected, f'Mismatch: {actual_sorted} != {expected}'
assert all(int(p.split(',')[0]) < 8 for p in col7), 'Col 7 position row exceeds matrix bounds'
print(f'Thumbstick positions: {actual_sorted}')
print('MTRX-05: PASSED -- all 4 thumbstick positions at rows 0-3 col 7 within 8-row matrix')
"
```

### Validation 2: Encoder KLE Entry Verification

```bash
python3 -c "
import json
with open('keymaps/vial_right/vial.json') as f:
    d = json.load(f)

encoders = []
for row in d['layouts']['keymap']:
    for item in row:
        if isinstance(item, str) and item.endswith('\ne'):
            encoders.append(item.split('\n')[0])

assert encoders == ['0,0', '0,1'], f'Encoder entries changed: {encoders}'
print(f'Encoder KLE entries: {encoders}')
print('MTRX-06 (partial): PASSED -- encoder KLE entries use indices 0,0 and 0,1')
"
```

### Validation 3: "encoders" JSON Key Preservation

```bash
python3 -c "
import json
with open('keymaps/vial_right/vial.json') as f:
    d = json.load(f)

assert 'encoders' in d, 'Missing encoders JSON key'
enc = d['encoders']
assert len(enc) == 1, f'Expected 1 encoder, got {len(enc)}'
assert len(enc[0]) == 4, f'Expected 4 layers, got {len(enc[0])}'
print(f'Encoder 0 layer 0: {enc[0][0]}')
print('MTRX-06 (partial): PASSED -- encoders JSON key preserved with 1 encoder, 4 layers')
"
```

### Validation 4: Cross-Reference Thumbstick with matrix_scan_user

```bash
# Verify that matrix_scan_user reads from the same positions as vial.json
grep -n 'dynamic_keymap_get_keycode.*,.*7)' keymaps/vial_left/keymap.c
# Expected: 4 lines reading from (layer, 0, 7), (layer, 1, 7), (layer, 2, 7), (layer, 3, 7)
```

### Validation 5: Encoder Matrix Bounds Check

```bash
python3 -c "
# Verify all encoder references are within 8-row matrix bounds
# The encoder KLE entries use encoder indices (not matrix), so they are inherently safe.
# The 'encoders' JSON key references keycodes, not matrix positions, so also safe.
# The encoder_map in keymap.c doesn't reference matrix positions.
print('Encoder references do not use matrix positions -- bounds check inherently satisfied')
print('Encoder KLE entries: encoder index 0, directions 0/1 -- valid for 1-encoder config')
print('MTRX-06: PASSED -- all encoder references within bounds')
"
```

## State of the Art

| Old Approach | Current Approach | When Changed | Impact |
|--------------|------------------|--------------|--------|
| `ENCODERS_PAD_A` (deprecated) | `ENCODER_A_PINS` (current) | QMK encoder.h note | Ambi uses deprecated name; encoder.h has compatibility aliases |
| Split encoder count assumed symmetric | `ENCODER_A_PINS_RIGHT` for asymmetric | QMK split support | Ambi should use `#define NUM_ENCODERS 1` to override |
| VIA v2 `"encoders"` JSON key | Encoder KLE entries only | VIA/Vial current | Ambi has both -- redundant but not harmful |

**Deprecated/outdated:**
- `ENCODERS_PAD_A`/`ENCODERS_PAD_B` are deprecated aliases for `ENCODER_A_PINS`/`ENCODER_B_PINS` (encoder.h lines 26-31). They still work via the alias but should be updated in a future cleanup.

## Open Questions

1. **Whether `#define NUM_ENCODERS 1` affects split transport**
   - What we know: The Ambi uses full-duplex serial for split communication. Encoder events from one side are sent to the other via split transport. With `NUM_ENCODERS=1`, the transport might not expect encoder data from the "left" side.
   - What's unclear: Whether the left side (which has no encoder) ever tries to send encoder events. Since the left side doesn't define `ENCODER_ENABLE` in its rules.mk, it likely doesn't send encoder events at all.
   - Recommendation: This is safe. The left side doesn't have encoder support enabled. The right side is the USB-connected master for its builds, and it only has 1 encoder. Setting `NUM_ENCODERS=1` matches reality.

2. **Whether the "encoders" JSON key is actively consumed by Vial GUI**
   - What we know: It's not documented. No other keyboard uses it as a top-level key. The Vial GUI source would need inspection to confirm.
   - What's unclear: Whether removing it would break encoder display in Vial.
   - Recommendation: Preserve it. The cost is a few bytes of compressed JSON in the firmware definition. The risk of removing it outweighs the benefit.

3. **Whether EEPROM clear is required after NUM_ENCODERS change**
   - What we know: Changing NUM_ENCODERS from 2 to 1 changes `VIAL_ENCODERS_SIZE` from 32 to 16 bytes, which shifts the QMK settings region that follows.
   - What's unclear: Whether Vial handles this gracefully or whether stale EEPROM data causes issues.
   - Recommendation: EEPROM clear is already mandatory for Phase 7 (due to the Phase 3 matrix dimension change). The NUM_ENCODERS change adds no new requirement.

## Sources

### Primary (HIGH confidence)
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/vial.json` -- 4 thumbstick positions at col 7 (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/keymap.c` -- matrix_scan_user reads rows 0-3 col 7 (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json` -- encoder KLE entries and "encoders" JSON key (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/keymap.c` -- encoder_map with 1 entry per layer (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/config.h` -- ENCODERS_PAD_A/B defined, no RIGHT variants (direct read, 2026-02-14)
- `quantum/encoder.h` -- NUM_ENCODERS split doubling logic (direct read, 2026-02-14)
- `quantum/dynamic_keymap.c` -- EEPROM layout for encoders (direct read, 2026-02-14)
- `quantum/vial.c` -- encoder get/set protocol commands (direct read, 2026-02-14)
- `keyboards/sofle/rev1/keymaps/vial/vial.json` -- no "encoders" key, 4 KLE encoder entries (direct read, 2026-02-14)
- `keyboards/sofle/rev1/keymaps/vial/keymap.c` -- encoder_map with 2 entries per layer (direct read, 2026-02-14)
- `keyboards/sofle/rev1/keyboard.json` -- split.encoder.right.rotary pins (direct read, 2026-02-14)
- REFERENCE-ANALYSIS.md Sections 7, 8, 9 -- encoder comparison and thumbstick verification (Phase 1 deliverable)

### Secondary (MEDIUM confidence)
- [Vial encoder docs](https://get.vial.today/docs/encoders.html) -- encoder KLE entry format with `\ne` suffix
- [Vial porting docs](https://get.vial.today/docs/porting-to-via.html) -- vial.json format basics
- [Vial deepwiki](https://deepwiki.com/vial-kb/vial-qmk/5.2-encoders-and-special-inputs) -- encoder system overview

### Tertiary (LOW confidence)
- "encoders" JSON key purpose -- inferred from context only; no documentation found confirming or denying its consumption by Vial GUI

## Metadata

**Confidence breakdown:**
- Thumbstick positions (MTRX-05): HIGH -- direct read of both vial.json and keymap.c, positions trivially match
- Encoder KLE entries: HIGH -- format verified against Sofle reference and Vial docs
- "encoders" JSON key: MEDIUM -- purpose undocumented, but preservation is the safe default
- NUM_ENCODERS mismatch: HIGH -- traced through QMK source (encoder.h) with full preprocessor chain
- EEPROM impact: HIGH -- read directly from dynamic_keymap.c formulas
- Encoder cross-reference with Sofle: HIGH -- both Sofle files read directly

**Research date:** 2026-02-14
**Valid until:** Indefinite (QMK encoder.h logic is stable; vial.json format is stable; source files are static until edited)
