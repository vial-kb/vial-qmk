# Project State

## Project Reference

See: .planning/PROJECT.md (updated 2026-02-14)

**Core value:** Both halves must communicate reliably over TRRS -- slave key presses must register on master
**Current focus:** Phase 10 - Diagnostic Testing (v1.1)

## Current Position

Phase: 10 of 11 (Diagnostic Testing)
Plan: 1 of 3 in current phase (PAUSED at checkpoint:human-action)
Status: Plan 10-01 awaiting user flash test (DIAG-00)
Last activity: 2026-02-14 -- SIO/UART config removed, firmware compiled, awaiting user test

Progress: [████████████████████████████░░] 88% (v1.0 complete, Phase 9-10 in progress)

## Performance Metrics

**Velocity (v1.0):**
- Total plans completed: 10
- Average duration: 2.2min
- Total execution time: 0.37 hours

**v1.1:**
- Plans completed: 1 (+1 paused at checkpoint)
- 09-01: 5min (2 tasks, 1 file)
- 10-01: 2min (2/3 tasks, 2 files) -- paused at checkpoint:human-action

*Updated after each plan completion*

## Accumulated Context

### Decisions

Decisions are logged in PROJECT.md Key Decisions table.

v1.0 decisions carried forward:
- SERIAL_PIO_USE_PIO1 committed as defensive config -- VERIFIED OK in Phase 9 (serial on PIO1, PIO0 free)
- mcuconf.h UART0/UART1 config pre-dates Phase 1 -- AUDITED in Phase 9: unnecessary for vendor driver
- Each half operates standalone with separate firmware (vial_left, vial_right)

v1.1 decisions:
- HAL_USE_SIO identified as unnecessary for PIO vendor driver -- REMOVED in 10-01 (commit 0dddbd763b)
- WS2812 PIO conflict hypothesis eliminated (driver never compiled, RGBLIGHT disabled)
- Phase 10 test order: DIAG-00 (SIO cleanup) > DIAG-02 (half-duplex) > DIAG-03/04 (wiring) > DIAG-05 (USB detect)
- DIAG-01 (PIO conflict) skipped -- audit proved no conflict exists
- SIO config removal is permanent regardless of DIAG-00 test result (it was incorrect config)

### Roadmap Evolution

- v1.0 shipped: 8 phases, 10 plans (2026-02-14)
- v1.1 roadmap created: 3 phases (9-11), diagnostic funnel (audit -> test -> verdict)

### Pending Todos

None yet.

### Blockers/Concerns

- Physical flashing and testing requires user -- Claude produces firmware, user reports results
- Firmware-first diagnosis mandate -- exhaust config possibilities before concluding PCB issue
- Dual-USB + TRRS causes monitor flicker -- likely VCC backfeed, needs investigation
- Some DIAG tests may be skipped based on audit findings (by design)

## Session Continuity

Last session: 2026-02-14
Stopped at: Paused 10-01-PLAN.md at Task 3 (checkpoint:human-action -- user must flash firmware)
Resume file: .planning/phases/10-diagnostic-testing/10-01-SUMMARY.md
