# Phase 2: Matrix Dimension Audit - Research

**Researched:** 2026-02-14
**Domain:** QMK/Vial matrix dimension sources -- cross-referencing config.h, info.json, vial.json, and LAYOUT macros
**Confidence:** HIGH

## Summary

Phase 2 is a documentation/audit phase that produces a cross-reference table showing every source of matrix dimensions in the Bipedal Ambi firmware and flagging all disagreements. The technical domain is well-understood from Phase 1: there are exactly 6 sources of matrix dimension information across the firmware, and 2 of them (both vial.json files) have a `rows` value of 4 that should be 8. The audit itself is mechanical -- the challenge is completeness, not complexity.

The critical finding from this research is that the info.json `layouts.LAYOUT` only defines positions for the left half (rows 0-3, 29 keys). It does NOT contain positions for rows 4-7. This is correct for the data-driven QMK LAYOUT system because the data-driven LAYOUT in info.json describes the physical layout of one side (the left), and the keymaps use side-specific macros (`LAYOUT_left` and `LAYOUT_right`) instead. The info.json LAYOUT was explicitly renamed to `LAYOUT_bipedalambi` in the header to avoid conflicting with the data-driven auto-generated LAYOUT. However, the info.json `matrix_pins` defines only 4 row pins, and QMK auto-doubles this to 8 for split boards -- so info.json is consistent with config.h MATRIX_ROWS=8. This is not a disagreement but requires clear documentation.

A secondary finding is that the LAYOUT macros in keymap.c (`LAYOUT_left` and `LAYOUT_right`) both produce 4-row-by-8-column arrays, which represent one half's physical keys. These macros are used inside `keymaps[][MATRIX_ROWS][MATRIX_COLS]` which is dimensioned as `[4][8][8]`. The LAYOUT macros fill only half of this matrix (rows 0-3 for both sides, since the right side is mapped into its own local 4-row space). The full 8-row dimension is the keymaps array dimension (MATRIX_ROWS=8), but each LAYOUT macro populates only 4 rows.

**Primary recommendation:** Build the cross-reference table by reading 6 dimension sources (config.h, info.json matrix_pins, info.json LAYOUT, left vial.json, right vial.json, keymap LAYOUT macros). Flag the 2 known disagreements (both vial.json rows=4 vs expected 8). Document that info.json dimensions are correct (physical pins, auto-doubled by QMK for split). Include the LAYOUT macro row/col spans as confirmatory evidence.

## Standard Stack

This is a documentation/audit phase. No libraries or tools are installed. The "stack" is the set of source files to read and the table format to produce.

### Dimension Sources to Audit

| # | Source | File(s) | What It Declares | How Firmware Uses It |
|---|--------|---------|------------------|---------------------|
| 1 | config.h MATRIX_ROWS | `bipedalambi/config.h` | `#define MATRIX_ROWS 8` | Compiled into firmware; used in EEPROM address calculation |
| 2 | config.h MATRIX_COLS | `bipedalambi/config.h` | `#define MATRIX_COLS 8` | Compiled into firmware; used in EEPROM address calculation |
| 3 | info.json matrix_pins | `bipedalambi/info.json` | 4 row pins, 8 col pins (7 + NO_PIN) | QMK auto-doubles rows for split: 4 x 2 = 8 effective rows |
| 4 | info.json layouts.LAYOUT | `bipedalambi/info.json` | 29 key positions spanning rows 0-3, cols 0-7 | Data-driven LAYOUT macro (left-half only); keymaps use separate macros |
| 5 | Left vial.json | `keymaps/vial_left/vial.json` | `"rows": 4, "cols": 8` | Vial GUI uses for EEPROM layer size calculation |
| 6 | Right vial.json | `keymaps/vial_right/vial.json` | `"rows": 4, "cols": 8` | Vial GUI uses for EEPROM layer size calculation |

### Supporting Files (Confirmatory, Not Primary Sources)

