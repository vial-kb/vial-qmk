# Phase 7: Build and Flash - Research

**Researched:** 2026-02-14
**Domain:** QMK firmware compilation for RP2040, UF2 flashing, EEPROM clear procedure for split keyboard
**Confidence:** HIGH

## Summary

Phase 7 has two distinct parts: (1) compilation, which Claude can do, and (2) flash/EEPROM clear, which only the user can do with physical hardware. The compilation step uses `make hidpress/bipedalambi:vial_left` and `make hidpress/bipedalambi:vial_right` from the vial-qmk repo root. Both commands produce `.uf2` firmware files in `.build/`. The flash step requires the user to enter RP2040 bootloader mode (double-tap reset or hold BOOTSEL while plugging in) and copy the UF2 file to the mass storage drive that appears. EEPROM must be cleared on EACH half independently after flashing -- the existing EEPROM-CLEAR-PROCEDURE.md documents both methods.

There is one critical finding: the working tree contains uncommitted changes to `bipedalambi/config.h` (adding `SERIAL_PIO_USE_PIO1`) and `bipedalambi/mcuconf.h` (enabling both UART peripherals in the ChibiOS SIO driver). These changes exist in the working tree but are NOT committed. Since `make` reads from the working tree, these will be included in compilation. However, they need to be committed before Phase 7 can cleanly track what was built. These appear to be pre-existing configuration additions from an earlier session, not changes from Phases 1-6.

The build toolchain is confirmed available: `arm-none-eabi-gcc 15.2.1` and `make` are installed, all git submodules (ChibiOS, pico-sdk, etc.) are checked out, and previous successful builds exist as `.build/hidpress_bipedalambi_vial_*.uf2` from February 2.

**Primary recommendation:** Plan 07-01 should compile both halves (resolving any build errors), producing `.uf2` files. Plan 07-02 should document a step-by-step flash and EEPROM clear procedure for the user to execute physically. The uncommitted config.h and mcuconf.h changes should be committed as part of 07-01 if they are needed for the build, or investigated and resolved first.

## Standard Stack

### Build Tools

| Tool | Version/Path | Purpose | Status |
|------|-------------|---------|--------|
| `arm-none-eabi-gcc` | 15.2.1 (Arm GNU Toolchain 15.2.Rel1) | ARM cross-compiler for RP2040 (Cortex-M0+) | Installed at `/opt/homebrew/bin/arm-none-eabi-gcc` |
| `make` | System make | Orchestrates QMK build system | Installed at `/usr/bin/make` |
| `qmk` CLI | N/A | QMK configuration tool (not needed for `make` builds) | Installed at `~/.local/bin/qmk` |
| `uf2conv.py` | In-tree | Converts binary to UF2 format for RP2040 | At `util/uf2conv.py` |
| `python3` | System | Required by uf2conv.py | Installed at `/usr/bin/python3` |

### Build Outputs

| File | Location | Format | Purpose |
|------|----------|--------|---------|
| Left firmware | `.build/hidpress_bipedalambi_vial_left.uf2` | UF2 | Flash to left half RP2040 |
| Right firmware | `.build/hidpress_bipedalambi_vial_right.uf2` | UF2 | Flash to right half RP2040 |

### ChibiOS / Platform Configuration

| Setting | Value | Source |
|---------|-------|--------|
| MCU | RP2040 | `rules.mk` |
| BOOTLOADER | rp2040 | `rules.mk` |
| BOARD | GENERIC_PROMICRO_RP2040 | Default from `mcu_selection.mk:172` |
| FIRMWARE_FORMAT | uf2 | Default for RP2040 from `mcu_selection.mk:176` |
| UF2_FAMILY | RP2040 | Default from `mcu_selection.mk:175` |
| SERIAL_DRIVER | vendor | `rules.mk` (uses PIO, not hardware UART) |

## Architecture Patterns

### Pattern 1: Two Separate Firmware Builds for Split Keyboard

