# Bipedal Ambi — Split Keyboard Firmware

## What This Is

Firmware for the Bipedal Ambi split keyboard (RP2040-based, vial-qmk) under the Hidpress brand. Each half connects via TRRS cable for split communication and can function standalone via USB from either side. Features an Azoteq TPS43 trackpad on the right half for cursor control and an analog joystick on the left half for custom keycodes and scroll. Uses a unified keymap with compile-time side selection (`SIDE=right`).

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
- ✓ TPS43 trackpad functioning as pointing device on right half — v1.2
- ✓ Joystick refactored: custom keys mode + scroll mode (mouse wheel keycodes) — v1.2
- ✓ Joystick mouse mode removed (trackpad replaces it) — v1.2

### Active

(None — planning next milestone)

### Out of Scope

- Macropad firmware changes — Bipedal Southpaw is a separate product
- Upstream Sofle file modifications — reference only
- Dual-USB + TRRS simultaneous connection — causes monitor flicker (VCC backfeed), needs PCB investigation
- Joystick mouse mode — replaced by TPS43 trackpad (v1.2)
- TPS43 swipe gestures — hardware unreliable on 43mm pad, needs software approach (TPAD-06)

## Context

- **Board**: Bipedal Ambi — RP2040-based split keyboard under the Hidpress brand
- **Firmware base**: Heavily based on Sofle rev1 Vial keymap (`keyboards/sofle/rev1/`)
- **Architecture**: Unified keymap (`keymaps/vial/`) with compile-time `SIDE=right` selection. `EE_HANDS` stores permanent handedness in EEPROM.
- **RP2040 constraint**: No true EEPROM — uses wear-leveling emulation over SPI flash (4KB logical / 8KB backing)
- **Shipped v1.2**: TPS43 trackpad on right half, joystick refactored to 2 modes, split transport for cross-half sync
- **Firmware LOC**: ~1,074 lines across main files (keymap.c, bipedalambi.c, bipedalambi.h, config.h)
- **TRRS cable**: 4-pole (3 black rings confirmed), carries VCC, GND, TX, RX
- **Serial config**: SERIAL_USART_FULL_DUPLEX, EE_HANDS, SPLIT_USB_DETECT, SERIAL_PIO_USE_PIO1
- **Split transport**: USER_SYNC_JOYSTICK (slave→master ADC), USER_SYNC_STATE (master→slave mode)
- **Build commands**: `make hidpress/bipedalambi:vial` (left), `make hidpress/bipedalambi:vial:clean && make hidpress/bipedalambi:vial SIDE=right` (right)

### v1.0 Root Cause (Confirmed)

The Vial layer offset bug was caused by **vial.json matrix rows mismatch**: both vial.json files declared `rows: 4` while config.h had `MATRIX_ROWS=8`.

### v1.1 Root Cause (Confirmed)

The serial communication failure was caused by **`MASTER_LEFT` misidentifying the right half**. When the right side was plugged into USB, `is_keyboard_left()` returned true, causing: wrong bootmagic row checked, joystick ADC reading encoder pins (cursor drift), and serial transport struct mismatches. Fixed by replacing `MASTER_LEFT` with `EE_HANDS` + `SPLIT_USB_DETECT` + `INIT_EE_HANDS_LEFT/RIGHT`.

### v1.2 Key Learnings

- TPS43 hardware swipe detection is unreliable on 43mm trackpad — needs software-based approach
- TPS43 generates phantom two-finger-tap events when right side is USB master (~3s after idle) — filtered with 2s activity gate
- QMK `matrix_scan_user()` runs on BOTH halves — reading ADC pins unconditionally causes issues on the half where those pins serve different functions
- `process_record_user()` only runs on master — slave OLED needs explicit state sync via split transport
- `SPLIT_ACTIVITY_ENABLE` syncs `last_input_activity_elapsed()` across halves — useful for OLED wake on slave
- Always clean build between left/right side switches — QMK cache doesn't detect `SIDE=right` flag changes

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
| EE_HANDS + SPLIT_USB_DETECT | Permanent per-side handedness via EEPROM, USB from either side | ✓ Fixed serial, bootmagic, joystick |
| Unified keymap (vial_left + vial_right → vial) | Prevents transport struct mismatches between halves | ✓ Single codebase, SIDE=right build flag |
| azoteq_iqs5xx driver for TPS43 | QMK's native driver handles I2C, gestures, and split pointing transport | ✓ Trackpad working with gestures |
| AZOTEQ_IQS5XX_TPS43 defined unconditionally | Both halves need it at compile time with SPLIT_POINTING_ENABLE | ✓ Both halves compile |
| Auto mouse layer 3 | Layer 1 used by MO(1) function layer, layer 3 is free | ✓ No layer conflicts |
| MODE_CUSTOM_KEYS=0 as default enum value | EEPROM value 0x200 maps correctly without migration needed | ✓ Clean transition from 3-mode to 2-mode |
| tap_code() for scroll mode | Discrete scroll steps per joystick deflection, no repeat/acceleration | ✓ Clean scroll behavior |
| Phantom right-click filter (right-master only) | TPS43 EMI causes false two-finger-tap when right is USB master | ✓ Filtered with 2s activity gate + double-tap override |
| Split transport for joystick and state | ADC on left slave, processing on right master; mode sync for slave OLED | ✓ Joystick works either-side-as-master |

---
*Last updated: 2026-02-22 after v1.2 milestone shipped*
