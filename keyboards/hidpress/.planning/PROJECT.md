# Bipedal Ambi — EEPROM / Vial Layer Fix

## What This Is

Firmware fix for the Bipedal Ambi split keyboard (RP2040-based, vial-qmk). The Vial layer offset bug has been diagnosed and fixed — keycodes now persist correctly across power cycles and layers display without offset in the Vial GUI.

## Core Value

Keycodes set in Vial must persist correctly across power cycles and map to the correct layers — this is the fundamental contract between the firmware and the configuration tool.

## Requirements

### Validated

- ✓ Layer 0 keycodes display correctly in Vial — existing
- ✓ RP2040-based split keyboard compiles and boots — existing
- ✓ OLED display, joystick, and encoders function — existing
- ✓ Split keyboard communication works (USART serial) — existing
- ✓ Keycodes set in Vial persist across power cycles — v1.0
- ✓ Layer indexing matches between firmware and Vial (no off-by-one shift) — v1.0
- ✓ KC_TRNS displays correctly on layers 1 and 3 — v1.0
- ✓ All 4 layers are visible and editable in Vial — v1.0
- ✓ Custom EEPROM features don't collide with Vial's dynamic keymap region — v1.0
- ✓ EEPROM budget fits within wear-leveling allocation (568/4096 bytes) — v1.0

### Active

(None — bug fix milestone complete)

### Out of Scope

- Macropad firmware changes — Bipedal Southpaw works fine, don't touch it
- Upstream Sofle file modifications — reference only
- New features or refactoring — this was a bug fix
- OLED display changes — display works correctly

## Context

- **Board**: Bipedal Ambi — RP2040-based split keyboard under the Hidpress brand
- **Firmware base**: Heavily based on Sofle rev1 Vial keymap (`keyboards/sofle/rev1/`)
- **Architecture**: Each half has its own separate firmware (vial_left, vial_right), operates standalone via USB
- **RP2040 constraint**: No true EEPROM — uses wear-leveling emulation over SPI flash (4KB logical / 8KB backing)
- **Shipped v1.0**: Both halves compile cleanly (left 124.5 KB, right 108 KB), flashed and verified working

### Root Cause (Confirmed)

The Vial layer offset bug was caused by **vial.json matrix rows mismatch**: both vial.json files declared `rows: 4` while config.h had `MATRIX_ROWS=8`. This caused Vial to calculate EEPROM offsets using a 4-row matrix while the firmware used an 8-row matrix, shifting every layer after layer 0.

The EEPROM collision hypothesis (Issue B) was ruled out — eeconfig_user (bytes 19-22) is 13 bytes away from VIA magic (byte 36), no overlap possible.

## Constraints

- **Target board only**: Only modify files in `keyboards/hidpress/bipedalambi/`
- **Minimal changes**: Bug fix only — no feature additions or refactoring
- **EEPROM clear required**: After any EEPROM layout change, the board must have EEPROM cleared
- **RP2040 flash limits**: Wear-leveling backing store shares SPI flash with firmware

## Key Decisions

| Decision | Rationale | Outcome |
|----------|-----------|---------|
| Diagnose matrix dimensions first | Layer offset is the more impactful bug and may resolve persistence issues too | ✓ Confirmed as root cause |
| Compare against Sofle rev1 reference | Known-working split Vial board with similar architecture | ✓ Established correct conventions |
| Calculate EEPROM budget before fixing | Need to understand if space is sufficient before changing allocations | ✓ 568/4096 bytes, no collisions |
| Right half KLE rows 0-3 (not 4-7) | Each half operates standalone, scanning its own 4 row pins as rows 0-3 | ✓ Fixed during Phase 7 flash |
| NUM_ENCODERS=1 explicit | QMK split-doubling auto-doubles to 2, causing phantom encoder EEPROM allocation | ✓ Prevents 16-byte waste |
| eeconfig_init_user hardcoded 0x200 | Must match save function encoding; never call load from init | ✓ Safe EEPROM clear defaults |
| SERIAL_PIO_USE_PIO1 | WS2812 may claim PIO0 on right half; PIO1 avoids conflict | ✓ Committed as defensive config |

---
*Last updated: 2026-02-14 after v1.0 milestone*
