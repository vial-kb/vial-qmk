# EEPROM Clear Procedure

## Overview

The Bipedal Ambi is a split keyboard with two independent RP2040 microcontrollers. Each half has its own EEPROM (4096 bytes of wear-leveled flash storage). **Clearing EEPROM on one half does NOT affect the other half.** Both halves must be cleared separately if a full reset is needed.

EEPROM stores:
- **Vial dynamic keymap** (layer keycodes customized in Vial)
- **User configuration** (layer modes and actuation sensitivity)

After clearing, both are reset to firmware defaults (PROGMEM keymap and `eeconfig_init_user()` values).

## Method 1: QK_CLEAR_EEPROM (EE_CLR) Key

Available on PROGMEM layer 1 of both halves. Since this key is in PROGMEM (not the dynamic keymap), it survives EEPROM clears and is always accessible.

### Left Half

1. Hold **MO(1)** (the key at the KC_MINS position in the bottom thumb row, matrix position k31) to activate layer 1
2. While holding MO(1), press the key at the **KC_DOWN position** (bottom-right key, matrix position k17)
3. The keyboard will reboot (brief USB disconnect/reconnect)
4. After reboot, the left half has factory defaults

### Right Half

1. Hold **MO(1)** (the bottom key, matrix position k31) to activate layer 1
2. While holding MO(1), press the key at the **KC_EQL position** (adjacent to MO(1), matrix position k35)
3. The keyboard will reboot (brief USB disconnect/reconnect)
4. After reboot, the right half has factory defaults

### Behavior

- `QK_CLEAR_EEPROM` calls `eeconfig_disable()` (invalidates the EEPROM magic number) followed by `soft_reset_keyboard()` (MCU soft reset)
- On the next boot, QMK detects the invalid magic number and calls the full EEPROM initialization chain, including `eeconfig_init_user()` which sets sane defaults
- The keyboard reconnects over USB automatically -- no need to unplug
- **This only clears the half that is currently connected via USB**

### Note on Vial Overrides

If a user remaps the EE_CLR key position in Vial (replacing it with a different keycode), the EE_CLR function is lost until the next EEPROM clear. Bootmagic (Method 2) is always available as a fallback.

## Method 2: Bootmagic (Hold Key While Plugging In)

Bootmagic is always available regardless of EEPROM state or dynamic keymap changes. It uses the physical key at matrix row 0, column 0.

### Left Half

1. **Unplug** the left half from USB
2. **Hold KC_ESC** (the Escape key, matrix position k00) on the left half
3. While holding KC_ESC, **plug in the USB cable**
4. EEPROM is cleared and the keyboard enters **bootloader mode** (DFU)
5. Either flash new firmware or **unplug and replug** to boot normally with defaults

### Right Half

1. **Unplug** the right half from USB
2. **Hold KC_BSPC** (the Backspace key, matrix position k00) on the right half
3. While holding KC_BSPC, **plug in the USB cable**
4. EEPROM is cleared and the keyboard enters **bootloader mode** (DFU)
5. Either flash new firmware or **unplug and replug** to boot normally with defaults

### Behavior

- Bootmagic calls `eeconfig_disable()` then `bootloader_jump()` (enters DFU mode)
- Unlike Method 1, Bootmagic enters the bootloader instead of doing a soft reset
- The user must flash firmware or power cycle (unplug/replug) to boot normally
- On the next normal boot, QMK detects invalid EEPROM and runs `eeconfig_init_user()` to restore defaults

## After Clearing

Both methods result in the same outcome on next boot:

1. `eeconfig_init_user()` runs, writing `0x200` to eeconfig_user
2. `keyboard_post_init_user()` runs, calling `load_layer_config_from_eeprom()` which reads the value back
3. Runtime state is set to:
   - **actuation_index = 2** (middle sensitivity, threshold 256)
   - **All layers = MODE_MOUSE** (trackball acts as mouse pointer)
4. The Vial dynamic keymap is reset to PROGMEM defaults
5. Any keys customized in Vial will need to be reconfigured

## When to Clear EEPROM

- **After flashing firmware with changed EEPROM layout** (matrix dimension changes, new layers, modified encoding)
- **If the keyboard behaves unexpectedly** (wrong actuation sensitivity, wrong layer modes, keys not matching expectations)
- **If Vial shows incorrect layer content** (stale dynamic keymap from previous firmware version)
- **After changing MATRIX_ROWS, MATRIX_COLS, or DYNAMIC_KEYMAP_LAYER_COUNT** in config.h

## Full Reset Procedure (Both Halves)

To fully reset both halves to factory defaults:

1. **Connect the left half** via USB
2. **Clear EEPROM on the left half** using Method 1 (EE_CLR key) or Method 2 (Bootmagic)
3. If using Bootmagic, unplug and replug the left half to boot normally
4. **Verify** the left half boots with correct defaults (middle actuation, mouse mode)
5. **Disconnect the left half**
6. **Connect the right half** via USB
7. **Clear EEPROM on the right half** using Method 1 (EE_CLR key) or Method 2 (Bootmagic)
8. If using Bootmagic, unplug and replug the right half to boot normally
9. **Verify** the right half boots with correct defaults
10. **Reconnect normally** and reconfigure in Vial if needed