| File | What It Confirms |
|------|-----------------|
| `keymaps/vial_left/keymap.c` LAYOUT_left macro | 4-row x 8-col array (left-half physical keys) |
| `keymaps/vial_right/keymap.c` LAYOUT_right macro | 4-row x 8-col array (right-half physical keys) |
| `keymaps/vial_left/keymap.c` keymaps array | Dimensioned `[4][MATRIX_ROWS][MATRIX_COLS]` = `[4][8][8]` |
| `keymaps/vial_right/keymap.c` keymaps array | Dimensioned `[4][MATRIX_ROWS][MATRIX_COLS]` = `[4][8][8]` |
| `bipedalambi.h` LAYOUT_bipedalambi macro | Identical to LAYOUT_left: 4x8 array for 29 left-half keys |
| `keymaps/vial_left/config.h` MATRIX_ROW_PINS | 4 pins: GP27, GP25, GP18, GP17 |
| `keymaps/vial_right/config.h` MATRIX_ROW_PINS | 4 pins: GP0, GP11, GP25, GP26 |

## Architecture Patterns

### Pattern 1: Cross-Reference Table Structure

**What:** A single table with one column per dimension source and one row per property (MATRIX_ROWS, MATRIX_COLS). Each cell shows the current value, expected value, and match status. Disagreements are flagged with the expected correct value and the source of truth for that correction.

**When to use:** When auditing consistency across multiple configuration files that must agree.

**Template:**

```markdown
| Property | config.h | info.json (effective) | Left vial.json | Right vial.json | LAYOUT macro span | Agreement? | Expected |
|----------|----------|----------------------|----------------|-----------------|-------------------|------------|----------|
| ROWS | 8 | 8 (4 pins x 2) | 4 | 4 | rows 0-3 (per-half) | NO | 8 |
| COLS | 8 | 8 (7+NO_PIN) | 8 | 8 | cols 0-7 | YES | 8 |
```

**Key columns:**
- **config.h**: The firmware's compiled truth. MATRIX_ROWS=8, MATRIX_COLS=8.
- **info.json (effective)**: The physical pin count x 2 for split. QMK computes this automatically.
- **Left/Right vial.json**: What the Vial GUI reads. Must match config.h exactly.
- **LAYOUT macro span**: The row/col range used by the LAYOUT macros. Not a direct "dimension" but confirms what the firmware expects.
- **Agreement?**: YES/NO. If NO, the expected correct value is stated.

### Pattern 2: Disagreement Documentation Format

**What:** Each disagreement is documented with: (a) the two conflicting values, (b) which value is correct and why, (c) the specific file and line/key to change, and (d) the impact of the disagreement.

**Template for each disagreement:**

```markdown
### Disagreement N: [Source A] vs [Source B]

| Aspect | Detail |
|--------|--------|
| Source A | [file]: [property] = [value] |
| Source B | [file]: [property] = [value] |
| Correct value | [value] (from [source of truth]) |
| Why A is wrong / Why B is wrong | [explanation] |
| Impact | [what breaks if not fixed] |
| Fix | Change [file] [property] from [old] to [new] |
| Phase | Phase [N] |
```

### Pattern 3: info.json Dimension Interpretation for Split Boards

**What:** QMK's data-driven configuration reads `matrix_pins.rows` from info.json as the physical pin count per side. For split boards (`"split": {"enabled": true}`), QMK automatically doubles the row count to produce the compiled MATRIX_ROWS. This means info.json declaring 4 row pins is NOT a disagreement with config.h MATRIX_ROWS=8 -- it is the expected input that produces that output.

**Verification chain:**
1. info.json declares 4 row pins
2. info.json declares `"split": {"enabled": true}`
3. QMK build system: effective MATRIX_ROWS = 4 pins x 2 = 8
4. config.h declares MATRIX_ROWS = 8
5. Result: 8 = 8, no disagreement

