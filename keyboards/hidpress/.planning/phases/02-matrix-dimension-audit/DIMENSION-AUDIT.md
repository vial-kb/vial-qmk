# Matrix Dimension Cross-Reference Audit

**Date:** 2026-02-14
**Phase:** 02 - Matrix Dimension Audit
**Purpose:** Cross-reference all 6 sources of matrix dimension information in the Bipedal Ambi firmware, flag all disagreements with the expected correct value, and confirm info.json agreement with config.h.

**Source documents:**
- `.planning/phases/02-matrix-dimension-audit/02-RESEARCH.md` -- research and methodology
- `.planning/phases/01-reference-analysis/FIX-CHECKLIST.md` -- Phase 2 fix items derived from Phase 1

---

## Section 1: Cross-Reference Table

All values extracted directly from source files on 2026-02-14 with line-number citations.

### Dimension Sources Legend

| Column | Source File | What It Declares |
|--------|-----------|------------------|
| config.h | `bipedalambi/config.h` | Compiled firmware matrix size |
| info.json (effective) | `bipedalambi/info.json` | Physical pin count, auto-doubled for split |
| Left vial.json | `keymaps/vial_left/vial.json` | Vial GUI matrix dimensions (left half) |
| Right vial.json | `keymaps/vial_right/vial.json` | Vial GUI matrix dimensions (right half) |
| LAYOUT macro span | `keymaps/vial_*/keymap.c`, `bipedalambi.h` | Physical key positions per macro |

### Cross-Reference Table

| Property | config.h | info.json (effective) | Left vial.json | Right vial.json | LAYOUT macro span | Agreement? | Expected |
|----------|----------|----------------------|----------------|-----------------|-------------------|------------|----------|
| **MATRIX_ROWS** | **8** (line 28: `#define MATRIX_ROWS 8`) | **8** (4 pins x 2 split) (lines 18-23: 4 row pins; line 14: `split.enabled=true`) | **4** (line 5: `"rows": 4`) | **4** (line 5: `"rows": 4`) | 4 rows per macro (left: lines 23-27; right: lines 21-25) | **NO** -- both vial.json disagree with config.h | **8** |
| **MATRIX_COLS** | **8** (line 29: `#define MATRIX_COLS 8`) | **8** (7 real + NO_PIN) (lines 24-33: 8 col pins) | **8** (line 6: `"cols": 8`) | **8** (line 6: `"cols": 8`) | 8 cols per macro (all macros output 8-element rows) | **YES** | **8** |
| **KLE layout row range** | N/A | rows 0-3 (info.json LAYOUT: lines 68-305, 29 positions all in rows 0-3) | rows 0-3 (KLE positions: lines 46-193) | rows 0-3 (KLE positions: lines 18-31) -- **WRONG** for right half | rows 0-3 per macro (local to each half) | **PARTIAL** -- right vial.json should use rows 4-7 | Left: 0-3, Right: 4-7 |
| **KLE layout col range** | N/A | cols 0-7 (all 8 columns used including col 7 thumbstick) | cols 0-7 (includes col 7: thumbstick positions 0,7 / 1,7 / 2,7 / 3,7) | cols 0-6 (no col 7 -- right side has no thumbstick) | Left: cols 0-7; Right: cols 0-6 | **YES** (right has no col 7 = no thumbstick, correct) | Left: 0-7, Right: 0-6 |
| **Key position count** | N/A | 29 (left half only, info.json LAYOUT) | 29 (KLE layout) | 25 keys + 2 encoder entries (KLE layout) | Left: 29 keys; Right: 25 keys | **YES** | Left: 29, Right: 25 |

### Citation Details

**config.h** (`keyboards/hidpress/bipedalambi/config.h`):
- Line 28: `#define MATRIX_ROWS 8  // 4 rows per hand * 2 hands`
- Line 29: `#define MATRIX_COLS 8  // Increased to 8 to support virtual Joystick columns (Col 7)`

