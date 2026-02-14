# Phase 3: vial.json Matrix Fix - Research

**Researched:** 2026-02-14
**Domain:** Vial JSON configuration editing -- matrix dimension correction and KLE layout row remapping for split keyboard
**Confidence:** HIGH

## Summary

Phase 3 is a surgical JSON editing phase that applies the two fixes identified and fully enumerated in Phases 1 and 2. The work consists of: (1) changing `"rows": 4` to `"rows": 8` in both vial.json files, and (2) remapping all 25 key position strings in the right vial.json from rows 0-3 to rows 4-7. This is the core bug fix that resolves the EEPROM layer offset problem.

The technical domain is well-understood. Prior phases have exhaustively documented every position that must change (REFERENCE-ANALYSIS.md Section 8), confirmed which entries must NOT change (encoder KLE entries and the "encoders" JSON key), and verified the expected values against the known-working Sofle rev1 reference. The primary risk is not conceptual but mechanical: accidentally modifying an encoder entry, missing a position, or breaking JSON syntax.

The Vial documentation confirms that `matrix.rows` and `matrix.cols` in vial.json must match `MATRIX_ROWS` and `MATRIX_COLS` from config.h. For split keyboards, `MATRIX_ROWS` is the doubled value (physical rows per side x 2), so vial.json must declare the full doubled count. The Sofle rev1 exemplifies this: 5 physical rows per side, MATRIX_ROWS=10, vial.json rows=10, right-half KLE positions use rows 5-9.

**Primary recommendation:** Execute the fix in two logical steps -- (1) dimension fix for both vial.json files (rows 4 to 8), then (2) right-half KLE row remapping (25 positions, +4 offset). Validate each step with a JSON parser and position count check.

## Standard Stack

This is a pure JSON editing phase. No libraries or build tools are needed. The "stack" is the set of files to modify and the validation tools to confirm correctness.

### Files to Modify

| File | Change | Lines Affected |
|------|--------|----------------|
| `keymaps/vial_left/vial.json` | `"rows": 4` to `"rows": 8` | Line 5 |
| `keymaps/vial_right/vial.json` | `"rows": 4` to `"rows": 8` | Line 5 |
| `keymaps/vial_right/vial.json` | All 25 key position strings: row +4 | Lines 19-30 (KLE layout) |

### Files NOT to Modify

| File | Reason |
|------|--------|
| `keymaps/vial_left/vial.json` KLE layout | Left-half rows 0-3 are already correct |
| `keymaps/vial_right/vial.json` encoder KLE entries | Encoder indices, not matrix rows |
| `keymaps/vial_right/vial.json` "encoders" JSON key | Encoder actions per layer, preserved as-is |
| `keymaps/vial_right/vial.json` "customKeycodes" | Unrelated to matrix fix |
| `keymaps/vial_left/vial.json` "customKeycodes" | Unrelated to matrix fix |
| `bipedalambi/config.h` | Already correct (MATRIX_ROWS=8) |
| `bipedalambi/info.json` | Already correct (4 pins, auto-doubled) |

## Architecture Patterns

### Pattern 1: Vial Split Matrix Convention

**What:** For split keyboards, vial.json `matrix.rows` must equal the compiled `MATRIX_ROWS` (which is physical_rows_per_side x 2). The left-half KLE layout uses rows 0 to ROWS_PER_HAND-1. The right-half KLE layout uses rows ROWS_PER_HAND to MATRIX_ROWS-1.

**Evidence:**
- Sofle rev1: 5 physical rows, MATRIX_ROWS=10, vial.json rows=10, left rows 0-4, right rows 5-9
- Bipedal Ambi target: 4 physical rows, MATRIX_ROWS=8, vial.json rows=8, left rows 0-3, right rows 4-7

**Source:** Sofle rev1 `vial.json` (verified locally), REFERENCE-ANALYSIS.md Section 5, Vial official docs (get.vial.today/docs/porting-to-via.html: "rows should match MATRIX_ROWS")

