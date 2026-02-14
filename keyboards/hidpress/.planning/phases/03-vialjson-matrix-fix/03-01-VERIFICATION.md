---
phase: 03-vialjson-matrix-fix
plan: 01
verified: 2026-02-14T04:15:00Z
status: passed
score: 6/6 must-haves verified
---

# Phase 3: vial.json Matrix Fix Verification Report

**Phase Goal:** Both vial.json files declare rows=8 to match config.h MATRIX_ROWS, and the right-half layout positions reference rows 4-7

**Verified:** 2026-02-14T04:15:00Z
**Status:** PASSED
**Re-verification:** No — initial verification

## Goal Achievement

### Observable Truths

| # | Truth | Status | Evidence |
|---|-------|--------|----------|
| 1 | Left vial.json declares rows=8 and cols=8, matching config.h MATRIX_ROWS=8 and MATRIX_COLS=8 | ✓ VERIFIED | `bipedalambi/keymaps/vial_left/vial.json` line 5: `"rows": 8`, line 6: `"cols": 8`. config.h MATRIX_ROWS=8 confirmed. |
| 2 | Right vial.json declares rows=8 and cols=8, matching config.h MATRIX_ROWS=8 and MATRIX_COLS=8 | ✓ VERIFIED | `bipedalambi/keymaps/vial_right/vial.json` line 5: `"rows": 8`, line 6: `"cols": 8`. config.h MATRIX_ROWS=8 confirmed. |
| 3 | Right vial.json layout positions use rows 4-7 for all 25 key positions | ✓ VERIFIED | Validation script confirmed 25 keys on rows [4, 5, 6, 7]. No keys on rows 0-3 (except encoder entries which use encoder indices). |
| 4 | Left vial.json layout positions remain on rows 0-3 (unchanged) | ✓ VERIFIED | Validation script confirmed 29 keys on rows [0, 1, 2, 3]. No keys on rows 4-7. |
| 5 | Encoder KLE entries in right vial.json are untouched (still 0,0 and 0,1 with \ne suffix) | ✓ VERIFIED | Validation script confirmed 2 encoder entries ['0,0', '0,1'] with \ne suffix preserved. These use encoder indices, not matrix rows. |
| 6 | The encoders JSON key in right vial.json is preserved unchanged | ✓ VERIFIED | `"encoders"` JSON key present in right vial.json with 1 encoder configured across 4 layers. |

**Score:** 6/6 truths verified

### Required Artifacts

| Artifact | Expected | Status | Details |
|----------|----------|--------|---------|
| `bipedalambi/keymaps/vial_left/vial.json` | Left-half Vial config with corrected matrix dimensions | ✓ VERIFIED | File exists (195 lines). Contains `"rows": 8` on line 5. Valid JSON. 29 key positions on rows 0-3. |
| `bipedalambi/keymaps/vial_right/vial.json` | Right-half Vial config with corrected matrix dimensions and remapped KLE positions | ✓ VERIFIED | File exists (42 lines). Contains `"rows": 8` on line 5. Valid JSON. 25 key positions on rows 4-7. Encoder entries preserved. |

### Key Link Verification

| From | To | Via | Status | Details |
|------|----|----|--------|---------|
| `bipedalambi/keymaps/vial_left/vial.json` | `bipedalambi/config.h` | matrix.rows must equal MATRIX_ROWS | ✓ WIRED | Left vial.json `"rows": 8` matches config.h `#define MATRIX_ROWS 8` |
| `bipedalambi/keymaps/vial_right/vial.json` | `bipedalambi/config.h` | matrix.rows must equal MATRIX_ROWS | ✓ WIRED | Right vial.json `"rows": 8` matches config.h `#define MATRIX_ROWS 8` |
| `bipedalambi/keymaps/vial_right/vial.json` KLE positions | split keyboard convention | right-half keys use rows ROWS_PER_HAND to MATRIX_ROWS-1 | ✓ WIRED | All 25 key positions use rows 4-7 (ROWS_PER_HAND=4 to MATRIX_ROWS-1=7). Split keyboard convention confirmed in Phase 1 reference analysis. |

### Requirements Coverage

| Requirement | Status | Blocking Issue |
|-------------|--------|----------------|
| MTRX-01: vial.json matrix rows match config.h MATRIX_ROWS value (rows=8 for both halves) | ✓ SATISFIED | None — both vial.json files declare rows=8 matching config.h MATRIX_ROWS=8 |
| MTRX-02: Right-side vial.json layout positions use rows 4-7 for the right half's keys | ✓ SATISFIED | None — all 25 key positions use rows 4-7 as required |

### Anti-Patterns Found

None detected.

Scanned files:
- `bipedalambi/keymaps/vial_left/vial.json` — Clean
- `bipedalambi/keymaps/vial_right/vial.json` — Clean

No TODO/FIXME/PLACEHOLDER comments found. No empty implementations. Both files are valid JSON with substantive content.

### Commit Verification

Both commits from SUMMARY.md exist in git history:

1. `3f2c4b00e4` - Task 1: Fix matrix dimensions in left vial.json
2. `8e5205ed81` - Task 2: Fix matrix dimensions and remap KLE positions in right vial.json

### Validation Script Results

**Left vial.json:**
```
Left vial.json: rows=8, cols=8
Left key positions: 29 keys on rows [0, 1, 2, 3]
Left vial.json: VERIFIED ✓
```

**Right vial.json:**
```
Right vial.json: rows=8, cols=8
Right key positions: 25 keys on rows [4, 5, 6, 7]
Right encoder entries: ['0,0', '0,1']
Encoders JSON key present: True
Right vial.json: VERIFIED ✓
```

### Success Criteria Assessment

All success criteria from ROADMAP.md Phase 3 are satisfied:

1. ✓ Left vial.json declares "rows": 8 and "cols": 8, matching config.h MATRIX_ROWS=8 and MATRIX_COLS=8
2. ✓ Right vial.json declares "rows": 8 and "cols": 8, matching config.h
3. ✓ Right vial.json layout positions use rows 4-7 (not 0-3) for the right half's physical keys, following the split keyboard convention confirmed in Phase 1
4. ✓ Left vial.json layout positions remain on rows 0-3 for the left half's physical keys

## Summary

**Phase 3 goal ACHIEVED.** Both vial.json files have been corrected to match config.h MATRIX_ROWS=8. The right-half layout positions have been successfully remapped from rows 0-3 to rows 4-7, following the split keyboard convention established in Phase 1. Encoder entries and configuration are preserved. All requirements satisfied. No gaps found.

The fix resolves the root cause of the EEPROM layer offset bug — Vial will now calculate EEPROM offsets based on the correct 8-row matrix (not 4-row), eliminating layer content misalignment.

**Ready to proceed to Phase 4 (Peripheral Matrix Mapping).**

---

_Verified: 2026-02-14T04:15:00Z_
_Verifier: Claude (gsd-verifier)_