**Source:** Phase 1 RESEARCH.md Pattern 1 (Split Keyboard Row Doubling Convention), verified from `quantum/matrix.c:29`:
```c
#ifdef SPLIT_KEYBOARD
#    define ROWS_PER_HAND (MATRIX_ROWS / 2)
#endif
```

**This is important to document clearly** because a naive audit would flag "info.json has 4 rows but config.h has 8" as a disagreement. It is not -- it is the expected QMK split behavior.

### Pattern 4: LAYOUT Macro Only Covers One Half

**What:** The info.json `layouts.LAYOUT` defines only the left half's 29 key positions (rows 0-3, cols 0-7). The right half is not included because each half builds independently and uses its own keymap-level LAYOUT macro (`LAYOUT_left` or `LAYOUT_right`).

**Verified by reading info.json:** All 29 matrix positions use rows 0-3. No positions reference rows 4-7.

**Verified by bipedalambi.h comment:** Line 23 says "Renamed to LAYOUT_bipedalambi to avoid QMK data-driven conflict" -- confirming the data-driven LAYOUT exists and the custom macros were renamed to avoid collision.

**This means the LAYOUT macro row span is not a disagreement with the 8-row matrix.** It represents one half's physical layout. The keymaps array is still dimensioned at [8][8] (MATRIX_ROWS x MATRIX_COLS), and the LAYOUT macros fill only their respective 4-row halves.

### Anti-Patterns to Avoid

- **Treating info.json physical pin count as a MATRIX_ROWS disagreement:** info.json pins are inputs to QMK's doubling logic, not the final compiled value.
- **Expecting info.json LAYOUT to span all 8 rows:** The LAYOUT only covers one half. This is correct for a per-half-build split keyboard.
- **Treating LAYOUT macro row span as a "dimension source" equivalent to config.h:** LAYOUT macros define physical key positions, not the matrix size. The matrix size comes from config.h/info.json, not from which positions happen to be used.

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| Extracting matrix positions from info.json | Manual counting | Systematic listing from the JSON structure | info.json has 29 entries; manual counting risks miscounting or missing edge positions |
| Comparing row/col ranges across files | Mental cross-referencing | A single table with all sources side-by-side | The whole point of Phase 2 is this table -- it must be comprehensive and correct |

**Key insight:** The audit is the deliverable. There is no code to write. The risk is not in implementation but in completeness -- missing a dimension source or misinterpreting a value.

## Common Pitfalls

### Pitfall 1: Flagging info.json as a Disagreement with config.h
**What goes wrong:** The auditor sees 4 row pins in info.json and MATRIX_ROWS=8 in config.h and flags this as a disagreement.
**Why it happens:** Without understanding QMK's split auto-doubling, the raw pin count looks like a different value.
**How to avoid:** Document the derivation chain: 4 pins -> split enabled -> x2 -> effective 8. Show this is agreement, not disagreement.
**Warning signs:** If the audit table flags info.json rows as "wrong," the auditor misunderstood the doubling.

### Pitfall 2: Forgetting to Audit the LAYOUT Macro Row/Col Range
**What goes wrong:** The audit covers config.h, info.json dimensions, and vial.json dimensions but omits the LAYOUT macro. The success criteria explicitly require LAYOUT macro row/col counts in the table.
**Why it happens:** LAYOUT macros are in C header/source files, not JSON config files. They're easy to overlook.
**How to avoid:** Include LAYOUT macro spans as a column in the cross-reference table.
**Warning signs:** Success criterion #1 explicitly lists "LAYOUT macro row/col counts."

### Pitfall 3: Treating Left and Right vial.json Identically
**What goes wrong:** The audit notes both vial.json files have rows=4 (wrong) and treats them as a single finding. But the right vial.json has an additional issue: its KLE layout positions use rows 0-3 instead of 4-7.
**Why it happens:** The matrix.rows dimension is the same in both files, so they seem identical.
**How to avoid:** Audit both the `matrix.rows/cols` values AND the KLE layout position row ranges separately for each vial.json.
**Warning signs:** If the audit only flags "rows=4 should be 8" without mentioning the right-half layout position rows, it's incomplete.

