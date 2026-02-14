# Project State

## Project Reference

See: .planning/PROJECT.md (updated 2026-02-14)

**Core value:** Both halves must communicate reliably over TRRS — slave key presses must register on master
**Current focus:** v1.1 Split Serial Communication Fix — diagnosing serial failure

## Current Position

Phase: Not started (defining requirements)
Plan: —
Status: Defining requirements for v1.1
Last activity: 2026-02-14 — Milestone v1.1 started

Progress: [░░░░░░░░░░] 0%

## Performance Metrics

**Velocity (v1.0):**
- Total plans completed: 10
- Average duration: 2.2min
- Total execution time: 0.37 hours

*Updated after each plan completion*

## Accumulated Context

### Decisions

Decisions are logged in PROJECT.md Key Decisions table.

v1.0 decisions carried forward:
- SERIAL_PIO_USE_PIO1 committed as defensive config — needs verification in v1.1
- mcuconf.h UART0/UART1 config pre-dates Phase 1 — needs audit
- Each half operates standalone with separate firmware (vial_left, vial_right)

### Roadmap Evolution

- Milestone v1.1 started: Split Serial Communication Fix

### Pending Todos

None yet.

### Blockers/Concerns

- Physical flashing and testing requires user — Claude cannot interact with hardware
- Firmware-first diagnosis mandate — exhaust config possibilities before concluding PCB issue
- Dual-USB + TRRS causes monitor flicker — likely VCC backfeed but needs SPLIT_USB_DETECT verification

## Session Continuity

Last session: 2026-02-14
Stopped at: Milestone v1.1 initialization
Resume file: None
