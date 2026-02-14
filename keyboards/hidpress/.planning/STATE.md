# Project State

## Project Reference

See: .planning/PROJECT.md (updated 2026-02-14)

**Core value:** Both halves must communicate reliably over TRRS -- slave key presses must register on master
**Current focus:** Phase 10 - Diagnostic Testing (v1.1)

## Current Position

Phase: 10 of 11 (Diagnostic Testing)
Plan: 2 of 3 in current phase (CHECKPOINT -- awaiting user flash/test)
Status: Plan 10-02 Task 1 complete, paused at Task 2 (user must flash DIAG-02 firmware and test)
Last activity: 2026-02-14 -- DIAG-02 half-duplex firmware compiled, awaiting user test

Progress: [█████████████████████████████░] 92% (v1.0 complete, 10-01 done, 10-02 Task 1 done)

## Performance Metrics

**Velocity (v1.0):**
- Total plans completed: 10
- Average duration: 2.2min
- Total execution time: 0.37 hours

**v1.1:**
- Plans completed: 2 (10-02 in progress -- checkpoint paused)
- 09-01: 5min (2 tasks, 1 file)
- 10-01: 2min (3 tasks, 2 files) -- DIAG-00 FAIL
- 10-02: 2min so far (1/2 tasks, 1 file) -- DIAG-02 checkpoint paused

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
- DIAG-00 FAIL: SIO/UART removal did not fix serial -- H1 eliminated as root cause
- User confirmed: TRRS power path works (slave OLED fully functional), serial data path broken
- Next diagnostic: DIAG-02 half-duplex fallback to isolate wiring vs PIO issue
- DIAG-02: SERIAL_USART_FULL_DUPLEX commented out in config.h (commit a007619ece), both halves compile clean
- DIAG-02 checkpoint: firmware ready, awaiting user flash and test result (PASS/FAIL/PARTIAL)

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
Stopped at: 10-02-PLAN.md Task 2 checkpoint (user must flash half-duplex firmware and test)
Resume file: .planning/phases/10-diagnostic-testing/10-02-SUMMARY.md
