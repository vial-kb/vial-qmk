# Phase 6: Defensive EEPROM Improvements - Research

**Researched:** 2026-02-14
**Domain:** QMK eeconfig_init_user callback, QK_CLEAR_EEPROM keycode, and EEPROM clear documentation for split keyboards
**Confidence:** HIGH

## Summary

Phase 6 adds three defensive improvements to the Bipedal Ambi firmware: (1) an `eeconfig_init_user()` callback in both keymap.c files that writes sane defaults when EEPROM is cleared, (2) a `QK_CLEAR_EEPROM` key in the keymap so the user can trigger an EEPROM reset without Bootmagic Lite, and (3) documentation of the EEPROM clear procedure for both halves independently.

All three are straightforward code and documentation tasks. The QMK APIs are well-established and verified from the vial-qmk fork source code. `eeconfig_init_user()` is a weak callback (already defined in `quantum/eeconfig.c` with a default that writes 0) that the keymap overrides. `QK_CLEAR_EEPROM` (alias `EE_CLR`, value `0x7C03`) is a built-in keycode that calls `eeconfig_disable()` followed by `soft_reset_keyboard()`, which invalidates the EEPROM magic number and triggers a soft reset. On the next boot, `quantum_init()` detects the invalid magic, calls `eeconfig_init_quantum()`, which calls `eeconfig_init_kb()`, which calls `eeconfig_init_user()` -- restoring defaults.

The key design consideration is what default value to write in `eeconfig_init_user()`. The current code packs layer_modes (bits 0-7, 2 bits per layer) and current_actuation_index (bits 8-10) into a uint32_t. The desired defaults are: all layer_modes = MODE_MOUSE (0), actuation_index = 2. This encodes to `0x00000200` (bit 9 set). Without this callback, EEPROM clear writes 0x00000000, which gives actuation_index = 0 (highest sensitivity, 352 threshold) instead of the intended middle setting (index 2, threshold 256).

**Primary recommendation:** Implement `eeconfig_init_user()` in both keymap.c files with `eeconfig_update_user(0x200)`, place `QK_CLEAR_EEPROM` on layer 1 in a non-critical position, and document the clear procedure for both halves.

## Standard Stack

This phase modifies firmware C code and produces documentation. No external libraries are involved.

### Core APIs (from vial-qmk fork source)

| API | Defined In | Purpose | Why Used |
|-----|-----------|---------|----------|
| `eeconfig_init_user(void)` | `quantum/eeconfig.c:28` | Weak callback invoked during EEPROM initialization | Override to set sane defaults for layer modes and actuation |
| `eeconfig_update_user(uint32_t)` | `quantum/eeconfig.h` | Write 4 bytes to eeconfig_user (bytes 19-22) | Called from `eeconfig_init_user()` to persist defaults |
| `QK_CLEAR_EEPROM` / `EE_CLR` | `quantum/keycodes.h:676` | Built-in keycode (0x7C03) that clears EEPROM and resets | Place in keymap for user-accessible EEPROM reset |
| `eeconfig_disable()` | `quantum/eeconfig.c:109` | Invalidates EEPROM magic number | Called by QK_CLEAR_EEPROM handler |
| `soft_reset_keyboard()` | `quantum/quantum.c:213` | MCU soft reset (no bootloader jump) | Called by QK_CLEAR_EEPROM handler after eeconfig_disable |
| `load_layer_config_from_eeprom()` | both keymap.c files | Reads eeconfig_user and applies to runtime state | Called from `keyboard_post_init_user()` on boot |

### Files Modified

| File | Change |
|------|--------|
| `keymaps/vial_left/keymap.c` | Add `eeconfig_init_user()`, add `QK_CLEAR_EEPROM` to layer 1 |
| `keymaps/vial_right/keymap.c` | Add `eeconfig_init_user()`, add `QK_CLEAR_EEPROM` to layer 1 |

### Files Created

| File | Content |
|------|---------|
| (documentation file, location TBD by planner) | EEPROM clear procedure for both halves |

## Architecture Patterns

### Pattern 1: The eeconfig_init_user Callback Chain