**What:** The Bipedal Ambi builds as two separate firmwares, not a single firmware that detects which side it is. Each keymap directory (vial_left, vial_right) has its own config.h, rules.mk, keymap.c, and vial.json. The build commands are completely independent.

**Build commands (from repo root `/Users/matthewthomas/dev/vial-qmk/`):**
```bash
make hidpress/bipedalambi:vial_left    # Left half firmware
make hidpress/bipedalambi:vial_right   # Right half firmware
```

**Output files:**
```
.build/hidpress_bipedalambi_vial_left.uf2    # ~125 KB
.build/hidpress_bipedalambi_vial_right.uf2   # ~108 KB
```

**Why the right is smaller:** The left half includes joystick/pointing device driver code, scroll handling, and matrix_scan_user for custom keys mode. The right half disables pointing device (`POINTING_DEVICE_ENABLE = no` in its rules.mk) and has no joystick code.

**Source:** `rules.mk`, `keymaps/vial_left/rules.mk`, `keymaps/vial_right/rules.mk`

### Pattern 2: RP2040 UF2 Bootloader and Flashing

**What:** The RP2040 has a built-in ROM bootloader that presents itself as a USB mass storage device (named "RPI-RP2") when entered. Flashing is done by copying a `.uf2` file to this drive. No special flashing tool is required.

**Entering bootloader mode:**
1. **Double-tap reset** (if supported by hardware): The firmware uses `RP2040_BOOTLOADER_DOUBLE_TAP_RESET` with a 200ms timeout. Rapidly pressing the reset button twice enters bootloader mode.
2. **BOOTSEL button**: Hold the BOOTSEL button on the Pico/RP2040 while plugging in USB. This always works regardless of firmware state.
3. **Bootmagic**: Hold row 0, col 0 key while plugging in USB. This clears EEPROM AND enters bootloader.
4. **`make flash`**: The QMK build system can auto-flash if the device is already in bootloader mode. It uses `uf2conv.py --wait --deploy` which waits for the UF2 drive to appear.

**Flashing:**
```bash
# Method A: QMK make flash (auto-detects bootloader mode)
make hidpress/bipedalambi:vial_left:flash

# Method B: Manual copy to mass storage drive
# 1. Enter bootloader (device appears as "RPI-RP2" drive)
# 2. Copy .uf2 file to the drive
cp .build/hidpress_bipedalambi_vial_left.uf2 /Volumes/RPI-RP2/

# Method C: uf2conv.py direct
python3 util/uf2conv.py --deploy .build/hidpress_bipedalambi_vial_left.uf2
```

**Source:** `platforms/chibios/flash.mk` lines 106-107, `platforms/chibios/bootloaders/rp2040.c`

### Pattern 3: EEPROM Clear After Matrix Dimension Changes

**What:** Phases 3, 4, and 5 changed matrix dimensions (rows from 4 to 8 in vial.json) and NUM_ENCODERS (from 2 to 1). These changes alter the EEPROM layout, making stale EEPROM data incompatible. EEPROM MUST be cleared on both halves after flashing the new firmware.

**Why:** The dynamic keymap region in EEPROM is addressed as `rows * cols * layers * 2` bytes. Changing from rows=4 to rows=8 doubles the dynamic keymap size, shifting all subsequent EEPROM regions. Stale data would cause layer content to be read from wrong addresses.

**Procedure:** Documented in `bipedalambi/EEPROM-CLEAR-PROCEDURE.md`. Two methods: EE_CLR key (layer 1) or Bootmagic (hold key while plugging in). Both halves must be cleared independently.

**Source:** Phase 3/4/5 summaries, EEPROM-CLEAR-PROCEDURE.md

### Pattern 4: Build Order Does Not Matter

**What:** The left and right firmware builds are completely independent. They share common board-level files (bipedalambi.c, bipedalambi.h, config.h, rules.mk, etc.) but each keymap has its own override files. Building left first or right first makes no difference.