### Pattern 2: KLE Position String Format

**What:** In the Vial KLE layout array, regular key positions are encoded as `"row,col"` strings (e.g., `"2,5"`). Encoder entries are encoded as `"encoder_index,direction\n\n\n\n\n\n\n\n\ne"` where the `\ne` suffix on the center legend marks them as encoder entries, and the numbers are encoder index (0-based) and direction (0=CCW, 1=CW), NOT matrix positions.

**Critical distinction:**
- `"0,3"` = regular key at matrix row 0, col 3 -- MUST be remapped for right half
- `"0,0\n\n\n\n\n\n\n\n\ne"` = encoder 0, CCW action -- must NOT be remapped

**Source:** Vial official docs (get.vial.today/docs/encoders.html: "These labels are completely unique to the encoders, and are NOT part of the matrix"), verified against Sofle rev1 vial.json

### Pattern 3: The "encoders" JSON Key

**What:** The Bipedal Ambi right vial.json contains a top-level `"encoders"` key that defines default encoder actions per layer. This is separate from the KLE encoder entries (which define where encoders appear visually) and from `ENCODER_MAP_ENABLE` (which enables keymap-level encoder_map in keymap.c). All three mechanisms exist in the right-half firmware:
1. `"encoders"` JSON key in vial.json (lines 33-40): Default encoder keycodes per layer
2. KLE encoder entries in vial.json (lines 27, 30): Visual placement of encoder in Vial GUI
3. `ENCODER_MAP_ENABLE = yes` in rules.mk: Enables `encoder_map` array in keymap.c

**Constraint:** The `"encoders"` JSON key must be preserved unchanged. It is NOT part of the matrix fix. Phase 4 will investigate any interactions between these three mechanisms.

**Source:** Direct read of `keymaps/vial_right/vial.json` and `keymaps/vial_right/rules.mk`

### Anti-Patterns to Avoid

- **Remapping encoder KLE entries:** The `"0,0\n\n\n\n\n\n\n\n\ne"` and `"0,1\n\n\n\n\n\n\n\n\ne"` entries use encoder indices, NOT matrix rows. Changing "0,0" to "4,0" in these strings would break the encoder display in Vial.
- **Modifying left vial.json KLE layout:** Left-half positions (rows 0-3) are already correct. Only the right-half positions need remapping.
- **Changing cols value:** Both vial.json files already have `"cols": 8` which matches `MATRIX_COLS=8`. Do not change this.
- **Editing the "encoders" JSON key:** This is a separate encoder configuration section, not part of the matrix dimension or KLE layout fix.
- **Using find-and-replace blindly:** A naive replace of `"0,` with `"4,` would also modify encoder entries and JSON property names. Each position string must be identified and changed individually.

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| Position enumeration | Mental counting of KLE entries | REFERENCE-ANALYSIS.md Section 8 position map (25 entries) | Already exhaustively enumerated with current/target values |
| Encoder entry identification | Pattern-matching guesses | Look for `\ne` suffix in string | Official Vial docs confirm `\ne` marks encoder entries |
| JSON validation | Eyeball inspection | `python3 -m json.tool` or `jq .` | Catches syntax errors, missing commas, malformed strings |
| Position count verification | Manual counting | `grep -c` for position pattern in modified file | Confirms no positions were added or lost |

**Key insight:** The position map from Phase 1 (REFERENCE-ANALYSIS.md Section 8) is the authoritative checklist. Every change is pre-enumerated. The executor should not re-derive the changes -- just apply and verify against the existing map.

## Common Pitfalls