**What:** QMK has a layered initialization chain for EEPROM. When EEPROM is detected as invalid (magic number mismatch), `quantum_init()` calls `eeconfig_init()` -> `eeconfig_init_quantum()` -> `eeconfig_init_kb()` -> `eeconfig_init_user()`. The user callback is the last in the chain and is where keyboard-specific defaults should be set.

**Boot sequence verified from source:**
```
keyboard_init()                     // quantum/keyboard.c:420
  -> quantum_init()                 // quantum/keyboard.c:394
    -> if (!eeconfig_is_enabled())   // checks magic number
      -> eeconfig_init()            // quantum/eeconfig.c:93
        -> eeconfig_init_quantum()  // quantum/eeconfig.c:47
          -> writes QMK core defaults (magic, debug, layer, etc.)
          -> via_eeprom_set_valid(false) + eeconfig_init_via()
          -> eeconfig_init_kb()     // quantum/eeconfig.c:35
            -> eeconfig_update_kb(0)
            -> eeconfig_init_user() // quantum/eeconfig.c:28 (WEAK)
              -> default: eeconfig_update_user(0)
              -> OUR OVERRIDE: eeconfig_update_user(0x200)
  -> keyboard_post_init_kb()
    -> keyboard_post_init_user()    // loads from EEPROM into runtime state
```

**Source:** `quantum/eeconfig.c` lines 28-87, `quantum/keyboard.c` lines 394-414

**Why this matters:** The override must call `eeconfig_update_user()` with the correct default value (not just load from EEPROM). After `eeconfig_init_user()` runs, `keyboard_post_init_user()` runs later and calls `load_layer_config_from_eeprom()`, which reads the value we just wrote and applies it to runtime state.

### Pattern 2: QK_CLEAR_EEPROM Keycode Flow

**What:** When the user presses a key mapped to `QK_CLEAR_EEPROM` (0x7C03), QMK's `process_record_quantum` handles it:

```c
// Source: quantum/quantum.c:431-438
case QK_CLEAR_EEPROM:
#ifdef NO_RESET
    eeconfig_init();           // re-init in place (NO_RESET path, not used by Ambi)
#else
    eeconfig_disable();        // invalidates magic number, formats EEPROM driver
    soft_reset_keyboard();     // MCU reset (not bootloader jump)
#endif
    return false;
```

After `soft_reset_keyboard()`, the MCU restarts and runs the boot sequence again. `quantum_init()` detects the invalid magic number and calls `eeconfig_init()`, which calls our `eeconfig_init_user()` to restore defaults.

**Source:** `quantum/quantum.c` lines 431-438, `quantum/eeconfig.c` lines 109-113

**Key detail:** `NO_RESET` is not defined for the Bipedal Ambi, so the normal path (disable + reset) is used. The keyboard will briefly reboot when EE_CLR is pressed.

### Pattern 3: Bootmagic Lite Default Configuration

**What:** Bootmagic is enabled (`info.json`: `"bootmagic": true`). The default Bootmagic key is row 0, col 0. Neither `BOOTMAGIC_ROW_RIGHT`/`BOOTMAGIC_COLUMN_RIGHT` are defined.

For each half as standalone firmware:
- **Left half:** Row 0, Col 0 = KC_ESC (the Escape key, from LAYOUT_left position k00)
- **Right half:** Row 0, Col 0 = KC_BSPC (the Backspace key, from LAYOUT_right position k00)

**Bootmagic procedure:** Hold the Bootmagic key while plugging in USB. This calls `bootmagic_reset_eeprom()` -> `eeconfig_disable()`, then `bootloader_jump()`. Unlike QK_CLEAR_EEPROM, Bootmagic jumps to bootloader (not soft reset), so the user must then flash firmware or power cycle.

**Source:** `quantum/bootmagic/bootmagic.c` lines 35-74, `quantum/bootmagic/bootmagic.h` lines 33-37

### Pattern 4: Default Value Encoding

**What:** The eeconfig_user uint32_t encodes:
- Bits 0-7: layer_modes[0..3], 2 bits each (MODE_MOUSE=0, MODE_SCROLLING=1, MODE_CUSTOM_KEYS=2)
- Bits 8-10: current_actuation_index (0-4, mapping to actuation_values[] = {352, 320, 256, 128, 64})
- Bits 11-31: unused (reserved)