**Recommended approach:** Build both sequentially with a clean first:
```bash
make clean
make hidpress/bipedalambi:vial_left
make hidpress/bipedalambi:vial_right
```

### Anti-Patterns to Avoid

- **Flashing wrong firmware to wrong half:** The left firmware contains joystick driver code with left-side GPIO pins. Flashing it to the right half would cause GPIO conflicts and non-functional firmware. Always verify which `.uf2` is being copied.
- **Forgetting to clear EEPROM after flashing:** The firmware will boot with stale EEPROM data, causing the exact same layer offset bugs that Phases 1-6 were fixing.
- **Clearing EEPROM on only one half:** Each RP2040 has independent flash storage. Both must be cleared.
- **Using `make flash` before entering bootloader:** The `make flash` target waits for the device to appear but can hang indefinitely if the device never enters bootloader mode.

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| UF2 conversion | Custom binary-to-UF2 converter | `make` target (auto-invokes uf2conv.py) | The build system handles the full toolchain |
| Firmware flashing | Direct flash programming | UF2 mass storage copy | RP2040 ROM bootloader handles it natively |
| EEPROM clear | Custom flash sector erase tool | EE_CLR key or Bootmagic | Already implemented in Phase 6, built into QMK |
| Build error resolution | Guessing at fixes | `make` verbose output with `VERBOSE=true` | QMK build system provides detailed error messages |

**Key insight:** Phase 7 is entirely about executing existing tooling (make, UF2 copy, EEPROM clear). No custom tools or scripts need to be written.

## Common Pitfalls

### Pitfall 1: Uncommitted Working Tree Changes

**What goes wrong:** The build includes uncommitted changes that are not tracked in git, making the build non-reproducible. If the user switches branches or resets, the changes are lost.
**Why it happens:** The working tree has uncommitted changes to `config.h` (adding `SERIAL_PIO_USE_PIO1`) and `mcuconf.h` (enabling UART0 and UART1 in ChibiOS SIO driver). These exist in the current working tree and will be compiled into the firmware.
**How to avoid:** Commit or stash these changes before building. If they are intentional and needed, commit them as part of 07-01 with a clear commit message.
**Warning signs:** `git diff` shows modified files in `bipedalambi/config.h` and `bipedalambi/mcuconf.h`.

**Current uncommitted changes:**
1. `config.h`: Added `#define SERIAL_PIO_USE_PIO1` -- switches PIO serial driver from PIO0 to PIO1 (needed because PIO0 is used by WS2812 on the left half)
2. `mcuconf.h`: Added `RP_SIO_USE_UART0 TRUE` and `RP_SIO_USE_UART1 TRUE` -- enables both UART peripherals in ChibiOS SIO driver

**Assessment:** The `SERIAL_PIO_USE_PIO1` define is likely needed to avoid PIO0 conflict with WS2812. However, the left half's config.h already undefines WS2812_DI_PIN (`#undef WS2812_DI_PIN`), which disables WS2812 on the left. The right half does not override WS2812_DI_PIN, so WS2812 may still be active on the right half (GP24 is the shared WS2812 pin in the board-level config.h, and GP24 is also listed as a matrix column pin). This warrants investigation during the build -- if WS2812 and PIO serial compete for PIO0, the PIO1 override is essential.

The mcuconf.h UART enables may be unnecessary since the serial driver uses PIO, not hardware UART. The `HAL_USE_SIO TRUE` in halconf.h and the UART enables may have been added during initial development and never removed. They should not cause build errors but may waste a small amount of RAM for unused driver objects.

### Pitfall 2: Stale Build Artifacts