### Pitfall 4: Not Explicitly Stating Which Value is Correct for Each Disagreement
**What goes wrong:** The audit flags a disagreement (e.g., "vial.json rows=4 but config.h MATRIX_ROWS=8") but doesn't state which value should change.
**Why it happens:** The disagreement is obvious, but the direction of the fix is assumed rather than stated.
**How to avoid:** Success criterion #2 requires: "Every disagreement between sources is explicitly flagged with the expected correct value (derived from Phase 1 reference)." Always state: "vial.json must change to 8 (matching config.h)" not just "they disagree."
**Warning signs:** Any disagreement entry that lacks a "correct value" and "which file to change" field.

### Pitfall 5: Missing the Right-Half KLE Layout Row Range Issue
**What goes wrong:** The audit documents the matrix dimension mismatch (rows=4 vs 8) but fails to audit the actual row numbers used in the right vial.json KLE layout array.
**Why it happens:** The KLE layout is a dense JSON array of strings like `"0,3"`. Auditing actual row values requires parsing this, not just reading the `matrix.rows` header.
**How to avoid:** Separately audit the row range used in each vial.json's KLE layout positions. For the right vial.json, confirm whether positions use rows 0-3 (wrong for right half) or rows 4-7 (correct for right half).
**Warning signs:** If the cross-reference table has a "LAYOUT macro row/col counts" column but no mention of vial.json KLE position row ranges, the audit is incomplete.

## Code Examples

### info.json LAYOUT Matrix Positions (All 29 -- Left Half Only)

Extracted from `keyboards/hidpress/bipedalambi/info.json` `layouts.LAYOUT.layout`:

```
Row 0: [0,3], [0,2], [0,4], [0,0], [0,1], [0,5], [0,7]  -- 7 positions (col 7 = thumbstick UP)
Row 1: [1,3], [1,2], [1,4], [1,0], [1,1], [1,5], [1,7]  -- 7 positions (col 7 = thumbstick DOWN)
Row 2: [2,3], [2,2], [2,4], [2,0], [2,1], [2,5], [2,6], [2,7]  -- 8 positions (col 6 = key, col 7 = thumbstick LEFT)
Row 3: [3,6], [3,7], [3,3], [3,2], [3,4], [3,1], [3,5]  -- 7 positions (col 6 = key, col 7 = thumbstick RIGHT)
Total: 29 positions
Row range: 0-3 (left half only)
Col range: 0-7
```

### Left vial.json KLE Layout Row Range

Extracted from `keymaps/vial_left/vial.json` `layouts.keymap`:

```
Rows used: 0, 1, 2, 3
Cols used: 0-7
Total key positions: 29
Includes col 7 positions: 0,7 / 1,7 / 2,7 / 3,7 (thumbstick)
```

### Right vial.json KLE Layout Row Range

Extracted from `keymaps/vial_right/vial.json` `layouts.keymap`:

```
Rows used: 0, 1, 2, 3  (WRONG -- should be 4, 5, 6, 7 for right half)
Cols used: 0-6 (no col 7 on right side)
Total key positions: 25
Encoder KLE entries: "0,0\n\n\n\n\n\n\n\n\ne" and "0,1\n\n\n\n\n\n\n\n\ne" (encoder indices, NOT matrix rows)
```

### LAYOUT_left Macro Output Shape

From `keymaps/vial_left/keymap.c` lines 9-27:

```c
#define LAYOUT_left( ... ) { \
    { k00, k01, k02, k03, k04, k05, KC_NO, k07 }, \  // Row 0: 8 cols
    { k10, k11, k12, k13, k14, k15, KC_NO, k17 }, \  // Row 1: 8 cols
    { k20, k21, k22, k23, k24, k25, k26,   k27 }, \  // Row 2: 8 cols
    { KC_NO, k31, k32, k33, k34, k35, k36, k37 }  \  // Row 3: 8 cols
}
// Shape: 4 rows x 8 cols
// Row range: 0-3 (left half)
```

