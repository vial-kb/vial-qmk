---
phase: 04-peripheral-matrix-mapping
verified: 2026-02-14T15:45:00Z
status: passed
score: 5/5 must-haves verified
re_verification: false
---

# Phase 4: Peripheral Matrix Mapping Verification Report

**Phase Goal:** Thumbstick (left half, col 7) and encoder (right half) matrix positions are correctly represented in vial.json

**Verified:** 2026-02-14T15:45:00Z

**Status:** passed

**Re-verification:** No - initial verification

## Goal Achievement

### Observable Truths

| # | Truth | Status | Evidence |
|---|-------|--------|----------|
| 1 | Left vial.json includes thumbstick positions at rows 0-3, col 7 matching matrix_scan_user dynamic_keymap_get_keycode calls | VERIFIED | vial.json lines 111, 151, 153, 191 define "0,7", "1,7", "2,7", "3,7"; keymap.c lines 234-271 call dynamic_keymap_get_keycode with matching (0,7), (1,7), (2,7), (3,7) positions |
| 2 | Right vial.json encoder KLE entries use encoder indices (0,0 and 0,1) not matrix row positions | VERIFIED | vial.json lines 27, 30 define "0,0\n...\ne" and "0,1\n...\ne" using encoder indices, not matrix positions |
| 3 | Right vial.json "encoders" JSON key is preserved with 1 encoder and 4 layers | VERIFIED | vial.json line 33 contains "encoders" key with structure: 1 encoder (length=1), 4 layers (length=4), layer 0 = ["QK_KB_2", "QK_KB_1"] |
| 4 | NUM_ENCODERS is explicitly set to 1, preventing QMK split-doubling from creating phantom encoder | VERIFIED | config.h line 38 contains "#define NUM_ENCODERS 1" in encoder section |
| 5 | Both peripheral mappings are cross-referenced against Sofle rev1 conventions | VERIFIED | SUMMARY.md documents Sofle comparison: Sofle uses ENCODER_MAP_ENABLE with 2 encoders, Ambi uses "encoders" JSON key with 1 encoder (known documented difference from Phase 1) |

**Score:** 5/5 truths verified

### Required Artifacts

| Artifact | Expected | Status | Details |
|----------|----------|--------|---------|
| `bipedalambi/keymaps/vial_right/config.h` | Explicit NUM_ENCODERS 1 define | VERIFIED | Line 38: "#define NUM_ENCODERS 1" present in encoder section after ENCODERS_PAD_B |

**Artifact Verification Breakdown:**
- **Exists:** Yes - file found at expected path
- **Substantive:** Yes - contains required "#define NUM_ENCODERS 1" pattern
- **Wired:** Yes - NUM_ENCODERS used in encoder_map array declaration in keymap.c line 186: `encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS]`

### Key Link Verification

| From | To | Via | Status | Details |
|------|----|----|--------|---------|
| `keymaps/vial_left/vial.json` | `keymaps/vial_left/keymap.c` | thumbstick col 7 positions match dynamic_keymap_get_keycode rows | WIRED | Found 8 dynamic_keymap_get_keycode calls (4 positions x 2 for press/release) at rows 0-3, col 7 matching vial.json "0,7", "1,7", "2,7", "3,7" entries |
| `keymaps/vial_right/config.h` | `quantum/encoder.h` | NUM_ENCODERS define prevents split-doubling calculation | WIRED | NUM_ENCODERS=1 explicitly defined, overriding encoder.h #ifndef guard (line 69); encoder_map in keymap.c uses NUM_ENCODERS in array declaration |

### Requirements Coverage

| Requirement | Status | Supporting Truth | Notes |
|-------------|--------|------------------|-------|
| MTRX-05: Thumbstick matrix positions (left half, col 7, rows 0-3) correctly mapped in left vial.json | SATISFIED | Truth 1 | All 4 thumbstick positions verified in both vial.json and keymap.c |
| MTRX-06: Encoder matrix positions (right half) correctly mapped in right vial.json | SATISFIED | Truths 2, 3, 4 | Encoder KLE entries use indices, "encoders" JSON key preserved, NUM_ENCODERS=1 prevents phantom encoder |

### Anti-Patterns Found

No anti-patterns detected.

| File | Line | Pattern | Severity | Impact |
|------|------|---------|----------|--------|
| - | - | - | - | - |

**Scan Summary:**
- Checked `bipedalambi/keymaps/vial_right/config.h` for TODO/FIXME/placeholders: None found
- Checked for empty implementations: None found
- Checked for console.log-only stubs: Not applicable (C code)

### Human Verification Required

None. All verifications completed programmatically.

### Gap Analysis

No gaps found. All must-haves verified.

---

## Verification Details

### Thumbstick Position Verification (Truth 1)

**Left vial.json entries:**
- Line 111: "0,7" (Up direction)
- Line 151: "2,7" (Left direction)  
- Line 153: "3,7" (Right direction - note: appears as second key in row due to KLE ordering)
- Line 191: "1,7" (Down direction)

**Left keymap.c dynamic_keymap_get_keycode calls:**
- Lines 234, 238: `dynamic_keymap_get_keycode(biton32(layer_state), 0, 7)` - Up press/release
- Lines 245, 249: `dynamic_keymap_get_keycode(biton32(layer_state), 1, 7)` - Down press/release
- Lines 256, 260: `dynamic_keymap_get_keycode(biton32(layer_state), 2, 7)` - Left press/release
- Lines 267, 271: `dynamic_keymap_get_keycode(biton32(layer_state), 3, 7)` - Right press/release

