# Project State

## Project Reference

See: .planning/PROJECT.md (updated 2026-02-13)

**Core value:** Keycodes set in Vial must persist correctly across power cycles and map to the correct layers
**Current focus:** Phase 5 - Dynamic Keymap EEPROM Audit

## Current Position

Phase: 5 of 8 (Dynamic Keymap EEPROM Audit)
Plan: 0 of 1 in current phase
Status: Phase 4 complete, ready for Phase 5
Last activity: 2026-02-14 -- Completed 04-01 peripheral matrix mapping (MTRX-05 and MTRX-06 satisfied, NUM_ENCODERS=1 fix applied)

Progress: [█████░░░░░] 50%

## Performance Metrics

**Velocity:**
- Total plans completed: 6
- Average duration: 2.3min
- Total execution time: 0.23 hours

**By Phase:**

| Phase | Plans | Total | Avg/Plan |
|-------|-------|-------|----------|
| 01-reference-analysis | 3/3 | 8min | 2.7min |
| 02-matrix-dimension-audit | 1/1 | 2min | 2min |
| 03-vialjson-matrix-fix | 1/1 | 2min | 2min |
| 04-peripheral-matrix-mapping | 1/1 | 2min | 2min |

**Recent Trend:**
- Last 5 plans: 01-03 (3min), 02-01 (2min), 03-01 (2min), 04-01 (2min)
- Trend: Stable ~2.3min/plan

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

### Pending Todos

None yet.

### Blockers/Concerns

- Both halves must be cleared and flashed independently (user has physical access to both boards)
- Phase 7 and 8 require physical keyboard interaction by the user (Claude cannot flash or test hardware)

## Session Continuity

Last session: 2026-02-14
Stopped at: Completed 04-01-PLAN.md -- Phase 4 complete, ready for Phase 5
Resume file: None