The desired defaults are:
- All layer_modes = MODE_MOUSE (0) -> bits 0-7 = 0x00
- actuation_index = 2 (middle sensitivity, value 256) -> bits 8-10 = 0b010 = 2

Encoded default value: `(2 << 8) = 0x00000200`

**Source:** `keymaps/vial_left/keymap.c` lines 64-90, `keymaps/vial_right/keymap.c` lines 52-78

**Verification:** When `load_layer_config_from_eeprom()` reads 0x200:
- layer_modes[0] = (0x200 >> 0) & 0x03 = 0 = MODE_MOUSE
- layer_modes[1] = (0x200 >> 2) & 0x03 = 0 = MODE_MOUSE
- layer_modes[2] = (0x200 >> 4) & 0x03 = 0 = MODE_MOUSE
- layer_modes[3] = (0x200 >> 6) & 0x03 = 0 = MODE_MOUSE
- act_idx = (0x200 >> 8) & 0x07 = 2 (valid, <= 4)
- current_actuation_index = 2, actuation = actuation_values[2] = 256

This matches the static initializers in both keymap.c files: `layer_modes[4] = {MODE_MOUSE, MODE_MOUSE, MODE_MOUSE, MODE_MOUSE}` and `current_actuation_index = 2`.

### Anti-Patterns to Avoid

- **Calling `load_layer_config_from_eeprom()` inside `eeconfig_init_user()`:** The init callback should WRITE defaults, not READ. `keyboard_post_init_user()` handles reading later in the boot sequence.
- **Using a different default encoding than what `save_layer_config_to_eeprom()` produces:** The init value must be consistent with the save function's encoding. If the encoding changes, both functions and the init value must change together.
- **Implementing `eeconfig_init_user()` in only one keymap.c:** Both halves have independent EEPROM and both need the callback. This is Pitfall 9 from the pitfalls analysis.
- **Placing QK_CLEAR_EEPROM on layer 0:** The user could accidentally trigger EEPROM clear during normal use. Place it on a higher layer behind a layer key.

## Don't Hand-Roll

| Problem | Don't Build | Use Instead | Why |
|---------|-------------|-------------|-----|
| EEPROM clear on key press | Custom EEPROM wipe function | `QK_CLEAR_EEPROM` built-in keycode | QMK handles the disable + reset cycle correctly, including driver format |
| Default value computation at runtime | Calling save functions from init | Hardcoded constant `0x200` | Init runs before runtime state is fully set up; use the known-correct constant |
| Bootmagic key configuration | Custom pre-init key scanning | QMK Bootmagic with default row 0, col 0 | Already enabled and working; just document the key |

**Key insight:** All three defensive improvements use existing QMK infrastructure. No custom EEPROM manipulation code is needed. The only new code is a 3-line `eeconfig_init_user()` override and a keycode placement in the LAYOUT macro.

## Common Pitfalls

### Pitfall 1: Wrong Default Value in eeconfig_init_user

**What goes wrong:** The developer writes `eeconfig_update_user(0)` or miscalculates the bit encoding, resulting in wrong defaults after EEPROM clear.
**Why it happens:** The default weak implementation writes 0. Copying it without calculating the correct value gives actuation_index=0 (highest sensitivity, 352 threshold) instead of the intended index=2 (middle sensitivity, 256 threshold).
**How to avoid:** Calculate the default value using the same bit-packing logic as `save_layer_config_to_eeprom()`. For defaults of MODE_MOUSE (0) for all layers and actuation_index=2: `(2 << 8) = 0x200`. Verify by running the decode logic mentally or in a test.
**Warning signs:** After EEPROM clear, the OLED shows actuation level 1 (most conservative) instead of level 3 (middle).

### Pitfall 2: Implementing eeconfig_init_user in Only One Keymap

**What goes wrong:** One half gets sane defaults after EEPROM clear; the other half gets actuation_index=0.
**Why it happens:** Separate firmware builds mean separate keymap.c files. The developer adds the callback to one and forgets the other.
**How to avoid:** Always modify both `keymaps/vial_left/keymap.c` and `keymaps/vial_right/keymap.c` simultaneously. Diff the two files after changes.
**Warning signs:** One half behaves differently from the other after EEPROM clear.