### LAYOUT_right Macro Output Shape

From `keymaps/vial_right/keymap.c` lines 7-25:

```c
#define LAYOUT_right( ... ) { \
    { k00, k01, k02, k03, k04, k05, KC_NO, KC_NO }, \  // Row 0: 8 cols
    { k10, k11, k12, k13, k14, k15, KC_NO, KC_NO }, \  // Row 1: 8 cols
    { k20, k21, k22, k23, k24, k25, k26,   KC_NO }, \  // Row 2: 8 cols
    { KC_NO, k31, k32, k33, k34, k35, k36, KC_NO }  \  // Row 3: 8 cols
}
// Shape: 4 rows x 8 cols
// Row range: 0-3 (local to right half -- NOT the doubled row numbers 4-7)
// The keymaps[][] array is [8][8], and this macro fills the first 4 rows
// The firmware's split logic places this data at the correct offset in the full matrix
```

### keymaps Array Dimension

From both keymap.c files:

```c
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { ... };
// Expands to: keymaps[4][8][8]
// 4 layers, 8 rows (full doubled matrix), 8 columns
```

**Note:** Even though each LAYOUT macro produces a 4x8 array, the keymaps array is dimensioned 8x8. QMK's compiler populates the unused rows with KC_NO (0x0000). This is standard QMK split behavior.

## Detailed Findings

### Finding 1: All 6 Dimension Sources Identified

The Bipedal Ambi has exactly 6 sources of matrix dimension information:

| # | Source | Location | Rows Value | Cols Value | Confidence |
|---|--------|----------|------------|------------|------------|
| 1 | config.h MATRIX_ROWS/COLS | `bipedalambi/config.h:28-29` | 8 | 8 | HIGH -- direct read |
| 2 | info.json matrix_pins | `bipedalambi/info.json:17-34` | 4 pins (effective 8) | 8 pins (7+NO_PIN) | HIGH -- direct read |
| 3 | info.json layouts.LAYOUT | `bipedalambi/info.json:67-307` | rows 0-3 (29 keys) | cols 0-7 | HIGH -- direct read |
| 4 | Left vial.json matrix | `keymaps/vial_left/vial.json:4-7` | 4 | 8 | HIGH -- direct read |
| 5 | Right vial.json matrix | `keymaps/vial_right/vial.json:4-7` | 4 | 8 | HIGH -- direct read |
| 6 | Keymap LAYOUT macros | `keymaps/vial_*/keymap.c` | 4 rows per macro | 8 cols per macro | HIGH -- direct read |

### Finding 2: Exactly 2 Disagreements Exist

**Disagreement 1:** Left vial.json rows (4) vs config.h MATRIX_ROWS (8)
- Correct value: 8 (must match compiled MATRIX_ROWS)
- Impact: Vial computes layer_size = 4*8*2 = 64 bytes; firmware uses 8*8*2 = 128 bytes. Every layer after 0 is addressed at wrong EEPROM offset.
- Fix: Change `keymaps/vial_left/vial.json` `"rows": 4` to `"rows": 8`
- Phase: Phase 3

**Disagreement 2:** Right vial.json rows (4) vs config.h MATRIX_ROWS (8)
- Correct value: 8 (must match compiled MATRIX_ROWS)
- Impact: Same as Disagreement 1
- Fix: Change `keymaps/vial_right/vial.json` `"rows": 4` to `"rows": 8`
- Phase: Phase 3

**Additional issue (not a dimension disagreement but related):** Right vial.json KLE layout positions use rows 0-3 for right-half keys. These should use rows 4-7 to represent the right half of the doubled matrix. This is documented in the cross-reference table's "KLE layout row range" row.

### Finding 3: info.json Dimensions Agree with config.h

The info.json `matrix_pins` declares 4 row pins and 8 col pins. Combined with `"split": {"enabled": true}`, QMK auto-doubles the row count: 4 x 2 = 8. This matches config.h MATRIX_ROWS=8 exactly.

