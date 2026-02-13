# Bipedal Ambi — EEPROM / Vial Layer Fix

## What This Is

A diagnosis and fix for the Bipedal Ambi split keyboard firmware where keycodes set via the Vial desktop app don't persist correctly and layers are offset (layer 1 content appears on layer 2 in Vial, odd-numbered layers are broken). The firmware lives at `keyboards/hidpress/bipedalambi/` in the vial-qmk repo.

## Core Value

Keycodes set in Vial must persist correctly across power cycles and map to the correct layers — this is the fundamental contract between the firmware and the configuration tool.

## Requirements

### Validated

- ✓ Layer 0 keycodes display correctly in Vial — existing
- ✓ RP2040-based split keyboard compiles and boots — existing
- ✓ OLED display, joystick, and encoders function — existing
- ✓ Split keyboard communication works (USART serial) — existing

### Active

- [ ] Keycodes set in Vial persist across power cycles
- [ ] Layer indexing matches between firmware and Vial (no off-by-one shift)
- [ ] KC_TRNS displays correctly on layers 1 and 3 (not shifted to 2 and 4)
- [ ] All 4 layers are visible and editable in Vial
- [ ] Custom EEPROM features (actuation, scroll direction) don't collide with Vial's dynamic keymap region
- [ ] EEPROM budget fits within wear-leveling allocation

### Out of Scope

- Macropad firmware changes — Bipedal Southpaw works fine, don't touch it
- Upstream Sofle file modifications — reference only
- New features or refactoring — this is a bug fix
- OLED display changes — display works correctly

## Context

- **Board**: Bipedal Ambi — RP2040-based split keyboard under the Hidpress brand
- **Firmware base**: Heavily based on Sofle rev1 Vial keymap (`keyboards/sofle/rev1/`)
- **Prior work**: Custom EEPROM features (joystick actuation persistence, scroll direction inversion) carried over from the Bipedal Southpaw macropad (`keyboards/hidpress/bipedalsouthpaw/`)
- **RP2040 constraint**: No true EEPROM — uses wear-leveling emulation over SPI flash (typically 4KB logical / 8KB backing)
- **First split board**: Matt's first split keyboard firmware; macropad is the known-good reference for custom features in isolation

### Suspected Root Causes

1. **Matrix dimension mismatch (Issue A)**: `MATRIX_ROWS × MATRIX_COLS` in config.h / info.json / vial.json don't agree, causing Vial to read/write layer data at wrong EEPROM offsets. For split boards, `MATRIX_ROWS` must be doubled (rows_per_side × 2).

2. **EEPROM collision (Issue B)**: Custom `eeconfig_read_user()` / `eeconfig_update_user()` calls from macropad code may write into Vial's dynamic keymap region, corrupting stored keycodes.

### Diagnostic Evidence

- Layer 1 content appears on layer 2 in Vial (off-by-one shift)
- KC_TRNS shows on layers 2 and 4 instead of 1 and 3
- Layer 0 displays correctly (first layer is unaffected by offset)
- Odd-numbered layers are broken — classic matrix dimension mismatch pattern
- Each layer occupies `rows × cols × 2` bytes; wrong dimensions shift every subsequent layer's start address

## Constraints

- **Target board only**: Only modify files in `keyboards/hidpress/bipedalambi/`
- **Minimal changes**: Bug fix only — no feature additions or refactoring
- **EEPROM clear required**: After any EEPROM layout change, the board must have EEPROM cleared
- **RP2040 flash limits**: Wear-leveling backing store shares SPI flash with firmware

## Key Decisions

| Decision | Rationale | Outcome |
|----------|-----------|---------|
| Diagnose matrix dimensions first | Layer offset is the more impactful bug and may resolve persistence issues too | — Pending |
| Compare against Sofle rev1 reference | Known-working split Vial board with similar architecture | — Pending |
| Calculate EEPROM budget before fixing | Need to understand if space is sufficient before changing allocations | — Pending |

---
*Last updated: 2026-02-13 after initialization*