**Result:** Perfect 1:1 mapping between vial.json positions and keymap.c references.

### Encoder KLE Verification (Truth 2)

**Right vial.json encoder entries:**
- Line 27: `"0,0\n\n\n\n\n\n\n\n\ne"` (CCW - encoder index 0, direction 0)
- Line 30: `"0,1\n\n\n\n\n\n\n\n\ne"` (CW - encoder index 0, direction 1)

**Format analysis:**
- Uses encoder index notation `0,0` and `0,1` (not matrix row positions like `4,0` or `5,0`)
- Includes `\ne` suffix indicating encoder type
- Both entries on encoder index 0 with different direction indices

**Result:** Encoder KLE entries correctly use encoder indices, not matrix positions. No references to rows 4-7 which would indicate incorrect Phase 3 remapping.

### Encoders JSON Key Verification (Truth 3)

**Right vial.json structure:**
```json
"encoders": [
    [
        ["QK_KB_2", "QK_KB_1"],  // Layer 0: CCW=CL_BWD, CW=CL_FWD
        ["KC_TRNS", "KC_TRNS"],  // Layer 1: transparent
        ["KC_TRNS", "KC_TRNS"],  // Layer 2: transparent  
        ["KC_TRNS", "KC_TRNS"]   // Layer 3: transparent
    ]
]
```

**Verification:**
- Outer array length: 1 (1 encoder)
- Inner array length: 4 (4 layers)
- Layer 0 mapping: ["QK_KB_2", "QK_KB_1"] matches encoder_map in keymap.c line 187: `ENCODER_CCW_CW(CL_BWD, CL_FWD)` where CL_BWD=QK_KB_2 and CL_FWD=QK_KB_1 from enum order

**Result:** "encoders" JSON key preserved correctly with expected structure.

### NUM_ENCODERS Verification (Truth 4)

**Right config.h encoder section (lines 34-38):**
```c
// RIGHT Encoder (GP28 A, GP29 B)
#define ENCODERS_PAD_A { GP28 }
#define ENCODERS_PAD_B { GP29 }
#define ENCODER_RESOLUTION 4
#define NUM_ENCODERS 1
```

**Right keymap.c encoder usage:**
```c
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(CL_BWD, CL_FWD) },
    // ... layers 1-3
};
#endif
```

**Impact analysis:**
- Prevents QMK encoder.h split-doubling logic (which would set NUM_ENCODERS=2)
- encoder_map array has 1 entry per layer (matching NUM_ENCODERS=1)
- Reduces VIAL_ENCODERS_SIZE from 32 to 16 bytes
- EEPROM layout shift covered by Phase 7 mandatory clear

**Result:** NUM_ENCODERS=1 correctly defined and wired to encoder_map.

### Sofle Cross-Reference Verification (Truth 5)

**From SUMMARY.md:**
> Documented Sofle cross-reference: Sofle uses ENCODER_MAP_ENABLE with 2 encoders vs Ambi's "encoders" JSON key with 1 encoder (known documented difference)

**Comparison:**
- **Sofle rev1:** 2 encoders (one per half), ENCODER_MAP_ENABLE, 4 KLE encoder entries
- **Ambi:** 1 encoder (right half only), "encoders" JSON key, 2 KLE encoder entries
- **Common format:** Both use `\ne` suffix in KLE entries

**Assessment:** Difference in encoder configuration approach is a known documented difference from Phase 1 research, not a bug. The "encoders" JSON key approach is valid for Vial (though undocumented).

**Result:** Cross-reference documented and differences explained.

---

## Commit Verification

**Task 2 commit:** `1bc7df4b60`

**Commit message:**
```
fix(04-01): set NUM_ENCODERS 1 to prevent split-doubling phantom encoder

- Add #define NUM_ENCODERS 1 to right config.h encoder section
- Prevents QMK encoder.h from doubling to NUM_ENCODERS=2 via split logic
- Reduces VIAL_ENCODERS_SIZE from 32 to 16 bytes (eliminates phantom encoder EEPROM)
- encoder_map already has 1 entry per layer, matching NUM_ENCODERS=1
```

**Files modified:** `keyboards/hidpress/bipedalambi/keymaps/vial_right/config.h` (+1 line)

**Verification:** Commit exists, modifies expected file, adds required line.

---

## Overall Assessment

**Status: PASSED**

All 5 must-have truths verified against the actual codebase. All artifacts exist, are substantive (contain required patterns), and are wired (actively used in code). All key links verified. Both requirements (MTRX-05, MTRX-06) satisfied.

**Key Findings:**
1. Thumbstick positions perfectly aligned between vial.json and keymap.c
2. Encoder KLE entries correctly use encoder indices, not matrix positions
3. "encoders" JSON key preserved with correct structure
4. NUM_ENCODERS=1 correctly prevents split-doubling phantom encoder
5. Sofle cross-reference documented, differences explained

**No gaps identified. Phase goal achieved.**

---

_Verified: 2026-02-14T15:45:00Z_
_Verifier: Claude (gsd-verifier)_