**info.json** (`keyboards/hidpress/bipedalambi/info.json`):
- Lines 18-23: `matrix_pins.rows` = `["GP27", "GP25", "GP18", "GP17"]` (4 pins)
- Lines 24-33: `matrix_pins.cols` = `["GP24", "GP23", "GP21", "GP20", "GP19", "GP26", "GP16", "NO_PIN"]` (8 pins: 7 real + 1 NO_PIN)
- Lines 13-15: `"split": {"enabled": true}`
- Lines 67-307: `layouts.LAYOUT.layout` = 29 key positions, all in rows 0-3, cols 0-7

**Left vial.json** (`keyboards/hidpress/bipedalambi/keymaps/vial_left/vial.json`):
- Line 5: `"rows": 4`
- Line 6: `"cols": 8`
- Lines 46-193: KLE layout with 29 key positions using rows 0-3, cols 0-7

**Right vial.json** (`keyboards/hidpress/bipedalambi/keymaps/vial_right/vial.json`):
- Line 5: `"rows": 4`
- Line 6: `"cols": 8`
- Lines 18-31: KLE layout with 25 key positions using rows 0-3 (should be 4-7), cols 0-6
- Line 27: Encoder entry `"0,0\n\n\n\n\n\n\n\n\ne"` (encoder index 0, CW)
- Line 31: Encoder entry `"0,1\n\n\n\n\n\n\n\n\ne"` (encoder index 1, CCW)

**Left keymap.c** (`keyboards/hidpress/bipedalambi/keymaps/vial_left/keymap.c`):
- Lines 9-27: `LAYOUT_left` macro outputs 4 rows x 8 cols
- Line 99: `keymaps[][MATRIX_ROWS][MATRIX_COLS]` expands to `keymaps[4][8][8]`

**Right keymap.c** (`keyboards/hidpress/bipedalambi/keymaps/vial_right/keymap.c`):
- Lines 7-25: `LAYOUT_right` macro outputs 4 rows x 8 cols
- Line 87: `keymaps[][MATRIX_ROWS][MATRIX_COLS]` expands to `keymaps[4][8][8]`

**bipedalambi.h** (`keyboards/hidpress/bipedalambi/bipedalambi.h`):
- Lines 24-42: `LAYOUT_bipedalambi` macro outputs 4 rows x 8 cols (identical to LAYOUT_left)
- Line 23: Comment confirms rename: "Renamed to LAYOUT_bipedalambi to avoid QMK data-driven conflict"

---

## Section 2: Disagreement Documentation

### Disagreement 1: Both vial.json `matrix.rows=4` vs config.h `MATRIX_ROWS=8`

| Aspect | Detail |
|--------|--------|
| **Source A** | `keymaps/vial_left/vial.json` line 5: `"rows": 4` |
| **Source B** | `keymaps/vial_right/vial.json` line 5: `"rows": 4` |
| **Source of truth** | `bipedalambi/config.h` line 28: `#define MATRIX_ROWS 8` |
| **Correct value** | **8** (both vial.json files must change from 4 to 8) |
| **Why it's wrong** | Split keyboard `MATRIX_ROWS = physical_rows_per_side x 2`. Vial uses this to compute `layer_size = rows * cols * 2 bytes`. With rows=4: layer_size=64 bytes. With rows=8: layer_size=128 bytes. The firmware allocates 128 bytes per layer (using the correct MATRIX_ROWS=8), so Vial reads layer 1 at byte offset 64 while firmware wrote it at byte offset 128. |
| **Impact** | Every layer after layer 0 is addressed at the wrong EEPROM offset. This is the root cause of the layer shift bug: keycodes set in Vial for layers 1-3 are written to incorrect EEPROM addresses, so they do not persist correctly across power cycles. |
| **Fix** | Change both `vial.json` files: `"rows": 4` to `"rows": 8` |
| **Phase** | Phase 3 (vial.json dimension fix) |

### Disagreement 2: Right vial.json KLE layout uses rows 0-3 instead of rows 4-7