The info.json `layouts.LAYOUT` covers rows 0-3 only (left half). This is correct because:
- The data-driven LAYOUT is for the left half
- The keymaps use per-side LAYOUT macros (LAYOUT_left, LAYOUT_right)
- The bipedalambi.h header explicitly renames its LAYOUT to `LAYOUT_bipedalambi` to avoid data-driven conflict

**Conclusion: info.json dimensions agree with config.h. Requirement MTRX-03 is satisfied -- no fix needed.**

### Finding 4: LAYOUT Macro Dimensions Are Consistent

Both LAYOUT_left and LAYOUT_right macros produce 4-row x 8-col arrays. This is the physical key layout for one half. The keymaps array is dimensioned `[4][MATRIX_ROWS][MATRIX_COLS]` = `[4][8][8]`, and the LAYOUT macros fill the first 4 rows of this 8-row matrix. The remaining 4 rows are implicitly KC_NO.

This is consistent with the split keyboard convention: each half only populates its own rows (0-3 for left, 4-7 for right in the full matrix; but locally each LAYOUT macro indexes 0-3).

## Open Questions

1. **Whether the info.json LAYOUT should eventually include right-half positions (rows 4-7)**
   - What we know: Currently it only has left-half positions. The right-half uses a keymap-level LAYOUT_right macro.
   - What's unclear: Whether QMK's data-driven system expects the full keyboard layout in info.json for split boards, or whether per-half is acceptable.
   - Recommendation: This is out of scope for Phase 2. The current setup compiles and works. Document it as-is in the cross-reference table. If it needs fixing, it would be a future enhancement, not part of this bug fix project.

2. **Whether the "effective rows" from info.json should be shown in the cross-reference table**
   - What we know: info.json declares 4 row pins, but the effective compiled value is 8 (doubled for split).
   - Recommendation: Show both in the table: "4 pins (effective 8 via split doubling)". This prevents the naive misreading described in Pitfall 1.

## Sources

### Primary (HIGH confidence)
- `keyboards/hidpress/bipedalambi/config.h` -- MATRIX_ROWS=8, MATRIX_COLS=8 (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/info.json` -- 4 row pins, 8 col pins, split enabled, 29-key LAYOUT (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/vial.json` -- rows=4, cols=8, KLE rows 0-3 (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json` -- rows=4, cols=8, KLE rows 0-3 (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/keymap.c` -- LAYOUT_left 4x8, keymaps[4][8][8] (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/keymap.c` -- LAYOUT_right 4x8, keymaps[4][8][8] (direct read, 2026-02-14)
- `keyboards/hidpress/bipedalambi/bipedalambi.h` -- LAYOUT_bipedalambi 4x8 (direct read, 2026-02-14)
- Phase 1 deliverables: EXTRACTED-DATA.md, REFERENCE-ANALYSIS.md, FIX-CHECKLIST.md (verified 2026-02-13)

### Secondary (MEDIUM confidence)
- Phase 1 RESEARCH.md -- Pattern 1 (split row doubling), Pattern 2 (vial.json must match MATRIX_ROWS)
- `quantum/matrix.c:29` -- ROWS_PER_HAND = MATRIX_ROWS / 2 (cited in Phase 1, verified from source)

### Tertiary (LOW confidence)
- None

## Metadata

**Confidence breakdown:**
- Dimension source identification: HIGH -- all 6 sources directly read and values extracted
- Disagreement identification: HIGH -- values are unambiguous integers; 4 != 8 is a clear disagreement
- info.json agreement with config.h: HIGH -- QMK split doubling verified in Phase 1 from source code
- LAYOUT macro analysis: HIGH -- macros directly read; output shape is explicit in the C code
- Cross-reference table format: HIGH -- template proven in Phase 1 (EXTRACTED-DATA.md side-by-side tables)

**Research date:** 2026-02-14
**Valid until:** Indefinite (these are static source file values that don't change until someone edits them)
