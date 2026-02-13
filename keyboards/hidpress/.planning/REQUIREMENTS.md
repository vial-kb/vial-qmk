# Requirements: Bipedal Ambi EEPROM / Vial Layer Fix

**Defined:** 2026-02-13
**Core Value:** Keycodes set in Vial must persist correctly across power cycles and map to the correct layers

## v1 Requirements

### Matrix Dimension Fix

- [ ] **MTRX-01**: vial.json matrix rows match config.h MATRIX_ROWS value (rows=8 for both halves)
- [ ] **MTRX-02**: Right-side vial.json layout positions use rows 4-7 for the right half's keys
- [ ] **MTRX-03**: info.json matrix dimensions agree with config.h MATRIX_ROWS and MATRIX_COLS
- [ ] **MTRX-04**: Sofle rev1 Vial keymap cross-referenced to verify split row-doubling convention in vial-qmk specifically (not upstream QMK/VIA assumptions)
- [ ] **MTRX-05**: Thumbstick matrix positions (left half, col 7, rows 0-3) correctly mapped in left vial.json
- [ ] **MTRX-06**: Encoder matrix positions (right half) correctly mapped in right vial.json

### EEPROM & Persistence

- [ ] **EEPR-01**: EEPROM clear procedure documented for both halves independently (Bootmagic Lite or QK_CLEAR_EEPROM)
- [ ] **EEPR-02**: All 4 layers display correct keycodes in Vial desktop app after fix
- [ ] **EEPR-03**: Keycodes set in Vial persist across power cycles on both halves
- [ ] **EEPR-04**: EEPROM budget calculated and documented with address ranges showing no overlaps between QMK core, eeconfig_user, VIA custom config, dynamic keymaps, encoder map, and macros

### Defensive Improvements

- [ ] **DFNS-01**: `eeconfig_init_user()` callback added to recover joystick actuation and scroll direction defaults on EEPROM reset
- [ ] **DFNS-02**: `QK_CLEAR_EEPROM` key added to keymap for easy EEPROM clearing without bootmagic

### Cross-Validation & Documentation

- [ ] **XVAL-01**: Matrix dimension cross-reference table created showing config.h vs info.json vs vial.json vs LAYOUT macro — all sources agree
- [ ] **XVAL-02**: All fixes verified against vial-qmk fork implementation (dynamic_keymap.c, vial.c) not upstream QMK/VIA docs alone
- [ ] **XVAL-03**: Sofle rev1 Vial split configuration compared as known-working reference for matrix doubling, vial.json structure, and encoder mapping

## v2 Requirements

### Enhanced Diagnostics

- **DIAG-01**: Console debug output for EEPROM address verification (CONSOLE_ENABLE + debug prints)
- **DIAG-02**: Runtime EEPROM dump utility via custom keycode for troubleshooting

## Out of Scope

| Feature | Reason |
|---------|--------|
| Macropad firmware changes | Bipedal Southpaw works fine — don't touch it |
| Upstream Sofle modifications | Reference only — never modify |
| New keyboard features | This is a bug fix, not feature development |
| OLED display changes | Display works correctly |
| Custom EEPROM collision fix | Research confirmed eeconfig_user does NOT collide with Vial — no fix needed |
| Reducing EEPROM allocation | Budget is healthy (598/4096 bytes) — no reduction needed |

## Traceability

Which phases cover which requirements. Updated during roadmap creation.

| Requirement | Phase | Status |
|-------------|-------|--------|
| MTRX-01 | Phase 3 | Pending |
| MTRX-02 | Phase 3 | Pending |
| MTRX-03 | Phase 2 | Pending |
| MTRX-04 | Phase 1 | Pending |
| MTRX-05 | Phase 4 | Pending |
| MTRX-06 | Phase 4 | Pending |
| EEPR-01 | Phase 6 | Pending |
| EEPR-02 | Phase 8 | Pending |
| EEPR-03 | Phase 8 | Pending |
| EEPR-04 | Phase 5 | Pending |
| DFNS-01 | Phase 6 | Pending |
| DFNS-02 | Phase 6 | Pending |
| XVAL-01 | Phase 2 | Pending |
| XVAL-02 | Phase 5 | Pending |
| XVAL-03 | Phase 1 | Pending |

**Coverage:**
- v1 requirements: 15 total
- Mapped to phases: 15
- Unmapped: 0

---
*Requirements defined: 2026-02-13*
*Last updated: 2026-02-13 after roadmap creation*