**What goes wrong:** `make` performs incremental builds by default. If source files changed between phases but object files were not cleaned, the build may use stale object files.
**Why it happens:** The `.build/` directory contains artifacts from a February 2 build, before any of the Phase 1-6 changes.
**How to avoid:** Run `make clean` before building, or use `make hidpress/bipedalambi:vial_left FORCE=true` to force a full rebuild.
**Warning signs:** Build succeeds but firmware behavior does not match source code changes.

### Pitfall 3: Flashing Wrong Firmware to Wrong Half

**What goes wrong:** The user copies `vial_left.uf2` to the right half or vice versa. The firmware boots with wrong GPIO pin configurations, causing non-functional keyboard or potential GPIO conflicts.
**Why it happens:** Both UF2 files look identical from the outside. The mass storage drive is always named "RPI-RP2" regardless of which half is in bootloader mode.
**How to avoid:** Document a clear procedure: flash left half first, verify it boots, then flash right half. Label the UF2 files clearly. The left/right firmware file names are already distinct (`vial_left.uf2` vs `vial_right.uf2`).
**Warning signs:** After flashing, keyboard half does not respond to keys, OLED shows unexpected content, or USB enumerates with wrong behavior.

### Pitfall 4: EEPROM Not Cleared After Flash

**What goes wrong:** New firmware reads stale EEPROM data with wrong layout assumptions, causing layer offset bugs, wrong actuation settings, or Vial showing corrupted data.
**Why it happens:** Flashing new firmware does NOT clear EEPROM. The RP2040 wear-leveling EEPROM is in a different flash sector than the firmware. The old EEPROM data persists across firmware updates.
**How to avoid:** ALWAYS clear EEPROM after flashing when the EEPROM layout has changed (which it has -- rows changed from 4 to 8, NUM_ENCODERS changed from 2 to 1). Use EE_CLR key (Method 1) or Bootmagic (Method 2).
**Warning signs:** After flashing, Vial shows wrong layer content, layers are still offset, or keyboard behaves like old firmware.

### Pitfall 5: Build Fails Due to Missing Submodules

**What goes wrong:** ChibiOS or pico-sdk submodules are not checked out, causing missing header errors.
**Why it happens:** The vial-qmk repo uses git submodules for dependencies.
**How to avoid:** Verify submodules are present: `git submodule status` should show commit hashes without `-` prefix for lib/chibios, lib/chibios-contrib, and lib/pico-sdk.
**Warning signs:** Build errors mentioning missing `ch.h`, `hal.h`, `pico/bootrom.h`, or similar headers.

**Current status:** All submodules verified present and checked out:
- lib/chibios: `be44b33`
- lib/chibios-contrib: `77cb0a4`
- lib/pico-sdk: `a3398d8`

### Pitfall 6: ARM Toolchain Version Incompatibility

**What goes wrong:** GCC 15.x may introduce new warnings-as-errors or deprecations that did not exist with older toolchain versions.
**Why it happens:** The installed toolchain is very recent (GCC 15.2.1, dated 2025-12-03). QMK/vial-qmk was developed against older GCC versions (typically 10.x-13.x).
**How to avoid:** If the build fails with new warnings, try building with `make EXTRAFLAGS=-Wno-error` or investigate specific warning suppressions.
**Warning signs:** Build errors that are warnings promoted to errors (e.g., `-Werror=...`), or new warnings about deprecated features.

## Code Examples

### Build Commands

```bash
# Full clean build of both halves (from repo root)
cd /Users/matthewthomas/dev/vial-qmk
make clean
make hidpress/bipedalambi:vial_left
make hidpress/bipedalambi:vial_right

# Verbose build (for debugging compile errors)
make hidpress/bipedalambi:vial_left VERBOSE=true

# Build + auto-flash (device must be in bootloader mode)
make hidpress/bipedalambi:vial_left:flash
```

**Source:** QMK build system (`Makefile`, `builddefs/common_rules.mk`)

### Flash Procedure (Manual UF2 Copy)

