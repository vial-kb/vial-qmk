# Serial/Split Configuration Audit

Audit of all serial communication and split keyboard configuration for the Bipedal Ambi RP2040 split keyboard.

**Audit Date:** 2026-02-14
**Firmware:** vial_left / vial_right keymaps
**Board:** keyboards/hidpress/bipedalambi

## Summary Table

| Requirement | File(s) | Finding | Status |
|---|---|---|---|
| AUDIT-01: Serial Driver Type | rules.mk:5, serial_vendor.c | `SERIAL_DRIVER = vendor` compiles PIO-based driver | OK |
| AUDIT-02: TX/RX Pin Assignments | keymaps/vial_left/config.h:15-16, keymaps/vial_right/config.h:15-16 | Left: GP0 TX / GP1 RX, Right: GP17 TX / GP16 RX. No pin conflicts found. PCB routing unverifiable from firmware. | OK (pins) / UNVERIFIED (wiring) |
| AUDIT-03: PIO Peripheral Assignments | config.h:8, ws2812_vendor.c | Serial on PIO1. WS2812 driver never compiled (RGBLIGHT disabled). PIO0 is completely free. No conflict. | OK |
| AUDIT-04: Full-Duplex Config | config.h:6, serial_vendor.c:43-51, 433-462 | Full-duplex enabled. No PIN_SWAP. Both halves TX on own TX pin, RX on own RX pin. Requires crossed wiring on TRRS. | OK (config) / UNVERIFIED (wiring) |
| AUDIT-05: Split Detection | config.h:7 | SPLIT_USB_DETECT only. No EE_HANDS, MASTER_LEFT, MASTER_RIGHT. Standard config. | OK |
| AUDIT-06: ChibiOS Peripheral Activation | halconf.h:5, mcuconf.h:17-23 | HAL_USE_SIO TRUE + RP_SIO_USE_UART0/UART1 TRUE. Unnecessary for vendor driver. Init resets UART peripherals but does NOT configure GPIO mux. Wasteful, unlikely harmful. | SUSPECT |
| AUDIT-07: info.json Split Config | info.json:13-15 | Minimal split config. No serial pin config in JSON. No conflict with config.h/rules.mk. | OK |

---

## Detailed Findings

### AUDIT-01: Serial Driver Type

**Status: OK**

**Evidence:**
- `rules.mk` line 5: `SERIAL_DRIVER = vendor`
- `builddefs/common_features.mk` line 694: sets `OPT_DEFS += -DSERIAL_DRIVER_VENDOR`
- `builddefs/common_features.mk` lines 698-699: compiles `serial_protocol.c` and `serial_vendor.c`
- `serial_vendor.c` line 6: `#include "hardware/pio.h"` -- uses RP2040 PIO SDK directly
- `serial_vendor.c` line 400: `pio_claim_unused_sm(pio, true)` -- claims PIO state machines
- `serial_vendor.c` does NOT use ChibiOS SIO/UART HAL (`sioStart`, `QMKSerialDriver`, `SIOD` never referenced)

**Analysis:**
The vendor driver is the correct choice for RP2040 split keyboards. It uses the Programmable I/O (PIO) peripheral directly via the Pico SDK, bypassing the ChibiOS HAL entirely. This provides deterministic bit-banged UART communication through PIO state machines, which is the standard approach for QMK split keyboards on RP2040.

**Verdict:** CORRECT. The vendor driver is PIO-based and appropriate for RP2040.

---

### AUDIT-02: TX/RX Pin Assignments

**Status: OK (pin definitions) / UNVERIFIED (PCB routing)**

**Evidence:**
- Left half (`keymaps/vial_left/config.h` lines 13-16):
  ```c
  #undef SERIAL_USART_TX_PIN
  #undef SERIAL_USART_RX_PIN
  #define SERIAL_USART_TX_PIN GP0
  #define SERIAL_USART_RX_PIN GP1
  ```
