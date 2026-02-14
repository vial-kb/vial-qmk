# Bipedal Ambi — Split Keyboard Firmware

## What This Is

Firmware for the Bipedal Ambi split keyboard (RP2040-based, vial-qmk) under the Hidpress brand. Each half connects via TRRS cable for split communication. Both halves also function standalone via USB.

## Core Value

Both halves of the split keyboard must communicate reliably over the TRRS cable — key presses on the slave side must register on the master, and the split must function as a single unified keyboard.

## Current Milestone: v1.1 Split Serial Communication Fix

**Goal:** Diagnose and fix the serial communication failure between halves — slave-side key presses don't reach the master when connected via TRRS cable.

**Target:**
- Diagnose root cause (firmware config vs PCB routing)
- Fix serial communication if firmware-solvable
- Produce PCB report if hardware issue

## Requirements

### Validated

- ✓ Layer 0 keycodes display correctly in Vial — existing
- ✓ RP2040-based split keyboard compiles and boots — existing
- ✓ OLED display, joystick, and encoders function — existing
- ✓ Keycodes set in Vial persist across power cycles — v1.0
- ✓ Layer indexing matches between firmware and Vial (no off-by-one shift) — v1.0
- ✓ KC_TRNS displays correctly on layers 1 and 3 — v1.0
- ✓ All 4 layers are visible and editable in Vial — v1.0
- ✓ Custom EEPROM features don't collide with Vial's dynamic keymap region — v1.0
- ✓ EEPROM budget fits within wear-leveling allocation (568/4096 bytes) — v1.0

### Active

- [ ] Split serial communication works — slave-side key presses register on master
- [ ] Root cause of serial failure identified and documented
- [ ] Dual-USB + TRRS behavior understood (monitor flicker issue)

### Out of Scope

- Macropad firmware changes — Bipedal Southpaw is a separate product
- Upstream Sofle file modifications — reference only
- New features or refactoring — this is a diagnostic/fix milestone
- OLED display changes — display works correctly

## Context

- **Board**: Bipedal Ambi — RP2040-based split keyboard under the Hidpress brand
- **Firmware base**: Heavily based on Sofle rev1 Vial keymap (`keyboards/sofle/rev1/`)
- **Architecture**: Each half has its own separate firmware (vial_left, vial_right), operates standalone via USB
- **RP2040 constraint**: No true EEPROM — uses wear-leveling emulation over SPI flash (4KB logical / 8KB backing)
- **Shipped v1.0**: Both halves compile cleanly (left 124.5 KB, right 108 KB), flashed and verified working
- **TRRS cable**: 4-pole (3 black rings confirmed), carries VCC, GND, TX, RX
- **ESD protection**: USBLC6 on TRRS lines (may affect serial data timing)
- **Serial config**: SERIAL_USART_FULL_DUPLEX enabled, SPLIT_USB_DETECT enabled

### v1.0 Root Cause (Confirmed)

The Vial layer offset bug was caused by **vial.json matrix rows mismatch**: both vial.json files declared `rows: 4` while config.h had `MATRIX_ROWS=8`.

### v1.1 Observed Symptoms

| Scenario | Result |
|----------|--------|
| Left standalone (USB, no TRRS) | All keys work |
| Right standalone (USB, no TRRS) | All keys work |
| Both USB + TRRS connected | Monitor flickers, both halves stop |
| Right USB + TRRS | Right keys work, left OLED lights up, left keys don't register |
| Left USB + TRRS | Left keys work, right keys don't register |

**Key clue**: Power delivery via TRRS works (slave OLED lights up) but serial data does not. This points to either firmware misconfiguration (pin assignment, driver, PIO conflict) or PCB routing issue on the data lines.

### Prior Work Relevant to v1.1

- `SERIAL_PIO_USE_PIO1` was committed in v1.0 Phase 7 as "defensive config" — needs verification that this actually resolved the PIO conflict or if both WS2812 and serial are still on the same PIO
- `mcuconf.h` has UART0/UART1 config from before Phase 1 — needs audit

## Constraints

- **Target board only**: Only modify files in `keyboards/hidpress/bipedalambi/`
- **Firmware-first diagnosis**: Exhaust all firmware/config possibilities before concluding PCB issue
- **Discrete tests**: Each diagnostic change must be isolated and reversible
- **EEPROM clear required**: After any EEPROM layout change, the board must have EEPROM cleared
- **RP2040 flash limits**: Wear-leveling backing store shares SPI flash with firmware
- **Physical testing**: User must flash and test — Claude cannot interact with hardware

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
*Last updated: 2026-02-14 after v1.1 milestone start*