```bash
# After entering bootloader mode on a half:
# macOS: drive mounts at /Volumes/RPI-RP2
cp /Users/matthewthomas/dev/vial-qmk/.build/hidpress_bipedalambi_vial_left.uf2 /Volumes/RPI-RP2/

# The drive auto-ejects and the keyboard reboots with new firmware.
# Repeat for the other half with the correct UF2 file.
```

**Source:** RP2040 UF2 bootloader specification

### EEPROM Clear After Flash

```
# For each half (connect one at a time via USB):
#
# Method 1: EE_CLR key (keyboard must be running new firmware)
#   Left:  Hold MO(1) at KC_MINS position + press KC_DOWN position
#   Right: Hold MO(1) at bottom key + press KC_EQL position
#   -> Keyboard reboots with defaults
#
# Method 2: Bootmagic (works even if firmware is broken)
#   Left:  Hold KC_ESC while plugging in USB -> enters bootloader
#   Right: Hold KC_BSPC while plugging in USB -> enters bootloader
#   -> Power cycle to boot normally with cleared EEPROM
```

**Source:** `bipedalambi/EEPROM-CLEAR-PROCEDURE.md`

## Detailed Findings

### Finding 1: Existing Build Artifacts Are From Before Phase 1-6 Changes

The `.build/` directory contains UF2 files dated February 2, 2026. All Phase 1-6 changes (vial.json matrix rows fix, KLE row remapping, NUM_ENCODERS fix, eeconfig_init_user addition, EE_CLR keycode) were made after that date. The existing UF2 files are stale and must not be flashed -- a clean rebuild is required.

**Confidence:** HIGH -- verified from `ls -la .build/*.uf2` (Feb 2) vs `git log` (Phase 3+ commits are Feb 14)

### Finding 2: Uncommitted Config Changes May Be Needed for Build

Two files have uncommitted changes that affect compilation:

1. **`config.h` +1 line:** `#define SERIAL_PIO_USE_PIO1` -- This redirects the PIO serial driver from PIO0 to PIO1. The comment says "PIO0 used by WS2812." On the left half, WS2812_DI_PIN is `#undef`'d (disabled), so PIO0 should be free. On the right half, WS2812_DI_PIN (GP24) is NOT undefined -- but GP24 is also a right-half matrix column pin (col 0), meaning there could be a pin conflict regardless. This define may be needed for the right half, or it may be a leftover from troubleshooting.

2. **`mcuconf.h` +8 lines:** Enables `RP_SIO_USE_UART0` and `RP_SIO_USE_UART1`. The board default (GENERIC_PROMICRO_RP2040) already enables UART0 and disables UART1. The keyboard's mcuconf.h overrides both to TRUE. Since the serial driver uses PIO (not hardware UART), these UART enables may be unnecessary. However, they should not cause build errors.

**Assessment:** These changes should be tested by building with them included (as they are in the working tree). If the build succeeds, they can be committed as part of 07-01. If they cause issues, they can be investigated.

**Confidence:** HIGH for the factual description of what the changes are; MEDIUM for whether they are strictly necessary

### Finding 3: Right Half WS2812 Pin Conflict Needs Attention

The board-level `config.h` defines `WS2812_DI_PIN GP24`. The left keymap's config.h does `#undef WS2812_DI_PIN` to disable it (GP24 is used as matrix col 0 on the left). The right keymap's config.h does NOT undefine WS2812_DI_PIN. However:

- The right half uses GP1 as matrix col 0, not GP24
- GP24 does not appear in the right half's matrix pins
- The right half's `rules.mk` sets `POINTING_DEVICE_ENABLE = no` and `POINTING_DEVICE_DRIVER = none`
- The board-level `rules.mk` has `WS2812_DRIVER = vendor`

If WS2812 is still enabled on the right half (because WS2812_DI_PIN is defined and WS2812_DRIVER is set), the WS2812 driver may claim PIO0 on the right half. With `SERIAL_PIO_USE_PIO1` defined in the shared config.h, the serial driver uses PIO1, avoiding the conflict. This would make the `SERIAL_PIO_USE_PIO1` define necessary.

