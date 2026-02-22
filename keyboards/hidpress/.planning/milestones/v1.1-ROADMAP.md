# Roadmap: Bipedal Ambi Split Keyboard Firmware

## Milestones

- ✅ **v1.0 EEPROM / Vial Layer Fix** -- Phases 1-8 (shipped 2026-02-14)
- **v1.1 Split Serial Communication Fix** -- Phases 9-11 (in progress)

## Phases

<details>
<summary>v1.0 EEPROM / Vial Layer Fix (Phases 1-8) -- SHIPPED 2026-02-14</summary>

- [x] Phase 1: Reference Analysis (3/3 plans) -- completed 2026-02-13
- [x] Phase 2: Matrix Dimension Audit (1/1 plans) -- completed 2026-02-14
- [x] Phase 3: vial.json Matrix Fix (1/1 plans) -- completed 2026-02-14
- [x] Phase 4: Peripheral Matrix Mapping (1/1 plans) -- completed 2026-02-14
- [x] Phase 5: EEPROM Budget Verification (1/1 plans) -- completed 2026-02-14
- [x] Phase 6: Defensive EEPROM Improvements (1/1 plans) -- completed 2026-02-14
- [x] Phase 7: Build and Flash (2/2 plans) -- completed 2026-02-14
- [x] Phase 8: End-to-End Verification (user verified) -- completed 2026-02-14

See `milestones/v1.0-ROADMAP.md` for full details.

</details>

### v1.1 Split Serial Communication Fix (In Progress)

**Milestone Goal:** Diagnose and fix the serial communication failure between halves -- slave-side key presses don't reach the master when connected via TRRS cable. Produce a confirmed fix if firmware-solvable, or a PCB report if hardware issue.

- [x] **Phase 9: Configuration Audit** -- Audit every serial/split config file to identify misconfigurations before touching hardware -- completed 2026-02-14
- [ ] **Phase 10: Diagnostic Testing** -- Test hypotheses from the audit with isolated firmware changes, priority-ordered
- [ ] **Phase 11: Verdict** -- Document root cause with evidence, deliver fix or PCB report

## Phase Details

### Phase 9: Configuration Audit
**Goal**: Every serial and split communication configuration setting is audited against RP2040/PIO requirements and PCB routing, producing a prioritized list of suspected misconfigurations
**Depends on**: Phase 8 (v1.0 shipped -- firmware compiles and boots on both halves)
**Requirements**: AUDIT-01, AUDIT-02, AUDIT-03, AUDIT-04, AUDIT-05, AUDIT-06, AUDIT-07
**Success Criteria** (what must be TRUE):
  1. Serial driver type is confirmed as correct for RP2040 (vendor/PIO) or flagged as wrong (usart/SIO) with the specific file and line identified
  2. TX/RX pin assignments are verified against actual PCB TRRS jack routing -- pin numbers confirmed or mismatch documented
  3. PIO peripheral assignments are mapped for both WS2812 and serial -- conflict or separation confirmed with evidence from config files
  4. A prioritized hypothesis list exists ranking the most likely cause of serial failure, with each hypothesis tied to specific config evidence
  5. Every config surface (config.h, rules.mk, mcuconf.h, halconf.h, info.json) has been checked and any conflicts between them are documented
**Plans**: 1 plan

Plans:
- [x] 09-01-PLAN.md -- Audit all serial/split config surfaces and produce prioritized hypothesis list -- completed 2026-02-14

### Phase 10: Diagnostic Testing
**Goal**: Each suspected misconfiguration is tested with an isolated, reversible firmware change -- user flashes and reports results for each test
**Depends on**: Phase 9 (audit complete, hypotheses prioritized)
**Requirements**: DIAG-01, DIAG-02, DIAG-03, DIAG-04, DIAG-05, DIAG-06
**Success Criteria** (what must be TRUE):
  1. PIO conflict between WS2812 and serial is either confirmed fixed (slave keys register) or ruled out as the cause
  2. Full-duplex vs half-duplex communication mode is either confirmed working or ruled out, with user-reported test results
  3. Each diagnostic test that was executed has a clear pass/fail result documented with the exact config change made and the user-observed behavior
  4. Tests skipped (because a prior test resolved the issue or audit ruled out the hypothesis) are documented with the reason for skipping
  5. If no single test resolves the issue, console debug output from the serial driver is captured and available for verdict analysis
