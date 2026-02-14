# Requirements: Bipedal Ambi — v1.1 Split Serial Communication Fix

**Defined:** 2026-02-14
**Core Value:** Both halves must communicate reliably over TRRS — slave key presses must register on master

## v1.1 Requirements

Requirements for diagnosing and fixing split serial communication failure. Follows a diagnostic funnel: audit config, test hypotheses, produce verdict.

### Configuration Audit

- [ ] **AUDIT-01**: Serial driver type identified and verified correct for RP2040 (must be `vendor`/PIO, not `usart`/SIO)
- [ ] **AUDIT-02**: TX/RX pin assignments verified against PCB TRRS jack routing
- [ ] **AUDIT-03**: PIO peripheral assignments verified — WS2812 and serial on separate PIOs (no silent conflict)
- [ ] **AUDIT-04**: Full-duplex configuration verified — TX/RX crossing correct (PCB or firmware `PIN_SWAP`)
- [ ] **AUDIT-05**: Split detection config verified — `SPLIT_USB_DETECT` and handedness (`EE_HANDS`/`MASTER_LEFT`/`MASTER_RIGHT`)
- [ ] **AUDIT-06**: ChibiOS peripheral activation verified (`mcuconf.h`, `halconf.h`)
- [ ] **AUDIT-07**: `info.json` split config verified — no conflicts with `config.h`/`rules.mk` settings

### Diagnostic Testing

- [ ] **DIAG-01**: PIO conflict test — separate WS2812 and serial onto different PIO peripherals
- [ ] **DIAG-02**: Half-duplex fallback test — eliminate TX/RX crossing as variable
- [ ] **DIAG-03**: Pin swap test — try `SERIAL_USART_PIN_SWAP` if full-duplex fails
- [ ] **DIAG-04**: TX/RX swap test — reverse pin assignments as brute-force check
- [ ] **DIAG-05**: Static master test — replace `SPLIT_USB_DETECT` with `MASTER_LEFT` to eliminate detection variable
- [ ] **DIAG-06**: Console debug — enable `CONSOLE_ENABLE` to inspect serial driver initialization

### Verdict

- [ ] **VERD-01**: Root cause identified and documented with evidence
- [ ] **VERD-02**: Fix implemented if firmware-solvable, OR PCB report produced if hardware issue

## Future Requirements

### Split Enhancements (deferred)

- **SPLIT-01**: Both halves work with dual-USB + TRRS connected simultaneously
- **SPLIT-02**: Hot-plug TRRS cable without requiring reboot

## Out of Scope

| Feature | Reason |
|---------|--------|
| Bipedal Southpaw macropad | Separate product, works fine |
| Upstream Sofle modifications | Reference only |
| New keyboard features | This is a diagnostic/fix milestone |
| PCB redesign | Only if firmware ruled out — produce report for designer |

## Traceability

| Requirement | Phase | Status |
|-------------|-------|--------|
| AUDIT-01 | — | Pending |
| AUDIT-02 | — | Pending |
| AUDIT-03 | — | Pending |
| AUDIT-04 | — | Pending |
| AUDIT-05 | — | Pending |
| AUDIT-06 | — | Pending |
| AUDIT-07 | — | Pending |
| DIAG-01 | — | Pending |
| DIAG-02 | — | Pending |
| DIAG-03 | — | Pending |
| DIAG-04 | — | Pending |
| DIAG-05 | — | Pending |
| DIAG-06 | — | Pending |
| VERD-01 | — | Pending |
| VERD-02 | — | Pending |

**Coverage:**
- v1.1 requirements: 15 total
- Mapped to phases: 0
- Unmapped: 15 (roadmap pending)

---
*Requirements defined: 2026-02-14*
*Last updated: 2026-02-14 after initial definition*