- Right half (`keymaps/vial_right/config.h` lines 13-16):
  ```c
  #undef SERIAL_USART_TX_PIN
  #undef SERIAL_USART_RX_PIN
  #define SERIAL_USART_TX_PIN GP17
  #define SERIAL_USART_RX_PIN GP16
  ```

**Pin Conflict Analysis:**
- Left GP0: Used only as SERIAL_USART_TX_PIN. Not in left matrix pins (GP27, GP25, GP18, GP17, GP24, GP23, GP21, GP20, GP19, GP26, GP16). No conflict.
- Left GP1: Used only as SERIAL_USART_RX_PIN. Not in left matrix pins. No conflict.
- Right GP17: Used only as SERIAL_USART_TX_PIN. Not in right matrix row pins (GP0, GP11, GP25, GP26) or col pins (GP1, GP2, GP3, GP4, GP5, GP10, GP27). No conflict.
- Right GP16: Used only as SERIAL_USART_RX_PIN. Not in right matrix pins. No conflict.

**CRITICAL NOTE -- Right half GP0 and GP1:**
- Right matrix ROW 0 = GP0 (keymaps/vial_right/config.h line 31)
- Right matrix COL 0 = GP1 (keymaps/vial_right/config.h line 32)
- Left serial TX = GP0, Left serial RX = GP1
- These are DIFFERENT physical MCUs (left RP2040 vs right RP2040), so there is NO electrical conflict. Each half has its own GPIO namespace.

**PCB Routing (unverifiable from firmware):**
For full-duplex communication without PIN_SWAP, the TRRS cable must cross:
- Left TX (GP0) wire --> Right RX (GP16) pad
- Left RX (GP1) wire --> Right TX (GP17) pad

This crossing cannot be verified from config files alone. The user must confirm from the PCB schematic or TRRS jack wiring diagram.

**Verdict:** Pin assignments are internally consistent with no conflicts. PCB routing requires physical verification.

---

### AUDIT-03: PIO Peripheral Assignments

**Status: OK**

**Evidence:**
- Serial PIO selection (`config.h` line 8): `#define SERIAL_PIO_USE_PIO1`
- `serial_vendor.c` lines 21-22: `#if defined(SERIAL_PIO_USE_PIO1)` -> `static const PIO pio = pio1;`
- Serial uses PIO1 with 2 state machines (TX SM + RX SM for full-duplex)
- WS2812 driver in `rules.mk` line 6: `WS2812_DRIVER = vendor`
- WS2812 pin in `config.h` line 20: `#define WS2812_DI_PIN GP24`

**WS2812 Compilation Analysis:**
- `builddefs/common_features.mk` line 936: `ifeq ($(strip $(WS2812_DRIVER_REQUIRED)), yes)` -- ws2812_vendor.c is ONLY compiled when `WS2812_DRIVER_REQUIRED = yes`
- `WS2812_DRIVER_REQUIRED` is set to `yes` only when:
  - `RGBLIGHT_ENABLE = yes` with `ws2812` driver (line 321), OR
  - `RGB_MATRIX_ENABLE = yes` with `ws2812` driver (line 555)
- `info.json` line 45: `"rgblight": false`
- No `RGBLIGHT_ENABLE = yes` or `RGB_MATRIX_ENABLE = yes` found anywhere in the bipedalambi tree
- **Therefore: ws2812_vendor.c is NEVER compiled. The WS2812 PIO driver is not linked into the firmware.**

**Left half specifics:**
- `keymaps/vial_left/config.h` line 35: `#undef WS2812_DI_PIN` -- explicitly disables WS2812 (GP24 used for matrix Col 0)
- Even if WS2812 were compiled, the left half would not initialize it

**Right half specifics:**
- `keymaps/vial_right/config.h`: Does NOT `#undef WS2812_DI_PIN` -- inherits `GP24` from board-level config.h
- However, since ws2812_vendor.c is never compiled, this is irrelevant at runtime
- GP24 is not in the right matrix (right uses GP0-GP5, GP10, GP11, GP25-GP27) -- no pin conflict exists