### Pitfall 1: Accidentally Remapping Encoder KLE Entries
**What goes wrong:** The executor sees `"0,0\n\n\n\n\n\n\n\n\ne"` on line 27 and changes the "0,0" part to "4,0", thinking it's a key position that needs the +4 offset.
**Why it happens:** The encoder entry starts with `"0,0"` which looks identical to a key position at row 0, col 0.
**How to avoid:** Identify all entries containing `\ne` suffix FIRST and mark them as DO NOT TOUCH. There are exactly 2 encoder entries in the right vial.json: `"0,0\n\n\n\n\n\n\n\n\ne"` (line 27) and `"0,1\n\n\n\n\n\n\n\n\ne"` (line 30).
**Warning signs:** If the modified file contains `"4,0\n\n\n\n\n\n\n\n\ne"` or `"4,1\n\n\n\n\n\n\n\n\ne"`, the encoder entries were incorrectly modified.

### Pitfall 2: Breaking JSON Syntax
**What goes wrong:** A missing comma, extra comma, mismatched bracket, or unescaped character in the modified JSON makes vial.json unparseable.
**Why it happens:** The KLE layout is a dense nested array of objects and strings. Manual editing is error-prone.
**How to avoid:** Validate with `python3 -m json.tool vial.json` or `jq . vial.json` after every edit. Both will report syntax errors with line numbers.
**Warning signs:** JSON validator reports parse error.