### Pitfall 3: Placing QK_CLEAR_EEPROM on Layer 0

**What goes wrong:** User accidentally hits EE_CLR during normal typing, wiping EEPROM and rebooting the keyboard.
**Why it happens:** Layer 0 is always active. Any key on layer 0 can be accidentally pressed.
**How to avoid:** Place EE_CLR on layer 1 or higher, behind a MO(1) layer hold. This requires intentional action: hold layer key + press EE_CLR key.
**Warning signs:** User reports keyboard randomly rebooting.

### Pitfall 4: Forgetting That QK_CLEAR_EEPROM Triggers a Reboot

**What goes wrong:** User presses EE_CLR and thinks the keyboard is broken because it disconnects and reconnects.
**Why it happens:** QK_CLEAR_EEPROM calls `soft_reset_keyboard()`, which performs an MCU reset. The keyboard disconnects from USB and re-enumerates.
**How to avoid:** Document this behavior explicitly. The user should expect a brief USB disconnect/reconnect after pressing EE_CLR.
**Warning signs:** User reports "keyboard stopped working" when they mean "keyboard rebooted."

### Pitfall 5: Not Also Updating Runtime State After Writing Defaults

**What goes wrong:** After `eeconfig_init_user()` writes 0x200, the runtime variables still have whatever values they had. If `keyboard_post_init_user()` does not run after init, the runtime state is stale.
**Why it happens:** Misunderstanding the boot sequence timing.
**How to avoid:** This is NOT actually a problem because the boot sequence ensures `keyboard_post_init_user()` (which calls `load_layer_config_from_eeprom()`) runs AFTER `eeconfig_init()`. The QK_CLEAR_EEPROM path also avoids this because it does a full MCU reset, so the entire boot sequence runs again.
**Warning signs:** None -- this is a theoretical concern that the boot sequence already handles correctly.

### Pitfall 6: QK_CLEAR_EEPROM Only Clears the Connected Half

**What goes wrong:** User presses EE_CLR on the left half. The left half's EEPROM is cleared and defaults restored. The right half's EEPROM is untouched and still has old data.
**Why it happens:** Each half has independent RP2040 with independent EEPROM. EEPROM operations only affect the local MCU's flash storage.
**How to avoid:** Document that EE_CLR (or Bootmagic) must be performed on EACH half separately. The clear procedure must specify: "Repeat on the other half."
**Warning signs:** One half has correct defaults, the other has stale/wrong settings.

## Code Examples

Verified patterns from the vial-qmk fork source code:

### eeconfig_init_user Override (Both Keymap Files)

```c
// Source: Derived from quantum/eeconfig.c:28-33 (default implementation)
// Place in both keymaps/vial_left/keymap.c and keymaps/vial_right/keymap.c
//
// Called when EEPROM is cleared/initialized. Sets sane defaults so
// the keyboard boots with middle actuation sensitivity and mouse mode.
void eeconfig_init_user(void) {
    // Default: all layers MODE_MOUSE (0), actuation_index = 2 (middle)
    // Encoding: bits 0-7 = layer modes, bits 8-10 = actuation index
    // (0 << 0) | (0 << 2) | (0 << 4) | (0 << 6) | (2 << 8) = 0x200
    eeconfig_update_user(0x200);
}
```

### QK_CLEAR_EEPROM Key in Layer 1 (Left Half)

```c
// Source: quantum/keycodes.h:676 (QK_CLEAR_EEPROM = 0x7C03, alias EE_CLR)
// Place EE_CLR on layer 1 in a position that is unlikely to be pressed accidentally.
// Layer 1 already requires holding MO(1) to activate.
//
// Example: Replace one KC_TRNS on layer 1 with EE_CLR
[1] = LAYOUT_left(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, EE_CLR  // <-- position k17
),
```

### QK_CLEAR_EEPROM Keycode Handler (Already in QMK -- no code needed)

```c
// Source: quantum/quantum.c:431-438
// This is already handled by QMK. No custom process_record_user case needed.
// Placing EE_CLR in the keymap is sufficient.
case QK_CLEAR_EEPROM:
    eeconfig_disable();        // writes invalid magic, formats driver
    soft_reset_keyboard();     // MCU reset -> re-runs boot sequence
    return false;              // -> quantum_init -> eeconfig_init -> eeconfig_init_user
```