**Contrast with bipedal65 (non-split, known working):**
- `bipedal65/config.h` line 19: `#define WS2812_PIO_USE_PIO1` -- moves WS2812 to PIO1
- bipedal65 has no serial, so it can use PIO1 for WS2812
- bipedalambi takes the opposite approach: serial on PIO1, WS2812 not compiled

**Verdict:** No PIO conflict. Serial uses PIO1. PIO0 is completely unused. The WS2812 driver code is not even compiled into the firmware because RGBLIGHT is disabled.

---

### AUDIT-04: Full-Duplex Configuration

**Status: OK (configuration) / UNVERIFIED (physical wiring)**

**Evidence:**
- `config.h` line 6: `#define SERIAL_USART_FULL_DUPLEX`
- `serial_vendor.c` lines 43-51: Full-duplex uses `out pins` instruction (transmits on dedicated TX pin)
- `serial_vendor.c` lines 178-182: Full-duplex disables the half-duplex TX/RX switching (`enter_rx_state` and `leave_rx_state` are no-ops)

**PIN_SWAP Analysis:**
- `SERIAL_USART_PIN_SWAP` is NOT defined anywhere in the bipedalambi tree (confirmed via grep)
- `serial_vendor.c` lines 442-446 (master init):
  ```c
  #if defined(SERIAL_USART_PIN_SWAP)
      pio_init(rx_pin, tx_pin);  // Swapped
  #else
      pio_init(tx_pin, rx_pin);  // Normal
  #endif
  ```
- Without PIN_SWAP, master calls `pio_init(tx_pin, rx_pin)`:
  - Left (master): TX on GP0, RX on GP1
- `serial_vendor.c` line 461 (slave init): Always calls `pio_init(tx_pin, rx_pin)`:
  - Right (slave): TX on GP17, RX on GP16

**Communication Path:**
- Left transmits on GP0, Left receives on GP1
- Right transmits on GP17, Right receives on GP16
- For data flow: Left GP0 must be wired to Right GP16 (TX-to-RX crossing)
- And: Right GP17 must be wired to Left GP1 (TX-to-RX crossing)
- This is the standard TRRS full-duplex crossing pattern

**Verdict:** Full-duplex configuration is internally correct. The PIO programs use `out pins` for dedicated TX output and `in pins` for dedicated RX input. Whether the physical TRRS wiring implements the required TX/RX crossing cannot be determined from firmware config alone.

---

### AUDIT-05: Split Detection Configuration

**Status: OK**

**Evidence:**
- `config.h` line 7: `#define SPLIT_USB_DETECT`
- No `EE_HANDS`, `MASTER_LEFT`, or `MASTER_RIGHT` defined anywhere (confirmed via grep)

**Analysis:**
- `SPLIT_USB_DETECT` determines master/slave by detecting USB VBUS (5V from USB host)
- The half connected to USB is master; the other is slave
- This uses hardware voltage detection on the USB VBUS pin, NOT serial communication
- If serial fails, the slave still correctly identifies as slave (no USB VBUS present)
- The slave will then attempt to initialize serial communication with the master

**Risk Assessment:**
- If serial communication fails entirely, the slave half still boots and identifies correctly
- The slave's keys will not register on the master, but there is no chicken-and-egg deadlock
- SPLIT_USB_DETECT is the standard and recommended approach for RP2040 split boards
- The dual-USB + TRRS monitor flicker issue (noted in STATE.md) is a separate VCC backfeed problem, not a SPLIT_USB_DETECT issue

**Verdict:** Standard configuration. No issues expected from split detection itself.

---

### AUDIT-06: ChibiOS Peripheral Activation

**Status: SUSPECT**

**Evidence:**
- `halconf.h` line 5: `#define HAL_USE_SIO TRUE  // Required for serial communication`
- `mcuconf.h` lines 17-19: `#define RP_SIO_USE_UART0 TRUE` (comment: "Enable UART0 for serial (LEFT side uses GP0/GP1)")
- `mcuconf.h` lines 21-23: `#define RP_SIO_USE_UART1 TRUE` (comment: "Enable UART1 for serial (RIGHT side uses GP16/GP17)")