### Pitfall 3: Wrong Position Count After Remapping
**What goes wrong:** A key position is accidentally deleted, duplicated, or the row offset is applied inconsistently (e.g., some positions get +4, others don't).
**Why it happens:** The KLE layout interleaves formatting objects `{...}` with position strings `"R,C"`, making it easy to skip or double-process an entry.
**How to avoid:** After editing, extract all position strings from the modified right vial.json and verify: (a) exactly 25 key positions, (b) all in rows 4-7, (c) columns unchanged, (d) 2 encoder entries unchanged.
**Warning signs:** Position count != 25, or any position string with row < 4 (except encoder entries).

### Pitfall 4: Forgetting to Change matrix.rows in BOTH Files
**What goes wrong:** Only one vial.json is updated from rows=4 to rows=8. The other remains at 4.
**Why it happens:** The two files are in different directories (vial_left/ vs vial_right/) and might be edited separately.
**How to avoid:** Verify both files after editing. The dimension fix is a prerequisite to the layout remapping.
**Warning signs:** `grep '"rows"' keymaps/vial_*/vial.json` shows different values.

### Pitfall 5: Modifying the Left vial.json Layout Positions
**What goes wrong:** The executor applies the +4 row offset to the left vial.json's KLE layout, moving left-half keys to rows 4-7.
**Why it happens:** Confusion about which half needs remapping.
**How to avoid:** Only the RIGHT vial.json layout positions change. Left positions remain at rows 0-3. This is explicitly confirmed in the success criteria.
**Warning signs:** Left vial.json KLE entries show rows > 3.

## Code Examples

### Current Right vial.json KLE Layout (Before Fix)

```json
// Source: keymaps/vial_right/vial.json lines 18-31
"keymap": [
    [{"x": 6}, "0,3"],                                                          // row 0
    [{"y": -0.75, "x": 5}, "0,4", {"x": 1}, "0,2"],                           // row 0
    [{"y": -0.75, "x": 4}, "0,5", {"x": 3}, "0,1", {"w": 1.25}, "0,0"],       // row 0
    [{"y": -0.5, "x": 6}, "1,3"],                                              // row 1
    [{"y": -0.75, "x": 5}, "1,4", {"x": 1}, "1,2"],                           // row 1
    [{"y": -0.75, "x": 4}, "1,5", {"x": 3}, "1,1", {"w": 1.25}, "1,0"],       // row 1
    [{"y": -0.5, "x": 6}, "2,3"],                                              // row 2
    [{"y": -0.75, "x": 5}, "2,4", {"x": 1}, "2,2"],                           // row 2
    [{"y": -0.75, "c": "#737373"}, "0,0\n\n\n\n\n\n\n\n\ne",                   // ENCODER (do NOT change)
        {"x": 2, "c": "#cccccc", "h": 2}, "2,6", "2,5",                        // row 2
        {"x": 3}, "2,1", {"w": 1.25}, "2,0"],                                  // row 2
    [{"y": -0.5, "x": 1.5, "c": "#737373"}, "3,6",                            // row 3
        {"x": 3.5, "c": "#cccccc", "h": 1.5}, "3,3"],                          // row 3
    [{"y": -0.75, "x": 5, "h": 1.25}, "3,4", {"x": 1, "h": 1.25}, "3,2"],    // row 3
    [{"y": -0.75, "c": "#737373"}, "0,1\n\n\n\n\n\n\n\n\ne",                   // ENCODER (do NOT change)
        {"x": 3, "c": "#cccccc"}, "3,5", {"x": 3}, "3,1"]                      // row 3
]
```

### Target Right vial.json KLE Layout (After Fix)

```json
// Target: all key positions remapped +4, encoders unchanged
"keymap": [
    [{"x": 6}, "4,3"],                                                          // row 4 (was 0)
    [{"y": -0.75, "x": 5}, "4,4", {"x": 1}, "4,2"],                           // row 4 (was 0)
    [{"y": -0.75, "x": 4}, "4,5", {"x": 3}, "4,1", {"w": 1.25}, "4,0"],       // row 4 (was 0)
    [{"y": -0.5, "x": 6}, "5,3"],                                              // row 5 (was 1)
    [{"y": -0.75, "x": 5}, "5,4", {"x": 1}, "5,2"],                           // row 5 (was 1)
    [{"y": -0.75, "x": 4}, "5,5", {"x": 3}, "5,1", {"w": 1.25}, "5,0"],       // row 5 (was 1)
    [{"y": -0.5, "x": 6}, "6,3"],                                              // row 6 (was 2)
    [{"y": -0.75, "x": 5}, "6,4", {"x": 1}, "6,2"],                           // row 6 (was 2)
    [{"y": -0.75, "c": "#737373"}, "0,0\n\n\n\n\n\n\n\n\ne",                   // ENCODER (unchanged)
        {"x": 2, "c": "#cccccc", "h": 2}, "6,6", "6,5",                        // row 6 (was 2)
        {"x": 3}, "6,1", {"w": 1.25}, "6,0"],                                  // row 6 (was 2)
    [{"y": -0.5, "x": 1.5, "c": "#737373"}, "7,6",                            // row 7 (was 3)
        {"x": 3.5, "c": "#cccccc", "h": 1.5}, "7,3"],                          // row 7 (was 3)
    [{"y": -0.75, "x": 5, "h": 1.25}, "7,4", {"x": 1, "h": 1.25}, "7,2"],    // row 7 (was 3)
    [{"y": -0.75, "c": "#737373"}, "0,1\n\n\n\n\n\n\n\n\ne",                   // ENCODER (unchanged)
        {"x": 3, "c": "#cccccc"}, "7,5", {"x": 3}, "7,1"]                      // row 7 (was 3)
]
```

### Matrix Dimension Fix (Both Files)

```json
// Before (both vial.json files):
"matrix": {
    "rows": 4,
    "cols": 8
}

// After (both vial.json files):
"matrix": {
    "rows": 8,
    "cols": 8
}
```

### Complete Position Change Map (from REFERENCE-ANALYSIS.md Section 8)

```
25 key positions to change in right vial.json:

Row 0 -> 4: "0,0"->"4,0", "0,1"->"4,1", "0,2"->"4,2", "0,3"->"4,3", "0,4"->"4,4", "0,5"->"4,5"
Row 1 -> 5: "1,0"->"5,0", "1,1"->"5,1", "1,2"->"5,2", "1,3"->"5,3", "1,4"->"5,4", "1,5"->"5,5"
Row 2 -> 6: "2,0"->"6,0", "2,1"->"6,1", "2,2"->"6,2", "2,3"->"6,3", "2,4"->"6,4", "2,5"->"6,5", "2,6"->"6,6"
Row 3 -> 7: "3,1"->"7,1", "3,2"->"7,2", "3,3"->"7,3", "3,4"->"7,4", "3,5"->"7,5", "3,6"->"7,6"

2 encoder entries to LEAVE UNCHANGED:
"0,0\n\n\n\n\n\n\n\n\ne" (encoder 0, CCW -- line 27)
"0,1\n\n\n\n\n\n\n\n\ne" (encoder 0, CW -- line 30)
```

## Validation Procedures

### Validation 1: JSON Syntax Check

```bash
# After each file edit, validate JSON syntax:
python3 -m json.tool keymaps/vial_left/vial.json > /dev/null
python3 -m json.tool keymaps/vial_right/vial.json > /dev/null
# No output = valid JSON. Error output = broken syntax.
```

### Validation 2: Matrix Dimension Verification

```bash
# Verify both files now declare rows=8:
python3 -c "
import json
for side in ['vial_left', 'vial_right']:
    with open(f'keymaps/{side}/vial.json') as f:
        d = json.load(f)
    rows = d['matrix']['rows']
    cols = d['matrix']['cols']
    assert rows == 8, f'{side}: rows={rows}, expected 8'
    assert cols == 8, f'{side}: cols={cols}, expected 8'
    print(f'{side}: rows={rows}, cols={cols} -- OK')
"
```

### Validation 3: Right vial.json Position Count and Row Range

```bash
# Extract all position strings from right vial.json, verify count and row range:
python3 -c "
import json, re
with open('keymaps/vial_right/vial.json') as f:
    d = json.load(f)
keymap = d['layouts']['keymap']
keys = []
encoders = []
for row in keymap:
    for item in row:
        if isinstance(item, str):
            if item.endswith('\ne'):
                encoders.append(item.split('\n')[0])
            elif re.match(r'^\d+,\d+$', item):
                keys.append(item)
print(f'Key positions: {len(keys)} (expected 25)')
print(f'Encoder entries: {len(encoders)} (expected 2)')
rows_used = sorted(set(int(k.split(',')[0]) for k in keys))
print(f'Rows used by keys: {rows_used} (expected [4, 5, 6, 7])')
assert len(keys) == 25, f'Wrong key count: {len(keys)}'
assert len(encoders) == 2, f'Wrong encoder count: {len(encoders)}'
assert rows_used == [4, 5, 6, 7], f'Wrong rows: {rows_used}'
print('ALL CHECKS PASSED')
"
```

### Validation 4: Left vial.json Layout Unchanged

```bash
# Verify left vial.json KLE positions still use rows 0-3:
python3 -c "
import json, re
with open('keymaps/vial_left/vial.json') as f:
    d = json.load(f)
keymap = d['layouts']['keymap']
keys = []
for row in keymap:
    for item in row:
        if isinstance(item, str) and re.match(r'^\d+,\d+$', item):
            keys.append(item)
print(f'Key positions: {len(keys)} (expected 29)')
rows_used = sorted(set(int(k.split(',')[0]) for k in keys))
print(f'Rows used: {rows_used} (expected [0, 1, 2, 3])')
assert len(keys) == 29
assert rows_used == [0, 1, 2, 3]
print('LEFT VIAL.JSON UNCHANGED -- OK')
"
```

### Validation 5: Encoder Entries Preserved

```bash
# Verify encoder entries in right vial.json are unchanged:
python3 -c "
import json
with open('keymaps/vial_right/vial.json') as f:
    d = json.load(f)
keymap = d['layouts']['keymap']
encoders_found = []
for row in keymap:
    for item in row:
        if isinstance(item, str) and item.endswith('\ne'):
            encoders_found.append(item.split('\n')[0])
print(f'Encoder entries: {encoders_found}')
assert encoders_found == ['0,0', '0,1'], f'Encoder entries changed! Got: {encoders_found}'
# Verify 'encoders' JSON key preserved:
assert 'encoders' in d, 'Missing encoders JSON key'
print(f'Encoders JSON key: {len(d[\"encoders\"])} encoder(s), {len(d[\"encoders\"][0])} layers')
print('ENCODER ENTRIES PRESERVED -- OK')
"
```

## State of the Art

| Old Approach | Current Approach | When Changed | Impact |
|--------------|------------------|--------------|--------|
| VIA-style single vial.json for whole keyboard | Per-half vial.json (Bipedal Ambi approach) | N/A (design choice) | Each half builds independently; both must declare full matrix dimensions |
| KLE editor for layout design | KLE JSON exported to vial.json keymap field | Vial v1.0+ | Layout strings use `"row,col"` format with `\ne` suffix for encoders |

**No deprecated features apply:** The vial.json format is stable and the matrix dimension/KLE position conventions have not changed since Vial's initial release.

## Open Questions

1. **Whether the "encoders" JSON key and ENCODER_MAP_ENABLE interact or conflict**
   - What we know: Right vial.json has an "encoders" key (lines 33-40) AND rules.mk has `ENCODER_MAP_ENABLE = yes`. The Sofle rev1 uses ENCODER_MAP_ENABLE without the "encoders" key.
   - What's unclear: Whether both can coexist safely, or if one overrides the other.
   - Recommendation: This is a Phase 4 concern. Phase 3 preserves the "encoders" key unchanged and makes no changes to encoder-related files.

2. **Whether EEPROM should be cleared after the dimension change**
   - What we know: Changing matrix.rows from 4 to 8 changes the EEPROM layout that Vial expects. Old EEPROM data was written with a 64-byte layer stride; the new layout expects a 128-byte stride.
   - What's unclear: Whether Vial auto-detects the change and reinitializes, or whether stale EEPROM data causes confusion.
   - Recommendation: EEPROM clear is handled in Phase 7 (Build and Flash). Phase 3 documents the fix; Phase 7 handles the operational procedure.

## Sources

### Primary (HIGH confidence)
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/vial.json` -- current state directly read (2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json` -- current state directly read (2026-02-14)
- `keyboards/hidpress/bipedalambi/config.h` -- MATRIX_ROWS=8, MATRIX_COLS=8 (direct read)
- `keyboards/sofle/rev1/keymaps/vial/vial.json` -- known-working split reference: rows=10, right-half rows 5-9 (direct read)
- REFERENCE-ANALYSIS.md Section 8 -- complete 25-entry position change map (Phase 1 deliverable)
- DIMENSION-AUDIT.md Section 2 -- disagreement documentation with correct values (Phase 2 deliverable)
- FIX-CHECKLIST.md Phase 3 section -- pre-enumerated fix items (Phase 1 deliverable)

### Secondary (MEDIUM confidence)
- [Vial official docs: Create JSON](https://get.vial.today/docs/porting-to-via.html) -- "rows should match MATRIX_ROWS", "cols should match MATRIX_COLS"
- [Vial official docs: Encoder support](https://get.vial.today/docs/encoders.html) -- encoder KLE entries use encoder indices not matrix rows, "\ne" suffix marks encoder entries

### Tertiary (LOW confidence)
- None

## Metadata

**Confidence breakdown:**
- Matrix dimension fix (rows 4 to 8): HIGH -- directly verified against config.h and Sofle reference
- Right-half KLE remapping: HIGH -- complete position map pre-built in Phase 1, verified in Phase 2
- Encoder entry preservation: HIGH -- encoder format confirmed by official Vial docs and Sofle reference
- Validation procedures: HIGH -- Python JSON parsing is deterministic

**Research date:** 2026-02-14
**Valid until:** Indefinite (vial.json format is stable; the position map is derived from static source files)