**Confidence:** MEDIUM -- the exact interaction between WS2812 driver and PIO allocation depends on whether WS2812 is actually compiled in when no RGB features are enabled. The build will resolve this definitively.

### Finding 4: `make flash` Auto-Detection Works for RP2040

The QMK build system recognizes the `rp2040` bootloader type and uses `uf2conv.py --wait --deploy` for flashing. This tool polls for a UF2-compatible device (the RPI-RP2 mass storage drive) and deploys the firmware when detected. The `--wait` flag means it will block until a device appears.

The user can use either:
1. `make hidpress/bipedalambi:vial_left:flash` (build + wait for device + flash)
2. Manual UF2 copy to /Volumes/RPI-RP2/

Both are equivalent. Manual copy is simpler for users unfamiliar with `make flash`.

**Confidence:** HIGH -- verified from `platforms/chibios/flash.mk` lines 106-107 and `builddefs/common_rules.mk`

### Finding 5: Double-Tap Reset Is Configured

The firmware defines `RP2040_BOOTLOADER_DOUBLE_TAP_RESET` with a 200ms timeout. This means rapidly pressing the reset button twice will enter bootloader mode without needing to hold BOOTSEL. The implementation is in `platforms/chibios/bootloaders/rp2040.c` using a magic token in uninitialized RAM.

This provides a third method to enter bootloader mode (in addition to BOOTSEL button and Bootmagic). This is useful because the user does not need to disconnect the USB cable.

**Confidence:** HIGH -- verified from `config.h` defines and `rp2040.c` implementation

### Finding 6: Phase 7 Is Split Between Claude-Executable and User-Only Tasks

| Task | Who Does It | Why |
|------|-------------|-----|
| Compile both halves | Claude (via `make`) | No hardware needed |
| Resolve build errors | Claude (code changes) | Can edit source and retry |
| Enter bootloader mode | User only | Requires physical button press or USB cable manipulation |
| Flash UF2 firmware | User only | Requires physical mass storage copy |
| Clear EEPROM (EE_CLR) | User only | Requires physical key press on connected keyboard |
| Clear EEPROM (Bootmagic) | User only | Requires physical key hold while plugging in |
| Verify boot success | User only | Requires physical observation of keyboard + OLED |

**Confidence:** HIGH -- fundamental hardware/software boundary

## State of the Art

| Old Approach | Current Approach | When Changed | Impact |
|--------------|------------------|--------------|--------|
| Build with stale vial.json (rows=4) | Build with fixed vial.json (rows=8) | Phase 3 | Dynamic keymap now has correct EEPROM layout |
| Build with NUM_ENCODERS auto-doubled | Build with NUM_ENCODERS=1 explicit | Phase 4 | Encoder EEPROM region correctly sized |
| No eeconfig_init_user | eeconfig_init_user(0x200) | Phase 6 | EEPROM clear restores sane defaults |
| No EE_CLR key in keymap | EE_CLR on layer 1 | Phase 6 | User can clear EEPROM without Bootmagic |
| .uf2 files from Feb 2 build | New .uf2 with all fixes | Phase 7 (this phase) | All fixes compiled into firmware |

## Open Questions

1. **Are the uncommitted config.h and mcuconf.h changes needed?**
   - What we know: They add `SERIAL_PIO_USE_PIO1` and SIO UART enables. They are in the working tree and will be compiled.
   - What's unclear: Whether they are strictly required for the build to succeed, or if they are leftover from earlier development.
   - Recommendation: Build with them included. If the build succeeds, commit them with a note. If they cause issues, investigate. The safest approach is to include them -- they should not hurt even if unnecessary. The `SERIAL_PIO_USE_PIO1` is likely needed for the right half where WS2812 may claim PIO0.