**Driver Path Analysis:**
The comment "Required for serial communication" in halconf.h is WRONG. Here is why:

1. `HAL_USE_SIO TRUE` tells ChibiOS to compile its SIO (Serial I/O) HAL driver
2. `RP_SIO_USE_UART0/UART1 TRUE` tells ChibiOS to instantiate SIODriver objects for UART0/UART1
3. The ChibiOS SIO HAL manages the RP2040's hardware UART peripherals (not PIO)
4. The `serial_vendor.c` driver (compiled for `SERIAL_DRIVER = vendor`) uses PIO directly via the Pico SDK
5. `serial_vendor.c` NEVER references `QMKSerialDriver`, `SIOD0`, `SIOD1`, `sioStart`, or any SIO API (confirmed via grep)

**What happens at boot:**
- ChibiOS HAL init calls `sio_lld_init()` (`hal_sio_lld.c` lines 151-163)
- `sio_lld_init()` calls `hal_lld_peripheral_reset(RESETS_ALLREG_UART0)` and `hal_lld_peripheral_reset(RESETS_ALLREG_UART1)`
- This puts UART0 and UART1 hardware into RESET state (held in reset)
- It does NOT configure GPIO pin mux -- on RP2040, GPIO function selection is in the IO bank, not the UART peripheral
- Nobody calls `sioStart()`, so `sio_lld_start()` never runs, UART peripherals stay in reset, no pin mux changes occur
- Later, `serial_vendor.c` calls `palSetLineMode(tx_pin, PAL_MODE_ALTERNATE_PIO1)` to configure GPIO pins for PIO1

**Cross-reference with bipedal65 (non-split, known working):**
- `bipedal65/halconf.h`: Only `HAL_USE_I2C TRUE` -- does NOT enable HAL_USE_SIO
- `bipedal65/mcuconf.h`: Only enables I2C0 -- no UART config
- This confirms: SIO/UART config was added specifically for bipedalambi, based on a misunderstanding that the vendor serial driver uses ChibiOS SIO

**Impact Analysis:**
- `sio_lld_init()` resets UART0/UART1 peripherals (puts them in reset state) -- this is benign
- UART peripherals in reset do not affect GPIO mux or PIO operation
- The SIO driver objects (`SIOD0`, `SIOD1`) are initialized but never started
- Memory cost: Two `SIODriver` structs allocated but unused
- Code cost: SIO HAL driver compiled and linked unnecessarily
- No GPIO pin mux conflict because `sio_lld_start()` is never called

**serial_usart.h Concern:**
- `serial_vendor.c` line 4: `#include "serial_usart.h"`
- `serial_usart.h` lines 56-64: When `HAL_USE_SIO` is true, defines `QMKSerialDriver` as `SIODriver` and defaults `SERIAL_USART_DRIVER` to `SIOD1`
- These typedefs/defines are compiled but NEVER USED by serial_vendor.c
- No functional impact, but the header inclusion creates misleading compile-time definitions

**Verdict:** SUSPECT. The HAL_USE_SIO and RP_SIO_USE_UART0/UART1 configuration is unnecessary for the vendor (PIO) serial driver. While the analysis shows this likely does NOT cause the serial failure (UART peripherals stay in reset, no GPIO mux conflict), it represents a misconfiguration that should be cleaned up. Removing it is a low-risk, high-value test to eliminate as a variable.

---

### AUDIT-07: info.json Split Config

**Status: OK**

**Evidence:**
- `info.json` lines 13-15:
  ```json
  "split": {
      "enabled": true
  }
  ```
- No `"serial"` key in info.json -- all serial pin config is in config.h files
- `info.json` `features.split: true` (line 48) matches `split.enabled: true`
- `matrix_pins` in info.json match the LEFT half pin assignments (default/board-level)
- No conflicting serial, transport, or split configuration in info.json

