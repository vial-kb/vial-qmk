---
phase: 04-peripheral-matrix-mapping
plan: 01
subsystem: firmware-config
tags: [encoder, thumbstick, vial-json, num-encoders, qmk-split, eeprom]

# Dependency graph
requires:
  - phase: 03-vialjson-matrix-fix
    provides: "Correct 8-row vial.json with right KLE rows 4-7 and preserved encoder entries"
provides:
  - "Verified thumbstick positions (0,7)-(3,7) match matrix_scan_user (MTRX-05)"
  - "Verified encoder KLE entries use encoder indices not matrix rows (MTRX-06)"
  - "NUM_ENCODERS=1 in right config.h preventing split-doubling phantom encoder"
  - "Sofle cross-reference documented for encoder configuration differences"
affects: [07-flash-eeprom-clear]

# Tech tracking
tech-stack:
  added: []
  patterns: ["Explicit NUM_ENCODERS override to prevent QMK split-doubling"]

key-files:
  created: []
  modified: ["bipedalambi/keymaps/vial_right/config.h"]

key-decisions:
  - "Set NUM_ENCODERS=1 explicitly to override QMK split-doubling (encoder.h #ifndef guard)"
  - "Preserved undocumented 'encoders' JSON key in right vial.json (risk of removal outweighs benefit)"
  - "No vial.json modifications needed -- all peripheral positions survived Phase 3 correctly"

patterns-established:
  - "NUM_ENCODERS explicit define: prevents QMK from auto-calculating incorrect encoder count for asymmetric split keyboards"

# Metrics
duration: 2min
completed: 2026-02-14
---

# Phase 4 Plan 1: Peripheral Matrix Mapping Summary

**Thumbstick col-7 positions and encoder KLE entries verified correct; NUM_ENCODERS set to 1 to fix split-doubling phantom encoder**

## Performance

- **Duration:** 2 min
- **Started:** 2026-02-14T04:30:22Z
- **Completed:** 2026-02-14T04:31:54Z
- **Tasks:** 2
- **Files modified:** 1

## Accomplishments
- Verified all 4 thumbstick positions (rows 0-3, col 7) in left vial.json match matrix_scan_user dynamic_keymap_get_keycode calls (MTRX-05 satisfied)
- Verified encoder KLE entries use encoder indices (0,0 and 0,1) not matrix row positions, correctly preserved during Phase 3 row remapping (MTRX-06 partial)
- Confirmed "encoders" JSON key preserved with 1 encoder, 4 layers, layer 0 matching encoder_map defaults
- Fixed NUM_ENCODERS split-doubling: added `#define NUM_ENCODERS 1` to right config.h, reducing VIAL_ENCODERS_SIZE from 32 to 16 bytes (MTRX-06 complete)
- Documented Sofle cross-reference: Sofle uses ENCODER_MAP_ENABLE with 2 encoders vs Ambi's "encoders" JSON key with 1 encoder (known documented difference)

## Task Commits

Each task was committed atomically:

1. **Task 1: Verify thumbstick and encoder positions with cross-reference validation** - no commit (read-only verification, no files modified)
2. **Task 2: Fix NUM_ENCODERS split-doubling mismatch in right config.h** - `1bc7df4b60` (fix)

**Plan metadata:** `edfc62d8f2` (docs: complete peripheral matrix mapping plan)

## Files Created/Modified
- `bipedalambi/keymaps/vial_right/config.h` - Added `#define NUM_ENCODERS 1` after encoder pin defines to prevent QMK split-doubling

## Verification Results

All 5 validation scripts passed:

| Validation | Result | Details |
|-----------|--------|---------|
| 1. Thumbstick positions (MTRX-05) | PASSED | Col 7 entries at rows 0-3 confirmed in left vial.json |
| 2. Encoder KLE entries (MTRX-06) | PASSED | Entries use encoder indices 0,0 and 0,1 (not matrix rows) |
| 3. Encoders JSON key preservation | PASSED | 1 encoder, 4 layers, layer 0 = [QK_KB_2, QK_KB_1] |
| 4. Cross-reference thumbstick vs keymap.c | PASSED | 8 dynamic_keymap_get_keycode calls at col 7, rows 0-3 |
| 5. Encoder matrix bounds check | PASSED | Encoder references use indices, not matrix positions |

Additional verifications:
- Left vial.json: UNCHANGED from Phase 3 (confirmed via git diff)
- Right vial.json: UNCHANGED from Phase 3 (confirmed via git diff)
- `grep 'NUM_ENCODERS' config.h` returns `#define NUM_ENCODERS 1`

## Decisions Made
- **NUM_ENCODERS=1 via explicit define:** Chose `#define NUM_ENCODERS 1` over `#define NUM_ENCODERS_RIGHT 0` because it directly overrides the split-doubling calculation via the `#ifndef NUM_ENCODERS` guard in encoder.h (line 69), is simpler, and matches the physical hardware (1 encoder on right side only)
- **Preserve "encoders" JSON key:** Despite being undocumented and absent from Sofle reference, preserved it to avoid breaking Vial GUI encoder display. Cost is negligible (few bytes of compressed JSON)
- **No vial.json changes:** Both vial.json files confirmed correct as-is from Phase 3 output

## Deviations from Plan

None - plan executed exactly as written.

## Issues Encountered

None.

## User Setup Required

None - no external service configuration required.

## EEPROM Impact Note

Changing NUM_ENCODERS from 2 to 1 shifts the EEPROM layout after the encoder region (VIAL_ENCODERS_SIZE: 32 -> 16 bytes). This is already covered by Phase 7's mandatory EEPROM clear, which was planned for the Phase 3 matrix dimension change. No additional user action required beyond what Phase 7 already specifies.

## Next Phase Readiness
- MTRX-05 (thumbstick positions) fully satisfied
- MTRX-06 (encoder positions) fully satisfied
- Ready for Phase 5 (dynamic keymap EEPROM audit)
- EEPROM clear still required in Phase 7 (now covers both matrix dimension change and NUM_ENCODERS change)

## Self-Check: PASSED

- FOUND: bipedalambi/keymaps/vial_right/config.h
- FOUND: .planning/phases/04-peripheral-matrix-mapping/04-01-SUMMARY.md
- FOUND: 1bc7df4b60 (Task 2 commit)
- VERIFIED: NUM_ENCODERS 1 in config.h

---
*Phase: 04-peripheral-matrix-mapping*
*Completed: 2026-02-14*
