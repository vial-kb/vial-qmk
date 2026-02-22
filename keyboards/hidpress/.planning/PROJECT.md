# Bipedal Ambi — Split Keyboard Firmware

## What This Is

Firmware for the Bipedal Ambi split keyboard (RP2040-based, vial-qmk) under the Hidpress brand. Each half connects via TRRS cable for split communication and can also function standalone via USB from either side. Uses a unified keymap with compile-time side selection (`SIDE=right`).

## Core Value

Both halves of the split keyboard must communicate reliably over the TRRS cable — key presses on the slave side must register on the master, and the split must function as a single unified keyboard.

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
- ✓ Split serial communication works — slave-side key presses register on master — v1.1
- ✓ Root cause of serial failure identified and documented (MASTER_LEFT misidentifying right half) — v1.1
- ✓ USB works from either side (EE_HANDS + SPLIT_USB_DETECT) — v1.1
- ✓ Split bootmagic works from both sides — v1.1

### Active

(None — planning next milestone)

### Out of Scope

- Macropad firmware changes — Bipedal Southpaw is a separate product
- Upstream Sofle file modifications — reference only
- OLED display changes — display works correctly
- Dual-USB + TRRS simultaneous connection — causes monitor flicker (VCC backfeed), needs PCB investigation

## Context

- **Board**: Bipedal Ambi — RP2040-based split keyboard under the Hidpress brand
- **Firmware base**: Heavily based on Sofle rev1 Vial keymap (`keyboards/sofle/rev1/`)
- **Architecture**: Unified keymap (`keymaps/vial/`) with compile-time `SIDE=right` selection. `EE_HANDS` stores permanent handedness in EEPROM.
- **RP2040 constraint**: No true EEPROM — uses wear-leveling emulation over SPI flash (4KB logical / 8KB backing)
- **Shipped v1.1**: Both halves compile cleanly, split serial communication working, USB from either side
- **TRRS cable**: 4-pole (3 black rings confirmed), carries VCC, GND, TX, RX
- **Serial config**: SERIAL_USART_FULL_DUPLEX, EE_HANDS, SPLIT_USB_DETECT, SERIAL_PIO_USE_PIO1
- **Build commands**: `make hidpress/bipedalambi:vial` (left), `make hidpress/bipedalambi:vial:clean && make hidpress/bipedalambi:vial SIDE=right` (right)

### v1.0 Root Cause (Confirmed)

The Vial layer offset bug was caused by **vial.json matrix rows mismatch**: both vial.json files declared `rows: 4` while config.h had `MATRIX_ROWS=8`.

### v1.1 Root Cause (Confirmed)

The serial communication failure was caused by **`MASTER_LEFT` misidentifying the right half**. When the right side was plugged into USB, `is_keyboard_left()` returned true, causing: wrong bootmagic row checked, joystick ADC reading encoder pins (cursor drift), and serial transport struct mismatches. Fixed by replacing `MASTER_LEFT` with `EE_HANDS` + `SPLIT_USB_DETECT` + `INIT_EE_HANDS_LEFT/RIGHT`.

## Constraints

- **Target board only**: Only modify files in `keyboards/hidpress/bipedalambi/`
- **EEPROM clear required**: After any EEPROM layout change, the board must have EEPROM cleared
- **RP2040 flash limits**: Wear-leveling backing store shares SPI flash with firmware
- **Physical testing**: User must flash and test — Claude cannot interact with hardware
- **SIDE=right build requires clean**: QMK incremental build doesn't detect OPT_DEFS changes

## Key Decisions

| Decision | Rationale | Outcome |
|----------|-----------|---------|
| Diagnose matrix dimensions first | Layer offset is the more impactful bug and may resolve persistence issues too | ✓ Confirmed as root cause |
| Compare against Sofle rev1 reference | Known-working split Vial board with similar architecture | ✓ Established correct conventions |
| Calculate EEPROM budget before fixing | Need to understand if space is sufficient before changing allocations | ✓ 568/4096 bytes, no collisions |
| Right half KLE rows 0-3 (not 4-7) | Each half operates standalone, scanning its own 4 row pins as rows 0-3 | ✓ Fixed during Phase 7 flash |
| NUM_ENCODERS=1 explicit | QMK split-doubling auto-doubles to 2, causing phantom encoder EEPROM allocation | ✓ Prevents 16-byte waste |
| eeconfig_init_user hardcoded 0x200 | Must match save function encoding; never call load from init | ✓ Safe EEPROM clear defaults |
| SERIAL_PIO_USE_PIO1 | WS2812 may claim PIO0 on right half; PIO1 avoids conflict | ✓ Verified OK — WS2812 driver never compiled |
| HAL_USE_SIO removal | SIO/UART config unnecessary for PIO vendor serial driver | ✓ Removed, cleaner config |
| EE_HANDS + SPLIT_USB_DETECT | Permanent per-side handedness via EEPROM, USB from either side | ✓ Fixed serial, bootmagic, joystick |
| Unified keymap (vial_left + vial_right → vial) | Prevents transport struct mismatches between halves | ✓ Single codebase, SIDE=right build flag |
| Negate joy_x in custom key mode | POINTING_DEVICE_INVERT_X only affects mouse/scroll, not custom key mode | ✓ Fixed X-axis inversion |

---
*Last updated: 2026-02-22 after v1.1 milestone completion*