2. **Will GCC 15.2.1 produce new warnings-as-errors?**
   - What we know: The previous successful build (Feb 2) used the same or similar toolchain. The Phase 1-6 changes are in config/JSON/C source files, not compiler options.
   - What's unclear: Whether any of the code changes (eeconfig_init_user, EE_CLR) introduce patterns that GCC 15 warns about.
   - Recommendation: Build and check. If new warnings appear, address them individually.

3. **Should `make clean` be run before building?**
   - What we know: Stale build artifacts from Feb 2 exist. Source files have changed significantly since then.
   - What's unclear: Whether QMK's incremental build correctly detects all changed dependencies (config.h changes, vial.json changes for vial.json compilation, etc.).
   - Recommendation: Yes, run `make clean` first for a guaranteed clean build. The build time cost is small (under 2 minutes per half on modern hardware).

## Sources

### Primary (HIGH confidence)
- `keyboards/hidpress/bipedalambi/rules.mk` -- MCU=RP2040, BOOTLOADER=rp2040, driver configuration
- `keyboards/hidpress/bipedalambi/config.h` -- Matrix dimensions, serial config, bootloader double-tap
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/config.h` -- Left half pin assignments, joystick config
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/config.h` -- Right half pin assignments, encoder config, NUM_ENCODERS=1
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/rules.mk` -- VIA_ENABLE, VIAL_ENABLE, LTO_ENABLE
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/rules.mk` -- VIA_ENABLE, VIAL_ENABLE, ENCODER_ENABLE, ENCODER_MAP_ENABLE
- `platforms/chibios/flash.mk` lines 106-107 -- RP2040 flash target uses `EXEC_UF2_UTIL_DEPLOY`
- `platforms/chibios/mcu_selection.mk` lines 168-177 -- RP2040 defaults: UF2_FAMILY=RP2040, FIRMWARE_FORMAT=uf2
- `platforms/chibios/bootloader.mk` lines 125-128 -- rp2040 bootloader type definition
- `platforms/chibios/bootloaders/rp2040.c` -- Double-tap reset implementation
- `builddefs/common_rules.mk` lines 154-158, 234-235 -- UF2 conversion rules
- `git submodule status` -- All submodules verified present (ChibiOS, pico-sdk, etc.)
- `arm-none-eabi-gcc --version` -- Toolchain version 15.2.1 confirmed
- `ls -la .build/*.uf2` -- Stale build artifacts from Feb 2
- `git diff HEAD -- keyboards/hidpress/` -- Uncommitted changes to config.h and mcuconf.h
- `bipedalambi/EEPROM-CLEAR-PROCEDURE.md` -- Existing per-half clear procedure documentation

### Secondary (MEDIUM confidence)
- Phase 4 summary (04-01-SUMMARY.md) -- NUM_ENCODERS=1 change, EEPROM layout impact
- Phase 6 summary (06-01-SUMMARY.md) -- eeconfig_init_user and EE_CLR additions
- Phase 6 research (06-RESEARCH.md) -- Detailed eeconfig_init_user and QK_CLEAR_EEPROM analysis

### Tertiary (LOW confidence)
- Assessment of whether `SERIAL_PIO_USE_PIO1` is strictly required or just defensive -- needs build testing to confirm

## Metadata

**Confidence breakdown:**
- Build commands and toolchain: HIGH -- verified from Makefile, mcu_selection.mk, and installed tools
- UF2 flash procedure: HIGH -- verified from flash.mk and RP2040 bootloader spec
- EEPROM clear procedure: HIGH -- documented in Phase 6, verified from QMK source
- Uncommitted changes impact: MEDIUM -- factual description is HIGH, necessity assessment is MEDIUM
- Build error prediction: MEDIUM -- previous builds succeeded, but changes have been made and toolchain is newer

**Research date:** 2026-02-14
**Valid until:** Indefinite for build system and flash procedure; re-verify if toolchain is updated or QMK fork is rebased