| Aspect | Detail |
|--------|--------|
| **Source** | `keymaps/vial_right/vial.json` lines 18-31: KLE layout key positions |
| **Current value** | All 25 key positions use rows 0-3 (e.g., "0,3", "1,4", "2,6", "3,3") |
| **Expected value** | Right-half keys should reference rows 4-7 (e.g., "4,3", "5,4", "6,6", "7,3") |
| **Why it's wrong** | The split keyboard's right half occupies the second half of the matrix (rows 4-7, computed as `ROWS_PER_HAND` + local row). When Vial sends a key assignment for "row 0, col 0" it targets the left half's matrix position, not the right half's. For the right half, Vial must reference the globally-offset row numbers (4-7). |
| **Impact** | Right-half key assignments in Vial may be written to wrong EEPROM positions, mapping to left-half matrix slots instead of right-half matrix slots. |
| **Fix** | Remap all 25 right-half key positions from rows 0-3 to rows 4-7 (add 4 to each row number) |
| **Phase** | Phase 3 (right vial.json KLE layout row remapping) |
| **Note** | Encoder KLE entries (`"0,0\n\n\n\n\n\n\n\n\ne"` and `"0,1\n\n\n\n\n\n\n\n\ne"`) use **encoder indices**, NOT matrix rows. These must **NOT** be remapped. The `\ne` suffix marks them as encoder entries. |

---

## Section 3: info.json Agreement Confirmation (MTRX-03)

### Verification Chain

| Step | Source | Value | Derivation |
|------|--------|-------|------------|
| 1 | `info.json` lines 18-23 | 4 physical row pins | `matrix_pins.rows = ["GP27", "GP25", "GP18", "GP17"]` |
| 2 | `info.json` lines 13-15 | split enabled | `"split": {"enabled": true}` |
| 3 | QMK build system | 4 x 2 = 8 effective rows | Auto-doubling for split boards (`quantum/matrix.c:29`: `ROWS_PER_HAND = MATRIX_ROWS / 2`) |
| 4 | `config.h` line 28 | MATRIX_ROWS = 8 | `#define MATRIX_ROWS 8` |
| 5 | Comparison | 8 = 8 | info.json effective rows match config.h MATRIX_ROWS |

**Result:** info.json dimensions **agree** with config.h. No fix needed for info.json.

**Conclusion:** Requirement **MTRX-03** is **SATISFIED** -- info.json matrix dimensions are confirmed as agreeing with config.h via QMK split auto-doubling.

### Additional Notes on info.json layouts.LAYOUT

The info.json `layouts.LAYOUT` defines only the left half's 29 key positions (rows 0-3, cols 0-7). This is correct because:

1. The data-driven `LAYOUT` macro in info.json represents one side's physical layout
2. Each half builds independently and uses its own keymap-level LAYOUT macro (`LAYOUT_left` in the left keymap, `LAYOUT_right` in the right keymap)
3. The `bipedalambi.h` header explicitly renames its shared LAYOUT to `LAYOUT_bipedalambi` (line 23: "Renamed to LAYOUT_bipedalambi to avoid QMK data-driven conflict")

The info.json LAYOUT spanning only rows 0-3 is **not** a disagreement with the 8-row matrix. It correctly represents one half's physical key positions.

---

## Section 4: Requirement Satisfaction

| Requirement | Status | Evidence |
|-------------|--------|----------|
| **XVAL-01** | **SATISFIED** | Cross-reference table created (Section 1) showing all 6 dimension sources -- config.h MATRIX_ROWS, config.h MATRIX_COLS, info.json dimensions (with effective split-doubled value), left vial.json rows/cols, right vial.json rows/cols, and LAYOUT macro row/col spans -- with agreement status for each property |
| **MTRX-03** | **SATISFIED** | info.json dimensions confirmed as agreeing with config.h via split auto-doubling chain: 4 pins x 2 (split) = 8 effective = config.h MATRIX_ROWS=8 (Section 3) |

### Summary of Findings

- **2 disagreements found** (Section 2): both vial.json `rows=4` (should be 8), and right vial.json KLE rows 0-3 (should be 4-7)
- **0 unexpected findings**: all extracted values match 02-RESEARCH.md predictions exactly
- **info.json confirmed correct**: no fix needed (MTRX-03 satisfied)
- **All fixes deferred to Phase 3**: this audit documents what needs fixing; Phase 3 implements the fixes