### Bootmagic Lite Key Identification

```c
// Source: quantum/bootmagic/bootmagic.h:33-37 (default values)
// Neither BOOTMAGIC_ROW nor BOOTMAGIC_COLUMN is overridden by the Ambi.
// Defaults: BOOTMAGIC_ROW = 0, BOOTMAGIC_COLUMN = 0
//
// Left half:  row 0, col 0 = k00 in LAYOUT_left = KC_ESC
// Right half: row 0, col 0 = k00 in LAYOUT_right = KC_BSPC
//
// Procedure: Hold the Bootmagic key while plugging in USB cable.
// This clears EEPROM and jumps to bootloader (DFU mode).
```

## Detailed Findings

### Finding 1: eeconfig_init_user Default Writes All Zeros

The weak default implementation in `quantum/eeconfig.c:28-33` writes `eeconfig_update_user(0)` when `EECONFIG_USER_DATA_SIZE == 0` (which is the case for the Ambi). This means after any EEPROM clear, the actuation_index is set to 0 (highest sensitivity, threshold 352) rather than the intended default of 2 (middle sensitivity, threshold 256).

The `load_layer_config_from_eeprom()` function does have validation (`act_idx <= 4` check) but index 0 IS a valid value, so the validation passes. The only way to get the correct default is to override `eeconfig_init_user()`.

**Confidence:** HIGH -- verified by reading `quantum/eeconfig.c:28-33` and both keymap.c load functions

### Finding 2: QK_CLEAR_EEPROM Is a Standard Built-in Keycode

`QK_CLEAR_EEPROM` (alias `EE_CLR`, value `0x7C03`) is processed by `process_record_quantum()` in `quantum/quantum.c:431`. It requires no custom handling in `process_record_user()`. The keycode just needs to be placed in the keymap.

The handler calls `eeconfig_disable()` (which formats the EEPROM driver and writes an invalid magic number) and then `soft_reset_keyboard()` (MCU reset, not bootloader jump). After reset, the keyboard re-initializes and calls `eeconfig_init_user()` because the magic number is invalid.

**Confidence:** HIGH -- verified from `quantum/quantum.c:431-438` and `quantum/keycodes.h:676`

### Finding 3: Bootmagic Lite Is Already Enabled

Bootmagic is enabled via `info.json` (`"bootmagic": true`). The Bootmagic key defaults to row 0, col 0. For the left half this is KC_ESC; for the right half this is KC_BSPC. Bootmagic clears EEPROM AND jumps to bootloader, unlike QK_CLEAR_EEPROM which does a soft reset only.

`BOOTMAGIC_ROW_RIGHT` and `BOOTMAGIC_COLUMN_RIGHT` are not defined. Since each half builds as standalone firmware with `SPLIT_USB_DETECT`, the Bootmagic key for each half is always its own row 0, col 0. The `is_keyboard_left()` check in the Bootmagic code would select the right-side key if defined, but since neither is defined, it always uses row 0, col 0.

**Confidence:** HIGH -- verified from `info.json:39`, `quantum/bootmagic/bootmagic.c:46-54`, `quantum/bootmagic/bootmagic.h:33-37`

### Finding 4: Each Half Has Independent EEPROM

The Bipedal Ambi uses separate firmware per half. Each RP2040 has its own 4096-byte wear-leveling EEPROM emulation in flash. EEPROM operations (read, write, clear) affect only the local MCU. Clearing the left half's EEPROM does not clear the right half's.

This means the EEPROM clear procedure must be performed independently on each half. The documentation must make this explicit.

**Confidence:** HIGH -- fundamental property of the split architecture with independent MCUs

### Finding 5: QK_CLEAR_EEPROM Placement Constraints

The keycode must be placed in the `keymaps[][]` PROGMEM array, NOT in the dynamic keymap (EEPROM). PROGMEM keymaps are always available regardless of EEPROM state. This is important because:

1. If EE_CLR were only in the dynamic keymap (set via Vial), clearing EEPROM would also clear the EE_CLR key assignment, making it a one-time-use key.
2. Placing it in the PROGMEM layer 1 means it survives EEPROM clears and is always accessible.