**Analysis:**
QMK info.json can optionally specify serial pins and split transport settings. This board uses config.h exclusively for serial configuration, which is the standard approach for complex split boards with per-half pin differences. The minimal `"split": { "enabled": true }` simply tells QMK this is a split keyboard, delegating all transport details to config.h and rules.mk.

**Verdict:** Clean. No info.json conflicts with config.h or rules.mk settings.

---

## Hypothesis Priority List

Hypotheses ranked from most to least likely cause of serial communication failure, based on audit evidence.

### Ranking Criteria

- **Severity:** Could this PREVENT serial communication entirely?
- **Confidence:** How certain are we from config analysis alone?
- **Testability:** Can this be tested with a single firmware change?

---

### H1: HAL_USE_SIO / UART Peripheral Misconfiguration

**Audit Evidence:** AUDIT-06
**Severity:** MEDIUM -- UART peripherals held in reset, unlikely to block PIO but unverified
**Confidence:** HIGH -- clear misconfiguration (vendor driver = PIO, not SIO/UART)
**Testability:** HIGH -- single change: remove 3 lines from halconf.h and mcuconf.h
**Could be sole cause:** UNLIKELY but possible -- if ChibiOS SIO init has side effects beyond what source analysis reveals (e.g., interaction with clock or pad configuration at the HAL level)

**Proposed Test:** Remove `HAL_USE_SIO TRUE` from halconf.h and `RP_SIO_USE_UART0 TRUE` / `RP_SIO_USE_UART1 TRUE` from mcuconf.h. This is the safest first test because it removes known-unnecessary configuration with zero risk of breaking PIO serial. Maps to new DIAG-00 (insert before existing DIAG-01).

**Rationale for #1 ranking:** Even though source analysis suggests this is benign, it is the ONLY confirmed misconfiguration found in the audit. Every other config surface is either OK or unverifiable. This should be eliminated first as a variable because: (a) it is the easiest fix, (b) it has zero risk, (c) the "Required for serial communication" comment proves the original author believed this was needed, suggesting they may have been following a USART-driver guide rather than a PIO-vendor guide, and (d) removing it aligns the config with bipedal65 (known working RP2040 board).

---

### H2: TX/RX Wiring Mismatch on TRRS

**Audit Evidence:** AUDIT-02, AUDIT-04
**Severity:** HIGH -- if TX/RX are not crossed on the PCB, full-duplex communication is impossible
**Confidence:** MEDIUM -- firmware config is correct, but physical wiring is unverified
**Testability:** MEDIUM -- requires either (a) PCB schematic review, (b) multimeter continuity test, or (c) trying PIN_SWAP in firmware
**Could be sole cause:** YES -- incorrect TX/RX routing would completely prevent communication

**Proposed Test:** Two approaches:
1. (Preferred) User verifies TRRS jack wiring from PCB schematic/KiCad files -- confirms Left GP0 connects to Right GP16, and Left GP1 connects to Right GP17. Maps to DIAG-03.
2. (Firmware) Try adding `#define SERIAL_USART_PIN_SWAP` to config.h -- this swaps TX/RX on the master side only. If communication starts working, the wiring is straight-through rather than crossed. Maps to DIAG-04.

**Rationale for #2 ranking:** This is the most likely hardware-level cause. Power routing works (slave OLED lights up via TRRS), confirming VCC and GND traces are correct. But data line routing is a separate concern. TRRS jacks can route the data pins in many configurations.

---

### H3: Half-Duplex as Diagnostic Workaround

**Audit Evidence:** AUDIT-04
**Severity:** N/A -- this is a diagnostic tool, not a failure cause
**Confidence:** HIGH -- half-duplex eliminates RX pin and crossing as variables
**Testability:** HIGH -- remove `SERIAL_USART_FULL_DUPLEX`, use only TX pin
**Could be sole cause:** N/A (workaround)

