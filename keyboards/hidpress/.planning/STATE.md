# Project State

## Project Reference

See: .planning/PROJECT.md (updated 2026-02-14)

**Core value:** Keycodes set in Vial must persist correctly across power cycles and map to the correct layers
**Current focus:** v1.0 milestone complete — bug fixed and verified

## Current Position

Phase: 8 of 8 (End-to-End Verification) -- COMPLETE
Plan: 2 of 2 in current phase -- COMPLETE
Status: All 8 phases complete -- Vial layer offset bug confirmed fixed
Last activity: 2026-02-14 -- User verified both halves working correctly in Vial GUI

Progress: [██████████] 100%

## Performance Metrics

**Velocity:**
- Total plans completed: 10
- Average duration: 2.2min
- Total execution time: 0.37 hours

**By Phase:**

| Phase | Plans | Total | Avg/Plan |
|-------|-------|-------|----------|
| 01-reference-analysis | 3/3 | 8min | 2.7min |
| 02-matrix-dimension-audit | 1/1 | 2min | 2min |
| 03-vialjson-matrix-fix | 1/1 | 2min | 2min |
| 04-peripheral-matrix-mapping | 1/1 | 2min | 2min |
| 05-eeprom-budget-verification | 1/1 | 3min | 3min |
| 06-defensive-eeprom-improvements | 1/1 | 2min | 2min |
| 07-build-and-flash | 2/2 | 4min | 2min |

**Recent Trend:**
- Last 5 plans: 05-01 (3min), 06-01 (2min), 07-01 (2min), 07-02 (2min)
- Trend: Stable ~2.2min/plan

*Updated after each plan completion*

## Accumulated Context

### Decisions

Decisions are logged in PROJECT.md Key Decisions table.
Recent decisions affecting current work:

- [Roadmap]: Root cause confirmed as vial.json rows=4 vs config.h MATRIX_ROWS=8 -- fix is mechanical
- [Roadmap]: EEPROM collision hypothesis (Issue B) ruled out -- eeconfig_user does NOT collide with Vial
- [Roadmap]: Sofle rev1 Vial keymap chosen as known-working reference for split row-doubling convention
- [01-01]: All 19 research claims verified against source files -- no discrepancies
- [01-01]: Encoder KLE entries documented separately from key positions to prevent row-number confusion
- [01-02]: Encoder KLE entries use encoder indices not matrix rows -- must NOT be adjusted during row remapping
- [01-02]: Ambi uses "encoders" JSON key (different from Sofle ENCODER_MAP_ENABLE) -- needs Phase 4 investigation
- [01-02]: EEPROM layer offset proven: Vial writes layer 1 at byte 64, firmware reads at byte 128
- [01-03]: FIX-CHECKLIST.md covers all 15 requirements across 8 phases with specific file paths, values, and citations
- [01-03]: Phase 7-8 items annotated as physical user actions (Claude cannot flash or test hardware)
- [01-03]: Phase 1 complete -- all 4 ROADMAP success criteria satisfied
- [02-01]: info.json 4 row pins confirmed correct via QMK split auto-doubling -- no fix needed (MTRX-03 satisfied)
- [02-01]: Right vial.json KLE row range (0-3 instead of 4-7) documented as separate disagreement from matrix.rows=4 issue
- [02-01]: Encoder KLE entries confirmed as encoder indices, not matrix rows -- must not be remapped in Phase 3
- [03-01]: Left KLE positions unchanged (rows 0-3 correct for left half)
- [03-01]: Right KLE positions remapped +4 rows (0-3 to 4-7) per split convention
- [03-01]: Encoder KLE entries preserved as encoder indices, not matrix rows
- [04-01]: NUM_ENCODERS=1 set explicitly to override QMK split-doubling (encoder.h #ifndef guard)
- [04-01]: Preserved undocumented "encoders" JSON key in right vial.json (risk of removal outweighs benefit)
- [04-01]: No vial.json modifications needed -- all peripheral positions survived Phase 3 correctly
- [05-01]: All addresses verified against vial-qmk fork source files, not upstream QMK docs (XVAL-02)
- [05-01]: eeconfig_user (bytes 19-22) confirmed 13 bytes away from VIA magic (byte 36) -- no collision possible
- [05-01]: Right half uses 568 bytes fixed (13.9% of 4096), left half uses 552 bytes (13.5%)
- [06-01]: Left EE_CLR at k17 (KC_DOWN position), right EE_CLR at k35 (KC_EQL position) -- k31 avoided because it is MO(1) itself
- [06-01]: Default value 0x200 = actuation_index=2 (middle sensitivity) + all layers MODE_MOUSE
- [06-01]: eeconfig_init_user writes hardcoded constant matching save function encoding -- never call load from init
- [07-01]: Pre-existing SERIAL_PIO_USE_PIO1 and UART0/UART1 config committed as-is -- hardware config from before Phase 1
- [07-02]: Right half vial.json KLE positions reverted from rows 4-7 to rows 0-3 -- standalone halves scan rows 0-3
- [07-02]: Phase 3 row remapping was incorrect for standalone split halves -- KLE must match firmware matrix scanning

### Pending Todos

None yet.

### Blockers/Concerns

- Both halves must be cleared and flashed independently (user has physical access to both boards)
- Phase 7 and 8 require physical keyboard interaction by the user (Claude cannot flash or test hardware)

## Session Continuity

Last session: 2026-02-14
Stopped at: All phases complete -- milestone done
Resume file: None