However, there is a subtlety: Vial stores the dynamic keymap in EEPROM. When a user modifies keys in Vial, those changes are written to EEPROM and override the PROGMEM defaults. If a user overwrites the EE_CLR position in Vial with a different key, EE_CLR is lost until the next EEPROM clear.

This is acceptable because:
- EE_CLR is a safety net, not a frequently used feature
- Bootmagic Lite is always available as a fallback (row 0, col 0 on plug-in)
- After EEPROM clear, the PROGMEM default (including EE_CLR) is restored

**Confidence:** HIGH -- verified from QMK dynamic keymap behavior

### Finding 6: Layer 1 Is Currently All KC_TRNS

Both keymap.c files define layers 1-3 as entirely `KC_TRNS`. This means any position on layer 1 can be used for EE_CLR without displacing a meaningful key. The position should be:
- On layer 1 (requires MO(1) to access -- intentional action)
- Not a commonly remapped position (to reduce risk of being overwritten in Vial)
- Accessible on both halves (or documented as "left-side only" / "right-side only")

**Candidate positions for left half:** The last key in the LAYOUT_left macro is position `k17` (row 1, col 7 -- the bottom-right joystick area). It is currently a dedicated joystick key position on layer 0, and KC_TRNS on layer 1.

**Candidate positions for right half:** Position `k31` (row 3, col 1 -- the bottom-most key in the right layout) is currently MO(1) on layer 0 and KC_TRNS on layer 1. However, since MO(1) is what activates layer 1, putting EE_CLR at this position on layer 1 would mean the user holds MO(1) and the same key... which is actually MO(1) itself. This won't work. A different position should be chosen.

**Confidence:** HIGH -- verified from both keymap.c layer definitions

### Finding 7: scroll_inverted Is Not Persisted in EEPROM

The `scroll_inverted` variable (left half only) is a runtime-only `bool` that defaults to `false` and toggles with `SCROLL_DIR`. It is NOT saved to EEPROM and resets to `false` on every power cycle. The success criteria mention "scroll direction defaults" but the current firmware does not persist this setting.

This means `eeconfig_init_user()` does NOT need to handle scroll_inverted -- it already resets to its default (`false`) on every boot.

**Confidence:** HIGH -- verified from `keymaps/vial_left/keymap.c:54` (`bool scroll_inverted = false`) and the `SCROLL_DIR` handler (line 151-155) which does NOT call `save_layer_config_to_eeprom()`

## State of the Art

| Old Approach | Current Approach | When Changed | Impact |
|--------------|------------------|--------------|--------|
| No `eeconfig_init_user` override | Override with sane defaults | This phase | After EEPROM clear, keyboard boots with correct middle actuation sensitivity |
| No EE_CLR keycode in keymap | EE_CLR on layer 1 | This phase | User can clear EEPROM without Bootmagic (hold key on plug-in) |
| EEPROM clear procedure undocumented | Documented per-half procedure | This phase | User knows how to reset each half independently |
| `BOOTMAGIC_LITE_ROW/COLUMN` | `BOOTMAGIC_ROW/COLUMN` | QMK rename | The `LITE` prefix is deprecated; current QMK uses `BOOTMAGIC_ROW/COLUMN` |

**Deprecated/outdated:**
- `BOOTMAGIC_LITE_ROW` / `BOOTMAGIC_LITE_COLUMN` are deprecated in favor of `BOOTMAGIC_ROW` / `BOOTMAGIC_COLUMN`. The Ambi does not define either, so defaults apply. The documentation should use the current names.

## Open Questions

1. **Which exact matrix position should QK_CLEAR_EEPROM occupy on each half?**
   - What we know: Layer 1 is entirely KC_TRNS on both halves, so any position is available. The position should be intentional (not easily hit) and preferably the same logical position on both halves.
   - What's unclear: The user may have a preference for which key position to use.
   - Recommendation: Use a corner or edge position on layer 1. Planner should pick a specific position and document it. The position should be visually identifiable (e.g., the bottom-right key on each half). The planner can make this decision without user input -- it's in Claude's discretion since CONTEXT.md doesn't exist.