**Plans**: 3 plans (sequential diagnostic funnel with early-exit support)

Plans:
- [ ] 10-01-PLAN.md -- DIAG-00: Remove HAL_USE_SIO/UART config (H1 test) + document DIAG-01 skip
- [ ] 10-02-PLAN.md -- DIAG-02: Half-duplex fallback test (wiring isolation diagnostic)
- [ ] 10-03-PLAN.md -- DIAG-03/04/05/06: Remaining diagnostics (wiring verification, PIN_SWAP, MASTER_LEFT, console debug)

**Test Priority Order** (updated from Phase 9 audit -- DIAG-01 eliminated, DIAG-00 added):
1. DIAG-00 (new): SIO/UART cleanup -- remove HAL_USE_SIO and UART0/UART1 config (Plan 10-01)
2. DIAG-01: SKIPPED -- PIO conflict eliminated by audit (WS2812 driver never compiled)
3. DIAG-02: Half-duplex fallback -- eliminate TX/RX crossing as a variable (Plan 10-02)
4. DIAG-03: Wiring verification -- user checks PCB schematic/TRRS routing (Plan 10-03)
5. DIAG-04: PIN_SWAP test -- try SERIAL_USART_PIN_SWAP for straight-through wiring (Plan 10-03)
6. DIAG-05: Static master -- replace SPLIT_USB_DETECT with MASTER_LEFT (Plan 10-03)
7. DIAG-06: Console debug -- enable CONSOLE_ENABLE for serial driver inspection (Plan 10-03)

### Phase 11: Verdict
**Goal**: Root cause is identified with evidence and either a confirmed fix is committed or a PCB report is produced for the hardware designer
**Depends on**: Phase 9 (audit), Phase 10 (testing)
**Requirements**: VERD-01, VERD-02
**Success Criteria** (what must be TRUE):
  1. Root cause is documented with specific evidence -- which config/hardware element was wrong and why it prevented serial communication
  2. If firmware-solvable: the fix is committed to the codebase, both halves compile cleanly, and user has verified slave-side key presses register on the master
  3. If hardware issue: a PCB report exists documenting which traces/connections need to change, with enough detail for the PCB designer to act on it
**Plans**: TBD

Plans:
- [ ] 11-01: TBD

## Progress

**Execution Order:**
Phases execute in numeric order: 9 -> 10 -> 11

| Phase | Milestone | Plans Complete | Status | Completed |
|-------|-----------|----------------|--------|-----------|
| 1. Reference Analysis | v1.0 | 3/3 | Complete | 2026-02-13 |
| 2. Matrix Dimension Audit | v1.0 | 1/1 | Complete | 2026-02-14 |
| 3. vial.json Matrix Fix | v1.0 | 1/1 | Complete | 2026-02-14 |
| 4. Peripheral Matrix Mapping | v1.0 | 1/1 | Complete | 2026-02-14 |
| 5. EEPROM Budget Verification | v1.0 | 1/1 | Complete | 2026-02-14 |
| 6. Defensive EEPROM Improvements | v1.0 | 1/1 | Complete | 2026-02-14 |
| 7. Build and Flash | v1.0 | 2/2 | Complete | 2026-02-14 |
| 8. End-to-End Verification | v1.0 | 2/2 | Complete | 2026-02-14 |
| 9. Configuration Audit | v1.1 | 1/1 | Complete | 2026-02-14 |
| 10. Diagnostic Testing | v1.1 | 0/? | Not started | - |
| 11. Verdict | v1.1 | 0/? | Not started | - |