**Proposed Test:** Remove `#define SERIAL_USART_FULL_DUPLEX` from config.h. In half-duplex mode, only the TX pin is used for bidirectional communication on a single wire. This eliminates RX pin assignment and TX/RX crossing as variables. If half-duplex works, the problem is in the full-duplex wiring (H2). Maps to DIAG-02.

**Rationale for #3 ranking:** This is not a hypothesis about a root cause but a powerful diagnostic tool. If H1 (removing SIO config) doesn't fix the problem, switching to half-duplex isolates whether the issue is wiring-related (H2) or something else entirely.

---

### H4: WS2812 Driver Residual on Right Half

**Audit Evidence:** AUDIT-03
**Severity:** LOW -- WS2812 driver is never compiled, so no runtime impact
**Confidence:** HIGH -- build system analysis confirms ws2812_vendor.c is not linked
**Testability:** LOW -- no test needed; this is confirmed as a non-issue
**Could be sole cause:** NO

**Original Concern:** The right keymap config.h does not `#undef WS2812_DI_PIN`, so GP24 remains defined as the WS2812 data pin. The plan hypothesized this could cause PIO0 contention.

**Resolution:** Build system analysis (`builddefs/common_features.mk` lines 936-943) proves `ws2812_vendor.c` is only compiled when `WS2812_DRIVER_REQUIRED = yes`, which requires `RGBLIGHT_ENABLE = yes` or `RGB_MATRIX_ENABLE = yes`. Neither is enabled. The WS2812 driver code is not in the firmware binary. PIO0 is completely free.

**Recommendation:** While not a serial issue, adding `#undef WS2812_DI_PIN` to `keymaps/vial_right/config.h` is good hygiene to prevent future confusion.

---

### H5: SPLIT_USB_DETECT Timing

**Audit Evidence:** AUDIT-05
**Severity:** LOW -- SPLIT_USB_DETECT uses VBUS hardware sensing, not serial
**Confidence:** HIGH -- this is the standard approach, well-tested across QMK ecosystem
**Testability:** HIGH -- replace with `MASTER_LEFT` for testing
**Could be sole cause:** VERY UNLIKELY

**Proposed Test:** If all other hypotheses fail, temporarily replace `#define SPLIT_USB_DETECT` with `#define MASTER_LEFT` in config.h. This hardcodes the left half as master, eliminating USB detection as a variable. Maps to DIAG-05.

**Rationale for #5 ranking:** SPLIT_USB_DETECT works independently of serial communication. The slave detects it lacks USB VBUS (5V) and identifies as slave, then attempts serial communication. Even if serial is broken, slave identification is correct. This is the least likely cause.

---

## Recommended Phase 10 Test Order

Based on the hypothesis ranking, the recommended diagnostic test order is:

| Priority | Test ID | Hypothesis | Action | Risk |
|---|---|---|---|---|
| 1 | DIAG-00 (new) | H1: SIO/UART cleanup | Remove HAL_USE_SIO, RP_SIO_USE_UART0/UART1 | Zero risk |
| 2 | DIAG-02 | H3: Half-duplex diagnostic | Remove SERIAL_USART_FULL_DUPLEX | Low risk, diagnostic |
| 3 | DIAG-03 | H2: Wiring verification | User checks PCB schematic/TRRS routing | No firmware change |
| 4 | DIAG-04 | H2: PIN_SWAP test | Add SERIAL_USART_PIN_SWAP | Low risk, reversible |
| 5 | DIAG-05 | H5: MASTER_LEFT test | Replace SPLIT_USB_DETECT with MASTER_LEFT | Low risk, reversible |

**Key insight:** DIAG-00 and DIAG-02 can be combined into a single firmware flash if DIAG-00 alone does not fix the issue. The most efficient path is:
1. Flash with SIO removed (DIAG-00) -- tests H1 in isolation
2. If still failing, flash with SIO removed AND half-duplex (DIAG-00 + DIAG-02) -- isolates wiring vs config
3. If half-duplex works, the problem is wiring (H2) -- verify with DIAG-03/DIAG-04
4. If half-duplex also fails, deeper investigation needed (PIO init failure, clock, etc.)