2. **Whether EE_CLR should be on both halves or just one**
   - What we know: Each half's EEPROM is independent, so clearing requires pressing EE_CLR on each half separately (or using Bootmagic). Having EE_CLR on both halves makes the procedure symmetric.
   - What's unclear: Whether the user always connects both halves via USB independently, or if one half is always the primary USB connection.
   - Recommendation: Place EE_CLR on layer 1 of BOTH halves. This satisfies success criterion 2 ("at least one layer includes QK_CLEAR_EEPROM") and makes the clear procedure identical for both halves.

3. **Documentation format and location**
   - What we know: EEPR-01 requires "EEPROM clear procedure documented for both halves independently." The roadmap suggests this goes into a documentation deliverable.
   - What's unclear: Whether this should be a .planning artifact or a project-level doc.
   - Recommendation: Create it as a planning phase deliverable (e.g., `EEPROM-CLEAR-PROCEDURE.md`). It is documentation about firmware behavior, not code.

## Sources

### Primary (HIGH confidence)
- `quantum/eeconfig.c` lines 28-33 -- default `eeconfig_init_user()` implementation (writes 0)
- `quantum/eeconfig.c` lines 35-42 -- `eeconfig_init_kb()` -> `eeconfig_init_user()` call chain
- `quantum/eeconfig.c` lines 47-87 -- `eeconfig_init_quantum()` full initialization sequence
- `quantum/eeconfig.c` lines 109-113 -- `eeconfig_disable()` implementation (format + invalid magic)
- `quantum/eeconfig.h` line 116 -- `eeconfig_init_user()` declaration
- `quantum/quantum.c` lines 431-438 -- `QK_CLEAR_EEPROM` handler (disable + soft reset)
- `quantum/quantum.c` lines 213-216 -- `soft_reset_keyboard()` (MCU reset)
- `quantum/keycodes.h` line 676 -- `QK_CLEAR_EEPROM = 0x7C03`
- `quantum/keycodes.h` line 1352 -- `EE_CLR = QK_CLEAR_EEPROM` alias
- `quantum/keyboard.c` lines 394-414 -- `quantum_init()` boot sequence (eeconfig check + init)
- `quantum/keyboard.c` lines 420-460+ -- `keyboard_init()` full init sequence
- `quantum/bootmagic/bootmagic.c` lines 35-74 -- Bootmagic implementation
- `quantum/bootmagic/bootmagic.h` lines 33-37 -- Default BOOTMAGIC_ROW=0, BOOTMAGIC_COLUMN=0
- `keyboards/hidpress/bipedalambi/keymaps/vial_left/keymap.c` lines 64-94 -- EEPROM save/load functions
- `keyboards/hidpress/bipedalambi/keymaps/vial_right/keymap.c` lines 52-82 -- EEPROM save/load functions (identical)
- `keyboards/hidpress/bipedalambi/info.json` line 39 -- `"bootmagic": true`
- Phase 5 research (`05-RESEARCH.md`) -- eeconfig_user at bytes 19-22, no collision with VIA

### Secondary (MEDIUM confidence)
- `.planning/research/PITFALLS.md` Pitfall 10 -- eeconfig_init_user not implemented, actuation_index defaults to 0
- `.planning/research/PITFALLS.md` Pitfall 9 -- duplicated EEPROM logic between left and right keymaps

### Tertiary (LOW confidence)
- None -- all findings verified from source code

## Metadata

**Confidence breakdown:**
- eeconfig_init_user API and behavior: HIGH -- read directly from quantum/eeconfig.c, verified call chain
- QK_CLEAR_EEPROM behavior: HIGH -- read from quantum/quantum.c and quantum/keycodes.h
- Default value encoding (0x200): HIGH -- calculated from save/load functions in both keymap.c files
- Bootmagic key identification: HIGH -- defaults verified in bootmagic.h, matrix positions verified in keymap.c LAYOUT macros
- Boot sequence ordering: HIGH -- traced through keyboard.c -> quantum_init -> eeconfig_init -> eeconfig_init_kb -> eeconfig_init_user
- Per-half EEPROM independence: HIGH -- fundamental property of split architecture with separate MCUs

**Research date:** 2026-02-14
**Valid until:** Indefinite (all values from static QMK APIs in vial-qmk fork)
