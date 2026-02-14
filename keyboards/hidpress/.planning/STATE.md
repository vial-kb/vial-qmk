# Project State

## Project Reference

See: .planning/PROJECT.md (updated 2026-02-13)

**Core value:** Keycodes set in Vial must persist correctly across power cycles and map to the correct layers
**Current focus:** Phase 3 - vial.json Matrix Fix

## Current Position

Phase: 3 of 8 (vial.json Matrix Fix)
Plan: 0 of 1 in current phase
Status: Phase 2 complete, ready for Phase 3
Last activity: 2026-02-14 -- Completed 02-01 matrix dimension cross-reference audit (DIMENSION-AUDIT.md with 2 disagreements documented, XVAL-01 and MTRX-03 satisfied)

Progress: [███░░░░░░░] 25%

## Performance Metrics

**Velocity:**
- Total plans completed: 4
- Average duration: 2.5min
- Total execution time: 0.17 hours

**By Phase:**

| Phase | Plans | Total | Avg/Plan |
|-------|-------|-------|----------|
| 01-reference-analysis | 3/3 | 8min | 2.7min |
| 02-matrix-dimension-audit | 1/1 | 2min | 2min |

**Recent Trend:**
- Last 5 plans: 01-01 (2min), 01-02 (3min), 01-03 (3min), 02-01 (2min)
- Trend: Stable ~2.5min/plan

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

### Pending Todos

None yet.

### Blockers/Concerns

- Both halves must be cleared and flashed independently (user has physical access to both boards)
- Phase 7 and 8 require physical keyboard interaction by the user (Claude cannot flash or test hardware)

## Session Continuity

Last session: 2026-02-14
Stopped at: Completed 02-01-PLAN.md -- Phase 2 complete, ready for Phase 3
Resume file: None
